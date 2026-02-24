// LeetCode #739 -- Daily Temperatures
// https://leetcode.com/problems/daily-temperatures/
// Difficulte : Medium
//
// Enonce :
//   Donne un array temperatures[i] representant la temperature du jour i.
//   Pour chaque jour i, retourne le nombre de jours a attendre pour avoir
//   une temperature plus chaude. Si aucune temperature future n'est plus
//   chaude, retourne 0 pour ce jour.
//
// Exemple :
//   temperatures = [73,74,75,71,69,72,76,73]  ->  [1,1,4,2,1,1,0,0]
//   temperatures = [30,40,50,60]              ->  [1,1,1,0]
//   temperatures = [30,60,90]                 ->  [1,1,0]

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
//  Pour chaque jour i, chercher lineairement le prochain jour
//  plus chaud.
// ============================================================

// vector<int> dailyTemperatures_brute(vector<int>& t) {
//     int n = t.size();
//     vector<int> result(n, 0);
//     for (int i = 0; i < n; i++)
//         for (int j = i + 1; j < n; j++)
//             if (t[j] > t[i]) { result[i] = j - i; break; }
//     return result;
// }

// ============================================================
//  SOLUTION OPTIMALE : Stack monotone decroissante -- O(n)
//
//  La stack stocke les indices des jours "en attente".
//  Quand on trouve une temperature plus chaude, on resout
//  tous les jours en attente qui sont plus froids.
//
//  La stack est maintenue decroissante en temperatures :
//  si temperatures[i] > temperatures[stack.top()], on pop et
//  on calcule la difference d'indices.
//
//  Complexite : O(n) temps, O(n) espace
// ============================================================

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);
        stack<int> st;  // indices, temperatures decroissantes

        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int j = st.top();
                st.pop();
                result[j] = i - j;  // nombre de jours d'attente
            }
            st.push(i);
        }
        // Les indices restants dans la stack -> 0 (deja initialise)
        return result;
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    // Exemple 1
    vector<int> t1 = {73,74,75,71,69,72,76,73};
    auto r1 = sol.dailyTemperatures(t1);
    for (int x : r1) cout << x << " ";
    cout << "\n";  // attendu : 1 1 4 2 1 1 0 0

    // Exemple 2 : toujours croissant
    vector<int> t2 = {30,40,50,60};
    auto r2 = sol.dailyTemperatures(t2);
    for (int x : r2) cout << x << " ";
    cout << "\n";  // attendu : 1 1 1 0

    // Exemple 3
    vector<int> t3 = {30,60,90};
    auto r3 = sol.dailyTemperatures(t3);
    for (int x : r3) cout << x << " ";
    cout << "\n";  // attendu : 1 1 0

    // Edge case : toujours decroissant
    vector<int> t4 = {90,80,70,60};
    auto r4 = sol.dailyTemperatures(t4);
    for (int x : r4) cout << x << " ";
    cout << "\n";  // attendu : 0 0 0 0

    return 0;
}
