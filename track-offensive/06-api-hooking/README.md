# Chapitre 06 - API Hooking (Interception de Fonctions) 🎣

> **DISCLAIMER EDUCATIF** ⚠️
> Ce chapitre est **strictement educatif**. Le hooking de fonctions est une technique
> utilisee legitimement par les debuggers, les outils de monitoring, et les sandboxes.
> Les EDR l'utilisent pour surveiller les appels systeme.
> **Toute utilisation malveillante est illegale et contraire a l'ethique.**

---

## Concept 📖

Le **hooking** consiste a **intercepter un appel de fonction** pour :
- **Logger** l'appel (quels arguments, quand, combien de fois)
- **Modifier** les arguments ou le retour
- **Rediriger** vers une autre fonction
- **Bloquer** l'appel completement

Sur Unix, la technique principale est **LD_PRELOAD** (Linux) / **DYLD_INSERT_LIBRARIES** (macOS) :
le systeme charge NOTRE lib avant les autres, nos fonctions remplacent celles de la libc.

### Pourquoi c'est important en Red Team ? 🎯

Le hooking permet de :
- **Monitorer les appels** d'un programme (ce qu'il lit, ecrit, envoie)
- **Modifier le comportement** sans recompiler (sandbox)
- Comprendre comment les **EDR interceptent** les APIs malveillantes
- **Analyser des malwares** en loggant leurs actions

---

## Schema ASCII - Hooking de Fonctions 🏗️

### Appel Normal vs Appel Hooke

```
APPEL NORMAL                          APPEL HOOKE (LD_PRELOAD)
┌──────────┐                         ┌──────────┐
│ Programme │                         │ Programme │
│           │                         │           │
│ malloc(n) │                         │ malloc(n) │
└─────┬─────┘                         └─────┬─────┘
      │                                     │
      │ appel direct                        │ appel intercepte
      │                                     ▼
      │                              ┌─────────────────┐
      │                              │ NOTRE malloc()   │
      │                              │ (dans hook.so)   │
      │                              │                  │
      │                              │ 1. Log l'appel   │
      │                              │ 2. Appel le vrai │
      │                              │    malloc (dlsym)│
      │                              │ 3. Log le retour │
      │                              └────────┬────────┘
      │                                       │
      ▼                                       ▼
┌─────────────────┐                  ┌─────────────────┐
│ libc malloc()   │                  │ libc malloc()   │
│ (allocation     │                  │ (allocation     │
│  reelle)        │                  │  reelle)        │
└─────────────────┘                  └─────────────────┘
```

### Chaine de Resolution des Symboles

```
SANS LD_PRELOAD :
Programme → libc.so → fonction originale

AVEC LD_PRELOAD :
Programme → hook.so (NOTRE lib) → libc.so → fonction originale
              │
              ├─ Log l'appel
              ├─ Peut modifier les args
              ├─ Appelle la vraie fonction via dlsym(RTLD_NEXT, "func")
              └─ Peut modifier le retour
```

### LD_PRELOAD vs DYLD_INSERT_LIBRARIES

```
┌───────────────────────┬────────────────────────────┐
│       LINUX            │        macOS                │
├───────────────────────┼────────────────────────────┤
│ LD_PRELOAD=./hook.so   │ DYLD_INSERT_LIBRARIES=     │
│ ./programme             │   ./hook.dylib             │
│                        │ DYLD_FORCE_FLAT_NAMESPACE=1│
│                        │ ./programme                 │
├───────────────────────┼────────────────────────────┤
│ dlsym(RTLD_NEXT,"f")  │ dlsym(RTLD_NEXT,"f")       │
│ Extension: .so         │ Extension: .dylib           │
└───────────────────────┴────────────────────────────┘
```

---

## Exemple - Hook de malloc avec LD_PRELOAD 💻

### La lib de hooking

```cpp
// hook_malloc.cpp
// Linux : g++ -std=c++17 -shared -fPIC -o hook_malloc.so hook_malloc.cpp -ldl
// macOS : g++ -std=c++17 -shared -fPIC -o hook_malloc.dylib hook_malloc.cpp -ldl

#define _GNU_SOURCE
#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>

// Compteurs
static int malloc_count = 0;
static size_t total_allocated = 0;

// Hook de malloc - intercepte toutes les allocations
extern "C" void* malloc(size_t size) {
    // Recupere le VRAI malloc
    static auto real_malloc = reinterpret_cast<void*(*)(size_t)>(
        dlsym(RTLD_NEXT, "malloc")
    );

    malloc_count++;
    total_allocated += size;

    void* ptr = real_malloc(size);

    // Log (utilise fprintf car cout utilise malloc → recursion infinie)
    fprintf(stderr, "[HOOK] malloc(%zu) = %p [total: %d appels, %zu bytes]\n",
            size, ptr, malloc_count, total_allocated);

    return ptr;
}

// Hook de free
extern "C" void free(void* ptr) {
    static auto real_free = reinterpret_cast<void(*)(void*)>(
        dlsym(RTLD_NEXT, "free")
    );

    if (ptr) {
        fprintf(stderr, "[HOOK] free(%p)\n", ptr);
    }
    real_free(ptr);
}
```

### Programme de test

```cpp
// test_program.cpp
// g++ -std=c++17 -o test_program test_program.cpp

#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cout << "=== Programme de Test ===" << std::endl;

    // Ces allocations seront interceptees par le hook
    auto* ptr1 = new int(42);
    auto* ptr2 = new char[100];

    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::string str = "Hello World - cette string alloue de la memoire";

    delete ptr1;
    delete[] ptr2;

    std::cout << "Programme termine." << std::endl;
    return 0;
}
```

**Utilisation :**
```bash
# Linux
LD_PRELOAD=./hook_malloc.so ./test_program

# macOS (peut ne pas marcher sur les dernieres versions a cause de SIP)
DYLD_INSERT_LIBRARIES=./hook_malloc.dylib DYLD_FORCE_FLAT_NAMESPACE=1 ./test_program
```

---

## Checkpoint ✅

Apres ce chapitre, tu dois savoir :
- [ ] Ce qu'est le hooking et pourquoi c'est utilise (defensif ET offensif)
- [ ] Comment LD_PRELOAD permet d'intercepter des fonctions
- [ ] Comment utiliser dlsym(RTLD_NEXT, ...) pour appeler la vraie fonction
- [ ] Pourquoi il faut utiliser fprintf au lieu de cout dans un hook malloc
- [ ] L'equivalent macOS : DYLD_INSERT_LIBRARIES
- [ ] Comment les EDR utilisent le hooking pour surveiller les programmes
