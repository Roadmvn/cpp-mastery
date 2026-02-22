// ============================================
// LeetCode #76 - Minimum Window Substring (Hard)
// https://leetcode.com/problems/minimum-window-substring/
// ============================================
// Enonce : Etant donne deux strings s et t, trouver la plus petite
// substring de s qui contient TOUS les caracteres de t (avec repetitions).
//
// Exemple : s = "ADOBECODEBANC", t = "ABC" -> Output: "BANC"
//
// Compile : g++ -std=c++17 04_minimum_window_substring.cpp -o 04

#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n² * m) temps | O(m) espace
// Verifier chaque substring de s
// -----------------------------------------------
string minWindowBrute(string s, string t) {
    int n = s.size();
    int minLen = INT_MAX;
    string result = "";

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Verifier si s[i..j] contient tous les chars de t
            unordered_map<char, int> need;
            for (char c : t) need[c]++;

            for (int k = i; k <= j; k++) {
                if (need.count(s[k])) {
                    need[s[k]]--;
                    if (need[s[k]] == 0) need.erase(s[k]);
                }
            }

            if (need.empty() && j - i + 1 < minLen) {
                minLen = j - i + 1;
                result = s.substr(i, minLen);
            }
        }
    }
    return result;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(m) espace
// Sliding window avec deux pointeurs + freq map
//
// Schema :
//   s = "A D O B E C O D E B A N C"    t = "ABC"
//        L                               need={A:1,B:1,C:1}
//        L               R               have A,B,C -> matched! "ADOBEC"
//              L         R               still valid -> "DOBEC"... non
//        Continuer a expand et shrink...
//                                L   R   "BANC" -> meilleur!
//
// Algorithme :
// 1. Expand right jusqu'a avoir tous les chars de t
// 2. Shrink left tant qu'on a encore tous les chars
// 3. Enregistrer le minimum
// -----------------------------------------------
string minWindowOptimal(string s, string t) {
    if (s.empty() || t.empty()) return "";

    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0;
    int matched = 0;       // nombre de chars completement matches
    int required = need.size(); // nombre de chars uniques requis

    int minLen = INT_MAX;
    int minStart = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        // Expand : ajouter s[right] a la fenetre
        char c = s[right];
        window[c]++;

        // Verifier si ce char est completement matche
        if (need.count(c) && window[c] == need[c]) {
            matched++;
        }

        // Shrink : tant qu'on a tous les chars requis
        while (matched == required) {
            // Mettre a jour le resultat
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }

            // Retirer s[left] de la fenetre
            char d = s[left];
            if (need.count(d) && window[d] == need[d]) {
                matched--;
            }
            window[d]--;
            left++;
        }
    }

    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

int main() {
    cout << "=== #76 Minimum Window Substring ===" << endl;

    string s1 = "ADOBECODEBANC", t1 = "ABC";
    cout << "Input: s=\"ADOBECODEBANC\", t=\"ABC\"" << endl;
    cout << "Brute force: \"" << minWindowBrute(s1, t1) << "\" (attendu: \"BANC\")" << endl;
    cout << "Optimal:     \"" << minWindowOptimal(s1, t1) << "\" (attendu: \"BANC\")" << endl;
    cout << endl;

    string s2 = "a", t2 = "a";
    cout << "Input: s=\"a\", t=\"a\"" << endl;
    cout << "Brute force: \"" << minWindowBrute(s2, t2) << "\" (attendu: \"a\")" << endl;
    cout << "Optimal:     \"" << minWindowOptimal(s2, t2) << "\" (attendu: \"a\")" << endl;
    cout << endl;

    string s3 = "a", t3 = "aa";
    cout << "Input: s=\"a\", t=\"aa\"" << endl;
    cout << "Brute force: \"" << minWindowBrute(s3, t3) << "\" (attendu: \"\")" << endl;
    cout << "Optimal:     \"" << minWindowOptimal(s3, t3) << "\" (attendu: \"\")" << endl;
    cout << endl;

    string s4 = "ab", t4 = "b";
    cout << "Input: s=\"ab\", t=\"b\"" << endl;
    cout << "Optimal:     \"" << minWindowOptimal(s4, t4) << "\" (attendu: \"b\")" << endl;

    return 0;
}
