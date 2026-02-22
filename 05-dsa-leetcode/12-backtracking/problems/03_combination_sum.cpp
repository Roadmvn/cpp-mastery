/*
 * ============================================
 *  LeetCode #39 - Combination Sum (Medium) 🔙
 * ============================================
 *  Lien : https://leetcode.com/problems/combination-sum/
 *
 *  Enonce :
 *  Etant donne un tableau de candidats DISTINCTS et un entier target,
 *  retourner toutes les combinaisons uniques dont la somme = target.
 *  Le MEME nombre peut etre utilise un nombre ILLIMITE de fois.
 *
 *  Exemple :
 *  Input:  candidates = [2,3,6,7], target = 7
 *  Output: [[2,2,3],[7]]
 *
 *  Contraintes :
 *  - 1 <= candidates.length <= 30
 *  - 2 <= candidates[i] <= 40
 *  - 1 <= target <= 40
 * ============================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * ─── BRUTE FORCE : Backtracking sans pruning ─────
 *
 * Explorer toutes les combinaisons possibles sans optimisation.
 * On continue meme quand la somme depasse le target.
 *
 * Complexite :
 *  - Temps  : O(n^(T/M)) - T=target, M=min(candidates)
 *  - Espace : O(T/M) - profondeur max de recursion
 */
class BruteForce {
public:
    vector<vector<int>> result;

    void backtrack(vector<int>& cands, int start, int target, vector<int>& path) {
        if (target == 0) {
            result.push_back(path);
            return;
        }
        if (target < 0) return;

        for (int i = start; i < (int)cands.size(); i++) {
            path.push_back(cands[i]);
            backtrack(cands, i, target - cands[i], path); // i et pas i+1 : repetition OK
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> path;
        backtrack(candidates, 0, target, path);
        return result;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Backtracking avec pruning ─
 *
 * Trier les candidats d'abord.
 * Si candidates[i] > target restant, on arrete la boucle
 * (tous les suivants sont encore plus grands).
 *
 *  Arbre pour candidates=[2,3,6,7], target=7 :
 *
 *                          target=7
 *                    /     |      \      \
 *                2(5)    3(4)    6(1)    7(0)✓
 *              / |  \    / \      X
 *           2(3) 3(2) 6 2(1) 3(1)
 *          / \    |     X    X
 *       2(1) 3(0)✓ 2(0)✓
 *        X
 *
 *   Solutions : [2,2,3] et [7]
 *
 * Complexite :
 *  - Temps  : O(n^(T/M)) mais beaucoup plus rapide en pratique grace au pruning
 *  - Espace : O(T/M)
 */
class Optimal {
public:
    vector<vector<int>> result;

    void backtrack(vector<int>& cands, int start, int target, vector<int>& path) {
        if (target == 0) {
            result.push_back(path);
            return;
        }

        for (int i = start; i < (int)cands.size(); i++) {
            if (cands[i] > target) break; // PRUNING : trie donc tout apres est > target

            path.push_back(cands[i]);
            backtrack(cands, i, target - cands[i], path);
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); // trier pour le pruning
        vector<int> path;
        backtrack(candidates, 0, target, path);
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
    // Test 1 : [2,3,6,7], target=7
    vector<int> c1 = {2, 3, 6, 7};
    cout << "=== Test 1 : candidates=[2,3,6,7], target=7 ===" << endl;

    BruteForce bf;
    auto r1 = bf.combinationSum(c1, 7);
    cout << "Brute Force : ";
    printResult(r1);

    Optimal opt;
    auto r2 = opt.combinationSum(c1, 7);
    cout << "Optimal     : ";
    printResult(r2);
    cout << "Attendu     : [[2,2,3], [7]]" << endl;

    // Test 2 : [2,3,5], target=8
    vector<int> c2 = {2, 3, 5};
    cout << "\n=== Test 2 : candidates=[2,3,5], target=8 ===" << endl;

    Optimal opt2;
    auto r3 = opt2.combinationSum(c2, 8);
    cout << "Optimal     : ";
    printResult(r3);
    cout << "Attendu     : [[2,2,2,2], [2,3,3], [3,5]]" << endl;

    // Test 3 : [2], target=1
    vector<int> c3 = {2};
    cout << "\n=== Test 3 : candidates=[2], target=1 ===" << endl;

    Optimal opt3;
    auto r4 = opt3.combinationSum(c3, 1);
    cout << "Optimal     : ";
    printResult(r4);
    cout << "Attendu     : []" << endl;

    return 0;
}
