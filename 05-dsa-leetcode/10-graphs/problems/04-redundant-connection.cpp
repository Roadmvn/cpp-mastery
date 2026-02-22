// ============================================
// LeetCode #684 - Redundant Connection (Medium) 
// https://leetcode.com/problems/redundant-connection/
// ============================================
//
// ENONCE :
// Un graphe non dirige qui etait un arbre, mais on a ajoute UNE arete
// supplementaire. Trouver cette arete redondante.
// S'il y a plusieurs reponses, retourner celle qui apparait en dernier.
//
//   edges = [[1,2],[1,3],[2,3]]
//
//   1 --- 2        L'arete [2,3] cree un cycle
//    \   /         -> retourner [2,3]
//     \ /
//      3
//
// Un arbre a n noeuds et n-1 aretes.
// Ici on a n noeuds et n aretes -> exactement 1 cycle.
//
// APPROCHE : Union-Find
// On ajoute les aretes une par une.
// Si les deux noeuds sont deja connectes -> c'est l'arete redondante !
//
// ============================================

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

// ============================================
// BRUTE FORCE : DFS pour chaque arete
// Avant d'ajouter chaque arete, verifier avec DFS si les 2 noeuds
// sont deja connectes dans le graphe actuel
// Temps : O(n^2) | Espace : O(n)
// ============================================
// (Pour chaque arete, DFS = O(n), et n aretes -> O(n^2))

// ============================================
// SOLUTION OPTIMALE : Union-Find
// On tente d'unir chaque arete. Si deja unis -> redondante !
// Temps : O(n * alpha(n)) ~ O(n) | Espace : O(n)
// ============================================
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
        int px = find(x), py = find(y);
        if (px == py) return false; // deja connectes !
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }
};

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    UnionFind uf(n);

    for (auto& e : edges) {
        if (!uf.unite(e[0], e[1])) {
            return e; // cette arete cree un cycle
        }
    }
    return {}; // ne devrait pas arriver
}

int main() {
    // Test 1 : [2,3] redondante
    vector<vector<int>> e1 = {{1,2},{1,3},{2,3}};
    auto r1 = findRedundantConnection(e1);
    cout << "Test 1 - [2,3]: " << (r1 == vector<int>({2,3}) ? "OK" : "FAIL") << endl;

    // Test 2 : [1,4] redondante
    vector<vector<int>> e2 = {{1,2},{2,3},{3,4},{1,4},{1,5}};
    auto r2 = findRedundantConnection(e2);
    cout << "Test 2 - [1,4]: " << (r2 == vector<int>({1,4}) ? "OK" : "FAIL") << endl;

    // Test 3 : triangle simple
    vector<vector<int>> e3 = {{1,2},{2,3},{3,1}};
    auto r3 = findRedundantConnection(e3);
    cout << "Test 3 - [3,1]: " << (r3 == vector<int>({3,1}) ? "OK" : "FAIL") << endl;

    // Test 4 : cycle plus long
    vector<vector<int>> e4 = {{1,2},{2,3},{3,4},{4,1}};
    auto r4 = findRedundantConnection(e4);
    cout << "Test 4 - [4,1]: " << (r4 == vector<int>({4,1}) ? "OK" : "FAIL") << endl;

    return 0;
}
