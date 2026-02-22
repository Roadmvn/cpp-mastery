# 09 - BFS vs DFS : Parcours de graphes et grilles 🔄

## C'est quoi BFS et DFS ?

Deux strategies fondamentales pour explorer un graphe ou une grille.

```
BFS (Breadth-First Search) = Parcours en LARGEUR 📊
  Explore niveau par niveau, comme une vague qui s'etend
  Utilise une QUEUE (FIFO)

DFS (Depth-First Search) = Parcours en PROFONDEUR 🔍
  Va le plus loin possible avant de revenir
  Utilise une STACK (LIFO) ou la RECURSION
```

## Schema ASCII : BFS vs DFS

```
Graphe :
        [1]
       / | \
     [2] [3] [4]
    / \       |
  [5] [6]    [7]

BFS (niveau par niveau) :
  File :  [1]
  Visit:  1
  File :  [2, 3, 4]
  Visit:  2, 3, 4
  File :  [5, 6, 7]
  Visit:  5, 6, 7
  Ordre final : 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7

DFS (profondeur d'abord) :
  Pile :  [1]
  Visit:  1 -> 2 -> 5 (fond!) -> retour -> 6 (fond!) -> retour
       -> 3 (fond!) -> retour -> 4 -> 7 (fond!)
  Ordre final : 1 -> 2 -> 5 -> 6 -> 3 -> 4 -> 7
```

## Application sur une grille 2D 🗺️

```
Grille (1 = terre, 0 = eau) :

  1 1 0 0 0         Ile 1       Ile 2
  1 1 0 0 0         [1 1] 0 0 0
  0 0 1 0 0    ->    0 0 [1] 0 0
  0 0 0 1 1          0 0  0 [1 1]
                                Ile 3

DFS depuis (0,0) :
  Visite (0,0) -> (0,1) -> (1,0) -> (1,1) -> fin de l'ile
  4 directions : haut, bas, gauche, droite
  dx = [-1, 1, 0, 0]
  dy = [0, 0, -1, 1]

BFS depuis (0,0) :
  Queue: (0,0)
  Visit (0,0) -> ajoute (0,1), (1,0)
  Visit (0,1) -> ajoute (1,1)
  Visit (1,0) -> ajoute (1,1) deja vu
  Visit (1,1) -> fin
```

## Quand utiliser BFS vs DFS ? 🎯

| Situation | Choix | Pourquoi |
|-----------|-------|----------|
| Plus court chemin (non pondere) | BFS | Garantit le plus court |
| Compter composantes connexes | DFS ou BFS | Les deux marchent |
| Detecter un cycle | DFS | Plus naturel avec recursion |
| Parcours par niveaux | BFS | C'est sa definition |
| Explorer toutes les solutions | DFS | Backtracking naturel |
| Espace memoire limite | DFS | O(h) vs O(largeur) |
| Propagation (virus, incendie) | BFS | Simule le temps reel |

## Templates de base 📋

```cpp
// DFS sur grille 2D
void dfs(vector<vector<int>>& grid, int r, int c) {
    int rows = grid.size(), cols = grid[0].size();
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 0)
        return;
    grid[r][c] = 0; // marquer visite
    dfs(grid, r-1, c); // haut
    dfs(grid, r+1, c); // bas
    dfs(grid, r, c-1); // gauche
    dfs(grid, r, c+1); // droite
}

// BFS sur grille 2D
void bfs(vector<vector<int>>& grid, int r, int c) {
    int rows = grid.size(), cols = grid[0].size();
    queue<pair<int,int>> q;
    q.push({r, c});
    grid[r][c] = 0;
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    while (!q.empty()) {
        auto [cr, cc] = q.front(); q.pop();
        for (auto& d : dirs) {
            int nr = cr + d[0], nc = cc + d[1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                grid[nr][nc] = 0;
                q.push({nr, nc});
            }
        }
    }
}
```

## Checkpoint ✅

Avant de passer au pattern suivant, tu dois savoir :
- [ ] Implementer BFS et DFS sur une grille 2D
- [ ] Compter les composantes connexes (iles)
- [ ] Utiliser BFS pour le plus court chemin
- [ ] Utiliser DFS pour explorer tout un composant
- [ ] Choisir entre BFS et DFS selon le probleme
