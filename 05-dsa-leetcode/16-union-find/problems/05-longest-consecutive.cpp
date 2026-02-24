// LeetCode #128 -- Longest Consecutive Sequence
// https://leetcode.com/problems/longest-consecutive-sequence/
// Difficulte : Medium
//
// Enonce :
//   Donne un array non-trie d'entiers, retourne la longueur de la plus longue
//   sequence d'entiers consecutifs.
//   L'algorithme doit tourner en O(n).
//
// Exemple :
//   nums = [100,4,200,1,3,2]  ->  4  (sequence [1,2,3,4])
//   nums = [0,3,7,2,5,8,4,6,0,1]  ->  9  (sequence [0..8])

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
//  BRUTE FORCE : tri -- O(n log n)
//  Trier l'array, puis parcourir lineairement.
// ============================================================

// int longestConsecutive_brute(vector<int>& nums) {
//     if (nums.empty()) return 0;
//     sort(nums.begin(), nums.end());
//     nums.erase(unique(nums.begin(), nums.end()), nums.end());
//     int best = 1, cur = 1;
//     for (int i = 1; i < (int)nums.size(); i++) {
//         if (nums[i] == nums[i-1] + 1) cur++;
//         else cur = 1;
//         best = max(best, cur);
//     }
//     return best;
// }

// ============================================================
//  SOLUTION CLASSIQUE : HashSet -- O(n) temps, O(n) espace
//  (Solution recommandee par LeetCode pour ce probleme)
//
//  Pour chaque nombre n, on ne demarre une sequence que si
//  n-1 n'est pas dans le set (c'est un debut de sequence).
//  Puis on compte combien de n+1, n+2, ... sont dans le set.
// ============================================================

// int longestConsecutive_hashset(vector<int>& nums) {
//     unordered_set<int> s(nums.begin(), nums.end());
//     int best = 0;
//     for (int n : s) {
//         if (!s.count(n - 1)) {  // debut de sequence
//             int len = 1;
//             while (s.count(n + len)) len++;
//             best = max(best, len);
//         }
//     }
//     return best;
// }

// ============================================================
//  SOLUTION UNION-FIND : O(n * alpha(n))
//
//  On cree un noeud par valeur unique. Pour chaque valeur v,
//  si v+1 existe dans l'array, on unit v et v+1.
//  La reponse est la taille de la plus grande composante.
//
//  Moins optimal que le HashSet pour ce probleme specifique,
//  mais illustre comment Union-Find peut tracker des tailles.
//
//  Complexite : O(n * alpha(n)) temps, O(n) espace
// ============================================================

class UnionFind {
    unordered_map<int, int> parent;
    unordered_map<int, int> size_;
public:
    void add(int x) {
        if (!parent.count(x)) {
            parent[x] = x;
            size_[x] = 1;
        }
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        // union by size
        if (size_[rx] < size_[ry]) swap(rx, ry);
        parent[ry] = rx;
        size_[rx] += size_[ry];
    }
    int getSize(int x) { return size_[find(x)]; }
};

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;

        UnionFind uf;
        unordered_set<int> numSet(nums.begin(), nums.end());

        for (int n : numSet) {
            uf.add(n);
            if (numSet.count(n + 1)) {
                uf.add(n + 1);
                uf.unite(n, n + 1);
            }
        }

        int best = 0;
        for (int n : numSet)
            best = max(best, uf.getSize(n));

        return best;
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    // Exemple 1
    vector<int> n1 = {100,4,200,1,3,2};
    cout << sol.longestConsecutive(n1) << "\n";  // attendu : 4

    // Exemple 2
    vector<int> n2 = {0,3,7,2,5,8,4,6,0,1};
    cout << sol.longestConsecutive(n2) << "\n";  // attendu : 9

    // Edge case : vide
    vector<int> n3 = {};
    cout << sol.longestConsecutive(n3) << "\n";  // attendu : 0

    // Edge case : un seul element
    vector<int> n4 = {5};
    cout << sol.longestConsecutive(n4) << "\n";  // attendu : 1

    // Edge case : tous identiques
    vector<int> n5 = {1,1,1,1};
    cout << sol.longestConsecutive(n5) << "\n";  // attendu : 1

    return 0;
}
