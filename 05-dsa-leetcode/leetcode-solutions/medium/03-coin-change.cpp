// https://leetcode.com/problems/coin-change/
// #322 - Coin Change
//
// Donner la monnaie pour un montant avec le moins de pieces possible.
// Retourner -1 si impossible.
//
// Approche : DP bottom-up.
// dp[i] = nombre minimum de pieces pour obtenir le montant i.
// Pour chaque montant, essayer chaque piece.
// Complexite temps : O(amount * n) | Complexite espace : O(amount)

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] = min pieces pour montant i, initialise a "infini"
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0; // 0 piece pour montant 0

        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                // Verifier que i - coin est atteignable
                if (coin <= i && dp[i - coin] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }

        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};

int main() {
    Solution sol;

    vector<int> coins1 = {1, 5, 10, 25};
    cout << sol.coinChange(coins1, 41) << endl; // 4 (25+10+5+1)
    cout << sol.coinChange(coins1, 30) << endl; // 2 (25+5)

    vector<int> coins2 = {1, 2, 5};
    cout << sol.coinChange(coins2, 11) << endl; // 3 (5+5+1)

    vector<int> coins3 = {2};
    cout << sol.coinChange(coins3, 3)  << endl; // -1 (impossible)

    vector<int> coins4 = {1};
    cout << sol.coinChange(coins4, 0)  << endl; // 0

    return 0;
}
