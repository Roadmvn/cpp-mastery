# Typedef & Aliases 🏷️

## Pourquoi c'est important

En HFT, on cree des alias comme `Price`, `Quantity`, `OrderId` pour rendre le code
lisible et eviter les erreurs. Quand tu lis `Price amount = 42567.89;` c'est plus
clair que `double amount = 42567.89;`. Tu sais immediatement que c'est un prix.

En maldev, les API Windows utilisent des tonnes de typedef. `DWORD`, `HANDLE`, `LPVOID`,
`BOOL`... Ce sont tous des alias vers des types C basiques. Si tu comprends pas les
typedef, tu peux pas lire le code Windows.

---

## C'est quoi un alias de type ?

Un **alias de type**, c'est un nouveau nom pour un type existant. Le type ne change pas,
seul le nom est different. C'est comme un surnom : "William" et "Will" designent la meme personne.

```
  Alias                      Type reel
 ┌────────────────┐         ┌────────────────┐
 │  Price          │ ──────> │  double         │
 │  Quantity       │ ──────> │  int            │
 │  OrderId        │ ──────> │  uint64_t       │
 │  Symbol         │ ──────> │  std::string    │
 └────────────────┘         └────────────────┘
       HFT

 ┌────────────────┐         ┌────────────────┐
 │  DWORD          │ ──────> │  unsigned long  │
 │  HANDLE         │ ──────> │  void*          │
 │  BOOL           │ ──────> │  int            │
 │  LPSTR          │ ──────> │  char*          │
 └────────────────┘         └────────────────┘
     Windows API
```

---

## typedef -- L'ancien style (C)

`typedef` vient du langage C. Ca marche toujours en C++ mais c'est l'ancienne facon de faire.

```cpp
// Syntaxe : typedef type_existant nouveau_nom;
typedef unsigned long DWORD;
typedef int BOOL;
typedef char* LPSTR;
typedef double Price;

// Utilisation -- exactement comme le type original
DWORD process_id = 1234;
BOOL is_running = 1;       // 1 = true, 0 = false (style C)
Price btc_price = 42567.89;
```

La syntaxe est un peu bizarre : le nouveau nom est a **droite**. Ca se lit comme
"definis le type `DWORD` comme etant un `unsigned long`".

---

## using = -- Le style moderne (C++11, prefere)

Depuis C++11, on utilise `using` pour creer des alias. C'est plus lisible et plus puissant.

```cpp
// Syntaxe : using nouveau_nom = type_existant;
using DWORD = unsigned long;
using BOOL = int;
using LPSTR = char*;
using Price = double;
using Quantity = int;
using OrderId = uint64_t;
using Symbol = std::string;

// Utilisation -- identique a typedef
Price btc_price = 42567.89;
Quantity lots = 10;
OrderId id = 100042;
Symbol ticker = "BTC/USD";
```

**Pourquoi preferer `using` ?**
- La syntaxe est plus naturelle : `using Price = double;` se lit comme "Price = double"
- Ca marche avec les templates (on verra ca plus tard)
- C'est le standard moderne C++11+

---

## Pourquoi creer des alias ?

### 1. Lisibilite

```cpp
// Sans alias -- qu'est-ce que ces doubles representent ?
double process_trade(double a, int b, std::string c) { ... }

// Avec alias -- tout est clair
Price process_trade(Price amount, Quantity lots, Symbol ticker) { ... }
```

### 2. Maintenabilite

Si tu decides de changer `Price` de `double` a `float` pour economiser de la memoire,
tu changes UN seul endroit :

```cpp
// Avant
using Price = double;

// Apres -- une seule ligne a modifier, tout le code s'adapte
using Price = float;
```

### 3. Abstraction

Tu caches le type reel derriere un nom qui a du sens. Si demain tu passes de
`uint64_t` a un type custom pour `OrderId`, le code appelant ne change pas.

---

## Exemple complet commente

```cpp
#include <iostream>
#include <string>
#include <cstdint>    // Pour uint64_t

// Alias pour un systeme de trading simplifie
using Price    = double;
using Quantity = int;
using OrderId  = uint64_t;
using Symbol   = std::string;

// Fonction qui utilise les alias -- beaucoup plus lisible
void display_order(OrderId id, Symbol sym, Price price, Quantity qty) {
    std::cout << "Ordre #" << id << " : "
              << qty << " lots de " << sym
              << " a " << price << " USD" << std::endl;
}

int main() {
    // Les variables sont auto-documentees grace aux alias
    OrderId  order_id = 100001;
    Symbol   ticker   = "ETH/USD";
    Price    amount   = 3245.67;
    Quantity lots     = 5;

    display_order(order_id, ticker, amount, lots);

    return 0;
}
```

Sortie :
```
Ordre #100001 : 5 lots de ETH/USD a 3245.67 USD
```

---

## Checkpoint ✅

Avant de passer aux exercices, assure-toi de savoir repondre :

1. **Quelle est la difference entre `typedef` et `using` ?**
   > `typedef` est l'ancien style C (`typedef double Price;`), `using` est le style moderne C++11 (`using Price = double;`). Les deux font la meme chose, mais `using` est prefere car plus lisible et plus puissant.

2. **Pourquoi creer un alias `Price` au lieu d'utiliser `double` directement ?**
   > Pour la lisibilite (on sait que c'est un prix), la maintenabilite (un seul endroit a changer si le type evolue) et l'abstraction (on cache le type reel).

3. **Que represente `DWORD` dans l'API Windows ?**
   > C'est un alias pour `unsigned long`. DWORD signifie "Double WORD" (32 bits). C'est utilise partout dans les API Windows pour les identifiants de processus, codes d'erreur, etc.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 👊
