# Projet : Custom Implant C2 (Simulation Educative) 🎓

> **DISCLAIMER EDUCATIF** ⚠️
> Ce projet est une **simulation educative** strictement limitee a localhost.
> Il est concu pour comprendre les architectures C2 dans le cadre de :
> - CTF (Capture The Flag)
> - Labs de securite controles
> - Formation en cybersecurite defensive
>
> **Contraintes techniques intentionnelles :**
> - Connexion UNIQUEMENT sur 127.0.0.1 (localhost)
> - Commandes limitees a une whitelist explicite (whoami, ls, pwd, id, etc.)
> - Communication en clair (pas de chiffrement, pour la lisibilite pedagogique)
>
> **Toute utilisation malveillante est illegale et contraire a l'ethique.**

---

## Architecture 🏗️

```
SIMULATION C2 EDUCATIVE (localhost uniquement)

┌─────────────────────────────────────────────────────────────┐
│                                                             │
│   [SERVEUR C2]                     [IMPLANT]                │
│   (operateur)                      (cible simulee)          │
│                                                             │
│   server.cpp                       main.cpp                 │
│   OU nc -lvp 4444                                           │
│                                                             │
│       │                                 │                   │
│       │   TCP localhost:4444            │                   │
│       │ ◄───────────────────────────── │ connect()         │
│       │                                 │                   │
│       │  "whoami\n"       ──────────── ►│                   │
│       │                                 │ popen("whoami")   │
│       │                                 │ → "user\n"        │
│       │ ◄──────────────  "user\n"       │                   │
│       │                                 │                   │
│       │  "ls\n"           ──────────── ►│                   │
│       │ ◄──────────────  "fichiers\n"   │                   │
│       │                                 │                   │
│       │  "exit\n"         ──────────── ►│ close()           │
│                                                             │
└─────────────────────────────────────────────────────────────┘

FLUX DE DONNEES :
  Operateur tape cmd → Serveur envoie → Implant recoit → popen() → Resultat → Serveur affiche
```

---

## Fichiers 📁

| Fichier     | Role                                                        |
|-------------|-------------------------------------------------------------|
| `implant.h` | Interface : whitelist, constantes, declarations             |
| `main.cpp`  | L'implant : se connecte au serveur, execute les commandes   |

---

## Compilation 💻

```bash
# Compiler l'implant
g++ -std=c++17 -o implant main.cpp

# Verifier la compilation
./implant --help  # affichera l'erreur de connexion (normal, pas de serveur)
```

---

## Utilisation (lab local) 🔬

### Methode 1 : avec netcat (simple)

```bash
# Terminal 1 : serveur C2 (netcat)
nc -lvp 4444

# Terminal 2 : lancer l'implant
./implant

# Dans le terminal netcat : taper les commandes
whoami
ls
pwd
id
exit
```

### Methode 2 : avec le serveur C2 du projet

```bash
# Voir /Users/tudygbaguidi/Desktop/full-c++/projects/c2-implant-cpp/
# Terminal 1 :
cd /Users/tudygbaguidi/Desktop/full-c++/projects/c2-implant-cpp
g++ -std=c++17 -o server server.cpp && ./server

# Terminal 2 :
./implant
```

---

## Commandes autorisees (whitelist) 📋

```
whoami     → nom de l'utilisateur courant
ls         → liste du repertoire courant
pwd        → repertoire de travail courant
id         → UID, GID et groupes
hostname   → nom de la machine
uname -a   → informations systeme
date       → date et heure
uptime     → temps depuis le boot
help       → afficher la whitelist
exit       → deconnexion propre
```

---

## Concepts appris 🎓

- Architecture client/serveur avec sockets TCP POSIX
- `popen()` pour executer des commandes et capturer stdout
- Whitelist de commandes pour limiter la surface d'attaque
- Protocol textuel simple (une commande = une ligne)
- Pourquoi les EDR surveillent `popen()`, `system()`, `execve()`
