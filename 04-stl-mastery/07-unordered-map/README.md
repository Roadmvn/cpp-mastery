# Unordered Map 

> Hash table — acces O(1) en moyenne, LE conteneur des frequency counters

## Pourquoi c'est important

`unordered_map` est probablement le conteneur STL le plus utilise en LeetCode apres `vector`. Two Sum, frequency counters, group anagrams, subarray sum... une enorme partie des problemes se resout avec une hash map. En competitive programming, c'est ton meilleur ami pour du O(1) lookup.

---

## Hash Table en memoire

```
unordered_map<string, int> m;
m["alice"] = 95;
m["bob"] = 87;
m["charlie"] = 92;

Hash Table interne :
┌─────────────────────────────────────┐
│ Bucket Array (taille = N)           │
├─────┬───────────────────────────────┤
│ [0] │  null                        │
│ [1] │  ("bob", 87)  null         │
│ [2] │  ("alice", 95)  null       │
│ [3] │  null                        │
│ [4] │  ("charlie", 92)  null     │
│ [5] │  null                        │
│ ... │                               │
└─────┴───────────────────────────────┘

Comment ca marche :
1. hash("alice") % N = 2    bucket [2]
2. hash("bob") % N = 1      bucket [1]
3. hash("charlie") % N = 4  bucket [4]

COLLISION : si deux cles tombent dans le meme bucket
hash("dave") % N = 2  bucket [2] deja occupe !

│ [2] │  ("alice", 95)  ("dave", 78)  null
         chained hashing (liste chainee)
```

---

## Methodes essentielles

| Methode            | Description                       | Complexite (moy) |
|-------------------|-----------------------------------|-------------------|
| `m[key]`           | Acces/creation                    | O(1)              |
| `m[key] = val`     | Insertion/modification            | O(1)              |
| `m.insert({k,v})`  | Insere (ne remplace pas)          | O(1)              |
| `m.find(key)`      | Iterateur vers l'element (ou end) | O(1)              |
| `m.count(key)`     | 0 ou 1                           | O(1)              |
| `m.erase(key)`     | Supprime par cle                  | O(1)              |
| `m.size()`         | Nombre d'elements                 | O(1)              |
| `m.empty()`        | True si vide                      | O(1)              |

**Attention :** `m[key]` cree l'entree avec valeur par defaut (0 pour int) si la cle n'existe pas !

```cpp
unordered_map<string, int> m;
cout << m["inexistant"];  // affiche 0, ET cree l'entree !
// Utiliser find() ou count() pour verifier sans creer
```

---

## Iteration sur une unordered_map

```cpp
unordered_map<string, int> scores = {{"Alice", 95}, {"Bob", 87}};

// Range-for avec structured bindings (C++17)
for (auto& [name, score] : scores) {
    cout << name << " : " << score << endl;
}

// Avec iterateur
for (auto it = scores.begin(); it != scores.end(); ++it) {
    cout << it->first << " : " << it->second << endl;
}
```

---

## Patterns LeetCode avec Hash Map 

### Two Sum (LE classique)
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;  // valeur -> index
    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}
```

### Frequency Counter
```cpp
unordered_map<char, int> freq;
for (char c : s) {
    freq[c]++;  // incrementer automatiquement (defaut = 0)
}
```

### Group by key
```cpp
unordered_map<string, vector<string>> groups;
for (string& word : words) {
    string key = /* calculer la cle */;
    groups[key].push_back(word);
}
```

---

## Complexites a retenir 

| Operation         | Moyenne | Pire cas |
|------------------|---------|----------|
| Insert/Access     | O(1)    | O(n) si toutes les cles collisionnent |
| Find/Count        | O(1)    | O(n)     |
| Erase             | O(1)    | O(n)     |
| Iteration totale  | O(n)    | O(n)     |

---

## Quand utiliser unordered_map 

| Signal dans l'enonce           | Pattern                     |
|--------------------------------|-----------------------------|
| "En O(1)" ou "en un seul pass"| Hash map pour lookup rapide |
| "Compter les frequences"       | Frequency counter           |
| "Trouver une paire/complement"| Two Sum pattern             |
| "Grouper par propriete"        | Group by key                |
| "Sous-tableau de somme K"      | Prefix sum + hash map       |

---

## Checkpoint

1. Quelle est la difference entre `m[key]` et `m.find(key)` ?
2. Que se passe-t-il quand on fait `m["new_key"]` sur une map vide ?
3. Pourquoi le pire cas est O(n) et pas O(1) ?
4. Quand preferer `unordered_map` a `map` ?

---

## Fichiers

| Fichier          | Description                                    |
|------------------|------------------------------------------------|
| `exercise.cpp`   | Exercices guides : insert, find, frequency     |
| `solution.cpp`   | Solutions completes                            |
| `challenge.cpp`  | Challenge : Two Sum + frequency counter        |
