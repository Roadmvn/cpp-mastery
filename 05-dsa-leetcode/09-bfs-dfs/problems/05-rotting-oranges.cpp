// ============================================
// LeetCode #994 - Rotting Oranges (Medium) 🔄
// https://leetcode.com/problems/rotting-oranges/
// ============================================
//
// ENONCE :
// Grille avec : 0 = vide, 1 = orange fraiche, 2 = orange pourrie.
// Chaque minute, les oranges fraiches adjacentes (4 directions) a une
// orange pourrie deviennent pourries.
// Retourner le nombre de minutes pour que TOUTES les oranges soient pourries.
// Si impossible -> retourner -1.
//
//   Minute 0:    Minute 1:    Minute 2:    Minute 3:    Minute 4:
//   2 1 1        2 2 1        2 2 2        2 2 2        2 2 2
//   1 1 0   ->   2 1 0   ->   2 2 0   ->   2 2 0   ->   2 2 0
//   0 1 1        0 1 1        0 1 1        0 2 1        0 2 2
//                                                        -> 4 minutes
//
// C'EST DU BFS MULTI-SOURCE !
// On met toutes les oranges pourries dans la queue au depart
// et on propage niveau par niveau (chaque niveau = 1 minute)
//
// ============================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ============================================
// BRUTE FORCE : Simuler minute par minute
// A chaque minute, scanner toute la grille et pourrir les voisins
// Temps : O((m*n)^2) pire cas | Espace : O(1)
// ============================================
// (Inefficace car on re-scanne toute la grille a chaque minute)

// ============================================
// SOLUTION OPTIMALE : BFS multi-source
// 1. Ajouter toutes les oranges pourries dans la queue
// 2. BFS niveau par niveau (chaque niveau = 1 minute)
// 3. Compter les oranges fraiches restantes
// Temps : O(m*n) | Espace : O(m*n)
// ============================================
int orangesRotting(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    queue<pair<int, int>> q;
    int fresh = 0;

    // Etape 1 : compter les fraiches et ajouter les pourries
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 2) q.push({r, c});
            else if (grid[r][c] == 1) fresh++;
        }
    }

    if (fresh == 0) return 0; // rien a pourrir

    int minutes = 0;
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

    // Etape 2 : BFS multi-source
    while (!q.empty()) {
        int size = q.size();
        bool rotted = false;
        for (int i = 0; i < size; i++) {
            auto [r, c] = q.front();
            q.pop();
            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols
                    && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    q.push({nr, nc});
                    fresh--;
                    rotted = true;
                }
            }
        }
        if (rotted) minutes++;
    }

    return fresh == 0 ? minutes : -1;
}

int main() {
    // Test 1 : 4 minutes
    vector<vector<int>> g1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    cout << "Test 1 - 4 minutes: " << (orangesRotting(g1) == 4 ? "OK" : "FAIL") << endl;

    // Test 2 : impossible (-1)
    vector<vector<int>> g2 = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    cout << "Test 2 - impossible: " << (orangesRotting(g2) == -1 ? "OK" : "FAIL") << endl;

    // Test 3 : deja tout pourri
    vector<vector<int>> g3 = {{0, 2}};
    cout << "Test 3 - deja pourri: " << (orangesRotting(g3) == 0 ? "OK" : "FAIL") << endl;

    // Test 4 : pas d'orange
    vector<vector<int>> g4 = {{0}};
    cout << "Test 4 - pas d'orange: " << (orangesRotting(g4) == 0 ? "OK" : "FAIL") << endl;

    // Test 5 : une fraiche, une pourrie adjacente
    vector<vector<int>> g5 = {{2, 1}};
    cout << "Test 5 - 1 minute: " << (orangesRotting(g5) == 1 ? "OK" : "FAIL") << endl;

    return 0;
}
