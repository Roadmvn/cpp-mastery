# Iterateurs 🔁

> Le pont entre les conteneurs et les algorithmes — comprendre les iterateurs, c'est comprendre la STL

## Pourquoi c'est important

Les iterateurs sont le mecanisme qui permet aux algorithmes STL (`sort`, `find`, `copy`...) de fonctionner sur n'importe quel conteneur. Maitriser les categories d'iterateurs te permet d'ecrire des fonctions generiques et de comprendre pourquoi certains algorithmes sont compatibles avec certains conteneurs (et d'autres non).

---

## Les 5 categories d'iterateurs

```
CATEGORIES (du moins capable au plus capable)
============================================================

InputIterator          OutputIterator
   |                       |
   +----------+------------+
              |
          ForwardIterator
              |
       BidirectionalIterator
              |
       RandomAccessIterator

Chaque categorie HERITE des capacites de la precedente.

CAPACITES PAR CATEGORIE :
┌──────────────────────┬──────┬───────┬───────┬────────┬────────┐
│ Operation            │ Input│Output │ Fwd   │ Bidir  │ Random │
├──────────────────────┼──────┼───────┼───────┼────────┼────────┤
│ Lire *it             │  OUI │  NON  │  OUI  │  OUI   │  OUI   │
│ Ecrire *it = val     │  NON │  OUI  │  OUI  │  OUI   │  OUI   │
│ Avancer ++it         │  OUI │  OUI  │  OUI  │  OUI   │  OUI   │
│ Reculer --it         │  NON │  NON  │  NON  │  OUI   │  OUI   │
│ it + n, it - n       │  NON │  NON  │  NON  │  NON   │  OUI   │
│ it[n]                │  NON │  NON  │  NON  │  NON   │  OUI   │
│ Comparaison <, >     │  NON │  NON  │  NON  │  NON   │  OUI   │
└──────────────────────┴──────┴───────┴───────┴────────┴────────┘

CONTENEURS et leurs iterateurs :
vector, array       -> RandomAccessIterator  (le plus puissant)
deque               -> RandomAccessIterator
list                -> BidirectionalIterator
set, map            -> BidirectionalIterator
unordered_set/map   -> ForwardIterator
istream_iterator    -> InputIterator
ostream_iterator    -> OutputIterator
```

---

## begin / end : les bornes de tout conteneur

```cpp
vector<int> v = {10, 20, 30, 40, 50};

v.begin()                       v.end()
   |                               |
   v                               v
[ 10 | 20 | 30 | 40 | 50 |   ]
  ^                          ^
  |                          |
premier element        apres le dernier (sentinelle)

// Iteration classique
for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}

// rbegin / rend : iteration en sens inverse
v.rbegin()                     v.rend()
   |                               |
   v                               v
[ 10 | 20 | 30 | 40 | 50 ]
                         ^    ^
                         |    |
                    dernier  avant le premier

for (auto it = v.rbegin(); it != v.rend(); ++it) {
    cout << *it << " ";  // 50 40 30 20 10
}
```

---

## Fonctions utilitaires

```cpp
#include <iterator>

vector<int> v = {10, 20, 30, 40, 50};
auto it = v.begin();  // pointe sur 10

// advance(it, n) : deplacement relatif (modifie it sur place)
advance(it, 2);
cout << *it;  // 30

// next(it, n) : retourne un nouvel iterateur avance de n (n=1 par defaut)
auto it2 = next(it);     // pointe sur 40
auto it3 = next(it, 2);  // pointe sur 50

// prev(it, n) : retourne un nouvel iterateur recule de n (n=1 par defaut)
auto it4 = prev(it);     // pointe sur 20

// distance(first, last) : nombre de pas entre deux iterateurs
auto d = distance(v.begin(), v.end());  // 5

// Attention : distance est O(n) pour les iterateurs non random-access !
//             O(1) pour vector, deque (random-access)
//             O(n) pour list, set, map (bidirectional/forward)
```

---

## Iterateurs sur string et tableau C

```cpp
// string : comme un vector<char>
string s = "hello";
for (auto it = s.begin(); it != s.end(); ++it) {
    cout << *it;  // h e l l o
}

// Tableau C : les pointeurs SONT des iterateurs random-access
int arr[] = {1, 2, 3, 4, 5};
sort(arr, arr + 5);  // arr = begin, arr+5 = end
auto pos = find(arr, arr + 5, 3);  // cherche 3
```

---

## Iterateurs speciaux

```cpp
#include <iterator>

// back_inserter : insere a la fin du conteneur via push_back
vector<int> src = {1, 2, 3};
vector<int> dst;
copy(src.begin(), src.end(), back_inserter(dst));
// dst = {1, 2, 3}

// istream_iterator : lire depuis un flux comme un iterateur
#include <sstream>
istringstream iss("1 2 3 4 5");
vector<int> data(istream_iterator<int>(iss), istream_iterator<int>());
// data = {1, 2, 3, 4, 5}

// ostream_iterator : ecrire dans un flux comme un iterateur
copy(data.begin(), data.end(), ostream_iterator<int>(cout, " "));
// affiche : 1 2 3 4 5
```

---

## Patterns LeetCode avec iterateurs 

### Trouver la position d'un element

```cpp
vector<int> v = {3, 1, 4, 1, 5, 9};
auto it = find(v.begin(), v.end(), 4);
if (it != v.end()) {
    int idx = distance(v.begin(), it);  // index = 2
}
```

### Inverser une portion

```cpp
vector<int> v = {1, 2, 3, 4, 5};
reverse(v.begin() + 1, v.begin() + 4);  // v = {1, 4, 3, 2, 5}
```

### Rotation

```cpp
vector<int> v = {1, 2, 3, 4, 5};
rotate(v.begin(), v.begin() + 2, v.end());  // v = {3, 4, 5, 1, 2}
```

---

## Complexites a retenir 

| Operation              | vector (random) | list (bidir)  | set (bidir)   |
|-----------------------|-----------------|---------------|---------------|
| ++it                   | O(1)            | O(1)          | O(log n)      |
| advance(it, n)         | O(1)            | O(n)          | O(n log n)    |
| distance(first, last)  | O(1)            | O(n)          | O(n)          |
| next / prev            | O(1)            | O(1)          | O(log n)      |

---

## Quand utiliser quoi 

| Besoin                             | Outil                              |
|------------------------------------|------------------------------------|
| Parcourir en sens inverse          | `rbegin() / rend()`                |
| Avancer de n positions             | `advance` (in-place) / `next`      |
| Reculer de n positions             | `advance(it, -n)` / `prev`         |
| Distance entre deux iterateurs     | `distance(first, last)`            |
| Inserer dynamiquement pendant copy | `back_inserter`                    |
| Lire un flux comme un range        | `istream_iterator`                 |

---

## Checkpoint

1. Quelle categorie d'iterateur le `set` fournit-il ? Pourquoi pas random-access ?
2. Quelle est la difference entre `advance(it, 2)` et `next(it, 2)` ?
3. Pourquoi `distance` est-il O(n) pour une `list` ?
4. Comment utiliser un tableau C classique avec `sort` ?

---

## Fichiers

| Fichier          | Description                                          |
|------------------|------------------------------------------------------|
| `exercise.cpp`   | Exercices guides : begin/end, advance, next, prev    |
| `solution.cpp`   | Solutions completes                                  |
| `challenge.cpp`  | Challenge : algorithmes generiques avec iterateurs   |
