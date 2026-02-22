# Chapitre 05 - Execution de Shellcode (Concept Educatif) 🧬

> **DISCLAIMER EDUCATIF** ⚠️
> Ce chapitre est **strictement educatif**. Le shellcode presente ici fait **uniquement**
> un appel systeme `exit(0)` - il ne fait RIEN de malveillant. L'objectif est de comprendre
> comment du code machine brut peut etre execute en memoire, car c'est fondamental pour
> comprendre les exploits et comment s'en defendre.
> **Toute utilisation malveillante est illegale et contraire a l'ethique.**

---

## Concept 📖

Le **shellcode** est du code machine brut (des octets) qui peut etre execute directement
par le processeur. Contrairement a un programme compile, le shellcode :
- N'a **pas de format executable** (pas de headers ELF/PE)
- Est **position-independent** (fonctionne a n'importe quelle adresse)
- Est souvent **tres compact** (quelques dizaines d'octets)

### Pourquoi c'est important en Red Team ? 🎯

Comprendre le shellcode permet de :
- Analyser les **payloads** utilises dans les exploits
- Comprendre comment les **protections memoire** (DEP/NX) fonctionnent
- Savoir comment les **antivirus detectent** le shellcode
- Ecrire de meilleurs **outils defensifs** et regles de detection

---

## Schema ASCII - Shellcode en Memoire 🏗️

### Du Code Source au Code Machine

```
CODE C                     ASSEMBLEUR                  SHELLCODE (octets)
┌──────────────┐          ┌──────────────┐            ┌──────────────────┐
│ #include...  │          │ mov rdi, 0   │            │ 48 31 FF         │
│              │  compile │ mov rax, 60  │  assemble  │ 48 C7 C0 3C 00  │
│ exit(0);     │ ───────> │ syscall      │ ─────────> │ 00 00            │
│              │          │              │            │ 0F 05            │
└──────────────┘          └──────────────┘            └──────────────────┘
                                                       ↑
                                                       Ce sont juste des
                                                       octets en memoire !
```

### Protections Memoire

```
MEMOIRE DU PROCESSUS
┌────────────────────────────────────────────────┐
│  Page 1 : CODE (.text)                          │
│  Permissions : R-X (Read + Execute, no Write)   │
│  → Le programme peut lire et executer           │
│  → Mais PAS ecrire (protection W^X)             │
├────────────────────────────────────────────────┤
│  Page 2 : DONNEES (.data)                       │
│  Permissions : RW- (Read + Write, no Execute)   │
│  → Le programme peut lire et ecrire             │
│  → Mais PAS executer (DEP/NX bit)               │
├────────────────────────────────────────────────┤
│  Page 3 : HEAP                                  │
│  Permissions : RW- (Read + Write, no Execute)   │
│  → Meme protection que les donnees              │
├────────────────────────────────────────────────┤
│  Page 4 : STACK                                 │
│  Permissions : RW- (Read + Write, no Execute)   │
│  → La stack n'est pas executable non plus        │
└────────────────────────────────────────────────┘

PROBLEME : Le shellcode est dans une zone RW- (pas executable)
SOLUTION EDUCATIVE : mprotect() pour ajouter le flag X
```

### Etapes d'Execution du Shellcode

```
1. ALLOCATION        2. COPIE            3. PROTECTION       4. EXECUTION
┌──────────┐        ┌──────────┐        ┌──────────┐       ┌──────────┐
│  mmap()  │        │ memcpy() │        │ mprotect │       │ cast en  │
│  alloue  │ ──────>│ copie le │ ──────>│ RW- → R-X│ ────> │ pointeur │
│  memoire │        │ shellcode│        │ rend     │       │ fonction │
│  RW-     │        │ dans buf │        │ executable│       │ et appel │
└──────────┘        └──────────┘        └──────────┘       └──────────┘
```

---

## Shellcode Educatif : exit(0) Uniquement 🔬

Le shellcode ci-dessous fait **uniquement** un appel systeme `exit(0)`.
C'est l'equivalent de `_exit(0)` en C.

### Assembleur x86_64 (Linux)

```asm
; exit(0) sur Linux x86_64
; Syscall number 60 = exit
mov rdi, 0      ; argument: code de retour 0
mov rax, 60     ; syscall number: exit
syscall         ; appel au noyau
```

### Assembleur x86_64 (macOS)

```asm
; exit(0) sur macOS x86_64
; macOS syscalls = 0x2000000 + numero
mov rdi, 0          ; argument: code de retour 0
mov rax, 0x2000001  ; syscall number: exit (macOS)
syscall             ; appel au noyau
```

---

## Exemple - Execution de Shellcode exit(0) 💻

```cpp
#include <iostream>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>
#include <cstdint>

int main() {
    std::cout << "=== Execution de Shellcode Educatif ===" << std::endl;
    std::cout << "[!] Le shellcode fait UNIQUEMENT exit(0)" << std::endl;
    std::cout << std::endl;

    // Shellcode exit(0) - x86_64
#ifdef __APPLE__
    // macOS : syscall exit = 0x2000001
    unsigned char shellcode[] = {
        0x48, 0x31, 0xff,                   // xor rdi, rdi      (rdi = 0)
        0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x02, // mov rax, 0x2000001
        0x0f, 0x05                           // syscall
    };
#else
    // Linux : syscall exit = 60
    unsigned char shellcode[] = {
        0x48, 0x31, 0xff,                   // xor rdi, rdi      (rdi = 0)
        0x48, 0xc7, 0xc0, 0x3c, 0x00, 0x00, 0x00, // mov rax, 60
        0x0f, 0x05                           // syscall
    };
#endif

    size_t sc_len = sizeof(shellcode);

    // Affiche le shellcode en hex
    std::cout << "[*] Shellcode (" << sc_len << " octets) :" << std::endl;
    std::cout << "    ";
    for (size_t i = 0; i < sc_len; i++) {
        printf("%02x ", shellcode[i]);
    }
    std::cout << std::endl << std::endl;

    // 1. Allouer de la memoire avec mmap (RW)
    size_t pageSize = sysconf(_SC_PAGESIZE);
    void* mem = mmap(nullptr, pageSize,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mem == MAP_FAILED) {
        std::cerr << "[!] mmap echoue" << std::endl;
        return 1;
    }
    std::cout << "[*] Memoire allouee a : " << mem << std::endl;

    // 2. Copier le shellcode
    std::memcpy(mem, shellcode, sc_len);
    std::cout << "[*] Shellcode copie en memoire" << std::endl;

    // 3. Rendre la memoire executable (R-X)
    if (mprotect(mem, pageSize, PROT_READ | PROT_EXEC) != 0) {
        std::cerr << "[!] mprotect echoue" << std::endl;
        munmap(mem, pageSize);
        return 1;
    }
    std::cout << "[*] Memoire rendue executable (R-X)" << std::endl;

    // 4. Executer
    std::cout << "[*] Execution du shellcode... (exit(0))" << std::endl;
    std::cout << "[*] Si aucune sortie apres ceci, le shellcode a fonctionne !" << std::endl;

    // Cast en pointeur de fonction et appel
    auto func = reinterpret_cast<void(*)()>(mem);
    func(); // Ceci va appeler exit(0) - le programme se termine

    // Cette ligne ne sera jamais atteinte
    std::cout << "[!] Cette ligne ne devrait pas s'afficher" << std::endl;
    munmap(mem, pageSize);
    return 0;
}
```

**Compilation :**
```bash
g++ -std=c++17 -o shellcode_demo example.cpp
```

---

## Checkpoint ✅

Apres ce chapitre, tu dois savoir :
- [ ] Ce qu'est un shellcode (code machine brut, position-independent)
- [ ] Les protections memoire (DEP/NX, W^X) et pourquoi elles existent
- [ ] Comment mmap/mprotect controlent les permissions memoire
- [ ] Le flux : allouer → copier → rendre executable → executer
- [ ] La difference entre les syscalls Linux et macOS
- [ ] Pourquoi les antivirus surveillent les changements de permissions memoire
