# Lambdas et fonctions d'ordre superieur 🎛

> Fonctions anonymes a la volee — le sucre syntaxique le plus puissant de C++11

## Pourquoi c'est important

Les lambdas transforment radicalement la facon d'utiliser les algorithmes STL. Au lieu de definir des foncteurs separement, tu ecris la logique directement ou elle est utilisee. En competitive programming, les lambdas te permettent des comparateurs custom pour `sort`, des predicats pour `find_if`, et des reduceurs pour `accumulate` — tout en une ligne lisible.

---

## Anatomie d'une lambda

```
[ captures ] ( parametres ) -> type_retour { corps }
      |             |               |           |
      |             |               |           +-- Code a executer
      |             |               +-- optionnel si deductible
      |             +-- Comme une fonction normale
      +-- Acces aux variables locales environnantes

EXEMPLES :
[](){}                              // lambda minimale (rien)
[](int x){ return x * 2; }         // doubler un entier
[](int a, int b){ return a < b; }  // comparateur
[x](){ return x + 1; }            // capture x par valeur
[&x](){ x++; }                    // capture x par reference
[=](){ return x + y; }            // capture tout par valeur
[&](){ x++; y++; }                // capture tout par reference
[x, &y](){}                       // mix : x par valeur, y par ref
```

---

## Captures en detail

```
CAPTURE PAR VALEUR [x] :
┌──────────────────────────────────────────┐
│  Variable locale x = 10                 │
│                  │                       │
│          COPIE au moment de              │
│          la creation de la lambda        │
│                  │                       │
│          [x]{ return x + 1; }           │
│                                         │
│          x copie = 10 (immutable)        │
│          Modifier x ici = ERREUR         │
│          (sauf si mutable)               │
└──────────────────────────────────────────┘

CAPTURE PAR REFERENCE [&x] :
┌──────────────────────────────────────────┐
│  Variable locale x = 10                 │
│                  │                       │
│          REFERENCE directe               │
│          (acces en lecture/ecriture)     │
│                  │                       │
│          [&x]{ x++; }                   │
│                                         │
│          x original modifie !            │
│          ATTENTION : duree de vie !      │
│          Si lambda outlive x => UB       │
└──────────────────────────────────────────┘

RESUME DES MODES :
[]          pas de capture
[=]         tout par valeur (copie au moment de creation)
[&]         tout par reference
[x, y]      x et y par valeur
[&x, &y]    x et y par reference
[=, &x]     tout par valeur sauf x par reference
[this]      capturer le pointeur this (dans une methode)
```

---

## mutable : modifier une capture par valeur

```cpp
int x = 10;

// Sans mutable : x est const dans la lambda, erreur de compilation
// auto f = [x](){ x++; return x; };  // ERREUR

// Avec mutable : la COPIE de x peut etre modifiee (pas l'original)
auto f = [x]() mutable { x++; return x; };

cout << f();  // 11 (copie modifiee)
cout << x;    // 10 (original inchange)
```

---

## std::function : stocker une lambda

```cpp
#include <functional>

// std::function<ReturnType(ParamTypes...)>
function<int(int)> doubler = [](int x) { return x * 2; };
function<bool(int, int)> cmp = [](int a, int b) { return a < b; };

// Utilisation dans un vecteur de fonctions
vector<function<int(int)>> ops = {
    [](int x) { return x + 1; },
    [](int x) { return x * 2; },
    [](int x) { return x * x; }
};

for (auto& op : ops) {
    cout << op(5) << " ";  // 6 10 25
}

// ATTENTION : std::function a un overhead (type erasure).
// Preferer auto pour les lambdas directes quand possible.
```

---

## Lambdas avec les algorithmes STL

```cpp
vector<int> v = {5, 2, 8, 1, 9, 3};

// sort avec comparateur custom (decroissant)
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
// v = {9, 8, 5, 3, 2, 1}

// find_if avec predicat
auto it = find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
// *it = 8 (premier pair)

// count_if
int pairs = count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });

// for_each (attention : preferer range-for en general)
for_each(v.begin(), v.end(), [](int& x) { x *= 2; });

// transform
vector<int> squared;
transform(v.begin(), v.end(), back_inserter(squared),
          [](int x) { return x * x; });

// accumulate avec lambda
int prod = accumulate(v.begin(), v.end(), 1,
                      [](int acc, int x) { return acc * x; });
```

---

## Patterns LeetCode avec lambdas 

### Trier des structures complexes

```cpp
struct Student { string name; int grade; int age; };
vector<Student> students = { {"Alice", 90, 20}, {"Bob", 85, 22}, {"Charlie", 90, 19} };

// Trier par note decroissante, puis par age croissant a egalite
sort(students.begin(), students.end(),
    [](const Student& a, const Student& b) {
        if (a.grade != b.grade) return a.grade > b.grade;
        return a.age < b.age;
    }
);
```

### Comparateur custom pour priority_queue

```cpp
// Min-heap par default -> max-heap avec lambda
auto cmp = [](int a, int b) { return a > b; };  // inverser l'ordre
priority_queue<int, vector<int>, decltype(cmp)> minHeap(cmp);
```

### Lambda recursive avec std::function

```cpp
// Fibonacci avec lambda recursive
function<int(int)> fib = [&](int n) -> int {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
};
```

---

## Complexites a retenir 

| Usage                         | Overhead lambda  | Notes                          |
|------------------------------|------------------|--------------------------------|
| Comparateur pour sort         | ~0               | Inline par le compilateur      |
| Predicat pour find_if         | ~0               | Inline par le compilateur      |
| std::function wrapping        | O(1) mais reel   | Type erasure = overhead        |
| Capture par valeur            | Copie au debut   | Pas de copie a chaque appel    |
| Capture par reference         | Acces direct     | Attention duree de vie !       |

---

## Quand utiliser les lambdas 

| Besoin                                    | Solution                              |
|------------------------------------------|---------------------------------------|
| Tri par critere custom                   | lambda dans sort                      |
| Filtrer avec une condition               | lambda dans find_if / count_if        |
| Transformer des elements                 | lambda dans transform                 |
| Accumuler avec une operation custom      | lambda dans accumulate                |
| Stocker une fonction pour plus tard      | std::function                         |
| Callback d'evenement                     | std::function ou lambda direct        |
| Priority queue custom                    | lambda + decltype(cmp)                |

---

## Checkpoint

1. Quelle est la difference entre `[x]` et `[&x]` ?
2. Pourquoi `[x]{ x++; }` est-il une erreur de compilation ?
3. Quand utiliser `std::function` plutot que `auto` ?
4. Comment capturer `this` dans une methode de classe ?

---

## Fichiers

| Fichier          | Description                                              |
|------------------|----------------------------------------------------------|
| `exercise.cpp`   | Exercices guides : syntaxe, captures, STL + lambdas      |
| `solution.cpp`   | Solutions completes                                      |
| `challenge.cpp`  | Challenge : tri de structures complexes (prix + timestamp) |
