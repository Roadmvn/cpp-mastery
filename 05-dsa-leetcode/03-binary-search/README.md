# Binary Search - Pattern

## C'est quoi le Binary Search ?

Le binary search divise l'espace de recherche **par 2** a chaque etape.
Au lieu de chercher lineairement en O(n), on trouve en O(log n).

---

## Schema ASCII

### Binary Search classique sur array trie :

```
Target = 7

Array: [1, 3, 5, 7, 9, 11, 13]
        0  1  2  3  4   5   6

Etape 1:  lo=0          mid=3         hi=6
          [1, 3, 5, 7, 9, 11, 13]
                    ^
                  arr[3]=7 == target -> TROUVE!

Target = 11

Etape 1:  lo=0          mid=3         hi=6
          [1, 3, 5, 7, 9, 11, 13]
                    ^
                  arr[3]=7 < 11 -> chercher a DROITE

Etape 2:              lo=4  mid=5     hi=6
                      [9, 11, 13]
                           ^
                         arr[5]=11 == target -> TROUVE!
```

### Binary Search sur espace de recherche (pas un array) :

```
"Koko mange des bananes a vitesse k, peut-elle finir en h heures?"

Espace de recherche : [1, 2, 3, ..., max(piles)]
                       lo                    hi

On binary search sur la reponse :
  mid = vitesse candidate
  Si elle peut finir a cette vitesse -> chercher plus petit (gauche)
  Sinon -> chercher plus grand (droite)
```

---

## Quand utiliser le Binary Search ?

- Array **trie** (ou espace de recherche monotone)
- On cherche un element, une position, ou une valeur optimale
- "Trouver le minimum qui satisfait X" -> binary search sur la reponse
- Mots-cles : "sorted", "minimum", "maximum", "search"

---

## Template de code

### Recherche exacte :
```cpp
int binarySearch(vector<int>& arr, int target) {
    int lo = 0, hi = arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
```

### Borne gauche (premier element >= target) :
```cpp
int lowerBound(vector<int>& arr, int target) {
    int lo = 0, hi = arr.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
```

### Binary search sur la reponse :
```cpp
int searchOnAnswer(int lo, int hi) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (condition(mid)) hi = mid;     // chercher plus petit
        else lo = mid + 1;
    }
    return lo;
}
```

---

## Complexite typique

| Approche      | Temps     | Espace |
|---------------|-----------|--------|
| Linear search | O(n)      | O(1)   |
| Binary search | O(log n)  | O(1)   |

---

## Checkpoint

- [ ] Tu sais ecrire un binary search sans bug (lo <= hi vs lo < hi)
- [ ] Tu sais calculer mid sans overflow : `lo + (hi - lo) / 2`
- [ ] Tu comprends la difference entre recherche exacte et lower bound
- [ ] Tu sais appliquer binary search sur un espace de reponse
- [ ] Tu as resolu les 5 problemes du dossier problems/
