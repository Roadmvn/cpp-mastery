# Chapitre 04 - Injection de Bibliotheques Dynamiques (dlopen/dlsym) 📚

> **DISCLAIMER EDUCATIF** 
> Ce chapitre est **strictement educatif**. Le chargement dynamique de bibliotheques
> est une technique de developpement standard, aussi utilisee en securite pour comprendre
> comment du code peut etre charge dans un processus a la volee.
> **Toute utilisation malveillante est illegale et contraire a l'ethique.**

---

## Concept 

Les bibliotheques dynamiques (.so sur Linux, .dylib sur macOS, .dll sur Windows) sont
des fichiers contenant du code executable **charge au runtime** plutot qu'a la compilation.

- **Liaison statique** : le code de la lib est copie dans l'executable
- **Liaison dynamique** : le code est charge en memoire a l'execution
- **Chargement explicite** : le programme decide LUI-MEME quand charger une lib (dlopen)

### Pourquoi c'est important en Red Team ? 

L'injection de DLL/shared library permet de :
- **Charger du code** dans un processus en cours d'execution
- **Etendre les fonctionnalites** d'un programme sans le recompiler
- Comprendre comment les **plugins** et **extensions** fonctionnent
- Analyser comment les **malwares utilisent le chargement dynamique**

---

## Schema ASCII - Chargement Dynamique 

### Liaison Statique vs Dynamique

```
LIAISON STATIQUE                     LIAISON DYNAMIQUE
┌──────────────┐                    ┌──────────────┐
│  mon_prog.cpp │                    │  mon_prog.cpp │
└──────┬───────┘                    └──────┬───────┘
       │ compile                           │ compile
       ▼                                   ▼
┌──────────────┐                    ┌──────────────┐
│  mon_prog.o   │                    │  mon_prog.o   │
└──────┬───────┘                    └──────┬───────┘
       │ + libmath.a (copie)               │ + libmath.so (reference)
       ▼                                   ▼
┌──────────────┐                    ┌──────────────┐  ┌──────────────┐
│  mon_prog     │                    │  mon_prog     │  │  libmath.so   │
│  (gros, 5MB)  │                    │  (petit, 50K) │  │  (charge au   │
│  [code lib    │                    │  [reference    │  │   runtime)    │
│   inclus]     │                    │   vers lib]    │  │              │
└──────────────┘                    └──────────────┘  └──────────────┘
```

### Chargement Explicite (dlopen)

```
┌──────────────────────────────────────────────────┐
│  PROCESSUS MON_PROG                               │
│                                                    │
│  1. dlopen("plugin.so", RTLD_NOW)                 │
│     ┌────────────────────────────┐                │
│     │  Charge plugin.so en       │                │
│     │  memoire dans le processus │                │
│     └────────────┬───────────────┘                │
│                  │                                 │
│  2. dlsym(handle, "execute")                      │
│     ┌────────────────────────────┐                │
│     │  Trouve l'adresse de la    │                │
│     │  fonction "execute" dans   │                │
│     │  plugin.so                 │                │
│     └────────────┬───────────────┘                │
│                  │                                 │
│  3. func_ptr = (execute_t)symbol;                 │
│     func_ptr("argument");                         │
│     ┌────────────────────────────┐                │
│     │  Appelle la fonction       │                │
│     │  comme si elle faisait     │                │
│     │  partie du programme       │                │
│     └────────────┬───────────────┘                │
│                  │                                 │
│  4. dlclose(handle)                               │
│     ┌────────────────────────────┐                │
│     │  Decharge la lib de la     │                │
│     │  memoire du processus      │                │
│     └────────────────────────────┘                │
└──────────────────────────────────────────────────┘
```

### Comparaison Windows vs Unix

```
┌─────────────────────┬──────────────────────┐
│     WINDOWS          │      UNIX             │
├─────────────────────┼──────────────────────┤
│ LoadLibrary("x.dll") │ dlopen("x.so", flags) │
│ GetProcAddress(h,"f") │ dlsym(handle, "f")    │
│ FreeLibrary(handle)  │ dlclose(handle)        │
│ Extension: .dll      │ Linux: .so macOS: .dylib│
└─────────────────────┴──────────────────────┘
```

---

## Exemple - Plugin System avec dlopen 

### Etape 1 : La shared library (plugin)

```cpp
// plugin.cpp - Compile en shared library
// g++ -std=c++17 -shared -fPIC -o plugin.so plugin.cpp (Linux)
// g++ -std=c++17 -shared -fPIC -o plugin.dylib plugin.cpp (macOS)

#include <iostream>
#include <string>
#include <cstring>

// Les fonctions exportees doivent avoir un linkage C
extern "C" {

    const char* plugin_name() {
        return "ReconPlugin v1.0";
    }

    const char* plugin_description() {
        return "Plugin de demonstration - collecte d'infos basiques";
    }

    // Fonction principale du plugin
    int execute(const char* arg) {
        std::cout << "[PLUGIN] Execute avec argument : " << arg << std::endl;
        std::cout << "[PLUGIN] Hello depuis la shared library !" << std::endl;
        return 0;
    }

    // Fonction de nettoyage
    void cleanup() {
        std::cout << "[PLUGIN] Nettoyage..." << std::endl;
    }
}
```

### Etape 2 : Le chargeur (loader)

```cpp
// loader.cpp - Charge dynamiquement le plugin
// g++ -std=c++17 -o loader loader.cpp -ldl

#include <iostream>
#include <dlfcn.h>

// Types des fonctions du plugin
using NameFunc = const char* (*)();
using ExecFunc = int (*)(const char*);
using CleanFunc = void (*)();

int main() {
    std::cout << "=== Chargeur de Plugin Dynamique ===" << std::endl;

    // Determine l'extension selon l'OS
#ifdef __APPLE__
    const char* pluginPath = "./plugin.dylib";
#else
    const char* pluginPath = "./plugin.so";
#endif

    // 1. Charger la lib
    void* handle = dlopen(pluginPath, RTLD_NOW);
    if (!handle) {
        std::cerr << "[!] Erreur dlopen : " << dlerror() << std::endl;
        return 1;
    }
    std::cout << "[*] Plugin charge : " << pluginPath << std::endl;

    // 2. Resoudre les symboles
    auto getName = reinterpret_cast<NameFunc>(dlsym(handle, "plugin_name"));
    auto getDesc = reinterpret_cast<NameFunc>(dlsym(handle, "plugin_description"));
    auto execute = reinterpret_cast<ExecFunc>(dlsym(handle, "execute"));
    auto cleanup = reinterpret_cast<CleanFunc>(dlsym(handle, "cleanup"));

    if (!getName || !execute) {
        std::cerr << "[!] Symboles manquants : " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    // 3. Utiliser les fonctions
    std::cout << "[*] Nom : " << getName() << std::endl;
    if (getDesc) std::cout << "[*] Desc : " << getDesc() << std::endl;

    execute("test_argument");

    // 4. Nettoyer et decharger
    if (cleanup) cleanup();
    dlclose(handle);
    std::cout << "[*] Plugin decharge." << std::endl;

    return 0;
}
```

---

## Checkpoint 

Apres ce chapitre, tu dois savoir :
- [ ] La difference entre liaison statique et dynamique
- [ ] Comment utiliser dlopen/dlsym/dlclose pour charger du code au runtime
- [ ] Pourquoi extern "C" est necessaire pour les fonctions exportees
- [ ] Comment compiler une shared library (.so / .dylib)
- [ ] L'analogie avec LoadLibrary/GetProcAddress sur Windows
- [ ] Comment un systeme de plugins fonctionne
