// ============================================
// PATTERN : BFS vs DFS - Templates 
// ============================================
// Squelettes copier-coller pour BFS et DFS
// Compile : g++ -std=c++17 -o pattern pattern-template.cpp
// ============================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ============================================
// TEMPLATE 1 : DFS sur grille 2D (recursif)
// ============================================
void dfsGrid(vector<vector<int>>& grid, int r, int c) {
    int rows = grid.size(), cols = grid[0].size();
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 0)
        return;
    grid[r][c] = 0; // marquer visite
    dfsGrid(grid, r - 1, c); // haut
    dfsGrid(grid, r + 1, c); // bas
    dfsGrid(grid, r, c - 1); // gauche
    dfsGrid(grid, r, c + 1); // droite
}

// ============================================
// TEMPLATE 2 : BFS sur grille 2D
// ============================================
void bfsGrid(vector<vector<int>>& grid, int r, int c) {
    int rows = grid.size(), cols = grid[0].size();
    queue<pair<int, int>> q;
    q.push({r, c});
    grid[r][c] = 0; // marquer visite
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        auto [cr, cc] = q.front();
        q.pop();
        for (auto& d : dirs) {
            int nr = cr + d[0], nc = cc + d[1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                grid[nr][nc] = 0;
                q.push({nr, nc});
            }
        }
    }
}

// ============================================
// TEMPLATE 3 : Compter les composantes connexes (iles)
// ============================================
int countIslands(vector<vector<int>> grid) { // copie volontaire
    int count = 0;
    for (int r = 0; r < (int)grid.size(); r++) {
        for (int c = 0; c < (int)grid[0].size(); c++) {
            if (grid[r][c] == 1) {
                dfsGrid(grid, r, c);
                count++;
            }
        }
    }
    return count;
}

// ============================================
// TEMPLATE 4 : DFS sur graphe (adjacency list)
// ============================================
void dfsGraph(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfsGraph(neighbor, adj, visited);
        }
    }
}

// ============================================
// TEMPLATE 5 : BFS sur graphe (adjacency list)
// ============================================
void bfsGraph(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// ============================================
// TEMPLATE 6 : BFS plus court chemin (retourne distance)
// ============================================
int bfsShortestPath(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> end) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, int>> q;
    q.push(start);
    visited[start.first][start.second] = true;
    int dist = 0;
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto [r, c] = q.front();
            q.pop();
            if (r == end.first && c == end.second) return dist;
            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols
                    && !visited[nr][nc] && grid[nr][nc] == 1) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        dist++;
    }
    return -1; // pas de chemin
}

int main() {
    // Test : compter les iles
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1}
    };

    cout << "Nombre d'iles: " << countIslands(grid) << endl; // 3

    // Test : DFS sur graphe
    //  0 -- 1 -- 2
    //       |
    //       3 -- 4
    int n = 5;
    vector<vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[3].push_back(4); adj[4].push_back(3);

    vector<bool> visited(n, false);
    dfsGraph(0, adj, visited);
    bool allVisited = true;
    for (bool v : visited) if (!v) allVisited = false;
    cout << "DFS graphe visite tout: " << (allVisited ? "OUI" : "NON") << endl;

    return 0;
}
