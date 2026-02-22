# Linked Lists - Pattern 

## C'est quoi une Linked List ? 

Une linked list est une structure ou chaque **noeud** pointe vers le suivant.
Contrairement aux arrays, les elements ne sont PAS contigus en memoire.

---

## Schema ASCII 

### Singly Linked List :

```
  head
   |
   v
  [1] -> [2] -> [3] -> [4] -> [5] -> NULL
   |       |       |       |       |
  val    val    val    val    val
  next   next   next   next   next=NULL
```

### Reverse Linked List :

```
Avant:  [1] -> [2] -> [3] -> [4] -> NULL

Etape 1: NULL <- [1]    [2] -> [3] -> [4] -> NULL
                 prev   curr

Etape 2: NULL <- [1] <- [2]    [3] -> [4] -> NULL
                        prev   curr

Etape 3: NULL <- [1] <- [2] <- [3]    [4] -> NULL
                               prev   curr

Etape 4: NULL <- [1] <- [2] <- [3] <- [4]
                                       prev
Apres:  [4] -> [3] -> [2] -> [1] -> NULL
```

### Two Pointers (slow/fast) :

```
Detecter un cycle :
  [1] -> [2] -> [3] -> [4]
                 ^       |
                 |       v
                [6] <- [5]

  slow: 1 pas a la fois    s
  fast: 2 pas a la fois    f

  s=1 f=1 -> s=2 f=3 -> s=3 f=5 -> s=4 f=3 -> s=5 f=5 RENCONTRE!
```

---

## Quand utiliser les Linked Lists ? 

- Inverser, fusionner, detecter un cycle
- Manipulations de pointeurs (reorder, remove nth)
- Fast/slow pointer pour trouver le milieu ou detecter un cycle
- Mots-cles : "linked list", "reverse", "merge", "cycle"

---

## Template de code 

### Structure de base :
```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

### Reverse iteratif :
```cpp
ListNode* reverse(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

### Fast/Slow pointer :
```cpp
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

---

## Complexite typique 

| Operation          | Temps | Espace |
|--------------------|-------|--------|
| Acces par index    | O(n)  | O(1)   |
| Insertion en tete  | O(1)  | O(1)   |
| Reverse            | O(n)  | O(1)   |
| Detect cycle       | O(n)  | O(1)   |

---

## Checkpoint 

- [ ] Tu sais reverser une linked list iterativement
- [ ] Tu comprends le pattern fast/slow pointer
- [ ] Tu sais utiliser un dummy node pour simplifier l'insertion
- [ ] Tu geres les edge cases (liste vide, un seul element)
- [ ] Tu as resolu les 5 problemes du dossier problems/
