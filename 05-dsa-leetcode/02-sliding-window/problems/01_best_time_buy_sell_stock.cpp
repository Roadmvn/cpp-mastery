// ============================================
// LeetCode #121 - Best Time to Buy and Sell Stock (Easy)
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
// ============================================
// Enonce : Etant donne un tableau de prix par jour, trouver le profit
// maximum en achetant un jour et vendant un jour FUTUR.
// Retourner 0 si aucun profit possible.
//
// Exemple : prices = [7,1,5,3,6,4] -> Output: 5 (acheter a 1, vendre a 6)
//
// Compile : g++ -std=c++17 01_best_time_buy_sell_stock.cpp -o 01

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n²) temps | O(1) espace
// Tester chaque paire (achat, vente)
// -----------------------------------------------
int maxProfitBrute(vector<int>& prices) {
    int maxProfit = 0;
    int n = prices.size();

    for (int i = 0; i < n; i++) {            // jour d'achat
        for (int j = i + 1; j < n; j++) {    // jour de vente
            int profit = prices[j] - prices[i];
            maxProfit = max(maxProfit, profit);
        }
    }
    return maxProfit;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(1) espace
// Sliding window : garder le prix min vu jusqu'ici
//
// Schema :
//   prices: [7, 1, 5, 3, 6, 4]
//            ^
//            minPrice=7, profit=0
//               ^
//               minPrice=1, profit=0
//                  ^
//                  profit=5-1=4
//                     ^
//                     profit=3-1=2
//                        ^
//                        profit=6-1=5  <- MAX
//                           ^
//                           profit=4-1=3
// -----------------------------------------------
int maxProfitOptimal(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;

    for (int price : prices) {
        minPrice = min(minPrice, price);           // mise a jour du min
        maxProfit = max(maxProfit, price - minPrice); // profit si on vend aujourd'hui
    }
    return maxProfit;
}

int main() {
    cout << "=== #121 Best Time to Buy and Sell Stock ===" << endl;

    vector<int> test1 = {7, 1, 5, 3, 6, 4};
    cout << "Input: [7,1,5,3,6,4]" << endl;
    cout << "Brute force: " << maxProfitBrute(test1) << " (attendu: 5)" << endl;
    cout << "Optimal:     " << maxProfitOptimal(test1) << " (attendu: 5)" << endl;
    cout << endl;

    vector<int> test2 = {7, 6, 4, 3, 1};
    cout << "Input: [7,6,4,3,1]" << endl;
    cout << "Brute force: " << maxProfitBrute(test2) << " (attendu: 0)" << endl;
    cout << "Optimal:     " << maxProfitOptimal(test2) << " (attendu: 0)" << endl;
    cout << endl;

    vector<int> test3 = {2, 4, 1};
    cout << "Input: [2,4,1]" << endl;
    cout << "Brute force: " << maxProfitBrute(test3) << " (attendu: 2)" << endl;
    cout << "Optimal:     " << maxProfitOptimal(test3) << " (attendu: 2)" << endl;

    return 0;
}
