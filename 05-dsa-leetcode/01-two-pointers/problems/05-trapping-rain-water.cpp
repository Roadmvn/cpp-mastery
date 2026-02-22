// ============================================================
// Probleme 05 : Trapping Rain Water (Hard)
// LeetCode #42 : https://leetcode.com/problems/trapping-rain-water/
// Compile : g++ -std=c++17 -o 05 05-trapping-rain-water.cpp && ./05
// ============================================================
//
// Enonce :
// Etant donne n entiers non-negatifs representant une elevation map
// ou la largeur de chaque barre est 1, calcule combien d'eau peut
// etre piegee apres la pluie.
//
// Visuel :
//
//                 #
//         # ~ ~ ~ # # ~ #
//     # ~ # # ~ # # # # # #
//   ─────────────────────────
//     0 1 0 2 1 0 1 3 2 1 2 1
//
//   ~ = eau piegee (total = 6)
//
// Exemple 1 : height = [0,1,0,2,1,0,1,3,2,1,2,1]  6
// Exemple 2 : height = [4,2,0,3,2,5]  9
//
// Contraintes :
// - n == height.length
// - 1 <= n <= 2 * 10^4
// - 0 <= height[i] <= 10^5
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// Solution 1 : Brute force — Pour chaque position, trouver le max
// Complexite : O(n^2) temps, O(1) espace
// ============================================================
// Pour chaque index i, l'eau au-dessus est :
//   water[i] = min(max_left, max_right) - height[i]
// On calcule max_left et max_right a chaque position.

int trap_bruteforce(vector<int>& height) {
    int n = height.size();
    int total = 0;

    for (int i = 0; i < n; i++) {
        // Trouver le max a gauche de i (inclus)
        int max_left = 0;
        for (int j = 0; j <= i; j++) {
            max_left = max(max_left, height[j]);
        }

        // Trouver le max a droite de i (inclus)
        int max_right = 0;
        for (int j = i; j < n; j++) {
            max_right = max(max_right, height[j]);
        }

        // L'eau a la position i
        total += min(max_left, max_right) - height[i];
    }

    return total;
}

// ============================================================
// Solution 2 : Optimale — Two Pointers
// Complexite : O(n) temps, O(1) espace
// ============================================================
// L'observation cle :
// - L'eau en un point = min(max_left, max_right) - height[i]
// - On n'a pas besoin de connaitre les DEUX max pour decider
//   quel cote traiter
//
// Si max_left < max_right :
//   L'eau a gauche est limitee par max_left (pas par max_right)
//    on peut calculer l'eau a gauche avec certitude
//    avancer left
//
// Si max_right <= max_left :
//   L'eau a droite est limitee par max_right
//    on peut calculer l'eau a droite avec certitude
//    reculer right
//
// Visuellement :
//
//   left_max=1        right_max=2
//                         
//   [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
//       L                          R
//
//   left_max < right_max  on sait que l'eau a L
//   est limitee par left_max  water += left_max - height[L]

int trap_optimal(vector<int>& height) {
    int n = height.size();
    if (n <= 2) return 0; // Impossible de pieger de l'eau

    int left = 0, right = n - 1;
    int left_max = 0, right_max = 0;
    int total = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            // Le cote gauche est le goulot d'etranglement
            if (height[left] >= left_max) {
                // Nouveau max, pas d'eau ici (c'est un mur)
                left_max = height[left];
            } else {
                // L'eau = left_max - hauteur actuelle
                total += left_max - height[left];
            }
            left++;
        } else {
            // Le cote droit est le goulot d'etranglement
            if (height[right] >= right_max) {
                right_max = height[right];
            } else {
                total += right_max - height[right];
            }
            right--;
        }
    }

    return total;
}

// ============================================================
// Tests
// ============================================================

void test(vector<int> height, int expected) {
    vector<int> h_copy = height;
    int result_bf = trap_bruteforce(height);
    int result_opt = trap_optimal(h_copy);

    cout << "Expected: " << expected << endl;
    cout << "  Brute force : " << result_bf
         << " | " << (result_bf == expected ? "PASS" : "FAIL") << endl;
    cout << "  Optimal     : " << result_opt
         << " | " << (result_opt == expected ? "PASS" : "FAIL") << endl;
}

int main() {
    cout << "=== Trapping Rain Water (LeetCode #42) ===" << endl << endl;

    test({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, 6);
    test({4, 2, 0, 3, 2, 5}, 9);
    test({2, 0, 2}, 2);
    test({3, 0, 0, 2, 0, 4}, 10);
    test({0}, 0);
    test({1, 2}, 0);

    cout << endl;
    cout << "Pattern : Two Pointers opposes avec tracking des max" << endl;
    cout << "C'est LE probleme Hard classique de Two Pointers." << endl;
    cout << "La cle : le cote avec le plus petit max est le goulot" << endl;
    cout << "d'etranglement, donc on peut calculer l'eau de ce cote" << endl;
    cout << "avec certitude sans connaitre le max de l'autre cote." << endl;

    return 0;
}
