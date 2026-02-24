// https://leetcode.com/problems/3sum/
// #15 - 3Sum
//
// Trouver tous les triplets uniques dans un tableau dont la somme vaut 0.
// Pas de doublons dans les triplets resultants.
//
// Approche : trier + two pointers.
// Fixer i, puis utiliser deux pointeurs left/right pour trouver la paire.
// Sauter les doublons pour eviter les triplets repetition.
// Complexite temps : O(n^2) | Complexite espace : O(1) (hors sortie)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = (int)nums.size();

        for (int i = 0; i < n - 2; i++) {
            // Optimisation : si le plus petit possible > 0, impossible d'atteindre 0
            if (nums[i] > 0) break;

            // Sauter les doublons pour l'element fixe
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    // Sauter les doublons pour left et right
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;  // augmenter la somme
                } else {
                    right--; // diminuer la somme
                }
            }
        }

        return result;
    }
};

void print(const vector<vector<int>>& res) {
    for (auto& triplet : res) {
        cout << "[" << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << "]" << endl;
    }
}

int main() {
    Solution sol;

    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    print(sol.threeSum(nums1)); // [-1,-1,2], [-1,0,1]

    cout << "---" << endl;

    vector<int> nums2 = {0, 1, 1};
    print(sol.threeSum(nums2)); // (vide)

    vector<int> nums3 = {0, 0, 0};
    print(sol.threeSum(nums3)); // [0,0,0]

    return 0;
}
