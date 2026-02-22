# 14 - Heap / Priority Queue 🏔

## C'est quoi un Heap ? 

Un heap (tas) est un **arbre binaire complet** ou chaque parent est plus petit (min-heap)
ou plus grand (max-heap) que ses enfants. En C++, `priority_queue` est un **max-heap** par defaut.

> Imagine une file d'attente ou le VIP passe toujours en premier,
> peu importe quand il arrive.

---

## Quand l'utiliser ? 

- Trouver le **k-ieme plus grand/petit** element
- Maintenir les **top k** elements en temps reel
- **Fusion de k listes** triees
- **Median** en flux continu (deux heaps)
- Problemes de **scheduling** avec priorites
- Mots cles : "kth largest", "top k", "median", "schedule"

---

## Schema ASCII - Min-heap et Max-heap 

```
    MAX-HEAP (parent >= enfants)     MIN-HEAP (parent <= enfants)
    C++ : priority_queue<int>        C++ : priority_queue<int,
                                            vector<int>, greater<int>>

          [50]                              [5]
         /    \                            /    \
       [30]   [40]                      [10]    [15]
      /   \   /                        /    \   /
    [10] [20][35]                    [30]  [20][25]

    ═══════════════════════════════════════════════
    Operations et complexites :
    ═══════════════════════════════════════════════

    ┌──────────────┬───────────┐
    │ Operation    │ Complexite│
    ├──────────────┼───────────┤
    │ push()       │ O(log n)  │   insertion + bubble up
    │ pop()        │ O(log n)  │   suppression + bubble down
    │ top()        │ O(1)      │   acces au sommet
    │ size()       │ O(1)      │
    │ Construire   │ O(n)      │   heapify
    └──────────────┴───────────┘

    ═══════════════════════════════════════════════
    Push (insertion) dans un min-heap :
    ═══════════════════════════════════════════════

    Ajouter 3 :         Bubble up :
         [5]                [3]          3 < 5, swap
        /   \              /   \
      [10]  [15]        [10]   [5]       3 monte
      /                 /
    [3]  nouveau    [15]                ancien parent descend

    ═══════════════════════════════════════════════
    Pattern deux heaps pour la mediane :
    ═══════════════════════════════════════════════

    max-heap (moitie gauche)  │  min-heap (moitie droite)
    stocke les petits         │  stocke les grands
                              │
         [5]                  │       [8]
        /   \                 │      /   \
      [3]   [4]               │   [10]   [12]
                              │
    top = 5 (max des petits)  │  top = 8 (min des grands)
                              │
           mediane = (5 + 8) / 2 = 6.5
```

---

## Le pattern general 

```
// Pour le k-ieme plus grand : min-heap de taille k
priority_queue<int, vector<int>, greater<int>> minHeap;

pour chaque element :
    minHeap.push(element)
    si minHeap.size() > k :
        minHeap.pop()     // virer le plus petit

retourner minHeap.top()   // k-ieme plus grand
```

---

## Syntaxe C++ essentielle 

| Type | Declaration |
|------|-------------|
| Max-heap (defaut) | `priority_queue<int> pq;` |
| Min-heap | `priority_queue<int, vector<int>, greater<int>> pq;` |
| Custom comparateur | `priority_queue<T, vector<T>, Compare> pq;` |
| Paires (tri par .first) | `priority_queue<pair<int,int>> pq;` |

---

## Complexite typique 

| Probleme | Temps | Espace |
|----------|-------|--------|
| Kth largest | O(n log k) | O(k) |
| Top k elements | O(n log k) | O(k) |
| Merge k lists | O(N log k) | O(k) |
| Median stream | O(n log n) | O(n) |

---

## Checkpoint 

Avant de passer au pattern suivant, tu dois pouvoir :
- [ ] Declarer un min-heap et un max-heap en C++
- [ ] Resoudre Kth Largest Element avec un heap de taille k
- [ ] Implementer le pattern deux heaps pour la mediane
- [ ] Utiliser un heap avec des paires ou un comparateur custom
- [ ] Expliquer pourquoi on utilise un min-heap pour le k-ieme plus grand
