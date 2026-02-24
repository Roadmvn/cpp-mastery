# Data Structures & Algorithms -- Roadmap LeetCode 

> De zero a "je solve des Hard en 30 minutes"

## Introduction

Cette section est le coeur du repo. C'est ici que tu vas apprendre a **penser en algorithmes** et a resoudre des problemes LeetCode de facon systematique.

Chaque pattern est un dossier. Chaque dossier contient :
- Un **README** qui explique le pattern, quand l'utiliser, et le template de code
- Un fichier **pattern-template.cpp** copier-coller pour tes solutions
- Un dossier **problems/** avec 5+ problemes classes par difficulte

L'objectif n'est pas de memoriser 500 solutions. C'est de **reconnaitre les patterns** et d'appliquer le bon outil au bon probleme.

---

## Prerequis

Avant de commencer cette section, assure-toi d'avoir complete :
- **Section 01** : Fondations C++ (syntaxe, boucles, fonctions)
- **Section 02** : Memoire et Arrays (pointeurs, allocation, arrays)
- **Section 03** : OOP (classes, heritage, polymorphisme)
- **Section 04** : STL Mastery (vectors, maps, sets, iterators)

Si tu maitrises pas les vectors et les maps, retourne dans la section 04. Serieusement.

---

## Roadmap 

Suis cet ordre. Chaque pattern depend des precedents.

```
                         ROADMAP DSA & LEETCODE
  ================================================================

  Phase 1 : Les Fondamentaux
  ─────────────────────────────────────────────────────────────────
  ┌──────────────────┐     ┌──────────────────┐     ┌──────────────────┐
  │  00. Big O       │────│  01. Two         │────│  02. Sliding     │
  │  Complexity      │     │  Pointers        │     │  Window          │
  └──────────────────┘     └──────────────────┘     └──────────────────┘
                                                            │
                                                            v
  Phase 2 : Structures Lineaires                   ┌──────────────────┐
  ──────────────────────────────────────────────────│  03. Binary      │
  ┌──────────────────┐     ┌──────────────────┐    │  Search          │
  │  04. Linked      │────│  05. Stacks &    │    └──────────────────┘
  │  Lists           │     │  Queues          │             │
  └──────────────────┘     └──────────────────┘             │
                                    │                       │
                                    v                       v
  Phase 3 : Hash & Arbres ──────────────────────────────────────────
  ┌──────────────────┐     ┌──────────────────┐     ┌──────────────────┐
  │  06. Hash Maps   │────│  07. Trees       │────│  08. BST         │
  │  Problems        │     │  Binary Tree     │     │                  │
  └──────────────────┘     └──────────────────┘     └──────────────────┘
                                                            │
                                                            v
  Phase 4 : Graphes & DP ──────────────────────────────────────────
  ┌──────────────────┐     ┌──────────────────┐     ┌──────────────────┐
  │  09. BFS / DFS   │────│  10. Graphs      │────│  11. Dynamic     │
  │                  │     │                  │     │  Programming     │
  └──────────────────┘     └──────────────────┘     └──────────────────┘
                                                            │
                                                            v
  Phase 5 : Patterns Avances ──────────────────────────────────────
  ┌──────────────────┐     ┌──────────────────┐     ┌──────────────────┐
  │  12. Backtracking│────│  13. Greedy      │────│  14. Heap        │
  │                  │     │                  │     │  Problems        │
  └──────────────────┘     └──────────────────┘     └──────────────────┘
                                                            │
                                                            v
                                                   ┌──────────────────┐
                                                   │  15. Tries       │
                                                   │                  │
                                                   └──────────────────┘
                                                            │
                                                            v
  Phase 6 : Structures Avancees ──────────────────────────────────────
  ┌──────────────────┐     ┌──────────────────┐
  │  16. Union-Find  │────│  17. Monotonic   │
  │  (DSU)           │     │  Stack           │
  └──────────────────┘     └──────────────────┘
```

---

## Table des Patterns

| #  | Pattern              | Problemes | Difficulte  | Concepts cles                                    |
|----|----------------------|-----------|-------------|--------------------------------------------------|
| 00 | Big O Complexity     | --        | Debutant    | Notation O, analyse temps/espace                 |
| 01 | Two Pointers         | 5         | Easy-Hard   | Pointeurs opposes, meme direction, arrays tries  |
| 02 | Sliding Window       | 5         | Easy-Hard   | Fenetre fixe/variable, sous-tableaux contigus    |
| 03 | Binary Search        | 5         | Easy-Hard   | Recherche dichotomique, bornes, rotated arrays   |
| 04 | Linked Lists         | 5         | Easy-Medium | Noeuds, reverse, merge, detection de cycle       |
| 05 | Stacks & Queues      | 5         | Easy-Hard   | LIFO/FIFO, monotonic stack, parentheses          |
| 06 | Hash Maps            | 5         | Easy-Medium | Lookup O(1), frequences, Two Sum                 |
| 07 | Trees (Binary Tree)  | 5         | Easy-Hard   | Traversals, hauteur, symetrie, serialisation     |
| 08 | BST                  | 5         | Easy-Medium | Propriete BST, validation, insertion, recherche  |
| 09 | BFS / DFS            | 5         | Medium-Hard | Parcours en largeur/profondeur, niveaux          |
| 10 | Graphs               | 5         | Medium-Hard | Adjacence, topological sort, composantes         |
| 11 | Dynamic Programming  | 8         | Medium-Hard | Memoisation, tabulation, sous-problemes          |
| 12 | Backtracking         | 5         | Medium-Hard | Exploration exhaustive, pruning, permutations    |
| 13 | Greedy               | 5         | Easy-Hard   | Choix local optimal, intervalles, scheduling     |
| 14 | Heap Problems        | 5         | Medium-Hard | Priority queue, top-K, median, merge K lists     |
| 15 | Tries                | 3         | Medium-Hard | Prefix tree, autocomplete, recherche de mots     |
| 16 | Union-Find           | 5         | Medium      | DSU, path compression, union by rank, cycles     |
| 17 | Monotonic Stack      | 5         | Medium-Hard | NGE, NSE, histogramme, span, somme de min/max    |

---

## Comment resoudre un probleme LeetCode -- Methodologie en 5 etapes

### Etape 1 : Comprendre (2-3 min)

- Lis l'enonce **deux fois**
- Identifie les **entrees** et les **sorties**
- Regarde les **exemples** et trace-les a la main
- Note les **contraintes** (taille de l'input, valeurs possibles)

### Etape 2 : Identifier le pattern (1-2 min)

Pose-toi ces questions :
- Array trie + recherche d'une paire ? **Two Pointers**
- Sous-tableau contigu ? **Sliding Window**
- Recherche dans un espace trie ? **Binary Search**
- Arbre ou graphe ? **BFS/DFS**
- Choix optimal a chaque etape ? **Greedy**
- Sous-problemes qui se repetent ? **DP**
- Explorer toutes les combinaisons ? **Backtracking**
- Composantes connexes / fusionner des groupes ? **Union-Find**
- Prochain plus grand / plus petit element ? **Monotonic Stack**

### Etape 3 : Brute Force d'abord (3-5 min)

- Ecris la solution la plus naive qui marche
- Calcule sa complexite
- Ca te donne une baseline et une meilleure comprehension du probleme

### Etape 4 : Optimiser (5-15 min)

- Applique le pattern identifie a l'etape 2
- Reduis la complexite temps (souvent de O(n^2) a O(n) ou O(n log n))
- Verifie avec les exemples

### Etape 5 : Coder et tester (5-10 min)

- Ecris le code propre
- Teste avec les exemples donnes
- Teste les edge cases : vide, un seul element, tous identiques, negatifs

---

## Progression recommandee

### Rythme

| Niveau         | Problemes/jour | Duree par probleme |
|----------------|----------------|--------------------|
| Debutant       | 1-2            | 30-45 min          |
| Intermediaire  | 2-3            | 20-30 min          |
| Avance         | 3-5            | 15-25 min          |

### Regles d'or

1. **Ne regarde pas la solution avant 20 minutes.** Le struggle est le processus d'apprentissage.
2. **Si tu bloques apres 25 min**, lis un indice (pas la solution complete). Reessaie.
3. **Si tu lis la solution**, comprends-la, ferme-la, et re-code-la de memoire.
4. **Revise les problemes** : refais un probleme 3 jours apres, puis 1 semaine apres.
5. **Un pattern a la fois.** Ne saute pas a DP avant de maitriser Two Pointers.
6. **Ecris la complexite** de chaque solution. Si tu peux pas l'expliquer, tu la comprends pas.

### Planning type (12 semaines)

```
Semaines 1-2  : Big O + Two Pointers + Sliding Window
Semaines 3-4  : Binary Search + Linked Lists + Stacks/Queues
Semaines 5-6  : Hash Maps + Trees + BST
Semaines 7-8  : BFS/DFS + Graphs
Semaines 9-10 : Dynamic Programming (la plus longue)
Semaines 11-12: Backtracking + Greedy + Heaps + Tries
Semaines 13-14: Union-Find + Monotonic Stack
```

Apres ces 12 semaines, tu seras capable de resoudre 80% des problemes Medium en moins de 30 minutes. Et ca, c'est le niveau ou les recruteurs FAANG commencent a te prendre au serieux.
