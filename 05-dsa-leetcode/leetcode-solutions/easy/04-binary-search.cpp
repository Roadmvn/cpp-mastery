// https://leetcode.com/problems/binary-search/
// #704 - Binary Search
//
// Chercher une cible dans un tableau trie. Retourner son index ou -1.
//
// Approche : iteratif - diviser l'espace de recherche par deux a chaque etape.
// Invariant : la cible, si elle existe, est dans [left, right].
// Complexite temps : O(log n) | Complexite espace : O(1)

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = (int)nums.size() - 1;

        while (left <= right) {
            // Eviter l'overflow : mid = left + (right - left) / 2
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;  // cible dans la moitie droite
            } else {
                right = mid - 1; // cible dans la moitie gauche
            }
        }

        return -1; // non trouve
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    cout << sol.search(nums1, 9)  << endl; // 4
    cout << sol.search(nums1, 2)  << endl; // -1

    vector<int> nums2 = {5};
    cout << sol.search(nums2, 5)  << endl; // 0
    cout << sol.search(nums2, -5) << endl; // -1

    // Borne gauche et droite
    cout << sol.search(nums1, -1) << endl; // 0
    cout << sol.search(nums1, 12) << endl; // 5

    return 0;
}
