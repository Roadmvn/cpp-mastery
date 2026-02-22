// ============================================================
// Probleme 04 : Container With Most Water (Medium)
// LeetCode #11 : https://leetcode.com/problems/container-with-most-water/
// Compile : g++ -std=c++17 -o 04 04-container-with-most-water.cpp && ./04
// ============================================================
//
// Enonce :
// Etant donne un array height de n entiers, ou height[i] represente
// la hauteur d'une ligne verticale au point i, trouver deux lignes
// qui forment avec l'axe X le conteneur qui contient le plus d'eau.
// Retourner la quantite maximale d'eau.
//
// Visuel :
//        |
//   |    |         |
//   | |  |    |    |
//   | |  | |  | |  |
//   | |  | |  | |  |
//   ──────────────────
//   1 8  6 2  5 4  8 3 7
//     ^              ^
//     left          right   aire = min(8,8) * (7-1) = 48 (pas le max)
//
// Exemple : height = [1,8,6,2,5,4,8,3,7]  49
//   Les lignes aux indices 1 (hauteur 8) et 8 (hauteur 7)
//   forment le plus grand conteneur : min(8,7) * (8-1) = 49
//
// Contraintes :
// - n == height.length
// - 2 <= n <= 10^5
// - 0 <= height[i] <= 10^4
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// Solution 1 : Brute force — Tester toutes les paires
// Complexite : O(n^2) temps, O(1) espace
// ============================================================

int maxArea_bruteforce(vector<int>& height) {
    int max_water = 0;
    int n = height.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int water = min(height[i], height[j]) * (j - i);
            max_water = max(max_water, water);
        }
    }

    return max_water;
}

// ============================================================
// Solution 2 : Optimale — Two Pointers opposes
// Complexite : O(n) temps, O(1) espace
// ============================================================
// L'intuition :
// On commence avec la plus grande largeur possible (left=0, right=n-1).
// A chaque etape, on deplace le pointeur qui a la plus PETITE hauteur.
//
// Pourquoi deplacer le plus petit ?
// - L'aire = min(h_left, h_right) * largeur
// - Si on deplace le plus grand, la largeur diminue ET le min reste
//   le meme (ou diminue)  l'aire ne peut QUE diminuer
// - Si on deplace le plus petit, la largeur diminue MAIS le min
//   pourrait augmenter  chance d'augmenter l'aire
//
// Donc on ne rate jamais la solution optimale.

int maxArea_optimal(vector<int>& height) {
    int left = 0;
    int right = (int)height.size() - 1;
    int max_water = 0;

    while (left < right) {
        // Calculer l'aire courante
        int water = min(height[left], height[right]) * (right - left);
        max_water = max(max_water, water);

        // Deplacer le pointeur avec la plus petite hauteur
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return max_water;
}

// ============================================================
// Tests
// ============================================================

void test(vector<int> height, int expected) {
    vector<int> h_copy = height;
    int result_bf = maxArea_bruteforce(height);
    int result_opt = maxArea_optimal(h_copy);

    cout << "Expected: " << expected << endl;
    cout << "  Brute force : " << result_bf
         << " | " << (result_bf == expected ? "PASS" : "FAIL") << endl;
    cout << "  Optimal     : " << result_opt
         << " | " << (result_opt == expected ? "PASS" : "FAIL") << endl;
}

int main() {
    cout << "=== Container With Most Water (LeetCode #11) ===" << endl << endl;

    test({1, 8, 6, 2, 5, 4, 8, 3, 7}, 49);
    test({1, 1}, 1);
    test({4, 3, 2, 1, 4}, 16);
    test({1, 2, 1}, 2);

    cout << endl;
    cout << "Pattern : Two Pointers opposes" << endl;
    cout << "La cle : toujours deplacer le pointeur avec la plus petite" << endl;
    cout << "hauteur, car c'est le seul mouvement qui peut ameliorer l'aire" << endl;

    return 0;
}
