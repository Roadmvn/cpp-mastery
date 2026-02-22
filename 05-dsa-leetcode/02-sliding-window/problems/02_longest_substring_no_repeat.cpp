// ============================================
// LeetCode #3 - Longest Substring Without Repeating Characters (Medium)
// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// ============================================
// Enonce : Trouver la longueur de la plus longue substring sans caracteres
// repetes.
//
// Exemple : s = "abcabcbb" -> Output: 3 ("abc")
//
// Compile : g++ -std=c++17 02_longest_substring_no_repeat.cpp -o 02

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n³) temps | O(n) espace
// Verifier chaque substring
// -----------------------------------------------
int lengthOfLongestSubstringBrute(string s) {
    int n = s.size();
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Verifier si substring s[i..j] a des doublons
            unordered_set<char> seen;
            bool valid = true;
            for (int k = i; k <= j; k++) {
                if (seen.count(s[k])) { valid = false; break; }
                seen.insert(s[k]);
            }
            if (valid) maxLen = max(maxLen, j - i + 1);
        }
    }
    return maxLen;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(min(n, m)) espace (m = taille alphabet)
// Sliding window avec HashSet
//
// Schema :
//   "a b c a b c b b"
//    L R             window={a}       len=1
//    L   R           window={a,b}     len=2
//    L     R         window={a,b,c}   len=3
//      L     R       window={b,c,a}   len=3  (retire a doublon)
//        L     R     window={c,a,b}   len=3
//          L     R   window={a,b,c}   len=3
//              L   R window={c,b}     len=2
//                L R window={b}       len=1
//
// Resultat: 3
// -----------------------------------------------
int lengthOfLongestSubstringOptimal(string s) {
    unordered_set<char> window;
    int left = 0;
    int maxLen = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        // Shrink tant qu'on a un doublon
        while (window.count(s[right])) {
            window.erase(s[left]);
            left++;
        }
        window.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// -----------------------------------------------
// OPTIMAL V2 : O(n) temps | O(min(n, m)) espace
// Avec HashMap pour sauter directement
// -----------------------------------------------
int lengthOfLongestSubstringV2(string s) {
    unordered_map<char, int> lastSeen; // char -> dernier index
    int left = 0;
    int maxLen = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        if (lastSeen.count(s[right]) && lastSeen[s[right]] >= left) {
            left = lastSeen[s[right]] + 1;  // sauter directement
        }
        lastSeen[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

int main() {
    cout << "=== #3 Longest Substring Without Repeating Characters ===" << endl;

    string test1 = "abcabcbb";
    cout << "Input: \"abcabcbb\"" << endl;
    cout << "Brute force: " << lengthOfLongestSubstringBrute(test1) << " (attendu: 3)" << endl;
    cout << "Optimal:     " << lengthOfLongestSubstringOptimal(test1) << " (attendu: 3)" << endl;
    cout << "Optimal V2:  " << lengthOfLongestSubstringV2(test1) << " (attendu: 3)" << endl;
    cout << endl;

    string test2 = "bbbbb";
    cout << "Input: \"bbbbb\"" << endl;
    cout << "Brute force: " << lengthOfLongestSubstringBrute(test2) << " (attendu: 1)" << endl;
    cout << "Optimal:     " << lengthOfLongestSubstringOptimal(test2) << " (attendu: 1)" << endl;
    cout << endl;

    string test3 = "pwwkew";
    cout << "Input: \"pwwkew\"" << endl;
    cout << "Brute force: " << lengthOfLongestSubstringBrute(test3) << " (attendu: 3)" << endl;
    cout << "Optimal:     " << lengthOfLongestSubstringOptimal(test3) << " (attendu: 3)" << endl;
    cout << endl;

    string test4 = "";
    cout << "Input: \"\"" << endl;
    cout << "Optimal:     " << lengthOfLongestSubstringOptimal(test4) << " (attendu: 0)" << endl;

    return 0;
}
