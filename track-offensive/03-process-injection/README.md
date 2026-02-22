# Chapitre 03 - Injection de Processus (Simulation IPC) 💉

> **DISCLAIMER EDUCATIF** ⚠️
> Ce chapitre est **strictement educatif**. L'injection de processus est une technique
> avancee etudiee pour **comprendre les attaques et mieux s'en defendre**.
> Nous utilisons des **simulations IPC** (Inter-Process Communication) pour illustrer
> les concepts sans creer de vrais outils offensifs.
> **Toute utilisation malveillante est illegale et contraire a l'ethique.**

---

## Concept 📖

L'injection de processus consiste a **faire executer du code dans l'espace memoire
d'un autre processus**. Sur Windows, cela passe par des APIs comme `VirtualAllocEx`,
`WriteProcessMemory`, `CreateRemoteThread`.

Ici, on **simule le concept** avec des mecanismes IPC Unix :
- **Shared Memory** (memoire partagee)
- **fork() + pipe** (communication parent-enfant)
- **Signaux** (notification entre processus)

### Pourquoi c'est important en Red Team ? 🎯

L'injection de processus permet de :
- **Cacher du code** dans un processus legitime (evasion)
- **Heriter des privileges** du processus cible
- **Contourner les firewalls** applicatifs (le processus injecte a deja les droits reseau)
- Comprendre comment les **EDR detectent** ces techniques

---

## Schema ASCII - Injection de Processus 🏗️

### Injection Classique (Windows - Conceptuel)

```
┌─────────────────┐         ┌─────────────────┐
│  PROCESSUS A     │         │  PROCESSUS B     │
│  (attaquant)     │         │  (cible/victime) │
│                  │         │                  │
│  1. OpenProcess()│────────>│                  │
│                  │         │                  │
│  2. VirtualAlloc │         │  ┌────────────┐  │
│     ExRemote()   │────────>│  │ Zone allouee│  │
│                  │         │  │ (vide)      │  │
│  3. WriteProcess │         │  │             │  │
│     Memory()     │────────>│  │ [CODE ECRIT]│  │
│                  │         │  │             │  │
│  4. CreateRemote │         │  │  ↓ Execute! │  │
│     Thread()     │────────>│  │ [RUNNING]   │  │
│                  │         │  └────────────┘  │
└─────────────────┘         └─────────────────┘
```

### Notre Simulation (IPC Unix)

```
┌─────────────────────┐      SHARED MEMORY      ┌─────────────────────┐
│   PROCESSUS PARENT   │    ┌──────────────┐     │   PROCESSUS ENFANT   │
│                       │    │              │     │                      │
│  1. Cree la zone     │───>│  shmget()    │     │                      │
│     memoire partagee  │    │  shmat()     │<───│  2. S'attache a la   │
│                       │    │              │     │     memoire partagee │
│  3. Ecrit des donnees│───>│ [DONNEES]    │     │                      │
│     (simule injection)│    │              │───>│  4. Lit les donnees   │
│                       │    │              │     │     et les execute    │
│  5. Signal SIGUSR1   │────────────────────────>│     (interprete)      │
│     "execute!"        │    │              │     │                      │
│                       │    └──────────────┘     │  6. Ecrit le resultat│
│  7. Lit le resultat  │<───────────────────────│     dans shared mem   │
└─────────────────────┘                          └─────────────────────┘
```

### Pipe (Communication Parent-Enfant)

```
    PARENT                    ENFANT
  ┌────────┐               ┌────────┐
  │        │   pipe[1]     │        │
  │ WRITE ─│──────────────>│─ READ  │  pipe_cmd : parent envoie commandes
  │        │               │        │
  │        │   pipe[0]     │        │
  │ READ ──│<──────────────│─ WRITE │  pipe_res : enfant renvoie resultats
  │        │               │        │
  └────────┘               └────────┘
```

---

## Exemple - Simulation avec fork + pipe 💻

```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>

// Simulation : le parent "injecte" des commandes dans l'enfant
// L'enfant les execute et renvoie le resultat

int main() {
    int pipe_cmd[2]; // Parent -> Enfant (commandes)
    int pipe_res[2]; // Enfant -> Parent (resultats)

    pipe(pipe_cmd);
    pipe(pipe_res);

    pid_t pid = fork();

    if (pid == 0) {
        // === PROCESSUS ENFANT (simule le processus "injecte") ===
        close(pipe_cmd[1]); // Ferme ecriture commande
        close(pipe_res[0]); // Ferme lecture resultat

        std::cout << "[ENFANT PID:" << getpid() << "] En attente de commandes..." << std::endl;

        char cmd[256];
        while (true) {
            ssize_t n = read(pipe_cmd[0], cmd, sizeof(cmd) - 1);
            if (n <= 0) break;
            cmd[n] = '\0';

            // Retire le newline si present
            char* nl = strchr(cmd, '\n');
            if (nl) *nl = '\0';

            if (strcmp(cmd, "EXIT") == 0) break;

            std::cout << "[ENFANT] Execute : " << cmd << std::endl;

            // Execute la commande et capture la sortie
            std::string result;
            FILE* fp = popen(cmd, "r");
            if (fp) {
                char buf[128];
                while (fgets(buf, sizeof(buf), fp)) {
                    result += buf;
                }
                pclose(fp);
            } else {
                result = "Erreur d'execution\n";
            }

            // Renvoie le resultat au parent
            write(pipe_res[1], result.c_str(), result.size());
        }

        close(pipe_cmd[0]);
        close(pipe_res[1]);
        _exit(0);

    } else {
        // === PROCESSUS PARENT (simule "l'injecteur") ===
        close(pipe_cmd[0]); // Ferme lecture commande
        close(pipe_res[1]); // Ferme ecriture resultat

        std::cout << "[PARENT PID:" << getpid() << "] Injection simulee dans PID:" << pid << std::endl;

        // "Injecte" des commandes
        const char* commands[] = {"whoami", "pwd", "uname -a", "EXIT"};

        for (const char* cmd : commands) {
            if (strcmp(cmd, "EXIT") == 0) {
                write(pipe_cmd[1], cmd, strlen(cmd));
                break;
            }

            std::cout << "\n[PARENT] Envoie commande : " << cmd << std::endl;
            write(pipe_cmd[1], cmd, strlen(cmd));

            // Attend un peu pour la reponse
            usleep(100000);

            char result[4096];
            ssize_t n = read(pipe_res[0], result, sizeof(result) - 1);
            if (n > 0) {
                result[n] = '\0';
                std::cout << "[PARENT] Resultat recu :\n" << result << std::endl;
            }
        }

        close(pipe_cmd[1]);
        close(pipe_res[0]);
        waitpid(pid, nullptr, 0);
        std::cout << "[PARENT] Processus enfant termine." << std::endl;
    }

    return 0;
}
```

---

## Checkpoint ✅

Apres ce chapitre, tu dois savoir :
- [ ] Le concept d'injection de processus (ecrire du code dans un autre processus)
- [ ] Les etapes classiques : allouer, ecrire, executer
- [ ] Comment fork() cree un processus enfant
- [ ] Comment les pipes permettent la communication inter-processus
- [ ] Comment la memoire partagee simule l'ecriture dans un autre processus
- [ ] Pourquoi les EDR surveillent ces APIs (VirtualAllocEx, WriteProcessMemory, etc.)
