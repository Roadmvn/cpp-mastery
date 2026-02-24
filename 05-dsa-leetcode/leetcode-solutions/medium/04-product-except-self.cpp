// https://leetcode.com/problems/product-of-array-except-self/
// #238 - Product of Array Except Self
//
// Retourner un tableau ou output[i] = produit de tous les elements sauf nums[i].
// Contrainte : pas de division, O(n) temps.
//
// Approche : prefix/suffix sans tableau auxiliaire.
// Passe gauche -> droite : result[i] = produit de tout ce qui est a gauche.
// Passe droite -> gauche : multiplier par le produit de tout ce qui est a droite.
// Complexite temps : O(n) | Complexite espace : O(1) (hors tableau de sortie)

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> result(n, 1);

        // result[i] contient le produit de tous les elements a gauche de i
        int prefix = 1;
        for (int i = 0; i < n; i++) {
            result[i] = prefix;
            prefix *= nums[i];
        }

        // Multiplier par le produit de tous les elements a droite de i
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= suffix;
            suffix *= nums[i];
        }

        return result;
    }
};

void print(const vector<int>& v) {
    for (int i = 0; i < (int)v.size(); i++) {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << endl;
}

int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 4};
    print(sol.productExceptSelf(nums1)); // 24, 12, 8, 6

    vector<int> nums2 = {-1, 1, 0, -3, 3};
    print(sol.productExceptSelf(nums2)); // 0, 0, 9, 0, 0

    vector<int> nums3 = {0, 0};
    print(sol.productExceptSelf(nums3)); // 0, 0

    return 0;
}
