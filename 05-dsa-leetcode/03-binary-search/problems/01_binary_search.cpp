// ============================================
// LeetCode #704 - Binary Search (Easy)
// https://leetcode.com/problems/binary-search/
// ============================================
// Enonce : Etant donne un tableau trie et un target, retourner l'index
// du target. Retourner -1 si absent.
//
// Exemple : nums = [-1,0,3,5,9,12], target = 9 -> Output: 4
//
// Compile : g++ -std=c++17 01_binary_search.cpp -o 01

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
// Binary search classique
//
// Schema :
//   [-1, 0, 3, 5, 9, 12]   target = 9
//     0  1  2  3  4   5
//
//   lo=0, hi=5, mid=2 -> nums[2]=3 < 9 -> lo=3
//   lo=3, hi=5, mid=4 -> nums[4]=9 == 9 -> return 4
// -----------------------------------------------
int searchOptimal(vector<int>& nums, int target) {
    int lo = 0, hi = (int)nums.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    cout << "=== #704 Binary Search ===" << endl;

    vector<int> test1 = {-1, 0, 3, 5, 9, 12};
    cout << "Input: [-1,0,3,5,9,12], target=9" << endl;
    cout << "Brute force: " << searchBrute(test1, 9) << " (attendu: 4)" << endl;
    cout << "Optimal:     " << searchOptimal(test1, 9) << " (attendu: 4)" << endl;
    cout << endl;

    cout << "Input: [-1,0,3,5,9,12], target=2" << endl;
    cout << "Brute force: " << searchBrute(test1, 2) << " (attendu: -1)" << endl;
    cout << "Optimal:     " << searchOptimal(test1, 2) << " (attendu: -1)" << endl;
    cout << endl;

    vector<int> test2 = {5};
    cout << "Input: [5], target=5" << endl;
    cout << "Optimal:     " << searchOptimal(test2, 5) << " (attendu: 0)" << endl;

    return 0;
}
