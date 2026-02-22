// ============================================
// LeetCode #875 - Koko Eating Bananas (Medium)
// https://leetcode.com/problems/koko-eating-bananas/
// ============================================
// Enonce : Koko a n piles de bananes. Elle mange a vitesse k bananes/heure.
// Chaque heure, elle choisit une pile et mange k bananes (si la pile < k,
// elle mange tout et attend). Elle a h heures. Trouver le k minimum.
//
// Exemple : piles = [3,6,7,11], h = 8 -> Output: 4
//
// Compile : g++ -std=c++17 03_koko_eating_bananas.cpp -o 03

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Calcul du nombre d'heures necessaires pour manger toutes les piles a vitesse k
long long hoursNeeded(vector<int>& piles, int k) {
    long long total = 0;
    for (int pile : piles) {
        total += (pile + k - 1) / k; // ceil(pile / k) sans flottant
    }
    return total;
}

// -----------------------------------------------
// BRUTE FORCE : O(max(piles) * n) temps | O(1) espace
// Tester chaque vitesse de 1 a max(piles)
// -----------------------------------------------
int minEatingSpeedBrute(vector<int>& piles, int h) {
    int maxPile = *max_element(piles.begin(), piles.end());

    for (int k = 1; k <= maxPile; k++) {
        if (hoursNeeded(piles, k) <= h) return k;
    }
    return maxPile;
}

// -----------------------------------------------
// OPTIMAL : O(n * log(max(piles))) temps | O(1) espace
// Binary search sur la vitesse k
//
// L'espace de recherche est [1, max(piles)]
// Plus k est grand, moins on a besoin d'heures -> MONOTONE
//
// Schema :
//   piles = [3, 6, 7, 11], h = 8
//
//   Vitesse:  1  2  3  4  5  6  7  8  9  10  11
//   Heures:  27 13  9  8  7  6  5  4  4   4   4
//   Valid?:   N  N  N  Y  Y  Y  Y  Y  Y   Y   Y
//                     ^
//                     Premier Y -> reponse = 4
//
//   BS: lo=1, hi=11
//   mid=6 -> heures=6<=8 -> hi=6
//   mid=3 -> heures=9>8  -> lo=4
//   mid=5 -> heures=7<=8 -> hi=5
//   mid=4 -> heures=8<=8 -> hi=4
//   lo==hi==4 -> reponse = 4
// -----------------------------------------------
int minEatingSpeedOptimal(vector<int>& piles, int h) {
    int lo = 1;
    int hi = *max_element(piles.begin(), piles.end());

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (hoursNeeded(piles, mid) <= h) {
            hi = mid;       // peut finir -> chercher plus petit
        } else {
            lo = mid + 1;   // ne peut pas finir -> aller plus vite
        }
    }
    return lo;
}

int main() {
    cout << "=== #875 Koko Eating Bananas ===" << endl;

    vector<int> test1 = {3, 6, 7, 11};
    cout << "Input: [3,6,7,11], h=8" << endl;
    cout << "Brute force: " << minEatingSpeedBrute(test1, 8) << " (attendu: 4)" << endl;
    cout << "Optimal:     " << minEatingSpeedOptimal(test1, 8) << " (attendu: 4)" << endl;
    cout << endl;

    vector<int> test2 = {30, 11, 23, 4, 20};
    cout << "Input: [30,11,23,4,20], h=5" << endl;
    cout << "Brute force: " << minEatingSpeedBrute(test2, 5) << " (attendu: 30)" << endl;
    cout << "Optimal:     " << minEatingSpeedOptimal(test2, 5) << " (attendu: 30)" << endl;
    cout << endl;

    vector<int> test3 = {30, 11, 23, 4, 20};
    cout << "Input: [30,11,23,4,20], h=6" << endl;
    cout << "Brute force: " << minEatingSpeedBrute(test3, 6) << " (attendu: 23)" << endl;
    cout << "Optimal:     " << minEatingSpeedOptimal(test3, 6) << " (attendu: 23)" << endl;

    return 0;
}
