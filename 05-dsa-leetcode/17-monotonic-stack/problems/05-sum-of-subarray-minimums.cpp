// LeetCode #907 -- Sum of Subarray Minimums
// https://leetcode.com/problems/sum-of-subarray-minimums/
// Difficulte : Medium
//
// Enonce :
//   Donne un array d'entiers arr, calculer la somme des minimums de tous les
//   sous-tableaux possibles de arr. Retourner le resultat modulo 10^9 + 7.
//
// Exemple :
//   arr = [3,1,2,4]  ->  17
//   Sous-tableaux : [3]=3, [1]=1, [2]=2, [4]=4,
//                  [3,1]=1, [1,2]=1, [2,4]=2,
//                  [3,1,2]=1, [1,2,4]=1, [3,1,2,4]=1
//   Somme = 3+1+2+4+1+1+2+1+1+1 = 17
//
// Insight cle :
//   Pour chaque element arr[i], compter dans combien de sous-tableaux
//   il est le minimum. Puis contribuer arr[i] * count a la somme totale.
//
//   Pour arr[i] minimum, il faut que le sous-tableau ne contienne pas
//   d'element plus petit a gauche ou a droite.
//   left[i]  = distance au precedent element strictement plus petit (ou debut)
//   right[i] = distance au prochain element inferieur ou egal (ou fin)
//   Nombre de sous-tableaux ou arr[i] est le min = left[i] * right[i]

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
//  BRUTE FORCE : O(n^2) ou O(n^3)
//  Generer tous les sous-tableaux, trouver le min de chacun.
// ============================================================

// int sumSubarrayMins_brute(vector<int>& arr) {
//     const int MOD = 1e9 + 7;
//     int n = arr.size();
//     long long sum = 0;
//     for (int l = 0; l < n; l++) {
//         int minVal = arr[l];
//         for (int r = l; r < n; r++) {
//             minVal = min(minVal, arr[r]);
//             sum = (sum + minVal) % MOD;
//         }
//     }
//     return sum;
// }

// ============================================================
//  SOLUTION OPTIMALE : 2 passes avec stack monotone -- O(n)
//
//  Passe 1 : Pour chaque i, trouver left[i] = nombre d'elements
//  consecutifs a gauche (i compris) ou arr[i] est le minimum.
//  -> previous strictly smaller element (PSE gauche)
//  Si PSE gauche de i est a l'indice j, alors left[i] = i - j
//
//  Passe 2 : Pour chaque i, trouver right[i] de meme a droite.
//  -> next smaller or equal element (NSE droite, <= pour eviter doublons)
//  Si NSE droite de i est a l'indice j, alors right[i] = j - i
//
//  Contribution de arr[i] = arr[i] * left[i] * right[i]
//
//  Note sur <= vs < : utiliser strict a gauche et <= a droite
//  (ou l'inverse) pour gerer les doublons sans les compter deux fois.
//
//  Complexite : O(n) temps, O(n) espace
// ============================================================

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int n = arr.size();
        vector<int> left(n), right(n);
        stack<int> st;

        // Passe 1 : previous strictly smaller (< strict)
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] >= arr[i])
                st.pop();
            left[i] = st.empty() ? i + 1 : i - st.top();
            st.push(i);
        }

        while (!st.empty()) st.pop();

        // Passe 2 : next smaller or equal (<= pour eviter de compter les doublons deux fois)
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] > arr[i])
                st.pop();
            right[i] = st.empty() ? n - i : st.top() - i;
            st.push(i);
        }

        // Calculer la somme
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum = (sum + (long long)arr[i] * left[i] % MOD * right[i]) % MOD;
        }
        return (int)sum;
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    // Exemple 1
    vector<int> a1 = {3,1,2,4};
    cout << sol.sumSubarrayMins(a1) << "\n";  // attendu : 17

    // Exemple 2 : LeetCode official
    vector<int> a2 = {11,81,94,43,3};
    cout << sol.sumSubarrayMins(a2) << "\n";  // attendu : 444

    // Edge case : un seul element
    vector<int> a3 = {5};
    cout << sol.sumSubarrayMins(a3) << "\n";  // attendu : 5

    // Edge case : tous identiques
    vector<int> a4 = {2,2,2};
    // sous-tableaux : [2],[2],[2],[2,2],[2,2],[2,2,2] -> 2*6=12
    cout << sol.sumSubarrayMins(a4) << "\n";  // attendu : 12

    // Edge case : decroissant strict
    vector<int> a5 = {4,3,2,1};
    // min([4])=4, min([3])=3, min([2])=2, min([1])=1
    // min([4,3])=3, min([3,2])=2, min([2,1])=1
    // min([4,3,2])=2, min([3,2,1])=1
    // min([4,3,2,1])=1  -> total = 4+3+2+1+3+2+1+2+1+1 = 20
    cout << sol.sumSubarrayMins(a5) << "\n";  // attendu : 20

    return 0;
}
