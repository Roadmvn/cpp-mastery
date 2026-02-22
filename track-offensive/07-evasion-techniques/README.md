# Chapitre 07 - Techniques d'Evasion 🕵️

> **DISCLAIMER EDUCATIF** ⚠️
> Ce chapitre est **strictement educatif** dans le cadre de CTF, labs de securite
> et formation en cybersecurite defensive. Les techniques presentees sont etudiees
> pour comprendre comment les **outils de securite (EDR/AV) les detectent et les bloquent**.
> **Toute utilisation en dehors d'un cadre legal et consenti est illegale.**

---

## Concept 📖

Les techniques d'**evasion** permettent a un programme de modifier son comportement
pour eviter d'etre detecte par des outils d'analyse (sandboxes, EDR, antivirus).
Comprendre ces techniques est **indispensable pour les defenseurs** : on ne peut
pas detecter ce qu'on ne comprend pas.

### Trois grandes familles d'evasion 🎯

| Technique              | But                                              | Contre-mesure defensive          |
|------------------------|--------------------------------------------------|----------------------------------|
| Obfuscation de strings | Cacher les IOC dans les binaires                 | Analyse dynamique, emulation     |
| Timing checks          | Detecter les analyses accelerees (sandboxes)     | Normalisation du temps           |
| Detection de VM        | Savoir si on tourne dans un environnement d'analyse | Masquage des artifacts VM     |

---

## Schema ASCII - Flux Normal vs Flux avec Checks d'Evasion 🏗️

```
FLUX NORMAL (sans evasion)
┌─────────────────────────────────────────┐
│ main()                                  │
│   │                                     │
│   ▼                                     │
│ Logique principale                      │
│   │                                     │
│   ▼                                     │
│ Action (connexion, lecture, etc.)       │
└─────────────────────────────────────────┘


FLUX AVEC CHECKS D'EVASION
┌─────────────────────────────────────────────────────────────────────────┐
│ main()                                                                  │
│   │                                                                     │
│   ▼                                                                     │
│ [CHECK 1] Obfuscation de strings                                        │
│   │  ├─ Strings critiques stockees XOR-encodees en memoire              │
│   │  └─ Decodage en runtime uniquement (pas de strings lisibles)        │
│   │                                                                     │
│   ▼                                                                     │
│ [CHECK 2] Timing check                                                  │
│   │  ├─ sleep(2)  ──────────────────────────────────────────┐           │
│   │  │                                                       │           │
│   │  │  Sandbox acceleree ?           Temps reel ?           │           │
│   │  │  chrono mesure < 1s  →  EXIT  chrono mesure ≥ 2s → OK│           │
│   │  └──────────────────────────────────────────────────────┘           │
│   │                                                                     │
│   ▼                                                                     │
│ [CHECK 3] Detection de VM                                               │
│   │  ├─ CPU count < 2 ?         → Suspect (VM legere)                  │
│   │  ├─ RAM < 2GB ?             → Suspect (VM minimale)                 │
│   │  ├─ Hostname contient       → Suspect ("sandbox", "malware",        │
│   │  │    des patterns suspects ?          "analysis", etc.)            │
│   │  └─ Score >= seuil         → EXIT                                   │
│   │                                                                     │
│   ▼                                                                     │
│ Environnement juge "safe" : execution de la logique principale          │
└─────────────────────────────────────────────────────────────────────────┘


TIMELINE D'ANALYSE EN SANDBOX
┌────────────────────────────────────────────────────────────────────────┐
│  t=0s    Programme lance                                               │
│  t=0.1s  Sandbox accelere le temps (10x → 1s "simulee" = 0.1s reelle) │
│  t=0.1s  Programme mesure : elapsed = 0.1s << 2s attendues → EVASION  │
│          Programme en environnement reel :                             │
│  t=0s    Programme lance                                               │
│  t=2.0s  sleep(2) s'ecoule normalement                                 │
│  t=2.0s  elapsed = 2.0s ≥ 2s → OK, on continue                        │
└────────────────────────────────────────────────────────────────────────┘
```

---

## Technique 1 - Obfuscation XOR de Strings 💻

### Pourquoi XOR ?

Les outils statiques (`strings`, YARA) lisent les strings directement dans le binaire.
XOR permet de stocker une string encodee et de la decoder **seulement en runtime** :

```
string originale  : "malicious_url"
cle XOR           : 0x42
string encodee    : stockee dans le binaire (non lisible)
decodage runtime  : str[i] ^= 0x42  → string originale reconstituee
```

```cpp
// Encoder une string avec XOR
std::string xorEncode(const std::string& input, uint8_t key) {
    std::string result = input;
    for (char& c : result) {
        c ^= key;
    }
    return result;
}

// XOR est son propre inverse : encoder deux fois = string originale
// xorEncode(xorEncode("hello", 0x42), 0x42) == "hello"
```

---

## Technique 2 - Timing Check 💻

Les sandboxes d'analyse accelerent souvent le temps pour analyser plus vite.
On peut le detecter en mesurant le temps reel ecoule apres un sleep() :

```cpp
#include <chrono>
#include <thread>

bool isSandboxAccelerated() {
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto end = std::chrono::steady_clock::now();

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
                      (end - start).count();

    // Si le temps ecoule est beaucoup plus court que prevu → sandbox
    return elapsed_ms < 1500;  // moins de 1.5s pour un sleep de 2s
}
```

---

## Technique 3 - Detection de VM (Heuristiques) 💻

```
HEURISTIQUES DE DETECTION (cross-platform)
┌─────────────────────────────────────────────────────────────────┐
│  Indicateur         │ Valeur suspecte  │ Valeur normale          │
│─────────────────────┼──────────────────┼─────────────────────────│
│  CPU count          │ < 2 cores        │ >= 2 cores              │
│  RAM totale         │ < 2 GB           │ >= 4 GB                 │
│  Hostname           │ "sandbox",       │ Nom personnel           │
│                     │ "malware",       │                         │
│                     │ "analysis",      │                         │
│                     │ "virus", etc.    │                         │
│─────────────────────┼──────────────────┼─────────────────────────│
│  Score > 2 points   │ → VM detectee    │                         │
└─────────────────────────────────────────────────────────────────┘
```

---

## Checkpoint ✅

Apres ce chapitre, tu dois savoir :
- [ ] Comment fonctionne l'encodage XOR et pourquoi il cache les strings
- [ ] Comment mesurer le temps avec `<chrono>` pour detecter les sandboxes
- [ ] Quelles heuristiques permettent de detecter un environnement d'analyse
- [ ] Pourquoi les defenseurs doivent connaitre ces techniques
- [ ] Comment les EDR/sandboxes contournent ces evasions (emulation, masquage)
