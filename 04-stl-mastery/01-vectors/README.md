# Vectors 

> Le conteneur le plus important de C++

## Pourquoi c'est important

90% des problemes LeetCode utilisent des vectors. En HFT, comprendre comment un vector gere sa memoire = optimiser tes structures de donnees critiques. En maldev, les vectors stockent tes payloads et tes buffers dynamiques. Bref, si tu maitrises pas `std::vector`, tu maitrises pas C++.

---

## C'est quoi un vector ?

Un **vector** est un tableau dynamique. Contrairement a un array C classique (`int arr[10]`), un vector :
- Gere sa propre memoire (allocation, reallocation, liberation)
- Connait sa taille (`size()`)
- Peut grandir ou retrecir a volonte
- Offre des methodes puissantes (push_back, erase, insert...)

```
Array C classique :
┌───┬───┬───┬───┬───┐
│ 1 │ 2 │ 3 │ ? │ ? │   Taille fixe a la compilation
└───┴───┴───┴───┴───┘   Pas de notion de "combien j'utilise"
     int arr[5];

Vector C++ :
┌───┬───┬───┐
│ 1 │ 2 │ 3 │      Grandit automatiquement
└───┴───┴───┘            Connait sa taille (3)
 vector<int> v = {1,2,3};
```

---

## Declaration et initialisation

```cpp
#include <vector>
using namespace std;

// Vide
vector<int> v1;

// Avec des valeurs
vector<int> v2 = {1, 2, 3, 4, 5};

// N elements initialises a une valeur
vector<int> v3(10, 0);      // 10 zeros

// Copie d'un autre vector
vector<int> v4(v2);

// Depuis un range (iterateurs)
vector<int> v5(v2.begin(), v2.begin() + 3);  // {1, 2, 3}
```

---

## Methodes essentielles

| Methode           | Description                          | Complexite |
|-------------------|--------------------------------------|------------|
| `push_back(val)`  | Ajoute a la fin                      | O(1) amorti |
| `pop_back()`      | Supprime le dernier                  | O(1)       |
| `size()`          | Nombre d'elements                    | O(1)       |
| `empty()`         | True si vide                         | O(1)       |
| `clear()`         | Supprime tout                        | O(n)       |
| `at(i)`           | Acces avec verif de bornes           | O(1)       |
| `v[i]`            | Acces direct (pas de verif)          | O(1)       |
| `front()`         | Premier element                      | O(1)       |
| `back()`          | Dernier element                      | O(1)       |
| `begin()`         | Iterateur vers le debut              | O(1)       |
| `end()`           | Iterateur apres le dernier           | O(1)       |
| `insert(pos,val)` | Insere a une position                | O(n)       |
| `erase(pos)`      | Supprime a une position              | O(n)       |
| `resize(n)`       | Change la taille                     | O(n)       |
| `reserve(n)`      | Pre-alloue de la capacite            | O(n)       |
| `shrink_to_fit()` | Reduit la capacite a size            | O(n)       |

---

## Size vs Capacity — CRUCIAL pour la perf 

C'est LA distinction que 90% des devs C++ ne comprennent pas.

```
size     = combien d'elements tu utilises
capacity = combien d'elements le vector PEUT contenir sans reallouer

Exemple apres push_back de 5 elements :

              size = 5
              ┌─────────────────┐
              v                 v
┌───┬───┬───┬───┬───┬───┬───┬───┐
│ 1 │ 2 │ 3 │ 4 │ 5 │   │   │   │   memoire allouee
└───┴───┴───┴───┴───┴───┴───┴───┘
                          ^       ^
                          └───────┘
                        capacity = 8
                   (espace reserve mais vide)
```

### Que se passe-t-il quand capacity est depassee ?

```
AVANT : capacity = 4, size = 4 (PLEIN)
┌───┬───┬───┬───┐
│ A │ B │ C │ D │
└───┴───┴───┴───┘
        
   push_back('E')
        
ETAPE 1 : Allouer un nouveau bloc 2x plus grand
┌───┬───┬───┬───┬───┬───┬───┬───┐
│   │   │   │   │   │   │   │   │  (nouveau bloc, capacity = 8)
└───┴───┴───┴───┴───┴───┴───┴───┘

ETAPE 2 : Copier tous les elements
┌───┬───┬───┬───┬───┬───┬───┬───┐
│ A │ B │ C │ D │   │   │   │   │   copie de l'ancien bloc
└───┴───┴───┴───┴───┴───┴───┴───┘

ETAPE 3 : Ajouter le nouvel element
┌───┬───┬───┬───┬───┬───┬───┬───┐
│ A │ B │ C │ D │ E │   │   │   │  size=5, capacity=8
└───┴───┴───┴───┴───┴───┴───┴───┘

ETAPE 4 : Liberer l'ancien bloc
┌───┬───┬───┬───┐
│ X │ X │ X │ X │   FREE (memoire rendue au systeme)
└───┴───┴───┴───┘
```

**Pourquoi c'est important :**
- La reallocation copie TOUT le vector = **O(n)**
- Si tu fais 1 million de push_back sans reserve(), tu forces des dizaines de reallocations
- En HFT, une seule reallocation au mauvais moment = latence inacceptable

### reserve() et shrink_to_fit()

```cpp
vector<int> v;
v.reserve(1000);    // Pre-alloue pour 1000 elements
                     // Aucune reallocation tant que size <= 1000

// Apres traitement, si tu n'utilises que 50 elements :
v.shrink_to_fit();  // Reduit capacity pour matcher size
                     // Libere la memoire inutilisee
```

---

## Structure interne d'un vector

```
std::vector<int> v = {10, 20, 30};

Stack (objet vector)          Heap (donnees)
┌──────────────────┐          ┌────┬────┬────┬────┐
│ _begin  ──────────┼────────│ 10 │ 20 │ 30 │    │
│ _size   = 3      │          └────┴────┴────┴────┘
│ _capacity = 4    │                         
└──────────────────┘           _begin    _begin + size
                                         _begin + capacity ── ┘

Quand le vector est detruit (sort du scope),
il appelle delete[] sur le pointeur _begin
= liberation automatique de la heap
```

---

## Iteration — 3 facons

```cpp
vector<int> v = {10, 20, 30, 40, 50};

// 1. Par index (classique)
for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}

// 2. Range-based for (moderne, prefere)
for (int val : v) {
    cout << val << " ";
}

// 3. Par reference (pour modifier)
for (int& val : v) {
    val *= 2;  // modifie directement le vector
}

// 4. Iterateurs (utile pour les algos STL)
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}
```

---

## Vector 2D (matrice)

```cpp
// Creer une matrice 3x3 remplie de zeros
vector<vector<int>> matrix(3, vector<int>(3, 0));

// Acces : matrix[ligne][colonne]
matrix[0][0] = 1;
matrix[1][1] = 5;
matrix[2][2] = 9;

// Resultat :
// 1 0 0
// 0 5 0
// 0 0 9

// Iteration d'une matrice
for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
        cout << matrix[i][j] << " ";
    }
    cout << endl;
}
```

---

## Checkpoint

Avant de passer aux exercices, reponds a ces questions :

1. Quelle est la difference entre `size()` et `capacity()` ?
2. Que se passe-t-il en memoire quand tu fais un `push_back()` sur un vector plein ?
3. Pourquoi `reserve()` est crucial en contexte haute performance ?
4. Quelle est la difference entre `v[i]` et `v.at(i)` ? Quand utiliser l'un ou l'autre ?

---

## Fichiers

| Fichier          | Description                                    |
|------------------|------------------------------------------------|
| `exercise.cpp`   | Exercices guides pour pratiquer                |
| `solution.cpp`   | Solutions completes                            |
| `challenge.cpp`  | Challenges LeetCode avec two pointers          |
