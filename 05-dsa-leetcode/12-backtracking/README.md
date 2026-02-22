# 12 - Backtracking 🔙

## C'est quoi le Backtracking ? 

Le backtracking est une technique de **recherche exhaustive** ou tu explores toutes les
possibilites en construisant une solution **etape par etape**, et tu **reviens en arriere**
(backtrack) des qu'une branche ne mene nulle part.

> Pense a un labyrinthe : tu avances, si c'est un cul-de-sac tu recules et tu prends
> un autre chemin.

---

## Quand l'utiliser ? 

- Generer **toutes les combinaisons/permutations/sous-ensembles**
- Problemes de **placement** (N-Queens, Sudoku)
- **Recherche de chemins** dans une grille/graphe
- Quand l'enonce dit "trouver toutes les solutions possibles"
- Problemes de **partitionnement**

---

## Schema ASCII - Arbre de decision avec pruning 

```
                    Subsets de [1,2,3]
                         []
                       / | \
                   [1]  [2]  [3]        choix: prendre ou pas
                  / \    |
             [1,2] [1,3] [2,3]         on continue avec les elements restants
              |
           [1,2,3]                      feuille = solution complete

    Arbre de decision detaille (include/exclude):

                              []
                     include 1 / \ exclude 1
                          [1]     []
                    inc 2/ \exc  inc 2/ \exc
                   [1,2] [1]    [2]    []
                  i3/\e  i3/\e  i3/\e  i3/\e
              [1,2,3][1,2][1,3][1][2,3][2][3][]

    ═══════════════════════════════════════════
    PRUNING (elagage) - couper les branches inutiles :
    ═══════════════════════════════════════════

                              []
                     /        |        \
                   [1]       [2]       [3]
                  / \         |         X   PRUNE si somme > cible
             [1,2] [1,3]   [2,3]
              |      X       X
           [1,2,3]
             seule solution valide si cible = 6
```

---

## Le pattern general 

```
backtrack(candidats, chemin_actuel, resultat):
    si condition_de_fin:
        ajouter chemin_actuel au resultat
        return

    pour chaque candidat dans candidats:
        si candidat est valide (pruning):
            ajouter candidat au chemin
            backtrack(candidats_restants, chemin, resultat)
            retirer candidat du chemin   BACKTRACK
```

---

## Les 3 cles du backtracking 

| Etape | Description | Code |
|-------|-------------|------|
| **1. Choisir** | Prendre un element | `path.push_back(x)` |
| **2. Explorer** | Recurser sur le reste | `backtrack(i+1, ...)` |
| **3. Annuler** | Revenir en arriere | `path.pop_back()` |

---

## Variantes courantes 

| Variante | Difference | Exemple |
|----------|-----------|---------|
| **Subsets** | start = i+1, pas de condition fin | Tous les sous-ensembles |
| **Permutations** | used[] array, pas de start | Tous les ordres possibles |
| **Combinations** | start = i+1, taille fixe | k elements parmi n |
| **Partitioning** | substring + validation | Palindrome partitioning |
| **Grid search** | 4 directions, visited[][] | Word search |

---

## Complexite typique 

| Type | Temps | Espace |
|------|-------|--------|
| Subsets | O(2^n) | O(n) |
| Permutations | O(n!) | O(n) |
| Combinations C(n,k) | O(C(n,k)) | O(k) |
| N-Queens | O(n!) | O(n) |

---

## Checkpoint 

Avant de passer au pattern suivant, tu dois pouvoir :
- [ ] Expliquer la difference entre backtracking et brute force
- [ ] Ecrire le template de backtracking de memoire
- [ ] Resoudre Subsets et Permutations sans aide
- [ ] Savoir quand et comment faire du pruning
- [ ] Identifier quand utiliser `start` vs `used[]`
