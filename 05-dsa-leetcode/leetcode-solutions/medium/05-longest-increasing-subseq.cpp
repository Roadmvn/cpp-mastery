// https://leetcode.com/problems/longest-increasing-subsequence/
// #300 - Longest Increasing Subsequence
//
// Trouver la longueur de la plus longue sous-sequence strictement croissante.
//
// Approche : patience sort (binary search) O(n log n).
// Maintenir un tableau "tails" ou tails[i] = plus petit element terminal
// d'une LIS de longueur i+1. Utiliser lower_bound pour placer chaque element.
// Propriete : "tails" est toujours trie.
// Complexite temps : O(n log n) | Complexite espace : O(n)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // tails[i] = plus petit element terminal d'une sous-sequence de longueur i+1
        vector<int> tails;

        for (int num : nums) {
            // Trouver la position ou num peut remplacer (ou etendre)
            auto it = lower_bound(tails.begin(), tails.end(), num);

            if (it == tails.end()) {
                // num est plus grand que tous : etendre la LIS
                tails.push_back(num);
            } else {
                // Remplacer pour maintenir le plus petit element terminal possible
                *it = num;
            }
        }

        return (int)tails.size();
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << sol.lengthOfLIS(nums1) << endl; // 4 (2,3,7,101 ou 2,5,7,101...)

    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    cout << sol.lengthOfLIS(nums2) << endl; // 4

    vector<int> nums3 = {7, 7, 7, 7, 7};
    cout << sol.lengthOfLIS(nums3) << endl; // 1 (strictement croissante)

    vector<int> nums4 = {1, 3, 6, 7, 9, 4, 10, 5, 6};
    cout << sol.lengthOfLIS(nums4) << endl; // 6 (1,3,6,7,9,10)

    return 0;
}
