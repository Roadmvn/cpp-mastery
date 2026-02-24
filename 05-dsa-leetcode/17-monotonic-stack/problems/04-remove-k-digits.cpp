// LeetCode #402 -- Remove K Digits
// https://leetcode.com/problems/remove-k-digits/
// Difficulte : Medium
//
// Enonce :
//   Donne un entier sous forme de string num et un entier k.
//   Retirer k chiffres de num de facon a obtenir le plus petit nombre possible.
//   Retourner le resultat sous forme de string (sans zeros non-significatifs).
//
// Exemple :
//   num = "1432219", k = 3  ->  "1219"
//   num = "10200",   k = 1  ->  "200"   ->  "200" (mais sans zero de tete -> "200")
//   num = "10",      k = 2  ->  "0"

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
//  BRUTE FORCE : O(k * n) -- supprimer k fois le premier chiffre
//  qui est plus grand que son suivant.
// ============================================================

// string removeKdigits_brute(string num, int k) {
//     while (k > 0 && !num.empty()) {
//         int i = 0;
//         while (i + 1 < (int)num.size() && num[i] <= num[i+1]) i++;
//         num.erase(i, 1);
//         k--;
//     }
//     // Retirer les zeros de tete
//     int start = 0;
//     while (start < (int)num.size() - 1 && num[start] == '0') start++;
//     return num.empty() ? "0" : num.substr(start);
// }

// ============================================================
//  SOLUTION OPTIMALE : Stack monotone croissante -- O(n)
//
//  Pour minimiser le nombre, on veut que les chiffres de gauche
//  soient les plus petits possibles.
//  Strategie : maintenir une stack croissante de chiffres.
//  Si le chiffre courant est plus petit que le sommet, on pop
//  (on "supprime" ce chiffre plus grand) en decrementant k.
//
//  Apres le parcours, si k > 0, on supprime les k derniers
//  elements de la stack (les plus grands, a droite).
//
//  Complexite : O(n) temps, O(n) espace
// ============================================================

class Solution {
public:
    string removeKdigits(string num, int k) {
        string stack_str;  // simule une stack avec string

        for (char c : num) {
            // Pop tant que le sommet est plus grand que c et qu'on peut encore supprimer
            while (k > 0 && !stack_str.empty() && stack_str.back() > c) {
                stack_str.pop_back();
                k--;
            }
            stack_str.push_back(c);
        }

        // S'il reste des suppressions a faire, on retire la fin (la plus grande)
        while (k > 0) {
            stack_str.pop_back();
            k--;
        }

        // Retirer les zeros non-significatifs en tete
        int start = 0;
        while (start < (int)stack_str.size() - 1 && stack_str[start] == '0')
            start++;

        return stack_str.empty() ? "0" : stack_str.substr(start);
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    // Exemple 1 : supprimer 4, 3, 2 (chacun > son suivant)
    // "1432219" -> supprimer 4 -> "132219"
    //           -> supprimer 3 -> "12219"
    //           -> supprimer 2 (pos 1) -> "1219"
    cout << sol.removeKdigits("1432219", 3) << "\n";  // attendu : "1219"

    // Exemple 2
    cout << sol.removeKdigits("10200", 1) << "\n";  // attendu : "200"

    // Exemple 3 : supprimer tous les chiffres
    cout << sol.removeKdigits("10", 2) << "\n";  // attendu : "0"

    // Edge case : deja croissant, supprimer les k derniers
    cout << sol.removeKdigits("12345", 2) << "\n";  // attendu : "123"

    // Edge case : zeros
    cout << sol.removeKdigits("100", 1) << "\n";  // attendu : "00" -> "0"

    return 0;
}
