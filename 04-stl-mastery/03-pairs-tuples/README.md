# Pairs et Tuples 🔗

> Grouper des valeurs sans creer de struct

## Pourquoi c'est important

En competitive programming, tu as constamment besoin de stocker des paires (index + valeur, coordonnees x/y, noeud + poids). `pair` est LE type que tu utilises avec les maps, les priority_queues, et les algorithmes de graphes. `tuple` etend le concept a 3+ valeurs. Les structured bindings C++17 rendent tout ca lisible.

---

## pair en memoire

```
pair<int, string> p = {42, "hello"};

Stack (objet pair)
┌───────────────────────────┐
│ first  = 42     (int)     │
│ second = "hello" (string) │  ← deux membres, acces direct
└───────────────────────────┘

pair<int, int> coord = {3, 7};
┌───────────┐
│ first = 3 │  ← souvent utilise pour (x, y) ou (index, valeur)
│ second= 7 │
└───────────┘
```

---

## pair — L'essentiel

```cpp
#include <utility>  // ou simplement <map> qui l'inclut

// Creation
pair<int, string> p1(42, "hello");
pair<int, string> p2 = {42, "hello"};
auto p3 = make_pair(42, "hello");

// Acces
cout << p1.first;   // 42
cout << p1.second;  // "hello"

// Structured bindings (C++17) — BEAUCOUP plus lisible
auto [id, name] = p1;
cout << id;    // 42
cout << name;  // "hello"

// Comparaison : d'abord first, puis second si egalite
pair<int,int> a = {1, 5};
pair<int,int> b = {1, 3};
// a > b car first egaux (1==1) et 5 > 3
```

---

## Cas d'utilisation en LeetCode 🏆

| Pattern                   | pair utilise              |
|---------------------------|---------------------------|
| Two Sum avec indices      | `pair<int,int>` (val, idx)|
| Tri par critere + garder index | `pair<int,int>` (val, idx)|
| Graphe pondere            | `pair<int,int>` (voisin, poids)|
| BFS avec distance         | `pair<int,int>` (noeud, dist)|
| Coordonnees 2D            | `pair<int,int>` (row, col)|
| Map entries               | `pair<key, value>` automatique|

```cpp
// Graphe pondere avec adjacency list
vector<vector<pair<int,int>>> adj(n);  // adj[u] = {(v, weight), ...}
adj[0].push_back({1, 5});  // arete 0->1, poids 5

// Trier par valeur en gardant les indices
vector<pair<int,int>> indexed;  // (valeur, index)
for (int i = 0; i < n; i++) {
    indexed.push_back({nums[i], i});
}
sort(indexed.begin(), indexed.end());
```

---

## tuple — Pour 3+ valeurs

```cpp
#include <tuple>

// Creation
tuple<int, string, double> t1(1, "alice", 95.5);
auto t2 = make_tuple(1, "alice", 95.5);

// Acces classique (verbeux)
cout << get<0>(t1);  // 1
cout << get<1>(t1);  // "alice"
cout << get<2>(t1);  // 95.5

// Structured bindings (C++17) — LA facon moderne
auto [id, name, score] = t1;
cout << id << " " << name << " " << score;

// tie — pour decomposer dans des variables existantes
int id2;
string name2;
double score2;
tie(id2, name2, score2) = t1;

// Ignorer certaines valeurs avec tie
tie(id2, ignore, score2) = t1;  // ignore le nom
```

---

## Comparaison pair vs tuple vs struct

```
pair<int,int>
  + Simple, rapide a ecrire
  + Comparaison integree (<, ==, >, etc.)
  + Compatible avec map, priority_queue directement
  - Limite a 2 elements
  - first/second pas tres descriptif

tuple<int,int,int>
  + Plus de 2 elements
  + Comparaison integree
  - get<0>() verbeux
  - Structured bindings resolvent ce probleme

struct Custom { int x, y, z; };
  + Noms descriptifs
  + Methodes possibles
  - Pas de comparaison par defaut
  - Plus de code a ecrire
```

---

## Complexites 📋

| Operation              | Complexite |
|-----------------------|------------|
| Creation pair/tuple    | O(1)       |
| Acces first/second     | O(1)       |
| Acces get<N>           | O(1)       |
| Comparaison            | O(1) pour types simples |
| Structured bindings    | O(1) (compile-time)    |

---

## Checkpoint

1. Quelle est la difference entre `make_pair` et `{val1, val2}` ?
2. Comment un `vector<pair<int,int>>` est trie par defaut ?
3. Pourquoi utiliser structured bindings au lieu de `.first` / `.second` ?
4. Dans quel cas preferer un struct a un tuple ?

---

## Fichiers

| Fichier          | Description                                    |
|------------------|------------------------------------------------|
| `exercise.cpp`   | Exercices guides : pair, tuple, bindings       |
| `solution.cpp`   | Solutions completes                            |
| `challenge.cpp`  | Challenge : coordonnees et graphes ponderes    |
