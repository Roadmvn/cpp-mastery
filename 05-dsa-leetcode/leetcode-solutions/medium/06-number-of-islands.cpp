// https://leetcode.com/problems/number-of-islands/
// #200 - Number of Islands
//
// Compter le nombre d'iles dans une grille 2D ('1' = terre, '0' = eau).
// Une ile est un groupe de '1' connectes horizontalement/verticalement.
//
// Approche : DFS — chaque fois qu'on trouve un '1', incrementer le compteur
// et faire un DFS pour marquer toute l'ile (eviter de la recompter).
// Complexite temps : O(m*n) | Complexite espace : O(m*n) pile recursive pire cas

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;

        int rows = (int)grid.size();
        int cols = (int)grid[0].size();
        int count = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    count++;
                    dfs(grid, r, c, rows, cols);
                }
            }
        }

        return count;
    }

private:
    void dfs(vector<vector<char>>& grid, int r, int c, int rows, int cols) {
        // Hors limites ou eau ou deja visite
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;

        // Marquer comme visite en "noyant" la terre
        grid[r][c] = '0';

        // Explorer les 4 directions
        dfs(grid, r + 1, c, rows, cols);
        dfs(grid, r - 1, c, rows, cols);
        dfs(grid, r, c + 1, rows, cols);
        dfs(grid, r, c - 1, rows, cols);
    }
};

int main() {
    Solution sol;

    // Test 1 : 1 ile
    vector<vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    cout << sol.numIslands(grid1) << endl; // 1

    // Test 2 : 3 iles
    vector<vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << sol.numIslands(grid2) << endl; // 3

    // Test 3 : grille d'eau
    vector<vector<char>> grid3 = {
        {'0','0'},
        {'0','0'}
    };
    cout << sol.numIslands(grid3) << endl; // 0

    return 0;
}
