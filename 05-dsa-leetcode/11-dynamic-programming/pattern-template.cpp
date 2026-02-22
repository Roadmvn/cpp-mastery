// ============================================
// Pattern Template - Dynamic Programming
// ============================================
// Ce fichier regroupe les templates DP les plus
// courants en competitive programming.
//
// Compile : g++ -std=c++17 pattern-template.cpp -o pattern

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

// ==============================================
// TEMPLATE 1 : 1D DP - Fibonacci Style
// Recurrence : dp[i] depend de dp[i-1] et dp[i-2]
// Optimisation espace : garder seulement 2 variables
// ==============================================

// Version naive (recursion pure) : O(2^n) temps
int fibNaif(int n) {
    if (n <= 1) return n;
    return fibNaif(n - 1) + fibNaif(n - 2);
}

// Top-down avec memoization : O(n) temps | O(n) espace
unordered_map<int, int> memo;
int fibTopDown(int n) {
    if (n <= 1) return n;
    if (memo.count(n)) return memo[n];
    memo[n] = fibTopDown(n - 1) + fibTopDown(n - 2);
    return memo[n];
}

// Bottom-up tabulation : O(n) temps | O(n) espace
int fibBottomUp(int n) {
    if (n <= 1) return n;
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// Espace optimise : O(1) espace
int fibOptimise(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

// ==============================================
// TEMPLATE 2 : 1D DP - Decision Binaire
// Recurrence : dp[i] = max/min(prendre, ne pas prendre)
// Usage : House Robber, Jump Game, etc.
// ==============================================

// Modele : dp[i] = max valeur en considerant elements 0..i
// Prendre i   : dp[i-2] + val[i]   (on ne peut pas prendre i-1)
// Ne pas prendre i : dp[i-1]
int decisionBinaireDP(const vector<int>& vals) {
    int n = vals.size();
    if (n == 0) return 0;
    if (n == 1) return vals[0];

    // Version avec tableau
    vector<int> dp(n);
    dp[0] = vals[0];
    dp[1] = max(vals[0], vals[1]);
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + vals[i]);
    }
    return dp[n - 1];
}

// ==============================================
// TEMPLATE 3 : 1D DP - Knapsack non borne (Coin Change)
// dp[amount] = min de pieces pour former amount
// ==============================================
int coinChangeDP(const vector<int>& coins, int amount) {
    // dp[i] = minimum de pieces pour former la somme i
    vector<int> dp(amount + 1, amount + 1); // init a "infini"
    dp[0] = 0; // cas de base : 0 piece pour somme 0

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}

// ==============================================
// TEMPLATE 4 : 2D DP - LCS (Longest Common Subsequence)
// dp[i][j] = LCS des i premiers chars de s1 et j premiers de s2
//
// Schema :
//        ""  b  o  m
//    ""   0  0  0  0
//    a    0  0  0  0
//    b    0  1  1  1
//    o    0  1  2  2
//    m    0  1  2  3  ← reponse
// ==============================================
int lcsDP(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    // dp[i][j] = LCS de s1[0..i-1] et s2[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // les chars matchent
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // le meilleur sans l'un d'eux
            }
        }
    }
    return dp[m][n];
}

// ==============================================
// TEMPLATE 5 : 2D DP - Knapsack 0/1
// dp[i][w] = valeur max en utilisant items 0..i avec capacite w
// ==============================================
int knapsackDP(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            // Ne pas prendre l'item i
            dp[i][w] = dp[i - 1][w];
            // Prendre l'item i (si son poids le permet)
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
        }
    }
    return dp[n][capacity];
}

// Optimisation espace knapsack : O(W) espace
int knapsackOptimise(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<int> dp(capacity + 1, 0);

    for (int i = 0; i < n; i++) {
        // Parcours INVERSE pour eviter de compter l'item deux fois (0/1)
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    return dp[capacity];
}

// -----------------------------------------------
// Demonstration de tous les templates
// -----------------------------------------------
int main() {
    cout << "=== Dynamic Programming Patterns ===" << endl;

    // Template 1 : Fibonacci
    {
        cout << "\n[1] Fibonacci" << endl;
        memo.clear();
        cout << "  fib(10) naif      = " << fibNaif(10) << endl;
        cout << "  fib(10) top-down  = " << fibTopDown(10) << endl;
        cout << "  fib(10) bottom-up = " << fibBottomUp(10) << endl;
        cout << "  fib(10) optimise  = " << fibOptimise(10) << endl;
        // Attendu : 55
    }

    // Template 2 : Decision binaire (House Robber style)
    {
        cout << "\n[2] Decision Binaire (House Robber style)" << endl;
        vector<int> vals = {2, 7, 9, 3, 1};
        cout << "  vals=[2,7,9,3,1]" << endl;
        cout << "  max sans adjacents = " << decisionBinaireDP(vals) << endl;
        // Attendu : 12 (2+9+1)
    }

    // Template 3 : Coin Change
    {
        cout << "\n[3] Coin Change DP" << endl;
        vector<int> coins = {1, 5, 10, 25};
        cout << "  coins=[1,5,10,25], amount=30" << endl;
        cout << "  min pieces = " << coinChangeDP(coins, 30) << endl;
        // Attendu : 2 (25+5)
    }

    // Template 4 : LCS
    {
        cout << "\n[4] LCS (Longest Common Subsequence)" << endl;
        string s1 = "abcde", s2 = "ace";
        cout << "  s1=\"" << s1 << "\", s2=\"" << s2 << "\"" << endl;
        cout << "  LCS = " << lcsDP(s1, s2) << endl;
        // Attendu : 3 ("ace")
    }

    // Template 5 : Knapsack 0/1
    {
        cout << "\n[5] Knapsack 0/1" << endl;
        vector<int> weights = {2, 3, 4, 5};
        vector<int> values  = {3, 4, 5, 6};
        int capacity = 8;
        cout << "  weights=[2,3,4,5], values=[3,4,5,6], capacity=8" << endl;
        cout << "  valeur max (tableau)  = " << knapsackDP(weights, values, capacity) << endl;
        cout << "  valeur max (optimise) = " << knapsackOptimise(weights, values, capacity) << endl;
        // Attendu : 10
    }

    return 0;
}
