# Stack 📚

> Last In, First Out — la structure des expressions et du backtracking

## Pourquoi c'est important

Les stacks sont partout en LeetCode : parentheses valides, evaluation d'expressions, histogrammes, monotonic stack. C'est aussi la base de la recursion (la call stack). Maitriser le stack = comprendre comment fonctionne ton programme ET resoudre une categorie entiere de problemes.

---

## Stack en memoire

```
stack<int> s;
s.push(10);
s.push(20);
s.push(30);

LIFO : Last In, First Out

         top()
           |
           v
       ┌──────┐
       │  30  │  ← push() ajoute ici
       ├──────┤
       │  20  │
       ├──────┤
       │  10  │  ← le premier ajoute sort en dernier
       └──────┘

pop() retire 30 (le dernier ajoute)

       ┌──────┐
       │  20  │  ← nouveau top()
       ├──────┤
       │  10  │
       └──────┘

En interne, stack<T> utilise un deque<T> par defaut :
┌──────────────────────────┐
│ stack<int>               │
│   container = deque<int> │  ← adaptateur, pas un conteneur
│   push() → push_back()  │     il encapsule un autre conteneur
│   pop()  → pop_back()   │
│   top()  → back()       │
└──────────────────────────┘
```

---

## Methodes essentielles

| Methode    | Description                    | Complexite |
|-----------|-------------------------------|------------|
| `push(x)` | Empile un element             | O(1)       |
| `pop()`    | Depile le sommet (ne retourne rien!) | O(1)  |
| `top()`    | Consulte le sommet            | O(1)       |
| `empty()`  | True si vide                  | O(1)       |
| `size()`   | Nombre d'elements             | O(1)       |

**Attention :** `pop()` ne retourne PAS la valeur. Tu dois d'abord lire avec `top()` puis supprimer avec `pop()`.

```cpp
#include <stack>

stack<int> s;
s.push(42);
int val = s.top();  // 42
s.pop();            // retire 42, retourne void
```

---

## Patterns LeetCode avec Stack 🏆

### 1. Validation de parentheses
```cpp
// Le pattern le plus classique
// Empiler les ouvrantes, depiler quand on rencontre une fermante
bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) return false;
            st.pop();
        }
    }
    return st.empty();
}
```

### 2. Monotonic Stack (Next Greater Element)
```cpp
// Trouver le prochain element plus grand pour chaque element
// Empiler les indices, depiler quand on trouve un plus grand
vector<int> nextGreater(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // contient des INDICES

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

## Quand utiliser un Stack en LeetCode 🎯

| Signal dans l'enonce              | Pattern Stack           |
|-----------------------------------|-------------------------|
| Parentheses/brackets imbriques    | Validation/matching     |
| "Prochain plus grand element"     | Monotonic stack         |
| Evaluer une expression            | Deux stacks (ops+vals)  |
| Annuler/revenir en arriere        | Stack comme historique  |
| Parcours en profondeur iteratif   | DFS avec stack          |

---

## Checkpoint

1. Pourquoi `pop()` ne retourne pas la valeur en C++ ?
2. Quelle structure de donnees est utilisee en interne par `stack<T>` ?
3. Comment detecter des parentheses non matchees avec un stack ?
4. Qu'est-ce qu'un monotonic stack et quand l'utiliser ?

---

## Fichiers

| Fichier          | Description                                    |
|------------------|------------------------------------------------|
| `exercise.cpp`   | Exercices guides : push, pop, top, patterns    |
| `solution.cpp`   | Solutions completes                            |
| `challenge.cpp`  | Challenge : parentheses imbriquees             |
