# Priority Queue et Heap 🏔

> Toujours acceder au max (ou min) en O(1) — la structure des Top K et Dijkstra

## Pourquoi c'est important

`priority_queue` est un heap binaire. C'est LA structure pour les problemes "Top K elements", "Kth Largest", "Merge K Sorted Lists", et Dijkstra. En competitive programming, un heap te permet de toujours extraire l'element le plus important en O(log n).

---

## Binary Heap en memoire

```
priority_queue<int> pq;  // MAX-HEAP par defaut
pq.push(10); pq.push(30); pq.push(20); pq.push(5); pq.push(25);

Representation en arbre (MAX-HEAP) :
            30               top() = maximum
           /  \
         25    20
        / \
       5   10

Stockage reel en array (vector interne) :
┌────┬────┬────┬────┬────┐
│ 30 │ 25 │ 20 │  5 │ 10 │
└────┴────┴────┴────┴────┘
  [0]  [1]  [2]  [3]  [4]

Relations :
  Parent de i     = (i - 1) / 2
  Enfant gauche   = 2 * i + 1
  Enfant droit    = 2 * i + 2

Propriete MAX-HEAP : parent >= enfants (toujours)
```

---

## push() et pop() — Comment ca marche

```
PUSH(15) :  Ajouter en bas, puis "bubble up"

Etape 1 : Ajouter a la fin
            30
           /  \
         25    20
        / \   /
       5  10 15

Etape 2 : 15 < 20 ? Oui  stop. (deja a la bonne place)

POP() :  Retirer le max, replacer, puis "bubble down"

Etape 1 : Remplacer root par le dernier element
            15
           /  \
         25    20
        / \
       5   10

Etape 2 : 15 < 25  swap avec le plus grand enfant
            25
           /  \
         15    20
        / \
       5   10

Etape 3 : 15 > 10 et 15 > 5  stop
```

---

## Methodes essentielles

| Methode    | Description                    | Complexite |
|-----------|-------------------------------|------------|
| `push(x)` | Ajoute un element             | O(log n)   |
| `pop()`    | Retire le top (max ou min)    | O(log n)   |
| `top()`    | Consulte le top               | O(1)       |
| `empty()`  | True si vide                  | O(1)       |
| `size()`   | Nombre d'elements             | O(1)       |

---

## Max-Heap vs Min-Heap

```cpp
#include <queue>

// MAX-HEAP (par defaut) : top() = plus grand
priority_queue<int> maxHeap;
maxHeap.push(10);
maxHeap.push(30);
maxHeap.push(20);
cout << maxHeap.top();  // 30

// MIN-HEAP : top() = plus petit
priority_queue<int, vector<int>, greater<int>> minHeap;
minHeap.push(10);
minHeap.push(30);
minHeap.push(20);
cout << minHeap.top();  // 10
```

---

## Custom comparator

```cpp
// Trier des pairs par le second element (min-heap sur le poids)
auto cmp = [](const pair<int,int>& a, const pair<int,int>& b) {
    return a.second > b.second;  // '>' pour min-heap
};
priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

pq.push({1, 5});
pq.push({2, 3});
pq.push({3, 8});
cout << pq.top().first;  // 2 (celui avec poids 3, le plus petit)
```

---

## Patterns LeetCode avec Heap 

### Top K Elements
```cpp
// Kth Largest Element — utiliser un min-heap de taille K
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int num : nums) {
        minHeap.push(num);
        if ((int)minHeap.size() > k) {
            minHeap.pop();  // retire le plus petit
        }
    }
    return minHeap.top();  // le k-ieme plus grand
}
```

### Dijkstra (shortest path)
```cpp
// Min-heap de (distance, noeud)
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
```

---

## Complexites a retenir 

| Operation                     | Complexite |
|------------------------------|------------|
| `push()`                     | O(log n)   |
| `pop()`                      | O(log n)   |
| `top()`                      | O(1)       |
| Construire un heap de n elts | O(n)       |
| Top K dans un array de n     | O(n log k) |

---

## Quand utiliser un Heap 

| Signal dans l'enonce         | Pattern                  |
|-----------------------------|--------------------------|
| "K plus grands/petits"       | Min/Max-heap de taille K |
| "Kth largest/smallest"       | Min-heap de taille K     |
| "Merge K sorted lists"       | Min-heap des heads       |
| "Shortest path pondere"      | Dijkstra avec min-heap   |
| "Median d'un stream"         | Deux heaps               |

---

## Checkpoint

1. Pourquoi `priority_queue` est un max-heap par defaut ?
2. Comment creer un min-heap en C++ ?
3. Pourquoi utiliser un min-heap de taille K pour "Kth largest" ?
4. Quelle est la complexite de construire un heap ?

---

## Fichiers

| Fichier          | Description                                    |
|------------------|------------------------------------------------|
| `exercise.cpp`   | Exercices guides : max-heap, min-heap, custom  |
| `solution.cpp`   | Solutions completes                            |
| `challenge.cpp`  | Challenge : Top K elements                     |
