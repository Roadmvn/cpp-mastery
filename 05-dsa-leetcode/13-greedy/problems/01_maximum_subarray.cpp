/*
 * ============================================
 *  LeetCode #53 - Maximum Subarray (Medium) 🤑
 * ============================================
 *  Lien : https://leetcode.com/problems/maximum-subarray/
 *
 *  Enonce :
 *  Etant donne un tableau d'entiers, trouver le sous-tableau
 *  contigu ayant la plus grande somme et retourner cette somme.
 *
 *  Exemple :
 *  Input:  nums = [-2,1,-3,4,-1,2,1,-5,4]
 *  Output: 6 (sous-tableau [4,-1,2,1])
 *
 *  Contraintes :
 *  - 1 <= nums.length <= 10^5
 *  - -10^4 <= nums[i] <= 10^4
 * ============================================
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
 * ─── BRUTE FORCE : Tester tous les sous-tableaux ─
 *
 * Enumerer toutes les paires (i, j) et calculer la somme.
 *
 * Complexite :
 *  - Temps  : O(n^2)
 *  - Espace : O(1)
 */
class BruteForce {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int maxSum = INT_MIN;

        for (int i = 0; i < n; i++) {
            int currentSum = 0;
            for (int j = i; j < n; j++) {
                currentSum += nums[j];
                maxSum = max(maxSum, currentSum);
            }
        }
        return maxSum;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Kadane's Algorithm ──────
 *
 * Idee greedy : a chaque position, on a deux choix :
 * 1. Continuer le sous-tableau precedent (current + nums[i])
 * 2. Demarrer un nouveau sous-tableau (nums[i] seul)
 *  On prend le MAX des deux.
 *
 *  Trace pour [-2, 1, -3, 4, -1, 2, 1, -5, 4] :
 *
 *  i   nums[i]   current   global
 *  0    -2        -2        -2
 *  1     1     max(1,-1)=1    1
 *  2    -3     max(-3,-2)=-2  1
 *  3     4     max(4,2)=4     4
 *  4    -1     max(-1,3)=3    4
 *  5     2     max(2,5)=5     5
 *  6     1     max(1,6)=6     6   MAX
 *  7    -5     max(-5,1)=1    6
 *  8     4     max(4,5)=5     6
 *
 *  Sous-tableau optimal : [4, -1, 2, 1] = 6
 *
 * Complexite :
 *  - Temps  : O(n) - un seul passage
 *  - Espace : O(1) - deux variables
 */
class Optimal {
public:
    int maxSubArray(vector<int>& nums) {
        int currentMax = nums[0];
        int globalMax = nums[0];

        for (int i = 1; i < (int)nums.size(); i++) {
            currentMax = max(nums[i], currentMax + nums[i]);
            globalMax = max(globalMax, currentMax);
        }
        return globalMax;
    }
};

int main() {
    // Test 1
    vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "=== Test 1 : [-2,1,-3,4,-1,2,1,-5,4] ===" << endl;

    BruteForce bf;
    cout << "Brute Force : " << bf.maxSubArray(nums1) << endl;

    Optimal opt;
    cout << "Optimal     : " << opt.maxSubArray(nums1) << endl;
    cout << "Attendu     : 6" << endl;

    // Test 2 : un seul element
    vector<int> nums2 = {1};
    cout << "\n=== Test 2 : [1] ===" << endl;

    Optimal opt2;
    cout << "Optimal     : " << opt2.maxSubArray(nums2) << endl;
    cout << "Attendu     : 1" << endl;

    // Test 3 : tous negatifs
    vector<int> nums3 = {-3, -2, -1, -4};
    cout << "\n=== Test 3 : [-3,-2,-1,-4] ===" << endl;

    Optimal opt3;
    cout << "Optimal     : " << opt3.maxSubArray(nums3) << endl;
    cout << "Attendu     : -1" << endl;

    // Test 4
    vector<int> nums4 = {5, 4, -1, 7, 8};
    cout << "\n=== Test 4 : [5,4,-1,7,8] ===" << endl;

    Optimal opt4;
    cout << "Optimal     : " << opt4.maxSubArray(nums4) << endl;
    cout << "Attendu     : 23" << endl;

    return 0;
}
