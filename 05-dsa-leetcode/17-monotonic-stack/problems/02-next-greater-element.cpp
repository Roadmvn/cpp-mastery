// LeetCode #496 -- Next Greater Element I
// https://leetcode.com/problems/next-greater-element-i/
// Difficulte : Easy
//
// Enonce :
//   nums1 est un sous-ensemble de nums2 (tous les elements sont distincts).
//   Pour chaque element de nums1, trouver le next greater element dans nums2.
//   Le next greater element de x dans nums2 est le premier element a droite
//   de x dans nums2 qui est plus grand que x. S'il n'existe pas, retourner -1.
//
// Exemple :
//   nums1 = [4,1,2], nums2 = [1,3,4,2]  ->  [-1,3,-1]
//   nums1 = [2,4],   nums2 = [1,2,3,4]  ->  [3,-1]

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
//  BRUTE FORCE : O(m * n)
//  Pour chaque element de nums1, trouver sa position dans nums2
//  puis chercher lineairement a droite.
// ============================================================

// vector<int> nextGreaterElement_brute(vector<int>& nums1, vector<int>& nums2) {
//     vector<int> result;
//     for (int x : nums1) {
//         int nge = -1;
//         bool found = false;
//         for (int y : nums2) {
//             if (found && y > x) { nge = y; break; }
//             if (y == x) found = true;
//         }
//         result.push_back(nge);
//     }
//     return result;
// }

// ============================================================
//  SOLUTION OPTIMALE : Stack monotone + HashMap -- O(n + m)
//
//  Etape 1 : Parcourir nums2 une seule fois avec une stack
//            decroissante. Pour chaque element, on enregistre
//            son next greater element dans une map.
//  Etape 2 : Pour chaque element de nums1, consulter la map.
//
//  Complexite : O(n + m) temps, O(n) espace
//  n = taille de nums2, m = taille de nums1
// ============================================================

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // Etape 1 : construire la map NGE pour tous les elements de nums2
        unordered_map<int, int> nge;
        stack<int> st;  // valeurs, ordre decroissant

        for (int x : nums2) {
            while (!st.empty() && st.top() < x) {
                nge[st.top()] = x;
                st.pop();
            }
            st.push(x);
        }
        // Les elements restants n'ont pas de NGE -> nge[x] = -1 par defaut

        // Etape 2 : repondre aux queries
        vector<int> result;
        for (int x : nums1)
            result.push_back(nge.count(x) ? nge[x] : -1);

        return result;
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    // Exemple 1
    vector<int> n1 = {4,1,2}, n2 = {1,3,4,2};
    auto r1 = sol.nextGreaterElement(n1, n2);
    for (int x : r1) cout << x << " ";
    cout << "\n";  // attendu : -1 3 -1

    // Exemple 2
    vector<int> n3 = {2,4}, n4 = {1,2,3,4};
    auto r2 = sol.nextGreaterElement(n3, n4);
    for (int x : r2) cout << x << " ";
    cout << "\n";  // attendu : 3 -1

    // Edge case : nums1 = nums2
    vector<int> n5 = {1,2,3}, n6 = {1,2,3};
    auto r3 = sol.nextGreaterElement(n5, n6);
    for (int x : r3) cout << x << " ";
    cout << "\n";  // attendu : 2 3 -1

    // Edge case : nums2 decroissant
    vector<int> n7 = {1,2,3}, n8 = {3,2,1};
    auto r4 = sol.nextGreaterElement(n7, n8);
    for (int x : r4) cout << x << " ";
    cout << "\n";  // attendu : -1 -1 -1

    return 0;
}
