/*
 * ============================================
 *  LeetCode #55 - Jump Game (Medium) 🤑
 * ============================================
 *  Lien : https://leetcode.com/problems/jump-game/
 *
 *  Enonce :
 *  Etant donne un tableau d'entiers non-negatifs ou chaque element
 *  represente le saut maximum depuis cette position,
 *  determiner si on peut atteindre le dernier index.
 *
 *  Exemple :
 *  Input:  nums = [2,3,1,1,4]
 *  Output: true (0→1→4 ou 0→2→3→4)
 *
 *  Contraintes :
 *  - 1 <= nums.length <= 10^4
 *  - 0 <= nums[i] <= 10^5
 * ============================================
 */

#include <iostream>
#include <vector>
using namespace std;

/*
 * ─── BRUTE FORCE : DP top-down ───────────────────
 *
 * dp[i] = true si on peut atteindre la fin depuis i.
 * Pour chaque position, essayer tous les sauts possibles.
 *
 * Complexite :
 *  - Temps  : O(n^2) - pour chaque position, scanner les sauts
 *  - Espace : O(n) - tableau dp + recursion
 */
class BruteForce {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1); // -1=unknown, 0=false, 1=true
        dp[n - 1] = 1;
        return solve(nums, dp, 0);
    }

    bool solve(vector<int>& nums, vector<int>& dp, int pos) {
        if (dp[pos] != -1) return dp[pos] == 1;

        int furthest = min(pos + nums[pos], (int)nums.size() - 1);
        for (int next = pos + 1; next <= furthest; next++) {
            if (solve(nums, dp, next)) {
                dp[pos] = 1;
                return true;
            }
        }
        dp[pos] = 0;
        return false;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Greedy max reach ────────
 *
 * Maintenir la portee maximale (maxReach).
 * A chaque position i, mettre a jour maxReach = max(maxReach, i + nums[i]).
 * Si a un moment i > maxReach, on ne peut pas y arriver.
 *
 *  Trace pour [2, 3, 1, 1, 4] :
 *
 *  Index:   0    1    2    3    4
 *  Value:  [2]  [3]  [1]  [1]  [4]
 *
 *  i=0: maxReach = max(0, 0+2) = 2
 *  i=1: maxReach = max(2, 1+3) = 4  ← atteint la fin !
 *  → true
 *
 *  Trace pour [3, 2, 1, 0, 4] :
 *
 *  i=0: maxReach = max(0, 0+3) = 3
 *  i=1: maxReach = max(3, 1+2) = 3
 *  i=2: maxReach = max(3, 2+1) = 3
 *  i=3: maxReach = max(3, 3+0) = 3  ← bloques ici
 *  i=4: 4 > 3 → false !
 *
 * Complexite :
 *  - Temps  : O(n) - un seul passage
 *  - Espace : O(1) - une variable
 */
class Optimal {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;

        for (int i = 0; i < (int)nums.size(); i++) {
            if (i > maxReach) return false;
            maxReach = max(maxReach, i + nums[i]);
            if (maxReach >= (int)nums.size() - 1) return true;
        }
        return true;
    }
};

int main() {
    // Test 1
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "=== Test 1 : [2,3,1,1,4] ===" << endl;

    BruteForce bf;
    cout << "Brute Force : " << (bf.canJump(nums1) ? "true" : "false") << endl;

    Optimal opt;
    cout << "Optimal     : " << (opt.canJump(nums1) ? "true" : "false") << endl;
    cout << "Attendu     : true" << endl;

    // Test 2
    vector<int> nums2 = {3, 2, 1, 0, 4};
    cout << "\n=== Test 2 : [3,2,1,0,4] ===" << endl;

    BruteForce bf2;
    cout << "Brute Force : " << (bf2.canJump(nums2) ? "true" : "false") << endl;

    Optimal opt2;
    cout << "Optimal     : " << (opt2.canJump(nums2) ? "true" : "false") << endl;
    cout << "Attendu     : false" << endl;

    // Test 3 : un seul element
    vector<int> nums3 = {0};
    cout << "\n=== Test 3 : [0] ===" << endl;

    Optimal opt3;
    cout << "Optimal     : " << (opt3.canJump(nums3) ? "true" : "false") << endl;
    cout << "Attendu     : true" << endl;

    // Test 4
    vector<int> nums4 = {2, 0, 0};
    cout << "\n=== Test 4 : [2,0,0] ===" << endl;

    Optimal opt4;
    cout << "Optimal     : " << (opt4.canJump(nums4) ? "true" : "false") << endl;
    cout << "Attendu     : true" << endl;

    return 0;
}
