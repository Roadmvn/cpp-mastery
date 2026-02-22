# Queue et Deque 🚶

> First In, First Out — la structure du BFS et du traitement sequentiel

## Pourquoi c'est important

Le BFS (Breadth-First Search) utilise une queue. C'est LE parcours pour trouver le chemin le plus court dans un graphe non pondere. `deque` est la version double-ended, utile pour le Sliding Window Maximum et les BFS a cout 0/1. Maitriser queue/deque = maitriser les parcours de graphes.

---

## Queue vs Deque en memoire

```
queue<int> q;                      deque<int> d;
q.push(10); q.push(20); q.push(30);   d.push_back(10); d.push_back(20); d.push_back(30);

QUEUE : FIFO (First In, First Out)

  front()                back()
    |                      |
    v                      v
┌──────┬──────┬──────┐
│  10  │  20  │  30  │
└──────┴──────┴──────┘
    ^                      ^
  pop()               push()
 (retire 10)         (ajoute ici)


DEQUE : Double-Ended Queue

  front()                      back()
    |                            |
    v                            v
┌──────┬──────┬──────┐
│  10  │  20  │  30  │
└──────┴──────┴──────┘
  ^  ^                      ^  ^
  |  push_front()     push_back()  |
  pop_front()        pop_back()

En interne, deque utilise des blocs de memoire :
┌─────────┐   ┌─────────┐   ┌─────────┐
│ bloc 0  │   │ bloc 1  │   │ bloc 2  │
│ [a][b]  │   │ [c][d]  │   │ [e][f]  │
└─────────┘   └─────────┘   └─────────┘
                                 
     └──────────────┼──────────────┘
              map de pointeurs
         (acces O(1) par index)
```

---

## Methodes essentielles

### queue

| Methode    | Description                    | Complexite |
|-----------|-------------------------------|------------|
| `push(x)` | Ajoute a la fin               | O(1)       |
| `pop()`    | Retire du debut               | O(1)       |
| `front()`  | Premier element               | O(1)       |
| `back()`   | Dernier element               | O(1)       |
| `empty()`  | True si vide                  | O(1)       |
| `size()`   | Nombre d'elements             | O(1)       |

### deque

| Methode         | Description                    | Complexite |
|----------------|-------------------------------|------------|
| `push_back(x)`  | Ajoute a la fin               | O(1)       |
| `push_front(x)` | Ajoute au debut               | O(1)       |
| `pop_back()`    | Retire de la fin              | O(1)       |
| `pop_front()`   | Retire du debut               | O(1)       |
| `front()`       | Premier element               | O(1)       |
| `back()`        | Dernier element               | O(1)       |
| `d[i]`          | Acces par index               | O(1)       |
| `size()`        | Nombre d'elements             | O(1)       |

---

## BFS avec queue — Le pattern fondamental 

```cpp
#include <queue>

// BFS sur une grille (trouver distance min)
int bfs(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> end) {
    int rows = grid.size(), cols = grid[0].size();
    queue<pair<int,int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    q.push(start);
    visited[start.first][start.second] = true;
    int dist = 0;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        int size = q.size();  // IMPORTANT : taille du niveau actuel
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();

            if (x == end.first && y == end.second) return dist;

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols
                    && !visited[nx][ny] && grid[nx][ny] == 0) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        dist++;
    }
    return -1;  // pas de chemin
}
```

---

## Quand utiliser queue vs deque 

| Besoin                                | Utiliser           |
|---------------------------------------|-------------------|
| BFS classique                         | `queue`           |
| Parcours niveau par niveau            | `queue`           |
| Ajout/retrait aux deux bouts          | `deque`           |
| Sliding Window Maximum                | `deque` (monotonic)|
| BFS 0-1 (poids 0 ou 1)               | `deque`           |
| Besoin d'acces par index + push/pop   | `deque`           |

---

## Checkpoint

1. Quelle est la difference fondamentale entre queue et stack ?
2. Pourquoi BFS utilise une queue et pas un stack ?
3. Quel avantage a deque sur queue ?
4. Comment gerer les "niveaux" dans un BFS avec une queue ?

---

## Fichiers

| Fichier          | Description                                    |
|------------------|------------------------------------------------|
| `exercise.cpp`   | Exercices guides : queue, deque, BFS basique   |
| `solution.cpp`   | Solutions completes                            |
| `challenge.cpp`  | Challenge : BFS sur grille                     |
