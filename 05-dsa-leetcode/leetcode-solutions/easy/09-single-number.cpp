// https://leetcode.com/problems/single-number/
// #136 - Single Number
//
// Chaque element apparait deux fois sauf un. Trouver cet element unique.
// Contrainte : espace lineaire interdit, doit etre O(1) espace.
//
// Approche : XOR — a ^ a = 0 et a ^ 0 = a.
// XOR de tous les elements annule les doublons, reste le singleton.
// Complexite temps : O(n) | Complexite espace : O(1)

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;

        // XOR de tous les elements
        // Les elements en double s'annulent (a ^ a = 0)
        // L'element unique reste (0 ^ a = a)
        for (int n : nums) {
            result ^= n;
        }

        return result;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {2, 2, 1};
    cout << sol.singleNumber(nums1) << endl; // 1

    vector<int> nums2 = {4, 1, 2, 1, 2};
    cout << sol.singleNumber(nums2) << endl; // 4

    vector<int> nums3 = {1};
    cout << sol.singleNumber(nums3) << endl; // 1

    // Test avec valeurs negatives
    vector<int> nums4 = {-1, -1, -2};
    cout << sol.singleNumber(nums4) << endl; // -2

    return 0;
}
