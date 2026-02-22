// ============================================
// LeetCode #322 - Coin Change (Medium)
// https://leetcode.com/problems/coin-change/
// ============================================
// Enonce : Donne un tableau de pieces coins[] et un montant amount,
// retourner le nombre MINIMUM de pieces pour atteindre amount.
// Si impossible, retourner -1. Chaque piece peut etre utilisee
// un nombre illimite de fois.
//
// Exemple :
//   coins=[1,5,10,25], amount=30  2  (25+5)
//   coins=[1,2,5],     amount=11  3  (5+5+1)
//   coins=[2],         amount=3   -1 (impossible)
//
// Compile : g++ -std=c++17 03_coin_change.cpp -o 03

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(S^n) temps | O(n) espace
// Recursion pure : essayer toutes les combinaisons de pieces.
// S = amount, n = nombre de types de pieces
// -----------------------------------------------
int coinChangeBrute(const vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    if (amount < 0) return -1;

    int best = -1;
    for (int coin : coins) {
        int sub = coinChangeBrute(coins, amount - coin);
        if (sub >= 0) {
            int total = sub + 1;
            if (best == -1 || total < best) {
                best = total;
            }
        }
    }
    return best;
}

// -----------------------------------------------
// TOP-DOWN : O(S*n) temps | O(S) espace
// Recursion + memoization.
// -----------------------------------------------
unordered_map<int, int> memo;
int coinChangeMemo(const vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    if (amount < 0) return -1;
    if (memo.count(amount)) return memo[amount];

    int best = -1;
    for (int coin : coins) {
        int sub = coinChangeMemo(coins, amount - coin);
        if (sub >= 0) {
            int total = sub + 1;
            if (best == -1 || total < best) best = total;
        }
    }
    memo[amount] = best;
    return best;
}

// -----------------------------------------------
// OPTIMAL - BOTTOM-UP : O(S*n) temps | O(S) espace
// dp[i] = min pieces pour former la somme i.
//
// Schema ASCII :
//
//   coins=[1,5,10,25], amount=30
//
//   dp[0]=0 (cas de base)
//   Pour chaque somme i de 1 a 30 :
//     Pour chaque piece c :
//       si c <= i : dp[i] = min(dp[i], dp[i-c]+1)
//
//   ┌──────┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
//   │  i   │ 0 │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │  ... │30 │
//   │ dp   │ 0 │ 1 │ 2 │ 3 │ 4 │ 1 │ 2 │  ... │ 2 │
//   └──────┴───┴───┴───┴───┴───┴───┴───┴───────┴───┘
//
//   dp[5]  = min(dp[4]+1, dp[0]+1) = min(5, 1) = 1  (une piece de 5)
//   dp[30] = min(dp[29]+1, dp[25]+1, dp[20]+1, dp[5]+1)
//           = min(6, 2, 3, 2) = 2  (25+5)
// -----------------------------------------------
int coinChangeOptimal(const vector<int>& coins, int amount) {
    // Initialiser a amount+1 comme "infini" (impossible d'utiliser plus que amount pieces de 1)
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}

int main() {
    cout << "=== LeetCode #322 - Coin Change ===" << endl;

    // Test 1 : exemple classique
    {
        vector<int> coins = {1, 5, 10, 25};
        int amount = 30;
        memo.clear();
        cout << "coins=[1,5,10,25], amount=30" << endl;
        cout << "Brute   : " << coinChangeBrute(coins, amount) << endl;
        cout << "TopDown : " << coinChangeMemo(coins, amount) << endl;
        cout << "Optimal : " << coinChangeOptimal(coins, amount) << endl;
        // Attendu : 2
        cout << endl;
    }

    // Test 2 : coins=[1,2,5], amount=11
    {
        vector<int> coins = {1, 2, 5};
        int amount = 11;
        memo.clear();
        cout << "coins=[1,2,5], amount=11" << endl;
        cout << "Brute   : " << coinChangeBrute(coins, amount) << endl;
        cout << "TopDown : " << coinChangeMemo(coins, amount) << endl;
        cout << "Optimal : " << coinChangeOptimal(coins, amount) << endl;
        // Attendu : 3
        cout << endl;
    }

    // Test 3 : impossible
    {
        vector<int> coins = {2};
        int amount = 3;
        memo.clear();
        cout << "coins=[2], amount=3" << endl;
        cout << "Brute   : " << coinChangeBrute(coins, amount) << endl;
        cout << "TopDown : " << coinChangeMemo(coins, amount) << endl;
        cout << "Optimal : " << coinChangeOptimal(coins, amount) << endl;
        // Attendu : -1
        cout << endl;
    }

    // Test 4 : amount=0
    {
        vector<int> coins = {1, 2, 3};
        int amount = 0;
        memo.clear();
        cout << "coins=[1,2,3], amount=0" << endl;
        cout << "Optimal : " << coinChangeOptimal(coins, amount) << endl;
        // Attendu : 0
        cout << endl;
    }

    cout << "Complexite Brute   : O(S^n)  temps | O(n) espace" << endl;
    cout << "Complexite TopDown : O(S*n)  temps | O(S) espace" << endl;
    cout << "Complexite Optimal : O(S*n)  temps | O(S) espace" << endl;

    return 0;
}
