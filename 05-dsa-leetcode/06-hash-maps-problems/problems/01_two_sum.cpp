// ============================================
// LeetCode #1 - Two Sum (Easy)
// https://leetcode.com/problems/two-sum/
// ============================================
// Enonce : Donne un tableau nums[] et un entier target, retourner
// les indices des deux nombres qui s'additionnent pour donner target.
// Exactement une solution, on ne peut pas utiliser le meme element deux fois.
//
// Exemple :
//   Input : nums=[2,7,11,15], target=9
//   Output: [0,1]  car nums[0] + nums[1] = 2 + 7 = 9
//
// Compile : g++ -std=c++17 01_two_sum.cpp -o 01

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n²) temps | O(1) espace
// Tester toutes les paires (i, j) avec i < j.
// -----------------------------------------------
vector<int> twoSumBrute(vector<int>& nums, int target) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {};
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(n) espace
// HashMap : pour chaque element, verifier si son
// complement (target - nums[i]) a deja ete vu.
//
// Schema ASCII :
//
//   nums   = [2, 7, 11, 15]  target = 9
//
//   i=0 : nums[0]=2, complement=7
//          map={}  7 absent  map={2:0}
//
//   i=1 : nums[1]=7, complement=2
//          map={2:0}  2 PRESENT !  return [map[2], 1] = [0, 1]
//
//   ┌────────────────────────────────────────┐
//   │ map[valeur] = indice                   │
//   │ Chercher (target - nums[i]) dans map   │
//   └────────────────────────────────────────┘
// -----------------------------------------------
vector<int> twoSumOptimal(vector<int>& nums, int target) {
    unordered_map<int, int> seen; // valeur -> indice

    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];

        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}

void printResult(const vector<int>& v, const string& label) {
    cout << label << " [";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i + 1 < (int)v.size()) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== LeetCode #1 - Two Sum ===" << endl;

    // Test 1 : exemple classique
    {
        vector<int> nums = {2, 7, 11, 15};
        int target = 9;
        cout << "Input : [2,7,11,15], target=" << target << endl;
        printResult(twoSumBrute(nums, target),   "Brute  :");
        printResult(twoSumOptimal(nums, target), "Optimal:");
        // Attendu : [0,1]
        cout << endl;
    }

    // Test 2 : complement au debut
    {
        vector<int> nums = {3, 2, 4};
        int target = 6;
        cout << "Input : [3,2,4], target=" << target << endl;
        printResult(twoSumBrute(nums, target),   "Brute  :");
        printResult(twoSumOptimal(nums, target), "Optimal:");
        // Attendu : [1,2]
        cout << endl;
    }

    // Test 3 : meme valeur deux fois
    {
        vector<int> nums = {3, 3};
        int target = 6;
        cout << "Input : [3,3], target=" << target << endl;
        printResult(twoSumBrute(nums, target),   "Brute  :");
        printResult(twoSumOptimal(nums, target), "Optimal:");
        // Attendu : [0,1]
        cout << endl;
    }

    // Test 4 : valeurs negatives
    {
        vector<int> nums = {-3, 4, 3, 90};
        int target = 0;
        cout << "Input : [-3,4,3,90], target=" << target << endl;
        printResult(twoSumBrute(nums, target),   "Brute  :");
        printResult(twoSumOptimal(nums, target), "Optimal:");
        // Attendu : [0,2]
        cout << endl;
    }

    cout << "Complexite Brute  : O(n^2) temps | O(1) espace" << endl;
    cout << "Complexite Optimal: O(n)   temps | O(n) espace" << endl;

    return 0;
}
