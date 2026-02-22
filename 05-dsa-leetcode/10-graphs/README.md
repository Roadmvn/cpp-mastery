# 10 - Graphs : Theorie des graphes 📊

## C'est quoi un graphe ?

Ensemble de noeuds (vertices) connectes par des aretes (edges).

```
Types de graphes :

DIRIGE (oriented) :         NON DIRIGE :
  A ---> B                   A --- B
  |      |                   |     |
  v      v                   |     |
  C ---> D                   C --- D

Aretes : A->B, A->C, B->D, C->D    Aretes : A-B, A-C, B-D, C-D
```

## Representations en memoire 📋

```
Graphe :    0 --- 1
            |   / |
            |  /  |
            2 --- 3

ADJACENCY LIST (la plus courante) :
  0: [1, 2]
  1: [0, 2, 3]
  2: [0, 1, 3]
  3: [1, 2]

  vector<vector<int>> adj(4);
  adj[0] = {1, 2};
  adj[1] = {0, 2, 3};
  ...

ADJACENCY MATRIX :
       0  1  2  3
    0 [0, 1, 1, 0]
    1 [1, 0, 1, 1]
    2 [1, 1, 0, 1]
    3 [0, 1, 1, 0]

  vector<vector<int>> mat(4, vector<int>(4, 0));
  mat[0][1] = mat[1][0] = 1;
  ...

             | Adjacency List | Adjacency Matrix
  -----------|----------------|------------------
  Espace     | O(V + E)       | O(V^2)
  Arete ?    | O(degre)       | O(1)
  Voisins    | O(degre)       | O(V)
  Meilleur   | Graphe creux   | Graphe dense
```

## Algorithmes essentiels 🔧

```
1. DFS / BFS : parcourir, composantes connexes
2. Topological Sort : ordre des dependances (DAG)
3. Union-Find : composantes connexes, detecter cycles
4. Dijkstra : plus court chemin (poids positifs)
5. Detection de cycle : DFS avec etats (blanc/gris/noir)
```

## Detection de cycle dans un graphe dirige 🔄

```
Etats des noeuds :
  BLANC (0) = pas encore visite
  GRIS  (1) = en cours de visite (dans la pile DFS)
  NOIR  (2) = completement traite

Si on rencontre un noeud GRIS pendant le DFS -> CYCLE !

  A -> B -> C
  ^         |
  |         v
  +-------- D      <- Cycle : A->B->C->D->A

DFS depuis A :
  A(gris) -> B(gris) -> C(gris) -> D(gris) -> A est GRIS = CYCLE!
```

## Union-Find (Disjoint Set) 🔗

```
Detecter si deux noeuds sont dans le meme composant.
Utile pour : composantes connexes, detecter aretes redondantes.

Initialement :    Apres union(0,1) :    Apres union(2,3) :
  {0} {1} {2} {3}     {0,1} {2} {3}       {0,1} {2,3}

  parent: [0,1,2,3]   parent: [0,0,2,3]   parent: [0,0,2,2]

find(1) = 0           find(3) = 2
union(1,3) -> parent: [0,0,2,0]  -> {0,1,2,3} tout connecte
```

## Quand utiliser quoi ? 🎯

| Probleme | Algorithme |
|----------|-----------|
| Composantes connexes | DFS/BFS ou Union-Find |
| Ordre des cours/taches | Topological Sort (BFS Kahn) |
| Detecter un cycle (dirige) | DFS avec 3 couleurs |
| Aretes redondantes | Union-Find |
| Plus court chemin (poids) | Dijkstra (priority queue) |

## Checkpoint ✅

Avant de passer au pattern suivant, tu dois savoir :
- [ ] Construire un graphe (adjacency list)
- [ ] Parcourir un graphe avec DFS et BFS
- [ ] Faire un tri topologique (Kahn's algorithm)
- [ ] Implementer Union-Find avec path compression
- [ ] Detecter un cycle dans un graphe dirige
- [ ] Utiliser Dijkstra pour le plus court chemin pondere
