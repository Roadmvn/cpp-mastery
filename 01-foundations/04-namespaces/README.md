# Namespaces 

## Pourquoi c'est important

Dans un projet HFT avec des milliers de lignes de code, tu vas avoir des fonctions
qui s'appellent pareil dans differents modules. `getPrice()` dans le module market ?
`getPrice()` dans le module order ? Sans namespaces, le compilateur ne sait pas lequel
tu veux. Collision. Erreur. Projet mort.

En maldev, tu vois des namespaces partout dans le Windows SDK. Comprendre comment ils
fonctionnent, c'est comprendre comment le code pro est organise.

---

## C'est quoi un namespace ?

Un **namespace** (espace de noms), c'est une boite qui regroupe du code sous un meme nom.
Ca permet d'avoir des fonctions ou variables avec le meme nom sans conflit.

Pense a ca comme des dossiers sur ton bureau : tu peux avoir un fichier `notes.txt`
dans le dossier `travail/` et un autre `notes.txt` dans le dossier `perso/`. Pas de conflit
parce qu'ils sont dans des espaces differents.

```
  Namespace "hft"                    Namespace "security"
 ┌───────────────────┐              ┌───────────────────┐
 │                   │              │                   │
 │  getPrice()       │              │  getPrice()       │
 │  sendOrder()      │              │  scanPort()       │
 │  checkLatency()   │              │  checkAccess()    │
 │                   │              │                   │
 └───────────────────┘              └───────────────────┘
         │                                   │
         │                                   │
         ▼                                   ▼
   hft::getPrice()                  security::getPrice()
                    PAS DE CONFLIT !
```

L'operateur `::` s'appelle l'**operateur de resolution de portee** (scope resolution operator).
C'est lui qui dit "va chercher dans CE namespace".

---

## "using namespace std" -- pratique mais dangereux

Tu as vu `using namespace std;` dans les chapitres precedents. Ca permet d'ecrire
`cout` au lieu de `std::cout`. Pratique pour un petit programme.

**Mais dans un gros projet, c'est dangereux.** Pourquoi ? Parce que `std` contient
des centaines de noms. Si tu crees une fonction `count()` ou `find()`, ca entre en
conflit avec `std::count()` ou `std::find()`.

```cpp
// PETIT programme de test -- OK
using namespace std;
cout << "Hello" << endl;

// GROS projet / code pro -- PREFERE ca :
std::cout << "Hello" << std::endl;
```

**Regle simple :**
- Exercices et petits programmes : `using namespace std;` c'est OK
- Projet serieux, headers (.h) : TOUJOURS utiliser `std::`

---

## Creer son propre namespace

```cpp
#include <iostream>
#include <string>

// Namespace pour le trading haute frequence
namespace hft {
    double getPrice() {
        return 42567.89;  // Prix simule du BTC
    }

    void sendOrder(std::string type, double price) {
        std::cout << "[HFT] Ordre " << type << " a " << price << " USD" << std::endl;
    }
}

// Namespace pour la securite
namespace security {
    double getPrice() {
        return 0.0;  // Pas le meme contexte !
    }

    void scanTarget(std::string target) {
        std::cout << "[SEC] Scan de " << target << "..." << std::endl;
    }
}

int main() {
    // On utilise :: pour preciser quel namespace
    double btc_price = hft::getPrice();          // 42567.89
    double sec_price = security::getPrice();      // 0.0

    std::cout << "Prix HFT : " << btc_price << std::endl;
    std::cout << "Prix SEC : " << sec_price << std::endl;

    hft::sendOrder("BUY", btc_price);
    security::scanTarget("192.168.1.1");

    return 0;
}
```

Les deux `getPrice()` coexistent sans probleme grace aux namespaces.

---

## Namespaces imbriques

Tu peux mettre un namespace dans un autre. C'est courant dans les gros projets
pour organiser le code en hierarchie.

```cpp
namespace company {
    namespace trading {
        namespace utils {
            int calculate(int a, int b) {
                return a + b;
            }
        }
    }
}

int main() {
    // Appel complet
    int result = company::trading::utils::calculate(10, 20);

    return 0;
}
```

C'est comme un chemin de dossiers : `company/trading/utils/calculate`.

---

## Raccourci avec "using"

Si tu utilises beaucoup un namespace specifique, tu peux creer un raccourci :

```cpp
// Importer UNE fonction specifique
using hft::getPrice;
double p = getPrice();  // OK, on sait que c'est hft::getPrice

// Importer tout un namespace (a eviter en gros projet)
using namespace hft;
sendOrder("SELL", 100.0);

// Alias de namespace (utile pour les noms longs)
namespace ctu = company::trading::utils;
int r = ctu::calculate(5, 10);
```

---

## Checkpoint 

Avant de passer aux exercices, assure-toi de savoir repondre :

1. **A quoi sert un namespace ?**
   > A regrouper du code sous un meme nom pour eviter les collisions de noms entre differentes parties du programme.

2. **Pourquoi "using namespace std" est deconseille dans les gros projets ?**
   > Parce que ca importe des centaines de noms dans la portee globale, ce qui peut creer des conflits avec tes propres fonctions ou variables.

3. **Comment appeler une fonction `run()` dans le namespace `tools::scanner` ?**
   > `tools::scanner::run();`

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 
