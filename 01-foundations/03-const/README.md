# Const & Constantes 

## Pourquoi c'est important

En HFT, les constantes permettent au compilateur d'optimiser a mort. Si le compilateur sait
qu'une valeur ne changera JAMAIS, il peut la remplacer directement dans le code machine
au lieu d'aller la chercher en memoire a chaque fois. Ca, c'est des nanosecondes gagnees.

En securite, modifier une constante en memoire est une technique d'exploitation classique.
Comprendre comment `const` fonctionne, c'est comprendre ce que l'attaquant essaie de contourner.

---

## Le mot-cle const

`const` rend une variable **en lecture seule**. Une fois initialisee, tu ne peux plus la modifier.

```cpp
const double PI = 3.14159265358979;
const int PORT_SSH = 22;
const string NOM_SERVEUR = "prod-hft-01";

PI = 3.14;  // ERREUR DE COMPILATION : assignment of read-only variable
```

Le compilateur te protege. Si tu essaies de modifier une constante, il refuse de compiler.

---

## const vs #define

Deux facons de definir une constante en C++ :

```
 ┌─────────────────────────────────────────────────────────────────┐
 │                    const vs #define                              │
 ├──────────────────────┬──────────────────────────────────────────┤
 │  #define PI 3.14     │  Remplacement de texte par le           │
 │                      │  preprocesseur AVANT la compilation.     │
 │                      │  Pas de type, pas de scope, pas de       │
 │                      │  verification. C'est du copier-coller.   │
 ├──────────────────────┼──────────────────────────────────────────┤
 │  const double PI     │  Vraie variable typee, scopee,           │
 │       = 3.14;        │  verifiee par le compilateur.            │
 │                      │  Visible dans le debugger.               │
 │                      │  C'est la methode C++ moderne.           │
 └──────────────────────┴──────────────────────────────────────────┘
```

**Regle** : En C++, utilise toujours `const` (ou `constexpr`). Laisse `#define` au C.

---

## constexpr : la constante ultime (C++11)

`constexpr` va encore plus loin que `const`. Ca garantit que la valeur est calculee
**a la compilation**, pas a l'execution.

```cpp
constexpr int TAILLE_BUFFER = 1024;
constexpr double FRAIS = 0.001;
constexpr int DOUBLE_BUFFER = TAILLE_BUFFER * 2;  // Calcule a la compilation !
```

### Difference entre const et constexpr

```cpp
const int a = 42;           // Peut etre calcule a la compilation OU a l'execution
constexpr int b = 42;       // GARANTI calcule a la compilation

int x;
cin >> x;
const int c = x;            // OK : const peut prendre une valeur runtime
// constexpr int d = x;     // ERREUR : constexpr exige une valeur connue a la compilation
```

En resume :
- `const` = "je promets de ne pas modifier cette variable"
- `constexpr` = "cette valeur est connue des la compilation"

---

## Convention de nommage

Les constantes se nomment en **SCREAMING_SNAKE_CASE** par convention :

```cpp
const int MAX_CONNEXIONS = 100;
const double TAUX_TVA = 0.20;
const string NOM_APPLICATION = "TradingBot_v2";
constexpr int TIMEOUT_MS = 5000;
constexpr int PORT_MIN = 1;
constexpr int PORT_MAX = 65535;
```

Ca permet de les reperer immediatement dans le code. Quand tu vois `MAX_CONNEXIONS`,
tu sais direct que c'est une constante sans aller chercher sa declaration.

---

## Exemple complet

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Constantes avec const
    const double PI = 3.14159265358979;
    const string VERSION = "1.0.0";
    const int MAX_TENTATIVES = 3;

    // Constantes avec constexpr (evaluees a la compilation)
    constexpr int TAILLE_TABLEAU = 256;
    constexpr double FRAIS_TRANSACTION = 0.0015;
    constexpr int OCTETS_PAR_KO = 1024;
    constexpr int OCTETS_PAR_MO = OCTETS_PAR_KO * 1024;

    cout << "PI                : " << PI << endl;
    cout << "Version           : " << VERSION << endl;
    cout << "Max tentatives    : " << MAX_TENTATIVES << endl;
    cout << "Taille tableau    : " << TAILLE_TABLEAU << endl;
    cout << "Frais transaction : " << FRAIS_TRANSACTION * 100 << "%" << endl;
    cout << "1 Mo              : " << OCTETS_PAR_MO << " octets" << endl;

    return 0;
}
```

---

## Checkpoint 

1. **Quelle est la difference entre `const` et `constexpr` ?**
   > `const` promet que la variable ne sera pas modifiee apres initialisation (mais la valeur peut venir du runtime). `constexpr` garantit que la valeur est calculee a la compilation.

2. **Pourquoi preferer `const` a `#define` en C++ ?**
   > `const` est type, scope et verifie par le compilateur. `#define` est un simple remplacement de texte sans verification, qui peut causer des bugs subtils.

3. **Quelle convention de nommage pour les constantes ?**
   > SCREAMING_SNAKE_CASE (tout en majuscules, mots separes par des underscores). Exemple : `MAX_CONNEXIONS`, `PORT_SSH`.

---

Passe aux exercices dans `exercise.cpp`. 
