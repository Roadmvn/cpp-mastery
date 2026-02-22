# Sliding Window - Pattern 🪟

## C'est quoi le Sliding Window ? 

Le sliding window maintient une **fenetre** qui glisse sur un tableau ou une string.
Au lieu de recalculer depuis zero a chaque position, on **ajoute/retire** un element a la fois.

---

## Schema ASCII 

### Fenetre fixe (taille k) :

```
Array: [2, 1, 5, 1, 3, 2]    k = 3

Etape 1:  [2, 1, 5] 1, 3, 2   sum = 8
           ^-----^
Etape 2:   2 [1, 5, 1] 3, 2   sum = 8 - 2 + 1 = 7
              ^-----^
Etape 3:   2, 1 [5, 1, 3] 2   sum = 7 - 1 + 3 = 9
                 ^-----^
Etape 4:   2, 1, 5 [1, 3, 2]  sum = 9 - 5 + 2 = 6
                    ^-----^
```

### Fenetre variable :

```
String: "abcabcbb"    -> Plus longue substring sans repetition

  a b c a b c b b
  L
  R                   window = {a}         len = 1
  L
    R                 window = {a,b}       len = 2
  L
      R               window = {a,b,c}    len = 3
    L
        R             window = {b,c,a}    len = 3  (retire a, ajoute a)
      L
          R           window = {c,a,b}    len = 3
        L
            R         window = {a,b,c}    len = 3
            L
              R       window = {b,c}      len = 2  (shrink)
              L
                R     window = {b}        len = 1
```

---

## Quand utiliser le Sliding Window ? 

- Sous-array/substring **contigue**
- On cherche un min/max/somme sur une fenetre
- "Plus long", "plus court" sous-array avec une condition
- Mots-cles : "contiguous", "substring", "subarray", "window"

---

## Template de code 

### Fenetre fixe :
```cpp
int fixedWindow(vector<int>& arr, int k) {
    int windowSum = 0, maxSum = 0;
    // Construire la premiere fenetre
    for (int i = 0; i < k; i++)
        windowSum += arr[i];
    maxSum = windowSum;
    // Glisser la fenetre
    for (int i = k; i < arr.size(); i++) {
        windowSum += arr[i] - arr[i - k];  // ajouter droite, retirer gauche
        maxSum = max(maxSum, windowSum);
    }
    return maxSum;
}
```

### Fenetre variable :
```cpp
int variableWindow(string& s) {
    unordered_set<char> window;
    int left = 0, maxLen = 0;
    for (int right = 0; right < s.size(); right++) {
        while (window.count(s[right])) {
            window.erase(s[left]);
            left++;
        }
        window.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}
```

---

## Complexite typique 

| Approche      | Temps    | Espace |
|---------------|----------|--------|
| Brute force   | O(n * k) | O(1)   |
| Sliding window| O(n)     | O(k)   |

---

## Checkpoint 

- [ ] Tu comprends la difference entre fenetre fixe et variable
- [ ] Tu sais quand shrink la fenetre (condition violee)
- [ ] Tu sais identifier un probleme de sliding window
- [ ] Tu as resolu les 5 problemes du dossier problems/
