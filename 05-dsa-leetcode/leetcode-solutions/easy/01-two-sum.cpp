// https://leetcode.com/problems/two-sum/
// #1 - Two Sum
//
// Etant donne un tableau d'entiers et une cible, retourner les indices des deux
// nombres qui s'additionnent a la cible. Exactement une solution existe.
//
// Approche : hash map - pour chaque element, chercher son complement dans la map.
// Complexite temps : O(n) | Complexite espace : O(n)

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // map : valeur -> index
        unordered_map<int, int> seen;

        for (int i = 0; i < (int)nums.size(); i++) {
            int complement = target - nums[i];

            // Si le complement existe deja dans la map, on a trouve la paire
            if (seen.count(complement)) {
                return {seen[complement], i};
            }

            seen[nums[i]] = i;
        }

        return {}; // jamais atteint (la solution existe toujours)
    }
};

int main() {
    Solution sol;

    // Test 1 : cas classique
    vector<int> nums1 = {2, 7, 11, 15};
    auto res1 = sol.twoSum(nums1, 9);
    cout << "[" << res1[0] << ", " << res1[1] << "]" << endl; // [0, 1]

    // Test 2 : doublon
    vector<int> nums2 = {3, 3};
    auto res2 = sol.twoSum(nums2, 6);
    cout << "[" << res2[0] << ", " << res2[1] << "]" << endl; // [0, 1]

    // Test 3 : valeurs negatives
    vector<int> nums3 = {-1, -2, -3, -4, -5};
    auto res3 = sol.twoSum(nums3, -8);
    cout << "[" << res3[0] << ", " << res3[1] << "]" << endl; // [2, 4]

    return 0;
}
