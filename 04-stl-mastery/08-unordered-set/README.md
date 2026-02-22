# Unordered Set 

> Hash set — existence en O(1), zero doublons

## Pourquoi c'est important

`unordered_set` est la version "cles seulement" de `unordered_map`. Tu l'utilises quand tu as besoin de verifier rapidement si un element existe, sans stocker de valeur associee. Detect duplicates, check membership, intersections... c'est simple, rapide, efficace.

---

## Hash Set en memoire

```
unordered_set<int> s = {10, 20, 30, 40};

Hash Table interne (meme structure que unordered_map, sans valeurs) :
┌─────┬──────────────────┐
│ [0] │  null           │
│ [1] │  (20)  null   │
│ [2] │  (10)  null   │
│ [3] │  (30)  (40)  null  │   collision
│ [4] │  null           │
│ ... │                  │
└─────┴──────────────────┘

Proprietes :
- Pas de doublons (insert d'un existant = no-op)
- Pas d'ordre garanti
- Lookup O(1) en moyenne
```

---

## Methodes essentielles

| Methode          | Description                        | Complexite (moy) |
|-----------------|------------------------------------|-------------------|
| `s.insert(x)`   | Ajoute (ignore si deja present)    | O(1)              |
| `s.find(x)`     | Iterateur vers x (ou end)          | O(1)              |
| `s.count(x)`    | 0 ou 1                            | O(1)              |
| `s.erase(x)`    | Supprime x                         | O(1)              |
| `s.size()`       | Nombre d'elements                  | O(1)              |
| `s.empty()`      | True si vide                       | O(1)              |
| `s.clear()`      | Supprime tout                      | O(n)              |

```cpp
#include <unordered_set>

unordered_set<int> s;
s.insert(10);
s.insert(20);
s.insert(10);  // ignore, deja present
cout << s.size();  // 2

if (s.count(10)) {
    cout << "10 existe";
}

s.erase(10);
cout << s.count(10);  // 0
```

---

## unordered_set vs unordered_map

```
unordered_set<int>           unordered_map<int, T>
┌──────────┐                 ┌──────────┬───────┐
│  cle     │                 │  cle     │ valeur│
├──────────┤                 ├──────────┼───────┤
│   10     │                 │   10     │  "a"  │
│   20     │                 │   20     │  "b"  │
│   30     │                 │   30     │  "c"  │
└──────────┘                 └──────────┴───────┘

Set = "est-ce que X existe ?"
Map = "quelle est la valeur associee a X ?"
```

---

## Patterns LeetCode avec Set 

### Detecter des doublons
```cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int num : nums) {
        if (seen.count(num)) return true;
        seen.insert(num);
    }
    return false;
}
```

### Intersection de deux arrays
```cpp
vector<int> intersection(vector<int>& a, vector<int>& b) {
    unordered_set<int> setA(a.begin(), a.end());
    vector<int> result;
    for (int x : b) {
        if (setA.count(x)) {
            result.push_back(x);
            setA.erase(x);  // eviter les doublons dans le resultat
        }
    }
    return result;
}
```

### Longest Consecutive Sequence
```cpp
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int maxLen = 0;
    for (int num : s) {
        if (!s.count(num - 1)) {  // debut de sequence
            int len = 1;
            while (s.count(num + len)) len++;
            maxLen = max(maxLen, len);
        }
    }
    return maxLen;
}
```

---

## Quand utiliser unordered_set 

| Besoin                              | Utiliser          |
|-------------------------------------|-------------------|
| Verifier existence en O(1)          | `unordered_set`   |
| Eliminer les doublons               | `unordered_set`   |
| Intersection/union d'ensembles      | `unordered_set`   |
| Stocker une valeur associee         | `unordered_map`   |
| Besoin d'ordre                      | `set` (ordonne)   |

---

## Checkpoint

1. Que se passe-t-il si on insere un element deja present ?
2. Quelle est la difference entre `count()` et `find()` ?
3. Pourquoi le pire cas est O(n) et pas O(1) ?
4. Quand preferer un set a un vector + sort + unique ?

---

## Fichiers

| Fichier          | Description                                    |
|------------------|------------------------------------------------|
| `exercise.cpp`   | Exercices guides : insert, find, operations    |
| `solution.cpp`   | Solutions completes                            |
| `challenge.cpp`  | Challenge : doublons et intersections          |
