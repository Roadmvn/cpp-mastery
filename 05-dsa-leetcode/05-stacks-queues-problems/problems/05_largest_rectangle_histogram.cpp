// ============================================
// LeetCode #84 - Largest Rectangle in Histogram (Hard)
// https://leetcode.com/problems/largest-rectangle-in-histogram/
// ============================================
// Enonce : Donne un tableau heights[] representant un histogramme ou
// chaque barre a une largeur de 1, retourner l'aire du plus grand
// rectangle que l'on peut former dans cet histogramme.
//
// Exemple :
//   Input : heights = [2,1,5,6,2,3]
//   Output: 10  (rectangle de hauteur 5, largeur 2 => barres 2 et 3)
//
// Compile : g++ -std=c++17 05_largest_rectangle_histogram.cpp -o 05

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n²) temps | O(1) espace extra
// Pour chaque paire (i, j), calculer la hauteur min
// entre i et j, puis aire = min_height * (j - i + 1).
// Garder l'aire maximale.
// -----------------------------------------------
int largestRectangleBrute(vector<int>& heights) {
    int n = heights.size();
    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        int minH = heights[i];
        for (int j = i; j < n; j++) {
            minH = min(minH, heights[j]);
            int area = minH * (j - i + 1);
            maxArea = max(maxArea, area);
        }
    }
    return maxArea;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(n) espace
// Monotonic Stack (pile croissante d'indices)
//
// Principe :
//   - On maintient une pile d'indices dont les hauteurs
//     sont en ordre croissant (sommet = plus grand).
//   - Pour chaque barre i, si heights[i] < heights[pile.top()],
//     on depile et calcule l'aire du rectangle avec la hauteur depilee.
//     La largeur s'etend de l'indice precedent dans la pile jusqu'a i-1.
//   - A la fin, vider la pile en traitant le reste.
//
// Astuce : on utilise des sentinelles (hauteur 0) pour simplifier
//           le traitement des bords.
//
// Schema ASCII :
//
//   heights : [2, 1, 5, 6, 2, 3]
//   indices :   0  1  2  3  4  5
//
//        6 |       [6]
//        5 |     [5][6]
//        3 |               [3]
//        2 | [2]       [2] [3]
//        1 |    [1][5][6][2][3]
//          +--------------------
//             0  1  2  3  4  5
//
//   Traitement de la pile :
//   i=0 : h=2, pile vide → push 0, pile=[0]
//   i=1 : h=1 < h[0]=2 → pop 0:
//           largeur = i - pile_vide => largeur=1, aire=2*1=2
//          push 1, pile=[1]
//   i=2 : h=5 > h[1]=1 → push 2, pile=[1,2]
//   i=3 : h=6 > h[2]=5 → push 3, pile=[1,2,3]
//   i=4 : h=2 < h[3]=6 → pop 3: largeur=4-2-1=1, aire=6*1=6
//           h=2 < h[2]=5 → pop 2: largeur=4-1-1=2, aire=5*2=10  ← MAX
//           h=2 = h[1]=1? non, 2 > 1 → push 4, pile=[1,4]
//   i=5 : h=3 > h[4]=2 → push 5, pile=[1,4,5]
//   Fin  : depiler tout
//     pop 5: largeur=6-4-1=1, aire=3*1=3
//     pop 4: largeur=6-1-1=4, aire=2*4=8
//     pop 1: largeur=6-(-1)-1=6, aire=1*6=6
//
//   Resultat : 10
// -----------------------------------------------
int largestRectangleOptimal(vector<int>& heights) {
    int n = heights.size();
    int maxArea = 0;
    stack<int> stk; // pile d'indices (ordre croissant de hauteur)

    for (int i = 0; i <= n; i++) {
        // On utilise 0 comme sentinelle apres le dernier element
        int curH = (i == n) ? 0 : heights[i];

        while (!stk.empty() && curH < heights[stk.top()]) {
            int h = heights[stk.top()];
            stk.pop();
            // Largeur : de l'element juste apres le nouveau sommet jusqu'a i-1
            int width = stk.empty() ? i : (i - stk.top() - 1);
            int area = h * width;
            maxArea = max(maxArea, area);
        }
        stk.push(i);
    }
    return maxArea;
}

int main() {
    cout << "=== LeetCode #84 - Largest Rectangle in Histogram ===" << endl;

    // Test 1 : exemple classique
    {
        vector<int> heights = {2, 1, 5, 6, 2, 3};
        cout << "Input : [2,1,5,6,2,3]" << endl;
        cout << "Brute  : " << largestRectangleBrute(heights) << endl;
        cout << "Optimal: " << largestRectangleOptimal(heights) << endl;
        // Attendu : 10
        cout << endl;
    }

    // Test 2 : deux barres egales
    {
        vector<int> heights = {2, 4};
        cout << "Input : [2,4]" << endl;
        cout << "Brute  : " << largestRectangleBrute(heights) << endl;
        cout << "Optimal: " << largestRectangleOptimal(heights) << endl;
        // Attendu : 4
        cout << endl;
    }

    // Test 3 : toutes les barres identiques
    {
        vector<int> heights = {3, 3, 3, 3};
        cout << "Input : [3,3,3,3]" << endl;
        cout << "Brute  : " << largestRectangleBrute(heights) << endl;
        cout << "Optimal: " << largestRectangleOptimal(heights) << endl;
        // Attendu : 12 (4 * 3)
        cout << endl;
    }

    // Test 4 : ordre decroissant
    {
        vector<int> heights = {5, 4, 3, 2, 1};
        cout << "Input : [5,4,3,2,1]" << endl;
        cout << "Brute  : " << largestRectangleBrute(heights) << endl;
        cout << "Optimal: " << largestRectangleOptimal(heights) << endl;
        // Attendu : 9 (hauteur 3 * largeur 3)
        cout << endl;
    }

    // Test 5 : ordre croissant
    {
        vector<int> heights = {1, 2, 3, 4, 5};
        cout << "Input : [1,2,3,4,5]" << endl;
        cout << "Brute  : " << largestRectangleBrute(heights) << endl;
        cout << "Optimal: " << largestRectangleOptimal(heights) << endl;
        // Attendu : 9 (hauteur 3 * largeur 3)
        cout << endl;
    }

    // Test 6 : une seule barre
    {
        vector<int> heights = {7};
        cout << "Input : [7]" << endl;
        cout << "Brute  : " << largestRectangleBrute(heights) << endl;
        cout << "Optimal: " << largestRectangleOptimal(heights) << endl;
        // Attendu : 7
        cout << endl;
    }

    cout << "Complexite Brute  : O(n^2) temps | O(1) espace" << endl;
    cout << "Complexite Optimal: O(n)   temps | O(n) espace" << endl;

    return 0;
}
