/*
 * ============================================
 *  LeetCode #46 - Permutations (Medium) 🔙
 * ============================================
 *  Lien : https://leetcode.com/problems/permutations/
 *
 *  Enonce :
 *  Etant donne un tableau d'entiers DISTINCTS, retourner
 *  toutes les permutations possibles dans n'importe quel ordre.
 *
 *  Exemple :
 *  Input:  nums = [1,2,3]
 *  Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 *  Contraintes :
 *  - 1 <= nums.length <= 6
 *  - -10 <= nums[i] <= 10
 *  - Tous les elements sont distincts
 * ============================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * ─── BRUTE FORCE : next_permutation STL ──────────
 *
 * Trier le tableau, puis utiliser next_permutation
 * pour generer toutes les permutations une par une.
 *
 * Complexite :
 *  - Temps  : O(n! * n) - n! permutations, O(n) pour copier chacune
 *  - Espace : O(n!) - stockage du resultat
 */
class BruteForce {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        do {
            result.push_back(nums);
        } while (next_permutation(nums.begin(), nums.end()));

        return result;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Backtracking avec used[] ─
 *
 * Contrairement aux subsets, on ne peut pas utiliser un index start
 * car l'ORDRE compte. On utilise un tableau used[] pour savoir
 * quels elements sont deja dans la permutation actuelle.
 *
 *  Arbre pour [1,2,3] :
 *                          []
 *               /          |          \
 *             [1]         [2]         [3]
 *            /   \       /   \       /   \
 *         [1,2] [1,3] [2,1] [2,3] [3,1] [3,2]
 *          |      |     |     |     |      |
 *       [1,2,3][1,3,2][2,1,3][2,3,1][3,1,2][3,2,1]
 *
 * Complexite :
 *  - Temps  : O(n! * n) - n! feuilles, O(n) pour copier
 *  - Espace : O(n) - profondeur recursion + used[]
 */
class Optimal {
public:
    vector<vector<int>> result;

    void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& used) {
        if ((int)path.size() == (int)nums.size()) {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < (int)nums.size(); i++) {
            if (used[i]) continue; // deja utilise dans ce chemin

            used[i] = true;
            path.push_back(nums[i]);
            backtrack(nums, path, used);
            path.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> path;
        vector<bool> used(nums.size(), false);
        backtrack(nums, path, used);
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
    auto r1 = bf.permute(nums1);
    cout << "Brute Force (" << r1.size() << " perms) : ";
    printResult(r1);

    Optimal opt;
    vector<int> nums1b = {1, 2, 3};
    auto r2 = opt.permute(nums1b);
    cout << "Optimal     (" << r2.size() << " perms) : ";
    printResult(r2);

    // Test 2 : [0,1]
    vector<int> nums2 = {0, 1};
    cout << "\n=== Test 2 : nums = [0,1] ===" << endl;

    Optimal opt2;
    auto r3 = opt2.permute(nums2);
    cout << "Optimal     : ";
    printResult(r3);
    cout << "Attendu     : [[0,1], [1,0]]" << endl;

    // Test 3 : [1]
    vector<int> nums3 = {1};
    cout << "\n=== Test 3 : nums = [1] ===" << endl;

    Optimal opt3;
    auto r4 = opt3.permute(nums3);
    cout << "Optimal     : ";
    printResult(r4);
    cout << "Attendu     : [[1]]" << endl;

    return 0;
}
