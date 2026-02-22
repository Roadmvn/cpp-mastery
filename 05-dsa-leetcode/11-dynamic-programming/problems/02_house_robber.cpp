// ============================================
// LeetCode #198 - House Robber (Medium)
// https://leetcode.com/problems/house-robber/
// ============================================
// Enonce : Tu es un voleur. Chaque maison contient une somme d'argent.
// Tu ne peux pas voler deux maisons adjacentes (alarme se declenche).
// Retourner le maximum que tu peux voler.
//
// Exemple :
//   nums=[1,2,3,1] → 4 (voler maisons 0 et 2 : 1+3)
//   nums=[2,7,9,3,1] → 12 (voler maisons 0,2,4 : 2+9+1)
//
// Compile : g++ -std=c++17 02_house_robber.cpp -o 02

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(2^n) temps | O(n) espace
// Recursion pure : a chaque maison, choisir de voler ou pas.
// -----------------------------------------------
int robBrute(const vector<int>& nums, int i) {
    if (i >= (int)nums.size()) return 0;
    // Voler la maison i (ne peut pas voler i+1) OU ne pas voler i
    int voler    = nums[i] + robBrute(nums, i + 2);
    int pasVoler = robBrute(nums, i + 1);
    return max(voler, pasVoler);
}

int housRobberBrute(vector<int>& nums) {
    return robBrute(nums, 0);
}

// -----------------------------------------------
// TOP-DOWN : O(n) temps | O(n) espace
// Recursion + memoization.
// -----------------------------------------------
unordered_map<int, int> memo;
int robMemo(const vector<int>& nums, int i) {
    if (i >= (int)nums.size()) return 0;
    if (memo.count(i)) return memo[i];
    int voler    = nums[i] + robMemo(nums, i + 2);
    int pasVoler = robMemo(nums, i + 1);
    memo[i] = max(voler, pasVoler);
    return memo[i];
}

// -----------------------------------------------
// OPTIMAL - BOTTOM-UP : O(n) temps | O(1) espace
// Recurrence : dp[i] = max(dp[i-1], dp[i-2] + nums[i])
//
// Schema ASCII :
//
//   nums = [2, 7, 9, 3, 1]
//
//   ┌────┬─────┬─────┬─────┬─────┬─────┐
//   │  i │  0  │  1  │  2  │  3  │  4  │
//   │nums│  2  │  7  │  9  │  3  │  1  │
//   │ dp │  2  │  7  │ 11  │ 11  │ 12  │
//   └────┴─────┴─────┴─────┴─────┴─────┘
//
//   dp[0] = 2   (voler la maison 0)
//   dp[1] = max(dp[0], nums[1]) = max(2, 7) = 7
//   dp[2] = max(dp[1], dp[0]+nums[2]) = max(7, 2+9) = 11
//   dp[3] = max(dp[2], dp[1]+nums[3]) = max(11, 7+3) = 11
//   dp[4] = max(dp[3], dp[2]+nums[4]) = max(11, 11+1) = 12  ← reponse
//
//   Maisons volees : 0 (2) + 2 (9) + 4 (1) = 12
// -----------------------------------------------
int houseRobberOptimal(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int prev2 = nums[0];           // dp[i-2]
    int prev1 = max(nums[0], nums[1]); // dp[i-1]

    for (int i = 2; i < n; i++) {
        int cur = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    cout << "=== LeetCode #198 - House Robber ===" << endl;

    // Test 1 : exemple classique 1
    {
        vector<int> nums = {1, 2, 3, 1};
        memo.clear();
        cout << "Input : [1,2,3,1]" << endl;
        cout << "Brute   : " << housRobberBrute(nums) << endl;
        cout << "TopDown : " << robMemo(nums, 0) << endl;
        cout << "Optimal : " << houseRobberOptimal(nums) << endl;
        // Attendu : 4
        cout << endl;
    }

    // Test 2 : exemple classique 2
    {
        vector<int> nums = {2, 7, 9, 3, 1};
        memo.clear();
        cout << "Input : [2,7,9,3,1]" << endl;
        cout << "Brute   : " << housRobberBrute(nums) << endl;
        cout << "TopDown : " << robMemo(nums, 0) << endl;
        cout << "Optimal : " << houseRobberOptimal(nums) << endl;
        // Attendu : 12
        cout << endl;
    }

    // Test 3 : maison unique
    {
        vector<int> nums = {5};
        memo.clear();
        cout << "Input : [5]" << endl;
        cout << "Brute   : " << housRobberBrute(nums) << endl;
        cout << "TopDown : " << robMemo(nums, 0) << endl;
        cout << "Optimal : " << houseRobberOptimal(nums) << endl;
        // Attendu : 5
        cout << endl;
    }

    // Test 4 : croissant pur
    {
        vector<int> nums = {1, 2, 3, 4, 5};
        memo.clear();
        cout << "Input : [1,2,3,4,5]" << endl;
        cout << "Brute   : " << housRobberBrute(nums) << endl;
        cout << "TopDown : " << robMemo(nums, 0) << endl;
        cout << "Optimal : " << houseRobberOptimal(nums) << endl;
        // Attendu : 9 (1+3+5)
        cout << endl;
    }

    cout << "Complexite Brute   : O(2^n) temps | O(n) espace" << endl;
    cout << "Complexite TopDown : O(n)   temps | O(n) espace" << endl;
    cout << "Complexite Optimal : O(n)   temps | O(1) espace" << endl;

    return 0;
}
