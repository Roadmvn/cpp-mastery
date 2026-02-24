// https://leetcode.com/problems/median-of-two-sorted-arrays/
// #4 - Median of Two Sorted Arrays
//
// Trouver la mediane de deux tableaux tries de taille m et n.
// Contrainte : O(log(m+n)) temps.
//
// Approche : binary search sur le plus petit tableau.
// Trouver la partition dans nums1 telle que :
//   - max(gauche1, gauche2) <= min(droite1, droite2)
//   - la moitie gauche et la moitie droite ont la meme taille (ou gauche +1)
// Complexite temps : O(log min(m,n)) | Complexite espace : O(1)

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Toujours faire la recherche sur le plus petit tableau
        if (nums1.size() > nums2.size()) {
            swap(nums1, nums2);
        }

        int m = (int)nums1.size();
        int n = (int)nums2.size();
        int half = (m + n + 1) / 2; // taille de la moitie gauche

        int left = 0, right = m;

        while (left <= right) {
            int i = (left + right) / 2;    // partition dans nums1
            int j = half - i;               // partition dans nums2

            // Valeurs aux bords des partitions
            int maxLeft1  = (i == 0) ? INT_MIN : nums1[i - 1];
            int minRight1 = (i == m) ? INT_MAX : nums1[i];
            int maxLeft2  = (j == 0) ? INT_MIN : nums2[j - 1];
            int minRight2 = (j == n) ? INT_MAX : nums2[j];

            if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
                // Partition correcte trouvee
                if ((m + n) % 2 == 1) {
                    return max(maxLeft1, maxLeft2); // mediane = max de la moitie gauche
                } else {
                    return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
                }
            } else if (maxLeft1 > minRight2) {
                right = i - 1; // trop a droite dans nums1
            } else {
                left = i + 1;  // trop a gauche dans nums1
            }
        }

        return 0.0; // jamais atteint si les tableaux sont tries
    }
};

int main() {
    Solution sol;

    vector<int> a1 = {1, 3}, b1 = {2};
    cout << sol.findMedianSortedArrays(a1, b1) << endl; // 2.0

    vector<int> a2 = {1, 2}, b2 = {3, 4};
    cout << sol.findMedianSortedArrays(a2, b2) << endl; // 2.5

    vector<int> a3 = {0, 0}, b3 = {0, 0};
    cout << sol.findMedianSortedArrays(a3, b3) << endl; // 0.0

    vector<int> a4 = {}, b4 = {1};
    cout << sol.findMedianSortedArrays(a4, b4) << endl; // 1.0

    vector<int> a5 = {2}, b5 = {};
    cout << sol.findMedianSortedArrays(a5, b5) << endl; // 2.0

    vector<int> a6 = {1, 2, 3, 4, 5}, b6 = {6, 7, 8, 9, 10};
    cout << sol.findMedianSortedArrays(a6, b6) << endl; // 5.5

    return 0;
}
