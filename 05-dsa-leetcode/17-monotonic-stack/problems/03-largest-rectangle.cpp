// LeetCode #84 -- Largest Rectangle in Histogram
// https://leetcode.com/problems/largest-rectangle-in-histogram/
// Difficulte : Hard
//
// Enonce :
//   Donne un array heights representant un histogramme (largeur de chaque barre = 1).
//   Trouver l'aire du plus grand rectangle qu'on peut former dans l'histogramme.
//
// Exemple :
//   heights = [2,1,5,6,2,3]  ->  10  (barres 5 et 6, largeur 2)
//   heights = [2,4]          ->  4

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

// ============================================================
//  BRUTE FORCE : O(n^2)
//  Pour chaque paire (l, r), l'aire est min(heights[l..r]) * (r-l+1).
// ============================================================

// int largestRectangleArea_brute(vector<int>& heights) {
//     int n = heights.size(), maxArea = 0;
//     for (int l = 0; l < n; l++) {
//         int minH = heights[l];
//         for (int r = l; r < n; r++) {
//             minH = min(minH, heights[r]);
//             maxArea = max(maxArea, minH * (r - l + 1));
//         }
//     }
//     return maxArea;
// }

// ============================================================
//  SOLUTION OPTIMALE : Stack monotone croissante -- O(n)
//
//  Idee : pour chaque barre i, calculer l'aire maximale du
//  rectangle dont heights[i] est la hauteur limitante.
//  - Largeur droite : premier j > i avec heights[j] < heights[i]
//  - Largeur gauche : premier k < i avec heights[k] < heights[i]
//
//  On utilise une stack croissante. Quand on trouve une barre
//  plus petite, on pop et on calcule l'aire pour la barre poppee.
//
//  Sentinelle : on ajoute 0 a la fin pour vider la stack.
//
//  Pour la barre poppee a l'indice top :
//    height = heights[top]
//    left_bound  = stack.top() (le nouveau sommet, ou -1 si vide)
//    right_bound = i
//    width = right_bound - left_bound - 1
//
//  Complexite : O(n) temps, O(n) espace
// ============================================================

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;  // indices, hauteurs croissantes
        int maxArea = 0;
        int n = heights.size();

        for (int i = 0; i <= n; i++) {
            int h = (i == n) ? 0 : heights[i];  // sentinelle pour vider la stack

            while (!st.empty() && heights[st.top()] > h) {
                int height = heights[st.top()];
                st.pop();
                // Largeur : de l'element juste en-dessous dans la stack jusqu'a i
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }
        return maxArea;
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    // Exemple 1 : rectangles imbriques
    // Histogramme : [2,1,5,6,2,3]
    //   _ _
    //  |   |
    //  | _ |_ _
    //  ||   |   |
    //  ||   |_  |
    //  |||_   | |
    //  ||||   | |
    // Le rectangle 5*2 (barres d'indice 2 et 3) donne aire = 10
    vector<int> h1 = {2,1,5,6,2,3};
    cout << sol.largestRectangleArea(h1) << "\n";  // attendu : 10

    // Exemple 2 : deux barres
    vector<int> h2 = {2,4};
    cout << sol.largestRectangleArea(h2) << "\n";  // attendu : 4

    // Edge case : une seule barre
    vector<int> h3 = {5};
    cout << sol.largestRectangleArea(h3) << "\n";  // attendu : 5

    // Edge case : toutes egales
    vector<int> h4 = {3,3,3,3};
    cout << sol.largestRectangleArea(h4) << "\n";  // attendu : 12

    // Edge case : croissant
    vector<int> h5 = {1,2,3,4,5};
    cout << sol.largestRectangleArea(h5) << "\n";  // attendu : 9 (3*3)

    // Edge case : decroissant
    vector<int> h6 = {5,4,3,2,1};
    cout << sol.largestRectangleArea(h6) << "\n";  // attendu : 9 (3*3)

    return 0;
}
