# Projet : Architecture C2 Educative (C++) 🎓

> **DISCLAIMER EDUCATIF** ⚠️
> Ce projet est une **simulation pedagogique** d'architecture Command & Control.
> Il est concu EXCLUSIVEMENT pour :
> - Comprendre les architectures reseau des outils offensifs
> - Formation en cybersecurite et CTF
> - Labs de securite controles et isoles
>
> **Contraintes techniques intentionnelles :**
> - Communication uniquement sur **localhost (127.0.0.1), port 4444**
> - Commandes limitees a une whitelist explicite
> - Communication en clair (pedagogique, pas de production)
> - Aucune fonctionnalite d'evasion ou de persistence
>
> **Toute utilisation en dehors d'un lab controle est illegale.**

---

## Architecture 🏗️

```
ARCHITECTURE C2 EDUCATIVE

    OPERATEUR                              CIBLE (simulee)
  ┌───────────────────────┐             ┌───────────────────────┐
  │      server.cpp       │             │      client.cpp       │
  │                       │             │                       │
  │  accept() connexion   │             │  connect() vers C2    │
  │                       │             │                       │
  │  > Entrez commande:   │             │  Attente commande...  │
  │    whoami             │             │                       │
  │         │             │             │                       │
  │         │  TCP :4444  │             │                       │
  │         └────────────►│─────────────►popen("whoami")        │
  │                       │             │  ↓                    │
  │  Resultat:            │◄────────────│"testuser\n"           │
  │  testuser             │             │                       │
  │                       │             │                       │
  │  > Entrez commande:   │             │                       │
  │    exit               │─────────────►close() + exit         │
  └───────────────────────┘             └───────────────────────┘

  LOCALHOST UNIQUEMENT - PORT 4444
  Toutes les donnees transitent en clair (pedagogique)


PROTOCOLE TEXTUEL :
  Server → Client : "<commande>\n"
  Client → Server : "<sortie de la commande>\n"
  Server → Client : "exit\n"  (pour terminer)


FLUX DETAILLE :
  ┌────────────────────────────────────────────────────────────────┐
  │ 1. server : bind(4444) + listen()                              │
  │ 2. client : connect(127.0.0.1:4444)                            │
  │ 3. server : accept() → fd client                               │
  │ 4. [BOUCLE]                                                    │
  │    a. server : lire stdin de l'operateur                       │
  │    b. server : send(fd, commande)                              │
  │    c. client : recv() la commande                              │
  │    d. client : verifier whitelist                              │
  │    e. client : popen(commande) → capturer stdout               │
  │    f. client : send(fd, resultat)                              │
  │    g. server : recv() + afficher le resultat                   │
  │ 5. "exit" → client se deconnecte, server ferme                 │
  └────────────────────────────────────────────────────────────────┘
```

---

## Fichiers 📁

| Fichier      | Role                                                           |
|--------------|----------------------------------------------------------------|
| `server.cpp` | Serveur C2 : accepte une connexion, envoie les commandes       |
| `client.cpp` | Client (implant) : se connecte, execute les commandes          |

---

## Compilation 💻

```bash
# Compiler les deux binaires
g++ -std=c++17 -o server server.cpp
g++ -std=c++17 -o client client.cpp
```

---

## Utilisation 🔬

```bash
# Terminal 1 : lancer le serveur C2
./server

# Terminal 2 : lancer le client (implant)
./client

# Dans le terminal serveur, taper les commandes :
whoami
ls
pwd
id
hostname
uname -a
date
uptime
exit
```

### Sortie attendue (serveur)

```
[C2-SERVER] Serveur C2 educatif - localhost:4444
[C2-SERVER] Attente de connexion...
[C2-SERVER] Client connecte !
[C2-SERVER] Message initial : [CLIENT] Connecte. Commandes: whoami|ls|pwd|id|...

[C2] Entrez une commande (ou 'exit') : whoami
[C2] Resultat :
testuser

[C2] Entrez une commande (ou 'exit') : exit
[C2-SERVER] Session terminee.
```

---

## Commandes autorisees (whitelist) 📋

```
whoami    ls    pwd    id    hostname    uname -a    date    uptime
help      exit
```

---

## Concepts appris 🎓

- Sockets TCP POSIX : `socket()`, `bind()`, `listen()`, `accept()`, `connect()`
- Protocol request/response textuel simple
- `popen()` pour la capture de stdout des commandes shell
- Whitelist de commandes cote client (defense en profondeur)
- Architecture C2 basique : pourquoi les SOC surveillent ces patterns reseau
- Comment les EDR detectent les connexions sortantes inhabituelles
