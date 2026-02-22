# Chapitre 10 : Passage par Valeur vs par Reference 🔄

## Ce que tu vas apprendre 🎯

- La difference entre passage par valeur et par reference
- L'operateur `&` dans les parametres de fonctions
- `const&` pour la performance sans risque de modification
- Quand utiliser quoi (et pourquoi ca compte en HFT)

---

## Passage par valeur : la copie 📋

Par defaut, C++ **copie** la variable quand tu la passes a une fonction. La fonction travaille sur sa propre copie — l'original ne bouge pas.

```
    PASSAGE PAR VALEUR
    ┌─────────────────┐         ┌─────────────────┐
    │   main()        │         │   doubler(x)    │
    │                 │  COPIE  │                  │
    │   age = 25      │ ──────► │   x = 25        │
    │                 │         │   x = x * 2     │
    │   age = 25 ✓    │         │   x = 50        │
    │   (inchange)    │         │   (copie locale) │
    └─────────────────┘         └─────────────────┘
```

```cpp
void doubler(int x) {    // x est une COPIE
    x = x * 2;           // modifie la copie
    cout << "Dans doubler : " << x << endl;  // 50
}

int main() {
    int age = 25;
    doubler(age);
    cout << "Dans main : " << age << endl;   // 25 (inchange!)
}
```

---

## Passage par reference : l'original 🎯

Avec `&`, tu passes **l'adresse** de la variable. La fonction modifie directement l'original.

```
    PASSAGE PAR REFERENCE
    ┌─────────────────┐         ┌─────────────────┐
    │   main()        │         │   doubler(x)    │
    │                 │  REF    │                  │
    │   age = 25      │◄──────► │   x → age       │
    │                 │         │   x = x * 2     │
    │   age = 50 ✓    │         │   (modifie      │
    │   (modifie!)    │         │    l'original)   │
    └─────────────────┘         └─────────────────┘
```

```cpp
void doubler(int& x) {   // x est une REFERENCE a l'original
    x = x * 2;           // modifie l'original !
    cout << "Dans doubler : " << x << endl;  // 50
}

int main() {
    int age = 25;
    doubler(age);
    cout << "Dans main : " << age << endl;   // 50 (modifie!)
}
```

---

## Visualisation de la stack 🏗️

```
    PASSAGE PAR VALEUR               PASSAGE PAR REFERENCE
    ┌──────────────────┐             ┌──────────────────┐
    │ Stack Frame:     │             │ Stack Frame:     │
    │ doubler()        │             │ doubler()        │
    │ ┌──────────────┐ │             │ ┌──────────────┐ │
    │ │ x = 25 (copy)│ │             │ │ x → 0x7FF004 │─┼──┐
    │ └──────────────┘ │             │ └──────────────┘ │  │
    ├──────────────────┤             ├──────────────────┤  │
    │ Stack Frame:     │             │ Stack Frame:     │  │
    │ main()           │             │ main()           │  │
    │ ┌──────────────┐ │             │ ┌──────────────┐ │  │
    │ │ age = 25     │ │             │ │ age = 25     │◄┼──┘
    │ │ @ 0x7FF004   │ │             │ │ @ 0x7FF004   │ │
    │ └──────────────┘ │             │ └──────────────┘ │
    └──────────────────┘             └──────────────────┘
      2 copies en memoire              1 seule donnee
```

---

## const& : le meilleur des deux mondes 🛡️

`const&` passe par reference (pas de copie = rapide) mais interdit la modification (securite).

```cpp
// MAUVAIS : copie un struct de 200 octets pour rien
void afficher(MarketData data) {
    cout << data.price << endl;
}

// BON : zero copie, zero risque
void afficher(const MarketData& data) {
    cout << data.price << endl;
    // data.price = 0;  // ERREUR : const empeche la modification
}
```

---

## Quand utiliser quoi ? 📊

| Situation                          | Utilise              | Pourquoi                               |
|------------------------------------|----------------------|----------------------------------------|
| Type primitif (int, char, bool)    | Valeur               | Copie = 4-8 octets, trivial            |
| Lire un gros objet                 | `const&`             | Pas de copie, pas de modification      |
| Modifier l'original                | `&`                  | Reference directe                      |
| Fonction swap / echange            | `&`                  | Doit modifier les deux variables       |

**Regle HFT** : tout struct/class passe en `const&` par defaut. Pas de copie inutile.

---

## Swap : l'exemple classique 🔄

```cpp
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;
    swap(x, y);
    cout << x << " " << y << endl;  // 20 10
}
```

Sans reference, `swap` copierait les valeurs et ne changerait rien dans `main`.

---

## Multiple retours avec des references 📤

Les references permettent a une fonction de "retourner" plusieurs valeurs :

```cpp
void minMax(const int arr[], int size, int& min, int& max) {
    min = max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
}

int main() {
    int data[] = {5, 2, 8, 1, 9};
    int minimum, maximum;
    minMax(data, 5, minimum, maximum);
    cout << "Min: " << minimum << " Max: " << maximum << endl;
}
```

---

## Points cles a retenir 🔑

1. **Par valeur** : la fonction recoit une copie (l'original est safe)
2. **Par reference `&`** : la fonction modifie l'original directement
3. **`const&`** : reference en lecture seule = performance + securite
4. Types primitifs → par valeur. Structs/objets → par `const&`
5. Utilise `&` quand tu veux modifier l'original (swap, out-params)

---

## Compilation 🔧

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
g++ -std=c++17 -Wall -Wextra -O2 -o challenge challenge.cpp && ./challenge
```
