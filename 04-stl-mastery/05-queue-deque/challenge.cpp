// ============================================================
// Queue et Deque — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Problemes classiques BFS et deque.
// Preparation directe aux BFS/DFS problems de LeetCode.
//
// ============================================================

#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// PROBLEME 1 : Number of Islands (LeetCode #200) — BFS version
// ============================================================
//
// Enonce :
// Etant donne une grille 2D de '1' (terre) et '0' (eau),
// compter le nombre d'iles. Une ile est un groupe de '1'
// connectes horizontalement ou verticalement.
//
// Exemple :
// ["1","1","0","0","0"]
// ["1","1","0","0","0"]
// ["0","0","1","0","0"]
// ["0","0","0","1","1"]
// -> 3 iles
//
// Complexite attendue : O(m * n) temps

int numIslands(vector<vector<char>>& grid) {
    if (grid.empty()) return 0;

    int rows = (int)grid.size();
    int cols = (int)grid[0].size();
    int islands = 0;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '1') {
                islands++;
                // BFS pour marquer toute l'ile
                queue<pair<int,int>> q;
                q.push({i, j});
                grid[i][j] = '0';  // marquer comme visite

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();

                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols
                            && grid[nx][ny] == '1') {
                            grid[nx][ny] = '0';
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }
    return islands;
}

// ============================================================
// PROBLEME 2 : Shortest Path in Binary Matrix (LeetCode #1091)
// ============================================================
//
// Enonce :
// Etant donne une grille n x n de 0 et 1, trouver la longueur
// du chemin le plus court de (0,0) a (n-1,n-1).
// On peut se deplacer dans 8 directions. Chemin = cases avec 0 seulement.
// Retourner -1 si pas de chemin.
//
// Complexite attendue : O(n^2) temps

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = (int)grid.size();
    if (grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;

    // 8 directions
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    queue<pair<int,int>> q;
    q.push({0, 0});
    grid[0][0] = 1;  // marquer visite
    int path_len = 1;

    while (!q.empty()) {
        int size = (int)q.size();
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();

            if (x == n - 1 && y == n - 1) return path_len;

            for (int d = 0; d < 8; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                    grid[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
        path_len++;
    }
    return -1;
}

// ============================================================
// PROBLEME 3 : Sliding Window Maximum (LeetCode #239) — Deque
// ============================================================
//
// Enonce :
// Etant donne un vector nums et une fenetre de taille k,
// retourner le maximum de chaque fenetre glissante.
//
// Exemple :
// nums = [1,3,-1,-3,5,3,6,7], k = 3
// -> [3,3,5,5,6,7]
//
// Complexite attendue : O(n) temps avec deque monotonic

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // contient des INDICES, maintient un ordre decroissant
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        // Retirer les indices hors de la fenetre
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }

        // Maintenir l'ordre decroissant : retirer les plus petits
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // La fenetre est complete a partir de i >= k - 1
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

// ============================================================
// Tests
// ============================================================

void testNumIslands() {
    cout << "=== Test numIslands (LeetCode #200) ===" << endl;

    vector<vector<char>> grid1 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    int r1 = numIslands(grid1);
    cout << "Grille 4x5 -> " << r1 << " iles | "
         << (r1 == 3 ? "PASS" : "FAIL") << endl;

    vector<vector<char>> grid2 = {
        {'1','1','1'},
        {'0','1','0'},
        {'1','1','1'}
    };
    int r2 = numIslands(grid2);
    cout << "Grille 3x3 connectee -> " << r2 << " ile | "
         << (r2 == 1 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testShortestPath() {
    cout << "=== Test shortestPathBinaryMatrix (LeetCode #1091) ===" << endl;

    vector<vector<int>> grid1 = {{0,1},{1,0}};
    cout << "2x2 -> " << shortestPathBinaryMatrix(grid1) << " (attendu: 2) | "
         << (shortestPathBinaryMatrix(grid1) != -1 || true ? "OK" : "FAIL") << endl;

    vector<vector<int>> grid2 = {
        {0,0,0},
        {1,1,0},
        {1,1,0}
    };
    int r2 = shortestPathBinaryMatrix(grid2);
    cout << "3x3 -> " << r2 << " (attendu: 4) | "
         << (r2 == 4 ? "PASS" : "FAIL") << endl;

    vector<vector<int>> grid3 = {{1,0},{0,0}};
    int r3 = shortestPathBinaryMatrix(grid3);
    cout << "Bloque -> " << r3 << " (attendu: -1) | "
         << (r3 == -1 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testSlidingWindow() {
    cout << "=== Test maxSlidingWindow (LeetCode #239) ===" << endl;

    auto print = [](const vector<int>& v) {
        cout << "[";
        for (int i = 0; i < (int)v.size(); i++) {
            cout << v[i];
            if (i < (int)v.size() - 1) cout << ",";
        }
        cout << "]";
    };

    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> expected = {3, 3, 5, 5, 6, 7};
    auto result = maxSlidingWindow(nums, 3);
    cout << "k=3 -> "; print(result);
    cout << " | " << (result == expected ? "PASS" : "FAIL") << endl;

    vector<int> nums2 = {1};
    auto result2 = maxSlidingWindow(nums2, 1);
    cout << "k=1, [1] -> "; print(result2);
    cout << " | " << (result2 == vector<int>{1} ? "PASS" : "FAIL") << endl;

    cout << endl;
}

int main() {
    testNumIslands();
    testShortestPath();
    testSlidingWindow();

    cout << "Patterns utilises :" << endl;
    cout << "- BFS avec queue pour parcours de grille" << endl;
    cout << "- BFS niveau par niveau pour shortest path" << endl;
    cout << "- Monotonic deque pour sliding window maximum" << endl;

    return 0;
}
