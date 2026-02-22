// ============================================
// LeetCode #424 - Longest Repeating Character Replacement (Medium)
// https://leetcode.com/problems/longest-repeating-character-replacement/
// ============================================
// Enonce : Etant donne une string s et un entier k, on peut remplacer
// au plus k caracteres. Trouver la longueur de la plus longue substring
// contenant le meme caractere.
//
// Exemple : s = "AABABBA", k = 1 -> Output: 4 ("AABA" -> "AAAA")
//
// Compile : g++ -std=c++17 03_longest_repeating_char_replacement.cpp -o 03

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(26 * n²) temps | O(1) espace
// Pour chaque substring, verifier si on peut la rendre
// uniforme avec au plus k remplacements
// -----------------------------------------------
int characterReplacementBrute(string s, int k) {
    int n = s.size();
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        int freq[26] = {};
        int maxFreq = 0;
        for (int j = i; j < n; j++) {
            freq[s[j] - 'A']++;
            maxFreq = max(maxFreq, freq[s[j] - 'A']);
            int windowLen = j - i + 1;
            // Nombre de chars a remplacer = taille fenetre - char le plus frequent
            if (windowLen - maxFreq <= k) {
                maxLen = max(maxLen, windowLen);
            }
        }
    }
    return maxLen;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(1) espace (26 chars max)
// Sliding window : la fenetre est valide si
// (taille fenetre - frequence max char) <= k
//
// Schema :
//   "A A B A B B A"   k=1
//    L R              freq={A:2}      maxF=2  len-maxF=0<=1 OK  len=2
//    L   R            freq={A:2,B:1}  maxF=2  len-maxF=1<=1 OK  len=3
//    L     R          freq={A:3,B:1}  maxF=3  len-maxF=1<=1 OK  len=4 <-
//    L       R        freq={A:3,B:2}  maxF=3  len-maxF=2>1  SHRINK
//      L     R        freq={A:2,B:2}  maxF=2  len-maxF=2>1  SHRINK
//        L   R        freq={A:1,B:2}  maxF=2  len-maxF=1<=1 OK  len=3
//        L     R      freq={A:1,B:3}  maxF=3  len-maxF=1<=1 OK  len=4 <-
//        L       R    freq={A:2,B:3}  maxF=3  len-maxF=2>1  SHRINK
//          L     R    freq={A:2,B:2}  maxF=2  ...
//
// Resultat: 4
// -----------------------------------------------
int characterReplacementOptimal(string s, int k) {
    int freq[26] = {};
    int left = 0;
    int maxFreq = 0;  // freq du char le plus frequent dans la fenetre
    int maxLen = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        freq[s[right] - 'A']++;
        maxFreq = max(maxFreq, freq[s[right] - 'A']);

        // Si la fenetre est invalide, shrink
        int windowLen = right - left + 1;
        if (windowLen - maxFreq > k) {
            freq[s[left] - 'A']--;
            left++;
        }

        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

int main() {
    cout << "=== #424 Longest Repeating Character Replacement ===" << endl;

    string test1 = "ABAB";
    cout << "Input: \"ABAB\", k=2" << endl;
    cout << "Brute force: " << characterReplacementBrute(test1, 2) << " (attendu: 4)" << endl;
    cout << "Optimal:     " << characterReplacementOptimal(test1, 2) << " (attendu: 4)" << endl;
    cout << endl;

    string test2 = "AABABBA";
    cout << "Input: \"AABABBA\", k=1" << endl;
    cout << "Brute force: " << characterReplacementBrute(test2, 1) << " (attendu: 4)" << endl;
    cout << "Optimal:     " << characterReplacementOptimal(test2, 1) << " (attendu: 4)" << endl;
    cout << endl;

    string test3 = "AAAA";
    cout << "Input: \"AAAA\", k=0" << endl;
    cout << "Brute force: " << characterReplacementBrute(test3, 0) << " (attendu: 4)" << endl;
    cout << "Optimal:     " << characterReplacementOptimal(test3, 0) << " (attendu: 4)" << endl;
    cout << endl;

    string test4 = "ABCD";
    cout << "Input: \"ABCD\", k=2" << endl;
    cout << "Brute force: " << characterReplacementBrute(test4, 2) << " (attendu: 3)" << endl;
    cout << "Optimal:     " << characterReplacementOptimal(test4, 2) << " (attendu: 3)" << endl;

    return 0;
}
