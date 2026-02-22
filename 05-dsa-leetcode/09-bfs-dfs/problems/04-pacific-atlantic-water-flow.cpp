// ============================================
// LeetCode #417 - Pacific Atlantic Water Flow (Medium) 
// https://leetcode.com/problems/pacific-atlantic-water-flow/
// ============================================
//
// ENONCE :
// Ile rectangulaire bordee par le Pacifique (haut/gauche)
// et l'Atlantique (bas/droite).
// L'eau coule d'une cellule vers une voisine si la voisine a
// une hauteur <= a la cellule actuelle.
// Trouver toutes les cellules d'ou l'eau peut couler vers LES DEUX oceans.
//
//   Pacific ~  ~  ~  ~  ~
//        ~  1  2  2  3 (5) *
//        ~  3  2  3 (4)(4) *
//        ~  2  4 (5) 3  1  *
//        ~ (6)(7) 1  4  5  *
//        ~ (5) 1  1  2  4  *
//           *  *  *  *  * Atlantic
//
// Parentheses = cellules qui atteignent les deux oceans
// Resultat : [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
//
// ASTUCE : au lieu de verifier "l'eau coule vers l'ocean",
// on fait l'INVERSE : depuis les bords, on remonte (DFS/BFS)
// vers les cellules plus hautes ou egales.
//
// ============================================

#include <iostream>
#include <vector>
using namespace std;

// ============================================
// BRUTE FORCE : DFS depuis chaque cellule vers les 2 oceans
// Pour chaque cellule, verifier si l'eau atteint Pacifique ET Atlantique
// Temps : O((m*n)^2) | Espace : O(m*n)
// ============================================
// (Trop lent, on fait DFS/BFS depuis chaque cellule independamment)

// ============================================
// SOLUTION OPTIMALE : DFS inverse depuis les bords
// 1. DFS depuis bord Pacifique (haut + gauche) -> marquer cellules atteignables
// 2. DFS depuis bord Atlantique (bas + droite) -> marquer cellules atteignables
// 3. Intersection des deux = reponse
// Temps : O(m*n) | Espace : O(m*n)
// ============================================
void dfs(vector<vector<int>>& heights, vector<vector<bool>>& reachable,
         int r, int c) {
    int rows = heights.size(), cols = heights[0].size();
    reachable[r][c] = true;
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    for (auto& d : dirs) {
        int nr = r + d[0], nc = c + d[1];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols
            && !reachable[nr][nc]
            && heights[nr][nc] >= heights[r][c]) { // remonter = >=
            dfs(heights, reachable, nr, nc);
        }
    }
}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    int rows = heights.size(), cols = heights[0].size();
    vector<vector<bool>> pacific(rows, vector<bool>(cols, false));
    vector<vector<bool>> atlantic(rows, vector<bool>(cols, false));

    // DFS depuis les bords Pacifique (ligne 0 + colonne 0)
    for (int c = 0; c < cols; c++) dfs(heights, pacific, 0, c);
    for (int r = 0; r < rows; r++) dfs(heights, pacific, r, 0);

    // DFS depuis les bords Atlantique (derniere ligne + derniere colonne)
    for (int c = 0; c < cols; c++) dfs(heights, atlantic, rows - 1, c);
    for (int r = 0; r < rows; r++) dfs(heights, atlantic, r, cols - 1);

    // Intersection
    vector<vector<int>> result;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (pacific[r][c] && atlantic[r][c]) {
                result.push_back({r, c});
            }
        }
    }
    return result;
}

int main() {
    vector<vector<int>> h1 = {
        {1, 2, 2, 3, 5},
        {3, 2, 3, 4, 4},
        {2, 4, 5, 3, 1},
        {6, 7, 1, 4, 5},
        {5, 1, 1, 2, 4}
    };

    auto res1 = pacificAtlantic(h1);
    cout << "Test 1 - nb cellules: " << res1.size() << " (attendu 7)" << endl;
    cout << "  Cellules: ";
    for (auto& cell : res1) cout << "[" << cell[0] << "," << cell[1] << "] ";
    cout << endl;
    cout << "  -> " << (res1.size() == 7 ? "OK" : "FAIL") << endl;

    // Test 2 : grille 1x1
    vector<vector<int>> h2 = {{1}};
    auto res2 = pacificAtlantic(h2);
    cout << "Test 2 - 1x1: " << (res2.size() == 1 ? "OK" : "FAIL") << endl;

    // Test 3 : hauteurs identiques -> tout atteint les deux
    vector<vector<int>> h3 = {
        {1, 1},
        {1, 1}
    };
    auto res3 = pacificAtlantic(h3);
    cout << "Test 3 - tout egal: " << (res3.size() == 4 ? "OK" : "FAIL") << endl;

    return 0;
}
