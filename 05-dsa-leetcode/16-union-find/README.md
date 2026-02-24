# Pattern 16 -- Union-Find (Disjoint Set Union)

## Principe

Union-Find est une structure de donnees qui gere une partition d'elements en ensembles disjoints.
Elle repond en quasi-O(1) amorti a deux operations :

- **find(x)** : quel ensemble contient x ? (retourne le representant/racine)
- **union(x, y)** : fusionner les ensembles de x et y

### Optimisations essentielles

**Path compression** : lors de find(), on fait pointer directement chaque noeud vers la racine.
Cela aplatit l'arbre pour les appels futurs.

**Union by rank** : on attache toujours le petit arbre sous le grand. On compare les "rangs"
(profondeur approximative) pour choisir qui devient racine.

Avec les deux optimisations, la complexite amortie est O(alpha(n)) -- pratiquement O(1).

---

## Schema ASCII : arbre avant / apres path compression

### Avant find(5)

```
         1  (racine)
        / \
       2   3
      /
     4
    /
   5        <- on cherche find(5)
```

Chemin parcouru : 5 -> 4 -> 2 -> 1

### Apres find(5) avec path compression

```
         1  (racine)
       / | \ \
      2  3  4  5   <- 4 et 5 pointent maintenant directement vers 1
     /
  (rien)
```

Tous les noeuds sur le chemin pointent desormais vers la racine.
Le prochain find(5) sera O(1).

### Union by rank

```
  Rang 0:  A    B    C    D    E

  union(A,B) -> rang A = 1, B sous A
       A (rang 1)
       |
       B

  union(C,D) -> rang C = 1, D sous C
       C (rang 1)
       |
       D

  union(A,C) -> rang egal -> A devient racine, rang A = 2
       A (rang 2)
      / \
     B   C
         |
         D
```

---

## Quand utiliser Union-Find

| Signal dans l'enonce            | Pattern                     |
|---------------------------------|-----------------------------|
| "composantes connexes"          | Union-Find ou BFS/DFS       |
| "meme groupe/cluster"           | Union-Find                  |
| "cycle dans un graphe non-oriente" | Union-Find              |
| "fusionner des groupes"         | Union-Find                  |
| "connexions dynamiques"         | Union-Find (pas BFS/DFS)    |
| "nombre de composantes"         | Union-Find (count--)        |

### Union-Find vs BFS/DFS

- Graphe **statique** + traversal simple -> BFS/DFS
- Graphe avec **ajout dynamique d'aretes** -> Union-Find
- Detecter un **cycle** en ajoutant des aretes une par une -> Union-Find
- Trouver le nombre de composantes **apres toutes les aretes** -> les deux marchent

---

## Complexite

| Operation | Sans optimisation | Path compression seul | Les deux |
|-----------|------------------|-----------------------|----------|
| find()    | O(n)             | O(log n) amorti       | O(alpha(n)) |
| union()   | O(n)             | O(log n) amorti       | O(alpha(n)) |
| Espace    | O(n)             | O(n)                  | O(n)     |

`alpha(n)` = inverse de la fonction d'Ackermann. Pour tout n pratique, alpha(n) <= 4.

---

## Problemes couverts

| # | Probleme                  | LeetCode | Difficulte |
|---|---------------------------|----------|------------|
| 1 | Number of Provinces       | #547     | Medium     |
| 2 | Redundant Connection      | #684     | Medium     |
| 3 | Accounts Merge            | #721     | Medium     |
| 4 | Most Stones Removed       | #947     | Medium     |
| 5 | Longest Consecutive Seq.  | #128     | Medium     |
