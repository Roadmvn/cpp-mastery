// ============================================
// LeetCode #695 - Max Area of Island (Medium) 
// https://leetcode.com/problems/max-area-of-island/
// ============================================
//
// ENONCE :
// Trouver l'aire maximale d'une ile dans une grille 2D.
// L'aire d'une ile = nombre de cellules '1' connectees.
// Retourner 0 si aucune ile.
//
//   0 0 1 0 0 0 0 1 1 0 0 0 0
//   0 0 0 0 0 0 0 1 1 0 1 0 0
//   0 0 0 0 1 0 0 0 0 0 1 0 0
//   0 0 0 0 1 1 0 0 1 0 1 0 0
//   0 0 0 0 1 1 0 0 1 1 1 0 0
//
//   Ile en bas a gauche : aire = 4 (la colonne de 1)
//   ... aire max = 6 (le bloc en bas a droite)
//
// ============================================

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// ============================================
// BRUTE FORCE : BFS pour calculer l'aire de chaque ile
// Pour chaque '1', BFS et compter les cellules
// Temps : O(m*n) | Espace : O(m*n)
// ============================================
// int maxAreaOfIsland(vector<vector<int>>& grid) {
//     int rows = grid.size(), cols = grid[0].size();
//     int maxArea = 0;
//     int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
//     for (int r = 0; r < rows; r++) {
//         for (int c = 0; c < cols; c++) {
//             if (grid[r][c] == 1) {
//                 int area = 0;
//                 queue<pair<int,int>> q;
//                 q.push({r, c});
//                 grid[r][c] = 0;
//                 while (!q.empty()) {
//                     auto [cr, cc] = q.front(); q.pop();
//                     area++;
//                     for (auto& d : dirs) {
//                         int nr = cr+d[0], nc = cc+d[1];
//                         if (nr>=0 && nr<rows && nc>=0 && nc<cols && grid[nr][nc]==1) {
//                             grid[nr][nc] = 0;
//                             q.push({nr, nc});
//                         }
//                     }
//                 }
//                 maxArea = max(maxArea, area);
//             }
//         }
//     }
//     return maxArea;
// }

// ============================================
// SOLUTION OPTIMALE : DFS recursif retournant l'aire
// Chaque appel DFS retourne 1 + aire des voisins
// Temps : O(m*n) | Espace : O(m*n) pire cas pile
// ============================================
int dfs(vector<vector<int>>& grid, int r, int c) {
    int rows = grid.size(), cols = grid[0].size();
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 0)
        return 0;
    grid[r][c] = 0; // marquer visite
    return 1 + dfs(grid, r-1, c) + dfs(grid, r+1, c)
             + dfs(grid, r, c-1) + dfs(grid, r, c+1);
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int maxArea = 0;
    for (int r = 0; r < (int)grid.size(); r++) {
        for (int c = 0; c < (int)grid[0].size(); c++) {
            if (grid[r][c] == 1) {
                maxArea = max(maxArea, dfs(grid, r, c));
            }
        }
    }
    return maxArea;
}

int main() {
    // Test 1
    vector<vector<int>> g1 = {
        {0,0,1,0,0,0,0,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,1,0,0},
        {0,0,0,0,1,0,0,0,0,0,1,0,0},
        {0,0,0,0,1,1,0,0,1,0,1,0,0},
        {0,0,0,0,1,1,0,0,1,1,1,0,0}
    };
    cout << "Test 1 - aire max 6: " << (maxAreaOfIsland(g1) == 6 ? "OK" : "FAIL")
         << " (got " << maxAreaOfIsland(g1) << ")" << endl;
    // Note: g1 est modifiee apres le premier appel, le 2e retourne 0

    // Test 2 : pas d'ile
    vector<vector<int>> g2 = {
        {0,0,0},
        {0,0,0}
    };
    cout << "Test 2 - pas d'ile: " << (maxAreaOfIsland(g2) == 0 ? "OK" : "FAIL") << endl;

    // Test 3 : une seule cellule
    vector<vector<int>> g3 = {{1}};
    cout << "Test 3 - une cellule: " << (maxAreaOfIsland(g3) == 1 ? "OK" : "FAIL") << endl;

    // Test 4 : tout terre
    vector<vector<int>> g4 = {
        {1,1,1},
        {1,1,1}
    };
    cout << "Test 4 - tout terre: " << (maxAreaOfIsland(g4) == 6 ? "OK" : "FAIL") << endl;

    // Test 5 : deux iles
    vector<vector<int>> g5 = {
        {1,1,0,0,1},
        {1,0,0,0,1},
        {0,0,0,1,1}
    };
    cout << "Test 5 - max entre 2 iles: " << (maxAreaOfIsland(g5) == 4 ? "OK" : "FAIL") << endl;

    return 0;
}
