// LeetCode #547 -- Number of Provinces
// https://leetcode.com/problems/number-of-provinces/
// Difficulte : Medium
//
// Enonce :
//   Il y a n villes. Certaines sont directement connectees, d'autres non.
//   Si la ville a est connectee a b, et b est connectee a c, alors a, b, c
//   font partie de la meme province.
//   On te donne isConnected[i][j] = 1 si i et j sont directement connectees.
//   Retourne le nombre de provinces.
//
// Exemple :
//   isConnected = [[1,1,0],[1,1,0],[0,0,1]]  ->  2
//   isConnected = [[1,0,0],[0,1,0],[0,0,1]]  ->  3

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

// ============================================================
//  BRUTE FORCE : DFS/BFS -- O(n^2) temps, O(n) espace
//  Visite chaque ville non visitee, explore sa composante.
// ============================================================

// int findCircleNum_brute(vector<vector<int>>& isConnected) {
//     int n = isConnected.size();
//     vector<bool> visited(n, false);
//     int provinces = 0;
//
//     function<void(int)> dfs = [&](int city) {
//         visited[city] = true;
//         for (int j = 0; j < n; j++)
//             if (isConnected[city][j] == 1 && !visited[j])
//                 dfs(j);
//     };
//
//     for (int i = 0; i < n; i++) {
//         if (!visited[i]) {
//             dfs(i);
//             provinces++;
//         }
//     }
//     return provinces;
// }

// ============================================================
//  SOLUTION OPTIMALE : Union-Find -- O(n^2 * alpha(n))
//
//  Pour chaque paire (i, j) avec isConnected[i][j] = 1, on
//  fustionne i et j. A la fin, le nombre de composantes est
//  le nombre de provinces.
//
//  Meme complexite asymptotique que DFS ici (matrice n x n),
//  mais le pattern Union-Find est plus adapte si les connexions
//  arrivent dynamiquement.
//
//  Complexite : O(n^2 * alpha(n)) temps, O(n) espace
// ============================================================

class UnionFind {
    vector<int> parent, rank_;
    int components;
public:
    UnionFind(int n) : parent(n), rank_(n, 0), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank_[rx] < rank_[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
        components--;
        return true;
    }
    int getComponents() const { return components; }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        UnionFind uf(n);

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (isConnected[i][j] == 1)
                    uf.unite(i, j);

        return uf.getComponents();
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    // Exemple 1 : 2 provinces
    vector<vector<int>> g1 = {{1,1,0},{1,1,0},{0,0,1}};
    cout << sol.findCircleNum(g1) << "\n";  // attendu : 2

    // Exemple 2 : 3 provinces (aucune connexion)
    vector<vector<int>> g2 = {{1,0,0},{0,1,0},{0,0,1}};
    cout << sol.findCircleNum(g2) << "\n";  // attendu : 3

    // Exemple 3 : 1 province (tous connectes)
    vector<vector<int>> g3 = {{1,1,1},{1,1,1},{1,1,1}};
    cout << sol.findCircleNum(g3) << "\n";  // attendu : 1

    return 0;
}
