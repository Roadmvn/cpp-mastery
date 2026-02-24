// https://leetcode.com/problems/house-robber/
// #198 - House Robber
//
// Voler des maisons en ligne. Ne pas voler deux maisons adjacentes.
// Maximiser la somme volee.
//
// Approche : DP O(1) espace.
// A chaque maison, choisir entre : voler cette maison + best(i-2), ou skipper (best(i-1)).
// Garder seulement les deux derniers etats au lieu d'un tableau complet.
// Complexite temps : O(n) | Complexite espace : O(1)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];

        int prev2 = 0; // meilleur jusqu'a i-2
        int prev1 = 0; // meilleur jusqu'a i-1

        for (int num : nums) {
            int curr = max(prev1, prev2 + num);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 1};
    cout << sol.rob(nums1) << endl; // 4 (voler 1 et 3)

    vector<int> nums2 = {2, 7, 9, 3, 1};
    cout << sol.rob(nums2) << endl; // 12 (voler 2, 9, 1)

    vector<int> nums3 = {1};
    cout << sol.rob(nums3) << endl; // 1

    vector<int> nums4 = {2, 1, 1, 2};
    cout << sol.rob(nums4) << endl; // 4 (voler 2 et 2)

    vector<int> nums5 = {5};
    cout << sol.rob(nums5) << endl; // 5

    return 0;
}
