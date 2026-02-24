// LeetCode #684 -- Redundant Connection
// https://leetcode.com/problems/redundant-connection/
// Difficulte : Medium
//
// Enonce :
//   Un graphe non-oriente avait n noeuds et n-1 aretes (c'etait un arbre).
//   Une arete supplementaire a ete ajoutee, creant un cycle.
//   On te donne edges[i] = [u, v] dans l'ordre d'ajout.
//   Retourne l'arete redondante (la derniere arete qui forme un cycle).
//   S'il y a plusieurs reponses, retourne celle qui apparait en dernier.
//
// Exemple :
//   edges = [[1,2],[1,3],[2,3]]  ->  [2,3]
//   edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]  ->  [1,4]

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
//  BRUTE FORCE : O(n^2) -- tenter de supprimer chaque arete
//  et verifier si le graphe reste connexe avec BFS/DFS.
// ============================================================

// bool isConnected_brute(int n, vector<vector<int>>& edges, int skip) {
//     vector<vector<int>> adj(n + 1);
//     for (int i = 0; i < (int)edges.size(); i++) {
//         if (i == skip) continue;
//         adj[edges[i][0]].push_back(edges[i][1]);
//         adj[edges[i][1]].push_back(edges[i][0]);
//     }
//     vector<bool> vis(n + 1, false);
//     queue<int> q;
//     q.push(1); vis[1] = true;
//     int count = 1;
//     while (!q.empty()) {
//         int u = q.front(); q.pop();
//         for (int v : adj[u]) if (!vis[v]) { vis[v] = true; count++; q.push(v); }
//     }
//     return count == n;
// }
//
// vector<int> findRedundantConnection_brute(vector<vector<int>>& edges) {
//     int n = edges.size();
//     for (int i = n - 1; i >= 0; i--)
//         if (isConnected_brute(n, edges, i))
//             return edges[i];
//     return {};
// }

// ============================================================
//  SOLUTION OPTIMALE : Union-Find -- O(n * alpha(n))
//
//  On insere les aretes une par une.
//  Si unite(u, v) retourne false -> u et v etaient deja
//  connectes -> cette arete cree un cycle -> c'est la reponse.
//
//  Complexite : O(n * alpha(n)) temps, O(n) espace
// ============================================================

class UnionFind {
    vector<int> parent, rank_;
public:
    UnionFind(int n) : parent(n + 1), rank_(n + 1, 0) {
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
        return true;
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n);

        for (auto& e : edges) {
            // Si les deux noeuds sont deja connectes, cette arete est redondante
            if (!uf.unite(e[0], e[1]))
                return e;
        }
        return {};
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    // Exemple 1
    vector<vector<int>> e1 = {{1,2},{1,3},{2,3}};
    auto r1 = sol.findRedundantConnection(e1);
    cout << "[" << r1[0] << "," << r1[1] << "]\n";  // attendu : [2,3]

    // Exemple 2
    vector<vector<int>> e2 = {{1,2},{2,3},{3,4},{1,4},{1,5}};
    auto r2 = sol.findRedundantConnection(e2);
    cout << "[" << r2[0] << "," << r2[1] << "]\n";  // attendu : [1,4]

    // Edge case : triangle simple
    vector<vector<int>> e3 = {{1,2},{2,3},{1,3}};
    auto r3 = sol.findRedundantConnection(e3);
    cout << "[" << r3[0] << "," << r3[1] << "]\n";  // attendu : [1,3]

    return 0;
}
