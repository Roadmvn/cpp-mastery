// ============================================
// LeetCode #547 - Number of Provinces (Medium) 
// https://leetcode.com/problems/number-of-provinces/
// ============================================
//
// ENONCE :
// n villes. isConnected[i][j] = 1 si ville i et j sont connectees directement.
// Une province = un groupe de villes connectees (directement ou indirectement).
// Retourner le nombre de provinces.
//
//   isConnected = [[1,1,0],    Ville 0-1 connectees, ville 2 isolee
//                  [1,1,0],    -> 2 provinces : {0,1} et {2}
//                  [0,0,1]]
//
//   isConnected = [[1,0,0],    Aucune connexion
//                  [0,1,0],    -> 3 provinces : {0}, {1}, {2}
//                  [0,0,1]]
//
// ============================================

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

// ============================================
// BRUTE FORCE : DFS pour compter les composantes connexes
// Pour chaque ville non visitee, DFS et compter
// Temps : O(n^2) | Espace : O(n)
// ============================================
// void dfs(int city, vector<vector<int>>& isConnected, vector<bool>& visited) {
//     visited[city] = true;
//     for (int j = 0; j < (int)isConnected.size(); j++) {
//         if (isConnected[city][j] == 1 && !visited[j]) {
//             dfs(j, isConnected, visited);
//         }
//     }
// }
// int findCircleNum(vector<vector<int>>& isConnected) {
//     int n = isConnected.size();
//     vector<bool> visited(n, false);
//     int count = 0;
//     for (int i = 0; i < n; i++) {
//         if (!visited[i]) {
//             dfs(i, isConnected, visited);
//             count++;
//         }
//     }
//     return count;
// }

// ============================================
// SOLUTION OPTIMALE : Union-Find
// Pour chaque arete, unir les deux villes.
// Le nombre de composantes = n - nombre d'unions reussies.
// Temps : O(n^2 * alpha(n)) ~ O(n^2) | Espace : O(n)
// ============================================
class UnionFind {
    vector<int> parent, rank_;
public:
    UnionFind(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }
};

int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    UnionFind uf(n);
    int provinces = n;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (isConnected[i][j] == 1) {
                if (uf.unite(i, j)) provinces--;
            }
        }
    }
    return provinces;
}

int main() {
    // Test 1 : 2 provinces
    vector<vector<int>> g1 = {{1,1,0}, {1,1,0}, {0,0,1}};
    cout << "Test 1 - 2 provinces: " << (findCircleNum(g1) == 2 ? "OK" : "FAIL") << endl;

    // Test 2 : 3 provinces (aucune connexion)
    vector<vector<int>> g2 = {{1,0,0}, {0,1,0}, {0,0,1}};
    cout << "Test 2 - 3 provinces: " << (findCircleNum(g2) == 3 ? "OK" : "FAIL") << endl;

    // Test 3 : 1 province (tout connecte)
    vector<vector<int>> g3 = {{1,1,1}, {1,1,1}, {1,1,1}};
    cout << "Test 3 - 1 province: " << (findCircleNum(g3) == 1 ? "OK" : "FAIL") << endl;

    // Test 4 : connexion indirecte
    // 0-1, 1-2 -> 0 et 2 dans la meme province via 1
    vector<vector<int>> g4 = {{1,1,0,0}, {1,1,1,0}, {0,1,1,0}, {0,0,0,1}};
    cout << "Test 4 - indirect: " << (findCircleNum(g4) == 2 ? "OK" : "FAIL") << endl;

    return 0;
}
