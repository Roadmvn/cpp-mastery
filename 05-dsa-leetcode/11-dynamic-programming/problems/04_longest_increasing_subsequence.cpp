// ============================================
// LeetCode #300 - Longest Increasing Subsequence (Medium)
// https://leetcode.com/problems/longest-increasing-subsequence/
// ============================================
// Enonce : Donne un tableau nums[], retourner la longueur de la plus
// longue sous-sequence strictement croissante (pas forcément contiguë).
//
// Exemple :
//   nums=[10,9,2,5,3,7,101,18]  4  (2,3,7,101 ou 2,5,7,101)
//   nums=[0,1,0,3,2,3]          4  (0,1,2,3 ou 0,1,3 ou ...)
//   nums=[7,7,7,7]              1
//
// Compile : g++ -std=c++17 04_longest_increasing_subsequence.cpp -o 04

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(2^n) temps | O(n) espace
// Generer toutes les sous-sequences et garder la
// plus longue qui est strictement croissante.
// -----------------------------------------------
int lisBrute(const vector<int>& nums, int idx, int prev) {
    if (idx == (int)nums.size()) return 0;

    // Option 1 : ne pas inclure nums[idx]
    int skip = lisBrute(nums, idx + 1, prev);

    // Option 2 : inclure nums[idx] si strictement croissant
    int take = 0;
    if (nums[idx] > prev) {
        take = 1 + lisBrute(nums, idx + 1, nums[idx]);
    }
    return max(skip, take);
}

int longestIncreasingSubsequenceBrute(vector<int>& nums) {
    return lisBrute(nums, 0, INT_MIN);
}

// -----------------------------------------------
// OPTIMAL DP : O(n²) temps | O(n) espace
// dp[i] = longueur de la LIS se terminant a l'indice i.
//
// Schema ASCII :
//
//   nums = [10, 9, 2, 5, 3, 7, 101, 18]
//
//   ┌────┬────┬───┬───┬───┬───┬─────┬────┐
//   │nums│ 10 │ 9 │ 2 │ 5 │ 3 │  7  │101 │ 18 │
//   │ dp │  1 │ 1 │ 1 │ 2 │ 2 │  3  │ 4  │  4 │
//   └────┴────┴───┴───┴───┴───┴─────┴────┘
//
//   dp[3]=2 : nums[3]=5, nums[2]=2 < 5  dp[3]=dp[2]+1=2
//   dp[5]=3 : nums[5]=7 > nums[4]=3 (dp=2) et > nums[3]=5 (dp=2)
//              dp[5] = max(dp[3]+1, dp[4]+1) = 3
//   dp[6]=4 : nums[6]=101 est plus grand que tout  dp[6]=max(dp[*])+1=4
//
//   Reponse : max(dp) = 4
// -----------------------------------------------
int longestIncreasingSubsequenceDP(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1); // chaque element est une LIS de longueur 1

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}

// -----------------------------------------------
// ULTRA OPTIMAL : O(n log n) temps | O(n) espace
// Patience Sorting avec recherche dichotomique.
//
// Principe : maintenir un tableau "tails" ou
// tails[i] = plus petit element terminal d'une
// sous-sequence croissante de longueur i+1.
//
// Pour chaque nums[i] :
//   - binary search pour trouver la premiere position
//     dans tails ou l'element est >= nums[i]
//   - remplacer tails[pos] par nums[i]
//   - si pos == tails.size() : extend
//
// La longueur de tails est la reponse.
//
// Exemple : nums = [10, 9, 2, 5, 3, 7, 101, 18]
//   i=0: tails=[10]
//   i=1: 9 remplace 10  tails=[9]
//   i=2: 2 remplace 9   tails=[2]
//   i=3: 5 > 2  extend  tails=[2,5]
//   i=4: 3 remplace 5   tails=[2,3]
//   i=5: 7 > 3  extend  tails=[2,3,7]
//   i=6: 101 > 7  extend  tails=[2,3,7,101]
//   i=7: 18 remplace 101  tails=[2,3,7,18]
//   len(tails) = 4
// -----------------------------------------------
int longestIncreasingSubsequenceUltra(vector<int>& nums) {
    vector<int> tails; // tails[i] = plus petit element terminal de LIS de longueur i+1

    for (int x : nums) {
        // Trouver la premiere position >= x (lower_bound pour strictement croissant)
        auto pos = lower_bound(tails.begin(), tails.end(), x);
        if (pos == tails.end()) {
            tails.push_back(x); // extend
        } else {
            *pos = x; // remplacer
        }
    }
    return tails.size();
}

int main() {
    cout << "=== LeetCode #300 - Longest Increasing Subsequence ===" << endl;

    // Test 1 : exemple classique
    {
        vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
        cout << "Input : [10,9,2,5,3,7,101,18]" << endl;
        cout << "Brute  : " << longestIncreasingSubsequenceBrute(nums) << endl;
        cout << "DP O(n²): " << longestIncreasingSubsequenceDP(nums) << endl;
        cout << "Ultra  : " << longestIncreasingSubsequenceUltra(nums) << endl;
        // Attendu : 4
        cout << endl;
    }

    // Test 2 : croissant pur
    {
        vector<int> nums = {1, 2, 3, 4, 5};
        cout << "Input : [1,2,3,4,5]" << endl;
        cout << "Brute  : " << longestIncreasingSubsequenceBrute(nums) << endl;
        cout << "DP O(n²): " << longestIncreasingSubsequenceDP(nums) << endl;
        cout << "Ultra  : " << longestIncreasingSubsequenceUltra(nums) << endl;
        // Attendu : 5
        cout << endl;
    }

    // Test 3 : tous egaux
    {
        vector<int> nums = {7, 7, 7, 7};
        cout << "Input : [7,7,7,7]" << endl;
        cout << "Brute  : " << longestIncreasingSubsequenceBrute(nums) << endl;
        cout << "DP O(n²): " << longestIncreasingSubsequenceDP(nums) << endl;
        cout << "Ultra  : " << longestIncreasingSubsequenceUltra(nums) << endl;
        // Attendu : 1
        cout << endl;
    }

    // Test 4 : decroissant pur
    {
        vector<int> nums = {5, 4, 3, 2, 1};
        cout << "Input : [5,4,3,2,1]" << endl;
        cout << "Brute  : " << longestIncreasingSubsequenceBrute(nums) << endl;
        cout << "DP O(n²): " << longestIncreasingSubsequenceDP(nums) << endl;
        cout << "Ultra  : " << longestIncreasingSubsequenceUltra(nums) << endl;
        // Attendu : 1
        cout << endl;
    }

    cout << "Complexite Brute   : O(2^n)     temps | O(n)  espace" << endl;
    cout << "Complexite DP O(n²): O(n^2)     temps | O(n)  espace" << endl;
    cout << "Complexite Ultra   : O(n log n) temps | O(n)  espace" << endl;

    return 0;
}
