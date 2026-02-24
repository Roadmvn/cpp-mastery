// LeetCode #947 -- Most Stones Removed with Same Row or Column
// https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/
// Difficulte : Medium
//
// Enonce :
//   Sur une grille 2D, on place n pierres (chaque cellule a au plus une pierre).
//   On peut retirer une pierre si elle partage une ligne ou une colonne avec
//   au moins une autre pierre.
//   Retourne le nombre maximum de pierres qu'on peut retirer.
//
// Exemple :
//   stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]  ->  5
//   stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]  ->  3
//   stones = [[0,0]]  ->  0
//
// Insight cle :
//   Dans une composante connexe de k pierres, on peut toujours en retirer k-1.
//   Car il reste toujours au moins une pierre par composante connexe.
//   Reponse = n - nombre_de_composantes_connexes

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
//  BRUTE FORCE : simulation -- O(n^2 * n) dans le pire cas
//  Repeter : trouver une pierre retirable, la retirer.
// ============================================================

// int removeStones_brute(vector<vector<int>>& stones) {
//     int removed = 0;
//     bool changed = true;
//     while (changed) {
//         changed = false;
//         for (int i = 0; i < (int)stones.size(); i++) {
//             if (stones[i].empty()) continue;
//             for (int j = 0; j < (int)stones.size(); j++) {
//                 if (i == j || stones[j].empty()) continue;
//                 if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {
//                     stones[i].clear();
//                     removed++;
//                     changed = true;
//                     break;
//                 }
//             }
//         }
//     }
//     return removed;
// }

// ============================================================
//  SOLUTION OPTIMALE : Union-Find -- O(n * alpha(n))
//
//  Deux pierres sont "connectees" si elles partagent une ligne
//  ou une colonne. On unit les pierres par ligne et par colonne.
//
//  Astuce : pour distinguer lignes et colonnes dans le meme
//  Union-Find, on mappe les colonnes avec un offset :
//  colonne c -> c + 10001 (les valeurs max sont 10^4)
//
//  Reponse = n - nombre_de_composantes (parmi les noeuds qui ont des pierres)
//
//  Complexite : O(n * alpha(n)) temps, O(n) espace
// ============================================================

class UnionFind {
    unordered_map<int, int> parent;
    int components = 0;
public:
    int find(int x) {
        if (!parent.count(x)) { parent[x] = x; components++; }
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        parent[rx] = ry;
        components--;
    }
    int getComponents() const { return components; }
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        UnionFind uf;

        for (auto& s : stones) {
            // On unit la ligne s[0] avec la colonne s[1]
            // Offset 10001 pour les colonnes (valeurs 0..10000)
            uf.unite(s[0], s[1] + 10001);
        }

        return (int)stones.size() - uf.getComponents();
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    // Exemple 1 : 6 pierres, 1 composante -> retirer 5
    vector<vector<int>> s1 = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    cout << sol.removeStones(s1) << "\n";  // attendu : 5

    // Exemple 2 : 5 pierres, 2 composantes -> retirer 3
    vector<vector<int>> s2 = {{0,0},{0,2},{1,1},{2,0},{2,2}};
    cout << sol.removeStones(s2) << "\n";  // attendu : 3

    // Exemple 3 : 1 pierre, seule -> retirer 0
    vector<vector<int>> s3 = {{0,0}};
    cout << sol.removeStones(s3) << "\n";  // attendu : 0

    return 0;
}
