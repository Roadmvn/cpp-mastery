// ============================================
// LeetCode #33 - Search in Rotated Sorted Array (Medium)
// https://leetcode.com/problems/search-in-rotated-sorted-array/
// ============================================
// Enonce : Array trie puis rotate. Chercher target et retourner son index.
// Retourner -1 si absent. Doit etre en O(log n).
//
// Exemple : nums = [4,5,6,7,0,1,2], target = 0 -> Output: 4
//
// Compile : g++ -std=c++17 05_search_rotated_sorted_array.cpp -o 05

#include <iostream>
#include <vector>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n) temps | O(1) espace
// Recherche lineaire
// -----------------------------------------------
int searchBrute(vector<int>& nums, int target) {
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] == target) return i;
    }
    return -1;
}

// -----------------------------------------------
// OPTIMAL : O(log n) temps | O(1) espace
// Binary search modifie : a chaque etape, determiner
// quelle moitie est triee, puis verifier si target y est
//
// Schema :
//   [4, 5, 6, 7, 0, 1, 2]   target = 0
//    lo        mid       hi
//
//   Partie gauche [4,5,6,7] est TRIEE (nums[lo] <= nums[mid])
//   Target 0 n'est PAS dans [4,7] -> chercher a droite
//
//   [4, 5, 6, 7, 0, 1, 2]
//                 lo mid hi
//
//   Partie gauche [0,1] est TRIEE (nums[lo]=0 <= nums[mid]=1)
//   Target 0 EST dans [0,1] -> chercher a gauche
//
//   lo=4, hi=4 -> nums[4]=0 == target -> return 4
// -----------------------------------------------
int searchOptimal(vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] == target) return mid;

        // Partie gauche triee
        if (nums[lo] <= nums[mid]) {
            // Target dans la partie gauche ?
            if (nums[lo] <= target && target < nums[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        // Partie droite triee
        else {
            // Target dans la partie droite ?
            if (nums[mid] < target && target <= nums[hi]) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
    }
    return -1;
}

int main() {
    cout << "=== #33 Search in Rotated Sorted Array ===" << endl;

    vector<int> test1 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Input: [4,5,6,7,0,1,2]" << endl;
    cout << "target=0 -> Brute: " << searchBrute(test1, 0)
         << " Optimal: " << searchOptimal(test1, 0)
         << " (attendu: 4)" << endl;
    cout << "target=3 -> Brute: " << searchBrute(test1, 3)
         << " Optimal: " << searchOptimal(test1, 3)
         << " (attendu: -1)" << endl;
    cout << "target=5 -> Optimal: " << searchOptimal(test1, 5)
         << " (attendu: 1)" << endl;
    cout << endl;

    vector<int> test2 = {1};
    cout << "Input: [1]" << endl;
    cout << "target=0 -> Optimal: " << searchOptimal(test2, 0)
         << " (attendu: -1)" << endl;
    cout << "target=1 -> Optimal: " << searchOptimal(test2, 1)
         << " (attendu: 0)" << endl;
    cout << endl;

    vector<int> test3 = {3, 1};
    cout << "Input: [3,1]" << endl;
    cout << "target=1 -> Optimal: " << searchOptimal(test3, 1)
         << " (attendu: 1)" << endl;
    cout << "target=3 -> Optimal: " << searchOptimal(test3, 3)
         << " (attendu: 0)" << endl;

    return 0;
}
