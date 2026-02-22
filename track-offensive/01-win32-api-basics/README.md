# Chapitre 01 - APIs Systeme : Comment l'OS Expose ses Fonctions 🔧

> **DISCLAIMER EDUCATIF** ⚠️
> Ce chapitre est **strictement educatif**. Il explique comment les systemes d'exploitation
> exposent leurs fonctions internes via des APIs. Ces connaissances sont essentielles pour
> la comprehension defensive, les CTF, et les labs de securite autorises.
> **Toute utilisation malveillante est illegale et contraire a l'ethique.**

---

## Concept 📖

Un systeme d'exploitation est une couche entre les programmes et le hardware.
Les programmes **ne peuvent pas** acceder directement au hardware : ils doivent
**demander a l'OS** via des **appels systeme** (syscalls).

### Pourquoi c'est important en Red Team ? 🎯

En securite offensive, comprendre les APIs systeme permet de :
- Savoir **quelles informations** un programme peut collecter sur un systeme
- Comprendre comment les outils de securite **surveillent** les appels
- Connaitre les **mecanismes** que les EDR/antivirus interceptent
- Ecrire des outils de **pentest** qui interagissent avec l'OS

---

## Schema ASCII - Architecture des Appels Systeme 🏗️

```
┌─────────────────────────────────────────────────────────────────┐
│                     ESPACE UTILISATEUR (Ring 3)                  │
│                                                                  │
│  ┌──────────────┐    ┌──────────────┐    ┌──────────────┐       │
│  │ Programme A   │    │ Programme B   │    │ Programme C   │       │
│  │ (ton code)    │    │ (navigateur)  │    │ (terminal)    │       │
│  └──────┬───────┘    └──────┬───────┘    └──────┬───────┘       │
│         │                   │                   │                │
│         ▼                   ▼                   ▼                │
│  ┌─────────────────────────────────────────────────────────┐    │
│  │              BIBLIOTHEQUE STANDARD (libc)                │    │
│  │   getpid()  gethostname()  open()  read()  write()      │    │
│  └──────────────────────┬──────────────────────────────────┘    │
│                         │                                        │
│                         │  Appel systeme (syscall)               │
│                         ▼                                        │
│  ┌─────────────────────────────────────────────────────────┐    │
│  │              INTERFACE SYSCALL                            │    │
│  │   Linux: int 0x80 / syscall      macOS: syscall           │    │
│  │   Windows: ntdll.dll → sysenter                           │    │
│  └──────────────────────┬──────────────────────────────────┘    │
│                         │                                        │
╠═════════════════════════╪════════════════════════════════════════╣
│                         ▼                                        │
│                     ESPACE NOYAU (Ring 0)                        │
│                                                                  │
│  ┌─────────────────────────────────────────────────────────┐    │
│  │                    KERNEL (Noyau)                         │    │
│  │   Gestion memoire │ Processus │ Fichiers │ Reseau        │    │
│  └──────────────────────┬──────────────────────────────────┘    │
│                         │                                        │
│                         ▼                                        │
│  ┌─────────────────────────────────────────────────────────┐    │
│  │                    HARDWARE                               │    │
│  │          CPU │ RAM │ Disque │ Carte reseau                │    │
│  └─────────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────────┘
```

### Comparaison Windows vs Unix 🔄

```
┌─────────────────────────┬──────────────────────────────┐
│      WINDOWS (Win32)     │       UNIX (POSIX)            │
├─────────────────────────┼──────────────────────────────┤
│ GetCurrentProcessId()    │ getpid()                      │
│ GetComputerNameA()       │ gethostname()                 │
│ GetUserNameA()           │ getlogin() / getenv("USER")   │
│ GetCurrentDirectoryA()   │ getcwd()                      │
│ GetEnvironmentVariableA()│ getenv()                      │
│ CreateFileA()            │ open()                        │
│ ReadFile()               │ read()                        │
│ WriteFile()              │ write()                       │
│ GetSystemTime()          │ time() / gettimeofday()       │
│ Sleep()                  │ sleep() / usleep()            │
└─────────────────────────┴──────────────────────────────┘
```

---

## Exemple - Wrapper Cross-Platform 💻

```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <pwd.h>
#include <ctime>

// Simulation de l'API Win32 avec des fonctions POSIX
// En Red Team, on wrappe souvent les APIs pour la portabilite

namespace WinAPI {

    // Simule GetCurrentProcessId()
    unsigned long GetCurrentProcessId() {
        return static_cast<unsigned long>(getpid());
    }

    // Simule GetComputerNameA()
    bool GetComputerNameA(char* buffer, unsigned long* size) {
        if (gethostname(buffer, *size) == 0) {
            *size = std::strlen(buffer);
            return true;
        }
        return false;
    }

    // Simule GetUserNameA()
    bool GetUserNameA(char* buffer, unsigned long* size) {
        const char* user = getlogin();
        if (!user) {
            struct passwd* pw = getpwuid(getuid());
            user = pw ? pw->pw_name : nullptr;
        }
        if (user) {
            std::strncpy(buffer, user, *size - 1);
            buffer[*size - 1] = '\0';
            *size = std::strlen(buffer);
            return true;
        }
        return false;
    }

    // Simule GetCurrentDirectoryA()
    unsigned long GetCurrentDirectoryA(unsigned long size, char* buffer) {
        if (getcwd(buffer, size)) {
            return std::strlen(buffer);
        }
        return 0;
    }

    // Simule GetTickCount() - uptime en ms
    unsigned long GetTickCount() {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return static_cast<unsigned long>(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    }

    // Simule Sleep()
    void Sleep(unsigned long milliseconds) {
        usleep(milliseconds * 1000);
    }
}

int main() {
    std::cout << "=== Simulation APIs Systeme ===" << std::endl;

    // GetCurrentProcessId
    std::cout << "[*] PID actuel : " << WinAPI::GetCurrentProcessId() << std::endl;

    // GetComputerNameA
    char hostname[256];
    unsigned long hostnameSize = sizeof(hostname);
    if (WinAPI::GetComputerNameA(hostname, &hostnameSize)) {
        std::cout << "[*] Nom machine : " << hostname << std::endl;
    }

    // GetUserNameA
    char username[256];
    unsigned long usernameSize = sizeof(username);
    if (WinAPI::GetUserNameA(username, &usernameSize)) {
        std::cout << "[*] Utilisateur : " << username << std::endl;
    }

    // GetCurrentDirectoryA
    char cwd[1024];
    if (WinAPI::GetCurrentDirectoryA(sizeof(cwd), cwd) > 0) {
        std::cout << "[*] Repertoire : " << cwd << std::endl;
    }

    // GetTickCount
    std::cout << "[*] Uptime (ms) : " << WinAPI::GetTickCount() << std::endl;

    return 0;
}
```

**Compilation :**
```bash
g++ -std=c++17 -o api_basics example.cpp
```

---

## Checkpoint ✅

Apres ce chapitre, tu dois savoir :
- [ ] Ce qu'est un syscall et pourquoi les programmes ne touchent pas le hardware directement
- [ ] La difference entre espace utilisateur (Ring 3) et espace noyau (Ring 0)
- [ ] Comment les APIs Win32 correspondent aux fonctions POSIX
- [ ] Pourquoi un attaquant s'interesse aux APIs systeme
- [ ] Comment wrapper des fonctions systeme pour la portabilite
