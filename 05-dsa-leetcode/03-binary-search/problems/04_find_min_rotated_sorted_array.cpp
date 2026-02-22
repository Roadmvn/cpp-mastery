// ============================================
// LeetCode #153 - Find Minimum in Rotated Sorted Array (Medium)
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
// ============================================
// Enonce : Un array trie en ordre croissant a ete "rotate" entre 1 et n fois.
// Trouver l'element minimum. Tous les elements sont uniques.
//
// Exemple : nums = [3,4,5,1,2] -> Output: 1
//
// Compile : g++ -std=c++17 04_find_min_rotated_sorted_array.cpp -o 04

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n) temps | O(1) espace
// Parcourir tout le tableau
// -----------------------------------------------
int findMinBrute(vector<int>& nums) {
    int minVal = nums[0];
    for (int x : nums) minVal = min(minVal, x);
    return minVal;
}

// -----------------------------------------------
// OPTIMAL : O(log n) temps | O(1) espace
// Binary search : le minimum est au point de rotation
//
// Schema :
//   Array original trie : [1, 2, 3, 4, 5]
//   Apres rotation (3x) : [3, 4, 5, 1, 2]
//
//   Propriete :
//   - La partie gauche du pivot est triee et > partie droite
//   - Si nums[mid] > nums[hi] -> le min est a DROITE
//   - Si nums[mid] <= nums[hi] -> le min est a GAUCHE (ou c'est mid)
//
//   [3, 4, 5, 1, 2]
//    lo     mid   hi
//    nums[mid]=5 > nums[hi]=2 -> lo = mid+1
//
//   [3, 4, 5, 1, 2]
//              lo hi
//              mid
//    nums[mid]=1 <= nums[hi]=2 -> hi = mid
//
//   lo == hi == 3 -> nums[3] = 1 -> MINIMUM
// -----------------------------------------------
int findMinOptimal(vector<int>& nums) {
    int lo = 0, hi = (int)nums.size() - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] > nums[hi]) {
            lo = mid + 1;   // min est dans la partie droite
        } else {
            hi = mid;       // min est dans la partie gauche (ou mid)
        }
    }
    return nums[lo];
}

int main() {
    cout << "=== #153 Find Minimum in Rotated Sorted Array ===" << endl;

    vector<int> test1 = {3, 4, 5, 1, 2};
    cout << "Input: [3,4,5,1,2]" << endl;
    cout << "Brute force: " << findMinBrute(test1) << " (attendu: 1)" << endl;
    cout << "Optimal:     " << findMinOptimal(test1) << " (attendu: 1)" << endl;
    cout << endl;

    vector<int> test2 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Input: [4,5,6,7,0,1,2]" << endl;
    cout << "Brute force: " << findMinBrute(test2) << " (attendu: 0)" << endl;
    cout << "Optimal:     " << findMinOptimal(test2) << " (attendu: 0)" << endl;
    cout << endl;

    vector<int> test3 = {11, 13, 15, 17};
    cout << "Input: [11,13,15,17] (pas de rotation)" << endl;
    cout << "Brute force: " << findMinBrute(test3) << " (attendu: 11)" << endl;
    cout << "Optimal:     " << findMinOptimal(test3) << " (attendu: 11)" << endl;
    cout << endl;

    vector<int> test4 = {2, 1};
    cout << "Input: [2,1]" << endl;
    cout << "Optimal:     " << findMinOptimal(test4) << " (attendu: 1)" << endl;

    return 0;
}
