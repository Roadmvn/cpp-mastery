# Big O Complexity - Notation et Analyse

## C'est quoi Big O ?

Big O decrit comment le temps d'execution ou la memoire **grandit** quand l'input grandit.
On s'interesse au **pire cas** et on ignore les constantes.

---

## Tableau comparatif des complexites

```
Temps 
|
|                                                    * O(2^n)
|                                                *
|                                            *
|                                        *
|                                   *
|                              *          * O(n²)
|                         *          *
|                    *           *
|               *           *
|          *           *
|     *           *
|  *         *
| *      *           * O(n log n)
|*    *          *
|*  *       *         * O(n)
|* *    *        *
|**  *      *
|* *   *              * O(log n)
|*  *                 * O(1)
+-----------------------------------------> Input (n)
  1   2   4   8  16  32  64  128  256
```

---

## Les complexites en detail

### O(1) - Constant

**Temps fixe**, peu importe la taille de l'input.

```
n=1       -> 1 operation
n=1000    -> 1 operation
n=1000000 -> 1 operation
```

**Exemples concrets :**
- Acces a un element par index dans un array : `arr[5]`
- Insertion/suppression en tete de liste chainee
- Push/pop sur une stack
- Lookup dans une hash map (cas moyen)

```cpp
// O(1) - Acces direct par index
int getElement(vector<int>& arr, int i) {
    return arr[i];  // 1 seule operation
}
```

---

### O(log n) - Logarithmique

A chaque etape, on **divise le probleme par 2**. Tres rapide meme pour des inputs enormes.

```
n=1       -> 0 etapes
n=8       -> 3 etapes  (8->4->2->1)
n=1024    -> 10 etapes
n=1000000 -> 20 etapes
```

**Exemples concrets :**
- Binary search dans un array trie
- Recherche dans un BST equilibre
- Exponentiation rapide

```cpp
// O(log n) - Binary search
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

---

### O(n) - Lineaire

Le temps croit **proportionnellement** a l'input.

```
n=1       -> 1 operation
n=100     -> 100 operations
n=1000000 -> 1000000 operations
```

**Exemples concrets :**
- Parcourir un array
- Chercher un element non trie (linear search)
- Compter les occurrences
- Trouver le max/min

```cpp
// O(n) - Parcours lineaire
int findMax(vector<int>& arr) {
    int maxVal = arr[0];
    for (int x : arr) {       // n iterations
        maxVal = max(maxVal, x);
    }
    return maxVal;
}
```

---

### O(n log n) - Linearithmique

Typique des **algorithmes de tri optimaux**. On divise ET on parcourt.

```
n=8       -> ~24  operations  (8 * 3)
n=1024    -> ~10240 operations (1024 * 10)
n=1000000 -> ~20000000 operations
```

**Exemples concrets :**
- Merge sort
- Quick sort (cas moyen)
- Heap sort
- Trier puis binary search

```cpp
// O(n log n) - Merge sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergeSort(arr, l, mid);       // log n niveaux
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);        // n operations par niveau
}
```

---

### O(n²) - Quadratique 🐢

**Deux boucles imbriquees** sur l'input. Devient lent rapidement.

```
n=10      -> 100 operations
n=100     -> 10000 operations
n=1000    -> 1000000 operations
n=10000   -> 100000000 operations   LENT
```

**Exemples concrets :**
- Bubble sort, selection sort, insertion sort
- Comparer chaque paire d'elements
- Brute force two sum

```cpp
// O(n²) - Double boucle
vector<pair<int,int>> allPairs(vector<int>& arr) {
    vector<pair<int,int>> result;
    for (int i = 0; i < arr.size(); i++) {       // n
        for (int j = i + 1; j < arr.size(); j++) { // n
            result.push_back({arr[i], arr[j]});
        }
    }
    return result;
}
```

---

### O(2^n) - Exponentielle

Le temps **double** a chaque element ajoute. Explose tres vite.

```
n=10  -> 1024 operations
n=20  -> 1048576 operations
n=30  -> 1073741824 operations   TRES LENT
n=40  -> ~1 trillion  
```

**Exemples concrets :**
- Fibonacci naif (recursif sans memo)
- Generer tous les sous-ensembles
- Probleme du sac a dos (brute force)

```cpp
// O(2^n) - Fibonacci naif
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);  // 2 appels recursifs
}
```

---

## Resume rapide

```
+------------+----------------+---------------------------+
| Complexite | Nom            | Exemple typique           |
+------------+----------------+---------------------------+
| O(1)       | Constant       | arr[i], hash map lookup   |
| O(log n)   | Logarithmique  | Binary search             |
| O(n)       | Lineaire       | Parcours de tableau       |
| O(n log n) | Linearithmique | Merge sort, tri optimal   |
| O(n²)      | Quadratique    | Double boucle, bubble sort|
| O(2^n)     | Exponentielle  | Sous-ensembles, fib naif  |
+------------+----------------+---------------------------+
```

## Regles pratiques pour identifier la complexite

1. **Une boucle simple** sur n elements -> O(n)
2. **Deux boucles imbriquees** -> O(n²)
3. **Diviser par 2 a chaque etape** -> O(log n)
4. **Trier puis parcourir** -> O(n log n)
5. **Toutes les combinaisons** -> O(2^n)
6. **Toutes les permutations** -> O(n!)

---

## Checkpoint

- [ ] Tu sais classer O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(2^n)
- [ ] Tu identifies la complexite d'une boucle simple
- [ ] Tu identifies la complexite de boucles imbriquees
- [ ] Tu sais pourquoi binary search est O(log n)
- [ ] Tu sais quel tri est O(n log n) vs O(n²)
