// ============================================
// LeetCode #200 - Number of Islands (Medium) 🔄
// https://leetcode.com/problems/number-of-islands/
// ============================================
//
// ENONCE :
// Compter le nombre d'iles dans une grille 2D.
// '1' = terre, '0' = eau.
// Une ile = un groupe de '1' connectes horizontalement/verticalement.
//
//   1 1 1 1 0
//   1 1 0 1 0       -> 1 ile
//   1 1 0 0 0
//   0 0 0 0 0
//
//   1 1 0 0 0
//   1 1 0 0 0       -> 3 iles
//   0 0 1 0 0
//   0 0 0 1 1
//
// ============================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ============================================
// BRUTE FORCE : BFS pour chaque ile
// Pour chaque '1' non visite, lancer un BFS et compter
// Temps : O(m*n) | Espace : O(m*n) pour la queue
// ============================================
// int numIslands(vector<vector<char>>& grid) {
//     int rows = grid.size(), cols = grid[0].size();
//     int count = 0;
//     int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
//     for (int r = 0; r < rows; r++) {
//         for (int c = 0; c < cols; c++) {
//             if (grid[r][c] == '1') {
//                 count++;
//                 queue<pair<int,int>> q;
//                 q.push({r, c});
//                 grid[r][c] = '0';
//                 while (!q.empty()) {
//                     auto [cr, cc] = q.front(); q.pop();
//                     for (auto& d : dirs) {
//                         int nr = cr+d[0], nc = cc+d[1];
//                         if (nr>=0 && nr<rows && nc>=0 && nc<cols && grid[nr][nc]=='1') {
//                             grid[nr][nc] = '0';
//                             q.push({nr, nc});
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     return count;
// }

// ============================================
// SOLUTION OPTIMALE : DFS recursif
// Pour chaque '1', couler toute l'ile avec DFS et incrementer le compteur
// Temps : O(m*n) | Espace : O(m*n) pire cas (pile d'appels)
// ============================================
void dfs(vector<vector<char>>& grid, int r, int c) {
    int rows = grid.size(), cols = grid[0].size();
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == '0')
        return;
    grid[r][c] = '0'; // couler la terre (marquer visite)
    dfs(grid, r - 1, c);
    dfs(grid, r + 1, c);
    dfs(grid, r, c - 1);
    dfs(grid, r, c + 1);
}

int numIslands(vector<vector<char>>& grid) {
    int count = 0;
    for (int r = 0; r < (int)grid.size(); r++) {
        for (int c = 0; c < (int)grid[0].size(); c++) {
            if (grid[r][c] == '1') {
                dfs(grid, r, c);
                count++;
            }
        }
    }
    return count;
}

int main() {
    // Test 1 : 1 ile
    vector<vector<char>> g1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    cout << "Test 1 - 1 ile: " << (numIslands(g1) == 1 ? "OK" : "FAIL") << endl;

    // Test 2 : 3 iles
    vector<vector<char>> g2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "Test 2 - 3 iles: " << (numIslands(g2) == 3 ? "OK" : "FAIL") << endl;

    // Test 3 : aucune ile
    vector<vector<char>> g3 = {
        {'0','0','0'},
        {'0','0','0'}
    };
    cout << "Test 3 - 0 ile: " << (numIslands(g3) == 0 ? "OK" : "FAIL") << endl;

    // Test 4 : tout est terre
    vector<vector<char>> g4 = {
        {'1','1'},
        {'1','1'}
    };
    cout << "Test 4 - tout terre: " << (numIslands(g4) == 1 ? "OK" : "FAIL") << endl;

    // Test 5 : damier
    vector<vector<char>> g5 = {
        {'1','0','1'},
        {'0','1','0'},
        {'1','0','1'}
    };
    cout << "Test 5 - damier 5 iles: " << (numIslands(g5) == 5 ? "OK" : "FAIL") << endl;

    return 0;
}
