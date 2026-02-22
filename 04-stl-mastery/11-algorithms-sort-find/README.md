# Algorithmes STL : sort, find, transform 

> La STL comme boite a outils — resoudre en une ligne ce qui en prendrait vingt

## Pourquoi c'est important

Les algorithmes STL (`<algorithm>` et `<numeric>`) sont des briques de haut niveau ultra-optimisees. Savoir les combiner te permet d'ecrire du code concis, lisible et performant. En competitive programming, une ligne `sort` + `unique` peut remplacer 20 lignes de tri manuel. En LeetCode, `accumulate`, `count_if`, `transform` te donnent des one-liners elegants.

---

## Vue d'ensemble des algorithmes essentiels

```
<algorithm>
┌────────────────────────────────────────────────────────┐
│  TRI                                                   │
│  sort(first, last)          O(n log n) | introsort     │
│  stable_sort(first, last)   O(n log n) | preserv ordre │
│  partial_sort(f, mid, l)    O(n log mid) | top-K       │
│  nth_element(f, nth, l)     O(n)       | pivot-like    │
├────────────────────────────────────────────────────────┤
│  RECHERCHE                                             │
│  binary_search(f, l, val)   O(log n)   | existe ?      │
│  lower_bound(f, l, val)     O(log n)   | premier >= val │
│  upper_bound(f, l, val)     O(log n)   | premier > val  │
│  find(f, l, val)            O(n)       | non trie       │
│  find_if(f, l, pred)        O(n)       | avec predicat  │
├────────────────────────────────────────────────────────┤
│  COMPTAGE / CONDITION                                  │
│  count(f, l, val)           O(n)       | nombre de val  │
│  count_if(f, l, pred)       O(n)       | avec predicat  │
│  all_of(f, l, pred)         O(n)       | tous vrais ?   │
│  any_of(f, l, pred)         O(n)       | un vrai ?      │
│  none_of(f, l, pred)        O(n)       | aucun vrai ?   │
├────────────────────────────────────────────────────────┤
│  TRANSFORMATION                                        │
│  transform(f, l, out, op)   O(n)       | appliquer op   │
│  remove_if(f, l, pred)      O(n)       | erase-remove   │
│  replace_if(f, l, pred, v)  O(n)       | remplacer      │
│  unique(f, l)               O(n)       | deduplique     │
│  reverse(f, l)              O(n)       | inverser       │
│  rotate(f, mid, l)          O(n)       | rotation       │
├────────────────────────────────────────────────────────┤
│  <numeric>                                             │
│  accumulate(f, l, init)     O(n)       | somme/produit  │
│  partial_sum(f, l, out)     O(n)       | prefix sums    │
│  iota(f, l, start)          O(n)       | remplir 0..n   │
└────────────────────────────────────────────────────────┘
```

---

## sort vs stable_sort vs partial_sort vs nth_element

```
sort          : ordre quelconque des egaux, le plus rapide
                -> pour usage general
stable_sort   : preserve l'ordre relatif des egaux
                -> quand l'ordre d'egalite compte (ex: tri multi-cle)
partial_sort  : trie seulement les k premiers
                -> top-K sans trier tout
nth_element   : garantit que l'element a la position k est le bon,
                elements avant <= [k], elements apres >= [k], non tries
                -> median en O(n), partition rapide

Exemple :
nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
n = 11, chercher le 4eme plus petit (k=3)

nth_element(nums.begin(), nums.begin()+3, nums.end())
-> nums[3] = 3 (le 4eme plus petit)
   nums[0..2] tous <= 3
   nums[4..10] tous >= 3
   (mais pas forcement tries)
```

---

## Le pattern erase-remove

```cpp
// PROBLEME : remove_if ne supprime pas vraiment !
// Il deplace les elements "gardes" au debut et retourne un iterateur
// sur la nouvelle "fin logique"

vector<int> v = {1, 2, 3, 4, 5, 6};

//  Avant : [1, 2, 3, 4, 5, 6]
//  remove_if impairs -> [2, 4, 6, ?, ?, ?]
//                                ^
//                                new_end (retourne ici)

// Il faut combiner avec erase pour vraiment supprimer !
v.erase(
    remove_if(v.begin(), v.end(), [](int x) { return x % 2 != 0; }),
    v.end()
);
//  Apres : [2, 4, 6]  (taille = 3)
```

---

## accumulate : reduire un range en une valeur

```cpp
#include <numeric>

vector<int> v = {1, 2, 3, 4, 5};

// Somme (valeur initiale = 0)
int sum = accumulate(v.begin(), v.end(), 0);         // 15

// Produit (valeur initiale = 1, operation custom)
int prod = accumulate(v.begin(), v.end(), 1, multiplies<int>());  // 120

// Concatener des strings
vector<string> words = {"Hello", " ", "World"};
string result = accumulate(words.begin(), words.end(), string(""));
// result = "Hello World"
```

---

## Patterns LeetCode one-liners 

```cpp
// Somme d'un tableau
int sum = accumulate(nums.begin(), nums.end(), 0);

// Nombre d'elements pairs
int cnt = count_if(nums.begin(), nums.end(), [](int x){ return x%2==0; });

// Tous positifs ?
bool allPos = all_of(nums.begin(), nums.end(), [](int x){ return x>0; });

// Doubler tous les elements
transform(nums.begin(), nums.end(), nums.begin(), [](int x){ return x*2; });

// Supprimer les zeros
nums.erase(remove(nums.begin(), nums.end(), 0), nums.end());

// Dedupliquer (apres tri)
sort(nums.begin(), nums.end());
nums.erase(unique(nums.begin(), nums.end()), nums.end());

// Remplir un vecteur 0..n-1
vector<int> indices(n);
iota(indices.begin(), indices.end(), 0);

// Trouver le maximum et son index
auto it = max_element(nums.begin(), nums.end());
int maxVal = *it;
int idx = distance(nums.begin(), it);
```

---

## Complexites a retenir 

| Algorithme           | Complexite    | Notes                          |
|---------------------|---------------|--------------------------------|
| sort                 | O(n log n)    | introsort (quicksort + heapsort) |
| stable_sort          | O(n log n)    | merge sort, plus de memoire    |
| partial_sort         | O(n log k)    | k = taille de la partie triee  |
| nth_element          | O(n)          | pas entierement trie           |
| binary_search        | O(log n)      | tableau trie requis            |
| lower/upper_bound    | O(log n)      | tableau trie requis            |
| find / find_if       | O(n)          | aucun ordre requis             |
| count / count_if     | O(n)          | -                              |
| transform            | O(n)          | -                              |
| accumulate           | O(n)          | -                              |
| remove / remove_if   | O(n)          | ne reduit pas size() seul !    |

---

## Quand utiliser quel algo 

| Besoin                                  | Algorithme                          |
|----------------------------------------|-------------------------------------|
| Trier un tableau                        | `sort`                              |
| Top-K elements les plus petits         | `partial_sort(f, f+k, l)`           |
| K-eme element (median, percentile)     | `nth_element(f, f+k, l)`            |
| Element existe dans tableau trie        | `binary_search`                     |
| Premiere position >= val dans trie     | `lower_bound`                       |
| Compter les elements pairs/negatifs    | `count_if`                          |
| Appliquer une fonction a chaque elem  | `transform`                         |
| Somme / produit                        | `accumulate`                        |
| Supprimer certains elements            | `erase` + `remove_if`              |
| Dedupliquer                            | `sort` + `unique` + `erase`         |

---

## Checkpoint

1. Pourquoi `remove_if` seul ne suffit pas pour supprimer des elements ?
2. Quelle est la difference entre `nth_element` et `partial_sort` ?
3. Comment trouver l'index du maximum d'un vecteur ?
4. Que faut-il faire avant d'utiliser `binary_search` ?

---

## Fichiers

| Fichier          | Description                                          |
|------------------|------------------------------------------------------|
| `exercise.cpp`   | Exercices guides : sort, find, count_if, transform   |
| `solution.cpp`   | Solutions completes                                  |
| `challenge.cpp`  | Challenge : one-liners STL pour problemes LeetCode   |
