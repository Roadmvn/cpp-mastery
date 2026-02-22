# Chapitre 08 - Mecanismes de Persistance 🔁

> **DISCLAIMER EDUCATIF** ⚠️
> Ce chapitre est **strictement educatif** dans le cadre de CTF et labs de securite.
> Les techniques de persistance sont etudiees pour que les **defenseurs sachent
> ou chercher lors d'un incident response**. Le code fourni agit **uniquement
> sur ta propre crontab utilisateur** (pas de privilege root).
> **Toute utilisation non consentie sur un systeme tiers est illegale.**

---

## Concept 📖

La **persistance** consiste a faire en sorte qu'un programme soit **re-execute
automatiquement** apres un reboot ou une reconnexion, sans que l'utilisateur
n'ait a le relancer manuellement.

En incident response, les defenseurs cherchent systematiquement ces points de
persistance ("persistence points") pour identifier si une compromission est toujours active.

---

## Schema ASCII - Timeline Boot → Login → Persistence Trigger 🏗️

```
MACHINE ALLUMEE
      │
      ▼
┌─────────────────────────────────────────────────────────────────────┐
│  PHASE 1 : BOOT SYSTEME                                             │
│                                                                     │
│  BIOS/UEFI                                                          │
│     │                                                               │
│     ▼                                                               │
│  Bootloader (GRUB / launchd macOS)                                  │
│     │                                                               │
│     ▼                                                               │
│  Kernel + init system (systemd / launchd)                           │
│     │                                                               │
│     ├──► Services systemd (Linux)  ◄── POINT DE PERSISTANCE #1      │
│     │    /etc/systemd/system/*.service                              │
│     │    /usr/lib/systemd/system/*.service                          │
│     │                                                               │
│     ├──► Launch Daemons (macOS)    ◄── POINT DE PERSISTANCE #2      │
│     │    /Library/LaunchDaemons/*.plist                             │
│     │    ~/Library/LaunchAgents/*.plist                             │
│     │                                                               │
│     └──► Cron daemon (crond)       ◄── POINT DE PERSISTANCE #3      │
│          /etc/cron.d/                                               │
│          /var/spool/cron/crontabs/                                  │
└─────────────────────────────────────────────────────────────────────┘
      │
      ▼
┌─────────────────────────────────────────────────────────────────────┐
│  PHASE 2 : SESSION UTILISATEUR (LOGIN)                              │
│                                                                     │
│  Shell de login                                                     │
│     │                                                               │
│     ├──► /etc/profile  (tous les users)                             │
│     ├──► ~/.bash_profile ou ~/.zprofile  ◄── PERSISTANCE #4         │
│     │                                                               │
│  Shell interactif                                                   │
│     ├──► ~/.bashrc ou ~/.zshrc       ◄── PERSISTANCE #5             │
│     │                                                               │
│  Interface graphique (si applicable)                                │
│     └──► XDG Autostart : ~/.config/autostart/*.desktop  ◄── #6      │
└─────────────────────────────────────────────────────────────────────┘
      │
      ▼
┌─────────────────────────────────────────────────────────────────────┐
│  PHASE 3 : TRIGGERS DE PERSISTANCE                                  │
│                                                                     │
│  Cron job (* * * * * /chemin/payload)                               │
│     └──► Execute TOUTES LES MINUTES (ou selon schedule)             │
│                                                                     │
│  .bashrc modifie                                                    │
│     └──► Execute a CHAQUE ouverture de terminal                     │
│                                                                     │
│  Service systemd (Type=simple, Restart=always)                      │
│     └──► Execute au boot, REDEMARRAGE AUTOMATIQUE si crash          │
└─────────────────────────────────────────────────────────────────────┘


RESUME : OU CHERCHER EN INCIDENT RESPONSE
┌──────────────────────────────┬──────────────────────────────────┐
│ Mechanism                    │ Ou regarder                      │
├──────────────────────────────┼──────────────────────────────────┤
│ Cron utilisateur             │ crontab -l                       │
│ Cron systeme                 │ /etc/cron*/, /var/spool/cron/    │
│ Bashrc/profile               │ ~/.bashrc, ~/.bash_profile, etc. │
│ Systemd service              │ systemctl list-units             │
│ LaunchAgent (macOS)          │ ~/Library/LaunchAgents/          │
│ LaunchDaemon (macOS)         │ /Library/LaunchDaemons/          │
│ XDG Autostart                │ ~/.config/autostart/             │
└──────────────────────────────┴──────────────────────────────────┘
```

---

## Methode 1 - Cron Jobs 💻

```bash
# Voir la crontab actuelle
crontab -l

# Syntaxe d'une entree cron
# ┌───── minute (0-59)
# │ ┌───── heure (0-23)
# │ │ ┌───── jour du mois (1-31)
# │ │ │ ┌───── mois (1-12)
# │ │ │ │ ┌───── jour de la semaine (0-7, 0=dimanche)
# │ │ │ │ │
# * * * * * /chemin/vers/commande

# Exemple : toutes les minutes
* * * * * /tmp/payload.sh >> /tmp/log.txt 2>&1

# Exemple : au reboot
@reboot /chemin/payload
```

```cpp
// En C++ : ajouter une entree cron via popen("crontab -l") + popen("crontab -")
// Voir le challenge.cpp pour l'implementation complete
```

---

## Methode 2 - Modification de .bashrc / .profile 💻

```cpp
// Ajouter une ligne a la fin de ~/.bashrc
#include <fstream>
#include <cstdlib>

void addBashrcEntry(const std::string& command) {
    const char* home = std::getenv("HOME");
    std::string path = std::string(home) + "/.bashrc";

    std::ofstream file(path, std::ios::app);  // mode append
    file << "\n# added entry\n";
    file << command << "\n";
}
```

---

## Methode 3 - Service Systemd (Linux) 💻

```ini
# /etc/systemd/system/my-service.service
[Unit]
Description=My Service
After=network.target

[Service]
Type=simple
ExecStart=/usr/bin/python3 /opt/payload.py
Restart=always
RestartSec=10

[Install]
WantedBy=multi-user.target
```

```bash
# Activer et demarrer
systemctl enable my-service
systemctl start my-service

# Verifier
systemctl status my-service
```

---

## Checkpoint ✅

Apres ce chapitre, tu dois savoir :
- [ ] Les principaux points de persistance sur Linux et macOS
- [ ] Comment lire et modifier une crontab par programmation
- [ ] Comment detecter une persistance dans .bashrc/.profile
- [ ] La structure d'un service systemd
- [ ] Ou chercher en incident response pour trouver des persistances
