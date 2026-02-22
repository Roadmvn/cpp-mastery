# Stacks & Queues - Pattern 📚

## C'est quoi Stack et Queue ? 🤔

- **Stack** (pile) : LIFO - Last In, First Out. Le dernier entre, le premier sort.
- **Queue** (file) : FIFO - First In, First Out. Le premier entre, le premier sort.

---

## Schema ASCII 📐

### Stack (LIFO) :

```
  push(1), push(2), push(3)

    |  3  |  <- top (dernier ajoute, premier sorti)
    |  2  |
    |  1  |
    +-----+

  pop() -> 3
  pop() -> 2
  pop() -> 1
```

### Queue (FIFO) :

```
  enqueue(1), enqueue(2), enqueue(3)

  front                    back
    |                       |
    v                       v
   [1] -> [2] -> [3]

  dequeue() -> 1 (premier entre, premier sorti)
  dequeue() -> 2
  dequeue() -> 3
```

### Monotonic Stack (decreasing) :

```
  Trouver le prochain element plus grand :

  Array: [2, 1, 2, 4, 3]

  stack: []     i=0: push 2       stack: [2]
  stack: [2]    i=1: 1<2, push    stack: [2,1]
  stack: [2,1]  i=2: 2>1, pop 1   next_greater[1]=2
                     2>=2, pop 2   next_greater[0]=2
                     push 2        stack: [2]
  stack: [2]    i=3: 4>2, pop 2   next_greater[2]=4
                     push 4        stack: [4]
  stack: [4]    i=4: 3<4, push    stack: [4,3]

  Result: [2, 2, 4, -1, -1]
```

---

## Quand utiliser Stacks/Queues ? 🎯

**Stack :**
- Parentheses matching / validation
- Expressions (postfix, infix)
- Monotonic stack (next greater/smaller element)
- Undo/redo, backtracking
- Mots-cles : "valid", "parentheses", "next greater", "histogram"

**Queue :**
- BFS (parcours en largeur)
- Sliding window maximum (deque)
- Process scheduling

---

## Template de code 💻

```cpp
// Stack classique
stack<int> st;
st.push(1);     // ajouter
st.top();       // voir le sommet
st.pop();       // retirer
st.empty();     // est vide ?

// Monotonic stack : prochain element plus grand
vector<int> nextGreater(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // stocke les indices

    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}
```

---

## Complexite typique 📊

| Operation     | Stack  | Queue  |
|---------------|--------|--------|
| Push/Enqueue  | O(1)   | O(1)   |
| Pop/Dequeue   | O(1)   | O(1)   |
| Top/Front     | O(1)   | O(1)   |
| Search        | O(n)   | O(n)   |

---

## Checkpoint ✅

- [ ] Tu sais quand utiliser une stack vs une queue
- [ ] Tu comprends le pattern monotonic stack
- [ ] Tu sais valider des parentheses avec une stack
- [ ] Tu sais evaluer une expression postfixe
- [ ] Tu as resolu les 5 problemes du dossier problems/
