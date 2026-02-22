/*
 * ============================================
 *  LeetCode #45 - Jump Game II (Medium) 🤑
 * ============================================
 *  Lien : https://leetcode.com/problems/jump-game-ii/
 *
 *  Enonce :
 *  Etant donne un tableau ou on peut toujours atteindre la fin,
 *  retourner le nombre MINIMUM de sauts pour atteindre le dernier index.
 *
 *  Exemple :
 *  Input:  nums = [2,3,1,1,4]
 *  Output: 2 (014)
 *
 *  Contraintes :
 *  - 1 <= nums.length <= 10^4
 *  - 0 <= nums[i] <= 1000
 *  - On peut toujours atteindre la fin
 * ============================================
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
 * ─── BRUTE FORCE : DP bottom-up ──────────────────
 *
 * dp[i] = nombre minimum de sauts pour atteindre la fin depuis i.
 * dp[n-1] = 0, dp[i] = 1 + min(dp[j]) pour j dans [i+1, i+nums[i]].
 *
 * Complexite :
 *  - Temps  : O(n^2)
 *  - Espace : O(n)
 */
class BruteForce {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, INT_MAX);
        dp[n - 1] = 0;

        for (int i = n - 2; i >= 0; i--) {
            int furthest = min(i + nums[i], n - 1);
            for (int j = i + 1; j <= furthest; j++) {
                if (dp[j] != INT_MAX) {
                    dp[i] = min(dp[i], 1 + dp[j]);
                }
            }
        }
        return dp[0];
    }
};

/*
 * ─── SOLUTION OPTIMALE : Greedy BFS-like ─────────
 *
 * On traite le probleme comme un BFS par niveaux.
 * Chaque "niveau" = un saut. On maintient :
 * - farthest : la portee max du prochain saut
 * - currentEnd : la fin du saut actuel
 *
 *  Trace pour [2, 3, 1, 1, 4] :
 *
 *  Saut 0: position 0
 *          |  portee = [1,2]
 *          
 *  Saut 1: positions 1,2
 *          |  depuis 1: portee jusqu'a 4
 *          |  depuis 2: portee jusqu'a 3
 *          
 *  Saut 2: positions 3,4  ARRIVEE
 *
 *  i=0: farthest=max(0,2)=2, i==currentEnd(0)  jumps=1, currentEnd=2
 *  i=1: farthest=max(2,4)=4, >= n-1  on sait qu'un saut de plus suffit
 *  i=2: i==currentEnd(2)  jumps=2, currentEnd=4
 *   Reponse : 2
 *
 * Complexite :
 *  - Temps  : O(n) - un seul passage
 *  - Espace : O(1)
 */
class Optimal {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;

        for (int i = 0; i < n - 1; i++) {
            farthest = max(farthest, i + nums[i]);

            if (i == currentEnd) { // on a epuise le saut actuel
                jumps++;
                currentEnd = farthest;

                if (currentEnd >= n - 1) break;
            }
        }
        return jumps;
    }
};

int main() {
    // Test 1
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "=== Test 1 : [2,3,1,1,4] ===" << endl;

    BruteForce bf;
    cout << "Brute Force : " << bf.jump(nums1) << endl;

    Optimal opt;
    cout << "Optimal     : " << opt.jump(nums1) << endl;
    cout << "Attendu     : 2" << endl;

    // Test 2
    vector<int> nums2 = {2, 3, 0, 1, 4};
    cout << "\n=== Test 2 : [2,3,0,1,4] ===" << endl;

    BruteForce bf2;
    cout << "Brute Force : " << bf2.jump(nums2) << endl;

    Optimal opt2;
    cout << "Optimal     : " << opt2.jump(nums2) << endl;
    cout << "Attendu     : 2" << endl;

    // Test 3 : un element
    vector<int> nums3 = {0};
    cout << "\n=== Test 3 : [0] ===" << endl;

    Optimal opt3;
    cout << "Optimal     : " << opt3.jump(nums3) << endl;
    cout << "Attendu     : 0" << endl;

    // Test 4
    vector<int> nums4 = {1, 2, 3};
    cout << "\n=== Test 4 : [1,2,3] ===" << endl;

    Optimal opt4;
    cout << "Optimal     : " << opt4.jump(nums4) << endl;
    cout << "Attendu     : 2" << endl;

    return 0;
}
