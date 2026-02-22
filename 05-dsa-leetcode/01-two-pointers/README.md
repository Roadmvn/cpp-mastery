# Two Pointers

> Le pattern qui transforme du O(n^2) en O(n)

## Pourquoi c'est important

Le pattern Two Pointers est le **premier pattern a maitriser** pour LeetCode. Il est simple a comprendre, puissant en pratique, et revient partout : arrays tries, strings, palindromes, sous-tableaux... Si tu dois choisir un seul pattern a apprendre aujourd'hui, c'est celui-la.

---

## Le concept

**Principe** : utiliser deux index (pointeurs) qui se deplacent dans un array selon une logique precise, au lieu d'utiliser deux boucles imbriquees.

### Variante 1 : Pointeurs opposes (debut/fin)

Les deux pointeurs partent de chaque extremite et convergent vers le centre.

**Quand l'utiliser :**
- Array **trie** et recherche d'une paire avec une somme cible
- Verification de **palindromes**
- Maximiser une surface / une distance

```
Array : [1, 3, 5, 7, 9, 11, 15]

  left                      right
   │                          │
   v                          v
 [ 1,  3,  5,  7,  9,  11, 15 ]
   └──────────────────────────┘
      Se rapprochent l'un de l'autre

Iteration 1 :  left=0, right=6    sum = 1+15 = 16 (trop grand  right--)
Iteration 2 :  left=0, right=5    sum = 1+11 = 12 (trop petit  left++)
Iteration 3 :  left=1, right=5    sum = 3+11 = 14 (trop grand  right--)
Iteration 4 :  left=1, right=4    sum = 3+9  = 12 (TROUVE)
```

### Variante 2 : Meme direction (lent/rapide)

Les deux pointeurs partent du debut. Le rapide avance toujours, le lent avance sous condition.

**Quand l'utiliser :**
- Retirer des elements **in-place**
- Retirer des **doublons** d'un array trie
- Problemes de type "slow/fast runner"

```
Array : [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
         s
         f

Objectif : retirer les doublons (garder un de chaque)

Etape 1 : f=1, nums[f]=0 == nums[s]=0    on skip
  [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
   s  f

Etape 2 : f=2, nums[f]=1 != nums[s]=0    s++, copie
  [0, 1, 1, 1, 1, 2, 2, 3, 3, 4]
      s  f

Etape 3 : f=3, nums[f]=1 == nums[s]=1    on skip
  [0, 1, 1, 1, 1, 2, 2, 3, 3, 4]
      s     f

...et ainsi de suite jusqu'a :
  [0, 1, 2, 3, 4, ...]   k=5 elements uniques
               s         f (hors limites)
```

---

## Templates de code

### Template : Pointeurs opposes

```cpp
int left = 0, right = nums.size() - 1;

while (left < right) {
    // Calculer la valeur courante
    int current = nums[left] + nums[right];

    if (current == target) {
        // Trouve ! Traiter le resultat
        return {left, right};
    } else if (current < target) {
        left++;   // Besoin d'une valeur plus grande
    } else {
        right--;  // Besoin d'une valeur plus petite
    }
}
```

### Template : Meme direction (slow/fast)

```cpp
int slow = 0;

for (int fast = 0; fast < nums.size(); fast++) {
    if (/* condition pour garder nums[fast] */) {
        nums[slow] = nums[fast];
        slow++;
    }
}
// slow = nombre d'elements gardes
```

---

## Quand utiliser Two Pointers ? -- Decision rapide

```
Le probleme implique :
│
├── Un array TRIE + recherche de paire/triplet ?
│   └── Pointeurs opposes
│
├── Un palindrome / string symetrique ?
│   └── Pointeurs opposes
│
├── Maximiser une aire / distance ?
│   └── Pointeurs opposes
│
├── Retirer des elements / doublons in-place ?
│   └── Meme direction (slow/fast)
│
└── Rien de tout ca ?
    └── Ce n'est probablement pas Two Pointers
```

---

## Checkpoint

1. Quelle est la difference entre les deux variantes de Two Pointers ?
2. Pourquoi le pattern Two Pointers necessite-t-il souvent un array trie pour la variante "opposes" ?
3. Quelle est la complexite temps typique d'un algorithme Two Pointers ?

---

## Fichiers

| Fichier                | Description                                    |
|------------------------|------------------------------------------------|
| `pattern-template.cpp` | Templates copier-coller pour les deux variantes|
| `problems/`            | 5 problemes classes par difficulte             |

## Problemes

| #  | Probleme                    | Difficulte | LeetCode |
|----|-----------------------------|------------|----------|
| 01 | Valid Palindrome            | Easy       | #125     |
| 02 | Two Sum II                  | Medium     | #167     |
| 03 | Three Sum                   | Medium     | #15      |
| 04 | Container With Most Water   | Medium     | #11      |
| 05 | Trapping Rain Water         | Hard       | #42      |
