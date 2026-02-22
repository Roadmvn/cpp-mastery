# 11 - Dynamic Programming (Programmation Dynamique)

## C'est quoi la DP ?

La programmation dynamique est une technique qui resout des problemes complexes
en les **decomposant en sous-problemes plus simples** et en **memorisant** leurs
solutions pour eviter les recalculs.

> Pense a la recursion, mais en sauvegardant chaque resultat intermediaire
> pour ne jamais recalculer deux fois la meme chose.

---

## Les 2 proprietes indispensables

### 1. Overlapping Subproblems (sous-problemes chevauchants)

```
    Fibonacci sans DP :          Fibonacci avec DP :

    fib(5)                        fib(5)
    ├── fib(4)                    ├── fib(4)  ← calcule une fois, stocke
    │   ├── fib(3)                │   ├── fib(3)  ← calcule une fois, stocke
    │   │   ├── fib(2)            │   │   └── ...
    │   │   └── fib(1)            │   └── fib(2)  ← deja stocke, reutilise !
    │   └── fib(2) ← recalcule!   └── fib(3)  ← deja stocke, reutilise !
    └── fib(3) ← recalcule!
        └── ...

    Sans DP : O(2^n)    Avec DP : O(n)
```

### 2. Optimal Substructure (sous-structure optimale)

La solution optimale globale peut etre construite a partir des solutions
optimales des sous-problemes. Exemple : le plus court chemin entre A et C
en passant par B = plus court(A,B) + plus court(B,C).

---

## Top-Down vs Bottom-Up

```
    ════════════════════════════════════════════════════════════════
    TOP-DOWN (Memoization)          BOTTOM-UP (Tabulation)
    ════════════════════════════════════════════════════════════════

    - Recursion + cache              - Iteration + tableau
    - Part du grand probleme         - Part des cas de base
    - Calcule uniquement ce          - Calcule tout, meme
      qui est necessaire               ce qui n'est pas utilise
    - Plus intuitif a ecrire         - Plus efficace en memoire

    Exemple fib(5) top-down :        Exemple fib(5) bottom-up :

    memo = {}                         dp[0]=0, dp[1]=1
    fib(5)                            dp[2]=1, dp[3]=2
      fib(4)                          dp[4]=3, dp[5]=5
        fib(3)
          fib(2) → memo[2]=1          ┌──┬──┬──┬──┬──┬──┐
          fib(1) → 1                  │0 │1 │1 │2 │3 │5 │
        → memo[3]=2                   └──┴──┴──┴──┴──┴──┘
        fib(2) → memo[2]=1 reutilise   0  1  2  3  4  5
      → memo[4]=3
      fib(3) → memo[3]=2 reutilise
    → memo[5]=5
```

---

## Schema ASCII - Tableau DP 2D (LCS)

```
    Probleme : Longest Common Subsequence de "abcde" et "ace"

          ""  a  c  e
    "" [  0   0  0  0 ]
    a  [  0   1  1  1 ]
    b  [  0   1  1  1 ]
    c  [  0   1  2  2 ]
    d  [  0   1  2  2 ]
    e  [  0   1  2  3 ]  ← Reponse : dp[5][3] = 3

    Regle de remplissage :
    ┌────────────────────────────────────────────────────────┐
    │ si s1[i] == s2[j] : dp[i][j] = dp[i-1][j-1] + 1      │
    │ sinon             : dp[i][j] = max(dp[i-1][j],        │
    │                                    dp[i][j-1])        │
    └────────────────────────────────────────────────────────┘

    Lecture : les fleches montrent d'ou vient chaque valeur

    dp[3][2] = 2 car 'c'=='c' → dp[2][1] + 1 = 1 + 1 = 2
    dp[5][3] = 3 car 'e'=='e' → dp[4][2] + 1 = 2 + 1 = 3
```

---

## Les frameworks de resolution

### Framework 1D (Climbing Stairs, House Robber, Coin Change)

```
    1. Definir dp[i] = reponse pour le sous-probleme i
    2. Trouver la recurrence : dp[i] = f(dp[i-1], dp[i-2], ...)
    3. Initialiser les cas de base (dp[0], dp[1])
    4. Remplir de gauche a droite

    Exemple : House Robber
    dp[i] = max(dp[i-1], dp[i-2] + nums[i])
             ↑ skip i   ↑ voler i
```

### Framework 2D (LCS, Edit Distance, Knapsack)

```
    1. Definir dp[i][j] = reponse pour sous-probleme (i, j)
    2. Trouver la recurrence avec conditions
    3. Initialiser la premiere ligne et colonne
    4. Remplir ligne par ligne (gauche→droite, haut→bas)
```

---

## Complexites typiques

| Probleme | Temps | Espace | Espace optimise |
|----------|-------|--------|-----------------|
| Fibonacci | O(n) | O(n) | O(1) (2 vars) |
| Climbing Stairs | O(n) | O(n) | O(1) |
| House Robber | O(n) | O(n) | O(1) |
| Coin Change | O(n*m) | O(n) | O(n) |
| LIS | O(n log n) | O(n) | O(n) |
| LCS | O(n*m) | O(n*m) | O(min(n,m)) |
| Knapsack 0/1 | O(n*W) | O(n*W) | O(W) |

---

## Checkpoint

Avant de passer au pattern suivant, tu dois pouvoir :
- [ ] Implementer Fibonacci en top-down et bottom-up
- [ ] Resoudre Climbing Stairs et House Robber sans aide
- [ ] Comprendre la difference entre 1D DP et 2D DP
- [ ] Optimiser l'espace memoire d'une DP 2D en O(n)
- [ ] Identifier si un probleme a les 2 proprietes DP
