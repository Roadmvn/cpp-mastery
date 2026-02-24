// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
// #121 - Best Time to Buy and Sell Stock
//
// Tableau de prix jour par jour. Acheter un jour, vendre un jour subsequent.
// Maximiser le profit. Retourner 0 si aucun profit possible.
//
// Approche : 1 passe — tracker le prix minimum vu jusqu'a present,
// calculer le profit potentiel a chaque jour, retenir le maximum.
// Complexite temps : O(n) | Complexite espace : O(1)

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;

        for (int price : prices) {
            if (price < minPrice) {
                // Nouveau minimum trouve : meilleur jour pour acheter
                minPrice = price;
            } else {
                // Calculer le profit si on vendait aujourd'hui
                maxProfit = max(maxProfit, price - minPrice);
            }
        }

        return maxProfit;
    }
};

int main() {
    Solution sol;

    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << sol.maxProfit(prices1) << endl; // 5 (acheter a 1, vendre a 6)

    vector<int> prices2 = {7, 6, 4, 3, 1};
    cout << sol.maxProfit(prices2) << endl; // 0 (prix toujours en baisse)

    vector<int> prices3 = {1, 2};
    cout << sol.maxProfit(prices3) << endl; // 1

    vector<int> prices4 = {2, 4, 1};
    cout << sol.maxProfit(prices4) << endl; // 2

    return 0;
}
