# Map et Set ordonnes 🌳

> Arbres rouge-noir — ordre garanti, O(log n) partout, puissants pour les range queries

## Pourquoi c'est important

`map` et `set` sont les conteneurs ordonnes de la STL. Contrairement a leurs versions `unordered_*`, ils garantissent un **ordre lexicographique** sur les cles. Cela ouvre des possibilites impossibles avec une hash table : trouver le plus petit element >= X, iterer dans l'ordre, faire des range queries... En competitive programming, `set` avec `lower_bound` remplace souvent des structures de donnees complexes.

---

## Structure interne : Arbre Rouge-Noir

```
set<int> s = {5, 3, 8, 1, 4, 7, 9};

Arbre Rouge-Noir interne (B=Noir, R=Rouge) :
                  5(B)
                /      \
            3(R)          8(R)
           /    \        /    \
         1(B)  4(B)   7(B)   9(B)

Proprietes :
- Chaque noeud est Rouge ou Noir
- La racine est toujours Noire
- Pas deux noeuds Rouges consecutifs
- Meme nombre de noeuds Noirs sur tout chemin vers une feuille
- Ces regles garantissent hauteur <= 2*log2(n)
  => toutes les operations sont O(log n) garanti

Iteration in-order = elements tries :
1 -> 3 -> 4 -> 5 -> 7 -> 8 -> 9
```

---

## map vs set

```
map<int, string>             set<int>
┌──────┬────────┐            ┌──────┐
│  cle │ valeur │            │  cle │
├──────┼────────┤            ├──────┤
│   1  │ "un"   │            │   1  │
│   3  │ "trois"│            │   3  │
│   5  │ "cinq" │            │   5  │
└──────┴────────┘            └──────┘

map = dictionnaire ordonne      set = ensemble ordonne
      "quelle valeur pour X ?"        "X existe-t-il ?"
```

---

## Methodes essentielles

### map<K,V>

| Methode                   | Description                          | Complexite |
|--------------------------|--------------------------------------|------------|
| `m[key]`                  | Acces/creation                       | O(log n)   |
| `m.insert({k,v})`         | Insere si absent                     | O(log n)   |
| `m.find(key)`             | Iterateur (ou end)                   | O(log n)   |
| `m.count(key)`            | 0 ou 1                              | O(log n)   |
| `m.erase(key)`            | Supprime par cle                     | O(log n)   |
| `m.lower_bound(key)`      | Premier element >= key               | O(log n)   |
| `m.upper_bound(key)`      | Premier element > key                | O(log n)   |
| `m.begin() / m.end()`     | Iterateurs (ordre croissant)         | O(1)       |

### set<T>

| Methode                   | Description                          | Complexite |
|--------------------------|--------------------------------------|------------|
| `s.insert(x)`             | Insere (ignore si present)           | O(log n)   |
| `s.find(x)`               | Iterateur (ou end)                   | O(log n)   |
| `s.count(x)`              | 0 ou 1                              | O(log n)   |
| `s.erase(x)`              | Supprime x                           | O(log n)   |
| `s.lower_bound(x)`        | Premier element >= x                 | O(log n)   |
| `s.upper_bound(x)`        | Premier element > x                  | O(log n)   |
| `*s.begin()`              | Plus petit element                   | O(1)       |
| `*s.rbegin()`             | Plus grand element                   | O(1)       |

---

## lower_bound et upper_bound : la puissance des conteneurs ordonnes

```cpp
set<int> s = {1, 3, 5, 7, 9};

// lower_bound(x) : premier element >= x
auto it1 = s.lower_bound(4);   // pointe sur 5
auto it2 = s.lower_bound(5);   // pointe sur 5 (inclus)
auto it3 = s.lower_bound(10);  // pointe sur end()

// upper_bound(x) : premier element > x
auto it4 = s.upper_bound(5);   // pointe sur 7 (exclu)
auto it5 = s.upper_bound(9);   // pointe sur end()

// Range [3, 7] inclusive :
auto lo = s.lower_bound(3);    // pointe sur 3
auto hi = s.upper_bound(7);    // pointe sur 9
for (auto it = lo; it != hi; ++it) {
    cout << *it << " ";  // 3 5 7
}
```

---

## Patterns LeetCode avec set ordonne 🏆

### Sliding window minimum/maximum

```cpp
// Maintenir un set ordonne dans une fenetre glissante
multiset<int> window;
for (int i = 0; i < k; i++) window.insert(nums[i]);
result.push_back(*window.begin());  // minimum

for (int i = k; i < n; i++) {
    window.erase(window.find(nums[i - k]));  // supprimer l'ancien
    window.insert(nums[i]);                  // ajouter le nouveau
    result.push_back(*window.begin());
}
```

### Trouver le successeur d'un element

```cpp
set<int> s = {1, 3, 5, 7};
int x = 4;
auto it = s.lower_bound(x);
if (it != s.end()) {
    cout << "Successeur de " << x << " : " << *it;  // 5
}
```

### Compter les elements dans un intervalle

```cpp
set<int> s = {1, 2, 3, 5, 7, 8, 10};
// Compter les elements dans [3, 7]
auto lo = s.lower_bound(3);
auto hi = s.upper_bound(7);
int count = distance(lo, hi);  // 3 (elements: 3, 5, 7)
```

---

## multiset : doublons autorises

```cpp
multiset<int> ms = {3, 1, 4, 1, 5, 9, 2, 6, 5};
// Iteration : 1 1 2 3 4 5 5 6 9

ms.erase(ms.find(1));  // supprimer UNE occurrence de 1
ms.erase(1);           // supprimer TOUTES les occurrences de 1
```

---

## map vs unordered_map : choisir le bon outil

| Critere                        | map (ordonne)    | unordered_map    |
|-------------------------------|------------------|------------------|
| Complexite                     | O(log n)         | O(1) moyenne     |
| Ordre des cles garanti         | OUI              | NON              |
| lower_bound / upper_bound      | OUI              | NON              |
| Range queries                  | OUI              | NON              |
| Memoire                        | Plus elevee      | Plus faible      |
| Hash collisions                | N/A              | Possible         |

---

## Complexites a retenir 📋

| Operation               | map/set  | unordered_map/set |
|------------------------|----------|-------------------|
| Insert / Find / Erase   | O(log n) | O(1) moy / O(n) pire |
| lower_bound/upper_bound | O(log n) | N/A               |
| Iteration ordonnee      | O(n)     | O(n) mais non ordonne |
| Min / Max               | O(1)     | O(n)              |

---

## Quand utiliser map/set ordonne 🎯

| Signal dans l'enonce                        | Pattern                         |
|--------------------------------------------|---------------------------------|
| "K-eme plus petit / plus grand"             | set + iterateurs                |
| "Elements dans un intervalle [L, R]"        | lower_bound + upper_bound       |
| "Suivant / predecesseur d'un element"       | lower_bound / upper_bound       |
| "Fenetre glissante avec min/max dynamique"  | multiset                        |
| "Compter les inversions"                    | Merge sort ou policy-based tree |
| "Ordre alphabetique garanti"               | map ordonne                     |

---

## Checkpoint

1. Pourquoi `map` garantit-il l'ordre alors que `unordered_map` ne le fait pas ?
2. Que retourne `lower_bound(x)` si x n'existe pas dans le set ?
3. Quelle est la difference entre `erase(it)` et `erase(val)` sur un multiset ?
4. Comment trouver le maximum d'un set en O(1) ?

---

## Fichiers

| Fichier          | Description                                        |
|------------------|----------------------------------------------------|
| `exercise.cpp`   | Exercices guides : map, set, lower/upper_bound     |
| `solution.cpp`   | Solutions completes                                |
| `challenge.cpp`  | Challenge : range queries et sliding window        |
