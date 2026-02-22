/*
 * ============================================
 *  LeetCode #78 - Subsets (Medium) 🔙
 * ============================================
 *  Lien : https://leetcode.com/problems/subsets/
 *
 *  Enonce :
 *  Etant donne un tableau d'entiers UNIQUES, retourner
 *  tous les sous-ensembles possibles (power set).
 *  La solution ne doit pas contenir de doublons.
 *
 *  Exemple :
 *  Input:  nums = [1,2,3]
 *  Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 *  Contraintes :
 *  - 1 <= nums.length <= 10
 *  - -10 <= nums[i] <= 10
 *  - Tous les elements sont uniques
 * ============================================
 */

#include <iostream>
#include <vector>
using namespace std;

/*
 * ─── BRUTE FORCE : Iteratif avec bitmask ─────────
 *
 * Pour n elements, il y a 2^n sous-ensembles.
 * Chaque nombre de 0 a 2^n-1 represente un masque
 * ou chaque bit indique si l'element est present.
 *
 *  Exemple : nums = [1,2,3], n=3, 2^3 = 8 masques
 *
 *  mask=000 → []        mask=100 → [3]
 *  mask=001 → [1]       mask=101 → [1,3]
 *  mask=010 → [2]       mask=110 → [2,3]
 *  mask=011 → [1,2]     mask=111 → [1,2,3]
 *
 * Complexite :
 *  - Temps  : O(n * 2^n) - 2^n sous-ensembles, n pour construire chacun
 *  - Espace : O(n * 2^n) - stockage du resultat
 */
class BruteForce {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int total = 1 << n; // 2^n
        vector<vector<int>> result;

        for (int mask = 0; mask < total; mask++) {
            vector<int> subset;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subset.push_back(nums[i]);
                }
            }
            result.push_back(subset);
        }
        return result;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Backtracking ────────────
 *
 * On construit l'arbre de decision : pour chaque element,
 * on le prend ou on ne le prend pas.
 *
 *  Arbre :
 *                     []
 *              /             \
 *          [1]                 []
 *        /     \            /     \
 *     [1,2]    [1]        [2]      []
 *    /   \    /   \      /  \    /   \
 * [1,2,3][1,2][1,3][1] [2,3][2][3]  []
 *
 * A chaque noeud, le chemin actuel EST un sous-ensemble valide.
 *
 * Complexite :
 *  - Temps  : O(n * 2^n) - meme que bitmask
 *  - Espace : O(n) - profondeur de recursion (hors resultat)
 */
class Optimal {
public:
    vector<vector<int>> result;

    void backtrack(vector<int>& nums, int start, vector<int>& path) {
        result.push_back(path); // chaque chemin = un sous-ensemble

        for (int i = start; i < (int)nums.size(); i++) {
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path);
            path.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        backtrack(nums, 0, path);
        return result;
    }
};

void printResult(vector<vector<int>>& res) {
    cout << "[";
    for (int i = 0; i < (int)res.size(); i++) {
        cout << "[";
        for (int j = 0; j < (int)res[i].size(); j++) {
            cout << res[i][j];
            if (j < (int)res[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < (int)res.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    // Test 1 : [1,2,3]
    vector<int> nums1 = {1, 2, 3};
    cout << "=== Test 1 : nums = [1,2,3] ===" << endl;

    BruteForce bf;
    auto res1 = bf.subsets(nums1);
    cout << "Brute Force : ";
    printResult(res1);

    Optimal opt;
    auto res2 = opt.subsets(nums1);
    cout << "Optimal     : ";
    printResult(res2);

    // Test 2 : [0]
    vector<int> nums2 = {0};
    cout << "\n=== Test 2 : nums = [0] ===" << endl;

    BruteForce bf2;
    auto res3 = bf2.subsets(nums2);
    cout << "Brute Force : ";
    printResult(res3);

    Optimal opt2;
    auto res4 = opt2.subsets(nums2);
    cout << "Optimal     : ";
    printResult(res4);

    // Test 3 : [1,2]
    vector<int> nums3 = {1, 2};
    cout << "\n=== Test 3 : nums = [1,2] ===" << endl;

    Optimal opt3;
    auto res5 = opt3.subsets(nums3);
    cout << "Optimal     : ";
    printResult(res5);
    cout << "Attendu     : [[], [1], [1,2], [2]]" << endl;

    return 0;
}
