# Chapitre 14 : Recursion 🔁

## Ce que tu vas apprendre 

- Le concept de recursion (une fonction qui s'appelle elle-meme)
- Cas de base et cas recursif
- La call stack et comment elle evolue
- Stack overflow : quand ca deborde
- Binary search recursif et memoization (techniques HFT/LeetCode)

---

## C'est quoi la recursion ? 

Une fonction **recursive** est une fonction qui s'appelle elle-meme. Elle a toujours :

1. **Cas de base** : la condition d'arret (sinon boucle infinie)
2. **Cas recursif** : l'appel a soi-meme avec un probleme plus petit

```cpp
// Factorielle : n! = n * (n-1) * (n-2) * ... * 1
int factorielle(int n) {
    if (n <= 1) return 1;       // Cas de base
    return n * factorielle(n - 1);  // Cas recursif
}
```

---

## La Call Stack : visualisation 

Quand `factorielle(4)` est appelee :

```
    APPELS (empiler)                    RETOURS (depiler)

    ┌──────────────────┐                ┌──────────────────┐
    │ factorielle(1)   │   return 1    │ return 1         │  1
    ├──────────────────┤                ├──────────────────┤
    │ factorielle(2)   │   2 * f(1)   │ return 2 * 1 = 2 │  2
    ├──────────────────┤                ├──────────────────┤
    │ factorielle(3)   │   3 * f(2)   │ return 3 * 2 = 6 │  6
    ├──────────────────┤                ├──────────────────┤
    │ factorielle(4)   │   4 * f(3)   │ return 4 * 6 = 24│  24
    └──────────────────┘                └──────────────────┘

    La stack EMPILE les appels       Puis DEPILE les retours
    (du bas vers le haut)            (du haut vers le bas)
```

Chaque appel recursif cree un **stack frame** avec ses propres variables locales.

---

## Schema detaille de la call stack 

```
    factorielle(4) — Etat de la stack a chaque etape :

    Etape 1: f(4)          Etape 2: f(3)         Etape 3: f(2)         Etape 4: f(1)
    ┌──────────┐           ┌──────────┐          ┌──────────┐          ┌──────────┐
    │          │           │          │          │          │          │ f(1)     │
    │          │           │          │          │ f(2)     │          │ n=1      │
    │          │           │ f(3)     │          │ n=2      │          │ return 1 │
    │ f(4)     │           │ n=3      │          │ wait...  │          ├──────────┤
    │ n=4      │           │ wait...  │          ├──────────┤          │ f(2)     │
    │ wait...  │           ├──────────┤          │ f(3)     │          │ n=2      │
    ├──────────┤           │ f(4)     │          │ n=3      │          │ wait...  │
    │ main()   │           │ n=4      │          │ wait...  │          ├──────────┤
    └──────────┘           │ wait...  │          ├──────────┤          │ f(3)     │
                           ├──────────┤          │ f(4)     │          │ n=3      │
                           │ main()   │          │ n=4      │          ├──────────┤
                           └──────────┘          │ wait...  │          │ f(4)     │
                                                 ├──────────┤          │ n=4      │
                                                 │ main()   │          ├──────────┤
                                                 └──────────┘          │ main()   │
                                                                       └──────────┘
    La stack grandit vers le haut a chaque appel recursif.
    Trop d'appels = Stack Overflow !
```

---

## Stack Overflow 

Si tu oublies le cas de base ou si la recursion est trop profonde :

```cpp
// PAS DE CAS DE BASE  stack overflow !
int infini(int n) {
    return n * infini(n - 1);  // ne s'arrete jamais
}

// RECURSION TROP PROFONDE  stack overflow aussi
int deepRecursion(int n) {
    if (n <= 0) return 0;
    return deepRecursion(n - 1);
}
// deepRecursion(1000000)  crash (stack ~1-8 MB = ~10000-100000 frames)
```

---

## Exemples classiques 📚

### Somme de 1 a n

```cpp
int somme(int n) {
    if (n <= 0) return 0;
    return n + somme(n - 1);
}
// somme(5) = 5 + 4 + 3 + 2 + 1 + 0 = 15
```

### Puissance

```cpp
int puissance(int base, int exp) {
    if (exp == 0) return 1;
    return base * puissance(base, exp - 1);
}
// puissance(2, 5) = 32
```

### Compter les chiffres

```cpp
int nbChiffres(int n) {
    if (n < 10) return 1;
    return 1 + nbChiffres(n / 10);
}
// nbChiffres(12345) = 5
```

---

## Recursion vs Iteration 

| Aspect          | Recursion                      | Iteration (boucle)            |
|-----------------|--------------------------------|-------------------------------|
| Lisibilite      | Elegante pour certains algos   | Plus directe                  |
| Performance     | Overhead de la stack           | Generalement plus rapide      |
| Memoire         | O(n) stack frames              | O(1) (une seule frame)        |
| Risque          | Stack overflow                 | Boucle infinie (mais pas UB)  |
| Cas d'usage     | Trees, divide & conquer, DFS   | Parcours simples, iteration   |

**En HFT** : on evite la recursion en hot path (trop de stack frames = lent). On la remplace par de l'iteration + stack explicite.

---

## Points cles a retenir 

1. Recursion = une fonction qui s'appelle elle-meme
2. **Cas de base** obligatoire (sinon stack overflow)
3. Chaque appel cree un **stack frame** (memoire + temps)
4. La recursion est elegante mais couteuse en memoire
5. Pour la performance : prefere l'iteration ou la memoization
6. Cas d'usage ideaux : arbres, graphes, divide & conquer

---

## Compilation 

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
g++ -std=c++17 -Wall -Wextra -O2 -o challenge challenge.cpp && ./challenge
```
