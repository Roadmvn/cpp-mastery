// https://leetcode.com/problems/kth-largest-element-in-an-array/
// #215 - Kth Largest Element in an Array
//
// Trouver le k-ieme plus grand element (sans trier completement).
//
// Approche : quickselect — partitionnement type quicksort, O(n) en moyenne.
// A chaque etape, le pivot est place a sa position finale.
// Si pivot == k-ieme depuis la fin : trouve.
// Sinon : recurser uniquement sur la moitie pertinente.
// Complexite temps : O(n) moyen, O(n^2) pire cas | Complexite espace : O(1)

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = (int)nums.size();
        return quickselect(nums, 0, n - 1, n - k); // k-ieme plus grand = (n-k)-ieme plus petit
    }

private:
    int quickselect(vector<int>& nums, int left, int right, int target) {
        if (left == right) return nums[left];

        // Pivot aleatoire pour eviter le pire cas sur tableaux tries
        int pivotIdx = left + rand() % (right - left + 1);
        swap(nums[pivotIdx], nums[right]);

        int pivotPos = partition(nums, left, right);

        if (pivotPos == target) {
            return nums[pivotPos];
        } else if (pivotPos < target) {
            return quickselect(nums, pivotPos + 1, right, target);
        } else {
            return quickselect(nums, left, pivotPos - 1, target);
        }
    }

    // Lomuto partition : place le pivot a sa position definitive
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[right];
        int i = left; // frontier des elements < pivot

        for (int j = left; j < right; j++) {
            if (nums[j] <= pivot) {
                swap(nums[i++], nums[j]);
            }
        }

        swap(nums[i], nums[right]);
        return i;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    cout << sol.findKthLargest(nums1, 2) << endl; // 5

    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << sol.findKthLargest(nums2, 4) << endl; // 4

    vector<int> nums3 = {1};
    cout << sol.findKthLargest(nums3, 1) << endl; // 1

    vector<int> nums4 = {7, 6, 5, 4, 3, 2, 1};
    cout << sol.findKthLargest(nums4, 1) << endl; // 7
    cout << sol.findKthLargest(nums4, 7) << endl; // 1 (reuse, nums4 modifie)

    return 0;
}
