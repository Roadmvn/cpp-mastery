# Track Offensive : Red Team C++

**Ecris des outils que les antivirus ne voient pas.**

Le C++ est le langage de prédilection du red teaming avancé. Pas de runtime .NET que Defender connaît par coeur. Pas d'interpréteur Python facile à détecter. Du code natif qui parle directement au kernel Windows, contrôle chaque byte en mémoire, et se fond dans les processus légitimes.

Cobalt Strike, Brute Ratel, Sliver — les meilleurs frameworks C2 sont écrits en C/C++ (ou Go). Comprendre le C++ offensif, c'est comprendre comment fonctionnent ces outils, et être capable de construire les tiens.

---

## Disclaimer

**Ce track est strictement éducatif.**

Le contenu présenté ici est destiné à :
- La recherche en sécurité informatique
- Le pentesting autorisé et encadré par un contrat
- Les compétitions CTF (Capture The Flag)
- La compréhension défensive (savoir attaquer pour mieux défendre)

**L'utilisation de ces techniques sur des systèmes sans autorisation explicite est illégale** et passible de poursuites pénales. Pratique uniquement dans des environnements contrôlés : machines virtuelles, labs personnels, HTB, TryHackMe, ou dans le cadre d'un engagement autorisé.

Tu es responsable de l'usage que tu fais de ces connaissances.

---

## Pourquoi C++ pour le Red Team ?

| Avantage | Explication |
|----------|-------------|
| **Pas de runtime** | Pas de .NET CLR, pas de JVM, pas d'interpréteur — binaire natif |
| **Accès direct au kernel** | Appels syscalls, manipulation de la mémoire au byte près |
| **Contrôle total** | Tu décides quand et comment la mémoire est allouée/libérée |
| **Difficile à reverser** | Code compilé optimisé vs bytecode .NET facile à décompiler |
| **Tradition** | La majorité des malwares avancés (APT) sont en C/C++ |
| **DLL natives** | Tu peux créer des DLL qui se chargent naturellement dans les processus Windows |

---

## Prérequis

Tu **dois** avoir complété ces sections avant de commencer :

| Section | Pourquoi |
|---------|----------|
| [01-foundations](../01-foundations) | Syntaxe C++ de base |
| [02-memory-and-arrays](../02-memory-and-arrays) | Pointeurs, mémoire dynamique, manipulation mémoire |
| [03-oop](../03-oop) | Classes, héritage, polymorphisme |

La section [04-stl-mastery](../04-stl-mastery) est recommandée mais pas obligatoire. En offensif, on utilise souvent les API Windows directement plutôt que la STL.

---

## Roadmap détaillée

### 01 — Win32 API Basics 🪟
[`01-win32-api-basics/`](01-win32-api-basics/)

Windows expose des milliers de fonctions via la Win32 API. C'est la porte d'entrée vers tout ce que fait le système d'exploitation. Tu vas apprendre à parler directement à Windows, sans couche d'abstraction.

**Concepts clés :**
- Handles : `HANDLE`, `HMODULE`, `HWND` — tout est handle sous Windows
- Types Windows : `DWORD`, `LPVOID`, `LPCSTR`, `BOOL`
- `CreateFile`, `ReadFile`, `WriteFile` — I/O bas niveau
- `GetModuleHandle`, `GetProcAddress` — résolution dynamique de fonctions
- `LoadLibrary` / `FreeLibrary` — chargement de DLL
- Headers : `<windows.h>`, `<tlhelp32.h>`, `<winternl.h>`

**Après ce chapitre :** Tu sauras utiliser la Win32 API pour interagir avec le système, résoudre des fonctions dynamiquement et comprendre la structure fondamentale d'un programme Windows natif.

---

### 02 — Process Enumeration
[`02-process-enumeration/`](02-process-enumeration/)

Avant d'injecter quoi que ce soit, tu dois savoir **ce qui tourne**. Énumérer les processus, c'est la première étape de toute opération offensive. Tu vas apprendre à voir tout ce que voit le Task Manager, et plus encore.

**Concepts clés :**
- `CreateToolhelp32Snapshot` + `Process32First` / `Process32Next`
- `EnumProcesses` et `EnumProcessModules`
- `NtQuerySystemInformation` — API native (ntdll)
- PID, PPID, arbre de processus
- Identifier les processus intéressants (lsass, explorer, svchost)
- Filtrer par nom, PID, privilèges

**Après ce chapitre :** Tu sauras lister tous les processus actifs, trouver un processus cible par nom ou PID, et récupérer ses informations (modules chargés, threads, mémoire).

---

### 03 — Process Injection 💉
[`03-process-injection/`](03-process-injection/)

L'injection de processus, c'est l'art de faire exécuter ton code **dans** un autre processus. C'est la technique fondamentale du maldev moderne. Tu vas apprendre la méthode classique et ses variantes.

**Concepts clés :**
- Classic injection : `OpenProcess`  `VirtualAllocEx`  `WriteProcessMemory`  `CreateRemoteThread`
- Permissions et tokens : `PROCESS_ALL_ACCESS`, `SeDebugPrivilege`
- APC Injection : `QueueUserAPC` — plus discret que CreateRemoteThread
- Early Bird Injection : injection avant que le thread ne commence
- Thread hijacking : détourner un thread existant
- `NtCreateThreadEx` vs `CreateRemoteThread`

**Après ce chapitre :** Tu sauras injecter du code (shellcode ou DLL) dans un processus distant en utilisant plusieurs techniques, de la classique à la plus furtive.

---

### 04 — DLL Injection
[`04-dll-injection/`](04-dll-injection/)

Une DLL, c'est du code qui se charge dans l'espace mémoire d'un processus. L'injection de DLL te permet de faire tourner ta propre bibliothèque dans n'importe quel processus. Technique utilisée autant par les jeux (mods) que par les APT.

**Concepts clés :**
- `LoadLibrary` injection via `CreateRemoteThread`
- Reflective DLL Injection : charger une DLL sans toucher le disque
- DLL hijacking / DLL search order abuse
- `DllMain` : point d'entrée, `DLL_PROCESS_ATTACH`
- Manual mapping : parser le PE, résoudre les imports, relocation
- Différence entre injection mémoire et injection disque

**Après ce chapitre :** Tu sauras injecter une DLL dans un processus de 3 manières différentes, dont le reflective loading qui ne touche jamais le disque — beaucoup plus difficile à détecter.

---

### 05 — Shellcode Execution 🐚
[`05-shellcode-execution/`](05-shellcode-execution/)

Le shellcode, c'est du code machine brut — pas de headers, pas de sections PE, juste des opcodes. C'est le payload final que tu veux exécuter. Tu vas apprendre à le générer, le charger, et l'exécuter proprement.

**Concepts clés :**
- Qu'est-ce qu'un shellcode : position-independent code (PIC)
- `VirtualAlloc` avec `PAGE_EXECUTE_READWRITE`
- Exécution : function pointer cast, `CreateThread`, fibers
- Shellcode runners : différentes méthodes d'exécution
- Encoder/obfusquer un shellcode (XOR, AES)
- Staged vs stageless payloads
- Syscalls directs : éviter les hooks de l'EDR sur ntdll

**Après ce chapitre :** Tu sauras charger et exécuter du shellcode de plusieurs façons, l'encoder pour bypasser la détection statique, et comprendre la différence entre les méthodes d'exécution.

---

### 06 — API Hooking
[`06-api-hooking/`](06-api-hooking/)

Les EDR (Endpoint Detection & Response) hookent les fonctions Windows pour surveiller ce que font les programmes. Comprendre le hooking, c'est comprendre comment fonctionne la défense — et comment la contourner.

**Concepts clés :**
- Inline hooking : réécrire les premiers bytes d'une fonction (trampoline)
- IAT hooking : modifier l'Import Address Table du PE
- Comment les EDR hookent ntdll.dll (userland hooks)
- Détecter les hooks : comparer ntdll en mémoire vs sur disque
- Unhooking : restaurer ntdll propre depuis le disque ou KnownDlls
- Syscall stubs : appeler le kernel directement sans passer par ntdll

**Après ce chapitre :** Tu sauras comment les EDR surveillent les appels API, comment détecter leurs hooks, et comment les contourner en restaurant une copie propre de ntdll ou en utilisant des syscalls directs.

---

### 07 — Evasion Techniques 🥷
[`07-evasion-techniques/`](07-evasion-techniques/)

Le code le plus puissant est inutile s'il se fait détecter. L'évasion, c'est l'art de rester invisible. Tu vas apprendre les techniques modernes pour contourner les antivirus et les EDR.

**Concepts clés :**
- Obfuscation de strings : chiffrement compile-time, stack strings
- Sleep obfuscation : chiffrer la mémoire pendant le sleep
- Payload encryption : AES/RC4 avec clé dérivée de l'environnement
- Anti-sandbox : détecter les VMs et sandboxes (CPUID, timing, hardware)
- Anti-debug : `IsDebuggerPresent`, `NtQueryInformationProcess`, timing checks
- AMSI bypass : patcher `AmsiScanBuffer` en mémoire
- ETW patching : désactiver le tracing Windows

**Après ce chapitre :** Tu sauras rendre ton code indétectable par les solutions de sécurité courantes en combinant obfuscation, chiffrement et techniques anti-analyse.

---

### 08 — Persistence Mechanisms
[`08-persistence-mechanisms/`](08-persistence-mechanisms/)

Avoir accès, c'est bien. Garder l'accès après un reboot, c'est mieux. La persistence, c'est l'art de survivre aux redémarrages et aux tentatives de nettoyage.

**Concepts clés :**
- Registry Run keys : `HKCU\Software\Microsoft\Windows\CurrentVersion\Run`
- Scheduled Tasks : `schtasks`, COM objects
- Services Windows : créer un service persistant
- DLL search order hijacking pour persistence
- COM hijacking
- WMI event subscriptions
- Startup folder, logon scripts
- Trade-offs : discrétion vs fiabilité

**Après ce chapitre :** Tu sauras implémenter plusieurs mécanismes de persistence avec différents niveaux de discrétion, et choisir le bon selon le contexte de l'opération.

---

## Projet final : Custom C2 Implant
[`projects/custom-implant/`](projects/custom-implant/)

Tu vas construire un **implant C2 complet** qui combine tout ce que tu as appris :

- Communication HTTP/HTTPS avec un serveur C2
- Chiffrement du trafic (AES-256)
- Exécution de commandes à distance
- Injection de shellcode dans un processus distant
- Sleep obfuscation entre les check-ins
- Anti-sandbox et anti-debug
- Mécanisme de persistence configurable
- Architecture modulaire (plugins)

---

## Architecture d'un implant C2

```
    ┌─────────────────────────────────────────────────────────┐
    │                    OPERATEUR (Attaquant)                │
    │                                                         │
    │  Terminal / GUI                                         │
    │  > execute-assembly payload.exe                         │
    │  > inject-shellcode -pid 1234                           │
    │  > persist -method registry                             │
    └────────────────────────┬────────────────────────────────┘
                             │ HTTPS
                             ▼
    ┌─────────────────────────────────────────────────────────┐
    │                    SERVEUR C2 (Team Server)             │
    │                                                         │
    │  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐   │
    │  │  Listeners   │  │   Task       │  │   Payload    │   │
    │  │  HTTP/HTTPS  │  │   Queue      │  │   Generator  │   │
    │  │  DNS         │  │              │  │              │   │
    │  └──────────────┘  └──────────────┘  └──────────────┘   │
    └────────────────────────┬────────────────────────────────┘
                             │ HTTPS (chiffré AES-256)
                             │ Jitter + Sleep aléatoire
                             ▼
    ┌─────────────────────────────────────────────────────────┐
    │              IMPLANT (Machine cible)                    │
    │                                                         │
    │  ┌──────────┐  ┌───────────┐  ┌──────────────────────┐  │
    │  │  Comms   │  │  Task     │  │  Modules             │  │
    │  │  Module  │  │  Executor │  │                      │  │
    │  │          │  │           │  │  - Shellcode inject  │  │
    │  │ Check-in │  │ Parse cmd │  │  - Process inject    │  │
    │  │ Exfil    │  │ Execute   │  │  - Keylogger         │  │
    │  │ Download │  │ Report    │  │  - Screenshot        │  │
    │  └──────────┘  └───────────┘  │  - Persistence       │  │
    │                               └──────────────────────┘  │
    │  ┌──────────────────────────────────────────────────┐   │
    │  │  Evasion Layer                                   │   │
    │  │                                                  │   │
    │  │  Sleep obfuscation  │  AMSI bypass               │   │
    │  │  ETW patching       │  Syscall directs           │   │
    │  │  Anti-sandbox       │  String encryption         │   │
    │  └──────────────────────────────────────────────────┘   │
    └─────────────────────────────────────────────────────────┘

    ═══════════════════════════════════════════════════════════
     L'implant check-in periodiquement, recoit des taches,
     les execute, et renvoie les resultats. Le tout chiffre.
    ═══════════════════════════════════════════════════════════
```

---

## Ressources recommandées 📚

### Livres
- **"Windows Internals Part 1 & 2"** — Russinovich, Solomon, Ionescu — La bible de Windows
- **"The Shellcoder's Handbook"** — Anley, Heasman, Lindner — Exploitation classique
- **"Malware Development for Ethical Hackers"** — Alexandre Borges — Maldev moderne
- **"Windows System Programming"** — Hart — Win32 API en profondeur

### Blogs et sites
- [MalDev Academy](https://maldevacademy.com/) — Formation maldev structurée
- [ired.team](https://www.ired.team/) — Red Team notes, techniques offensives documentées
- [modexp](https://modexp.wordpress.com/) — Shellcoding et techniques Windows avancées
- [0xPat Blog](https://0xpat.github.io/) — Malware development pas à pas
- [Crow (CrowsCPP)](https://www.crow.nz/) — Red team tooling

### Labs et pratique
- [Hack The Box](https://www.hackthebox.com/) — Machines et challenges
- [TryHackMe](https://tryhackme.com/) — Parcours guidés Red Team
- [Maldev Labs](https://github.com/topics/malware-development) — Repos open source pour apprendre
- [YOURCTF / CTFtime](https://ctftime.org/) — Compétitions CTF

### Outils indispensables
- **x64dbg** — Debugger Windows user-mode
- **Process Hacker** — Meilleur que Task Manager (processus, handles, mémoire)
- **PE-bear** — Analyse de fichiers PE (headers, sections, imports)
- **Ghidra** — Reverse engineering (NSA, gratuit et puissant)

---

## Environnement de lab recommandé

```
Host (Linux/Mac)
└── VirtualBox / VMware
    ├── Windows 10/11 (victime)     # Defender désactivé pour les tests
    ├── Windows Server (DC)          # Pour les scénarios Active Directory
    └── Kali Linux (attaquant)       # Outils offensifs pré-installés
```

Travaille **toujours** dans un environnement isolé. Jamais sur ta machine principale. Jamais sur un réseau de production.

---

## Let's hack

```
x86_64-w64-mingw32-g++ -std=c++17 -o implant.exe 01-win32-api-basics/exercise.cpp -lws2_32
```

On compile avec MinGW pour cibler Windows. Le flag `-lws2_32` lie la bibliothèque Winsock pour le networking.
