# Chapitre 02 - Enumeration de Processus 🔍

> **DISCLAIMER EDUCATIF** ⚠️
> Ce chapitre est **strictement educatif**. L'enumeration de processus est une technique
> de base en administration systeme et en securite. Elle est utilisee legitimement par
> les outils de monitoring, les EDR, et les outils de forensic.
> **Toute utilisation malveillante est illegale et contraire a l'ethique.**

---

## Concept 📖

Chaque programme en cours d'execution est un **processus**. L'OS lui attribue :
- Un **PID** (Process ID) : identifiant unique
- Un **PPID** (Parent PID) : le processus qui l'a cree
- Un **UID** : l'utilisateur qui l'execute
- De la **memoire** : heap, stack, code, data
- Des **descripteurs** : fichiers ouverts, sockets, etc.

### Pourquoi c'est important en Red Team ? 🎯

L'enumeration de processus permet de :
- **Identifier les defenses** : antivirus, EDR, monitoring en cours d'execution
- **Trouver des cibles** : processus privilegies, services vulnerables
- **Comprendre l'environnement** : quels logiciels tournent sur la machine
- **Detecter du sandboxing** : peu de processus = possible sandbox/VM

---

## Schema ASCII - Arbre de Processus 🌳

```
                        ┌─────────────┐
                        │  init / PID 1│
                        │  (systemd)   │
                        └──────┬──────┘
                               │
              ┌────────────────┼────────────────┐
              │                │                │
       ┌──────┴──────┐ ┌──────┴──────┐ ┌──────┴──────┐
       │  sshd        │ │  cron        │ │  apache2     │
       │  PID: 450    │ │  PID: 520    │ │  PID: 680    │
       │  PPID: 1     │ │  PPID: 1     │ │  PPID: 1     │
       └──────┬──────┘ └─────────────┘ └──────┬──────┘
              │                                │
       ┌──────┴──────┐              ┌─────────┼─────────┐
       │  sshd        │              │         │         │
       │  PID: 1200   │         worker    worker    worker
       │  PPID: 450   │         PID:681   PID:682  PID:683
       └──────┬──────┘
              │
       ┌──────┴──────┐
       │  bash        │
       │  PID: 1201   │
       │  PPID: 1200  │
       └──────┬──────┘
              │
       ┌──────┴──────┐
       │  ./mon_prog  │
       │  PID: 1350   │
       │  PPID: 1201  │
       └─────────────┘
```

### Structure d'un Processus en Memoire 🧠

```
┌──────────────────────────────────┐  Adresses hautes
│           STACK                   │  ← Variables locales, retours
│           ↓ (grandit vers le bas)│
├──────────────────────────────────┤
│                                  │
│       (espace libre)             │
│                                  │
├──────────────────────────────────┤
│           ↑ (grandit vers haut)  │
│           HEAP                   │  ← Allocations dynamiques (new/malloc)
├──────────────────────────────────┤
│           BSS                    │  ← Variables non initialisees
├──────────────────────────────────┤
│           DATA                   │  ← Variables initialisees
├──────────────────────────────────┤
│           TEXT (CODE)            │  ← Instructions du programme
└──────────────────────────────────┘  Adresses basses
```

---

## Methodes d'Enumeration par OS 🖥️

```
┌────────────┬─────────────────────────────────────────┐
│    OS       │  Methode d'enumeration                   │
├────────────┼─────────────────────────────────────────┤
│  Linux      │  /proc/<pid>/status, /proc/<pid>/cmdline │
│             │  Chaque processus = un dossier dans /proc│
├────────────┼─────────────────────────────────────────┤
│  macOS      │  Commande 'ps aux' (pas de /proc)        │
│             │  sysctl + kinfo_proc                     │
├────────────┼─────────────────────────────────────────┤
│  Windows    │  CreateToolhelp32Snapshot()               │
│             │  EnumProcesses() / NtQuerySystemInfo     │
└────────────┴─────────────────────────────────────────┘
```

---

## Exemple - Enumeration Cross-Platform 💻

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <unistd.h>

struct ProcessInfo {
    int pid;
    int ppid;
    std::string user;
    std::string command;
    float cpu;
    float mem;
};

// Enumere les processus via la commande ps (cross-platform macOS/Linux)
std::vector<ProcessInfo> enumerateProcesses() {
    std::vector<ProcessInfo> processes;

    // ps compatible macOS et Linux
    FILE* pipe = popen("ps -eo pid,ppid,user,%cpu,%mem,comm 2>/dev/null", "r");
    if (!pipe) return processes;

    char line[512];
    // Sauter le header
    if (fgets(line, sizeof(line), pipe) == nullptr) {
        pclose(pipe);
        return processes;
    }

    while (fgets(line, sizeof(line), pipe)) {
        ProcessInfo proc;
        char user[64], cmd[256];

        if (sscanf(line, "%d %d %63s %f %f %255s",
                   &proc.pid, &proc.ppid, user, &proc.cpu, &proc.mem, cmd) >= 6) {
            proc.user = user;
            proc.command = cmd;
            processes.push_back(proc);
        }
    }
    pclose(pipe);
    return processes;
}

int main() {
    std::cout << "=== Enumeration de Processus ===" << std::endl;

    auto procs = enumerateProcesses();
    std::cout << "[*] " << procs.size() << " processus trouves" << std::endl;
    std::cout << std::endl;

    // Affichage formate
    printf("%-8s %-8s %-12s %-6s %-6s %s\n",
           "PID", "PPID", "USER", "CPU%", "MEM%", "COMMAND");
    printf("%-8s %-8s %-12s %-6s %-6s %s\n",
           "---", "----", "----", "----", "----", "-------");

    for (const auto& p : procs) {
        printf("%-8d %-8d %-12s %-6.1f %-6.1f %s\n",
               p.pid, p.ppid, p.user.c_str(), p.cpu, p.mem, p.command.c_str());
    }

    return 0;
}
```

---

## Checkpoint ✅

Apres ce chapitre, tu dois savoir :
- [ ] Ce qu'est un PID et un PPID, et comment ils forment un arbre
- [ ] Comment enumerer les processus sur Linux (/proc) et macOS (ps)
- [ ] La structure memoire d'un processus (stack, heap, text, data)
- [ ] Pourquoi un attaquant enumere les processus (detection EDR, cibles)
- [ ] Comment parser la sortie de commandes systeme en C++
