// ============================================
// LeetCode #1143 - Longest Common Subsequence (Medium)
// https://leetcode.com/problems/longest-common-subsequence/
// ============================================
// Enonce : Donne deux strings text1 et text2, retourner la longueur
// de leur plus longue sous-sequence commune. Une sous-sequence est
// une sequence derivee en supprimant certains elements sans changer
// l'ordre des elements restants.
//
// Exemple :
//   text1="abcde", text2="ace"  3  (sous-sequence "ace")
//   text1="abc",   text2="abc"  3  (sous-sequence "abc")
//   text1="abc",   text2="def"  0  (pas de sous-sequence commune)
//
// Compile : g++ -std=c++17 05_longest_common_subsequence.cpp -o 05

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(2^(m+n)) temps | O(m+n) espace
// Recursion pure : pour chaque paire de positions (i,j)
// comparer les caracteres et recurser.
// -----------------------------------------------
int lcsBrute(const string& s1, const string& s2, int i, int j) {
    if (i == (int)s1.size() || j == (int)s2.size()) return 0;

    if (s1[i] == s2[j]) {
        return 1 + lcsBrute(s1, s2, i + 1, j + 1);
    }
    // Essayer les deux options et prendre le max
    return max(lcsBrute(s1, s2, i + 1, j),
               lcsBrute(s1, s2, i, j + 1));
}

int longestCommonSubsequenceBrute(string& text1, string& text2) {
    return lcsBrute(text1, text2, 0, 0);
}

// -----------------------------------------------
// TOP-DOWN : O(m*n) temps | O(m*n) espace
// Recursion + memoization avec un tableau 2D.
// -----------------------------------------------
vector<vector<int>> dpMemo;
int lcsMemo(const string& s1, const string& s2, int i, int j) {
    if (i == (int)s1.size() || j == (int)s2.size()) return 0;
    if (dpMemo[i][j] != -1) return dpMemo[i][j];

    if (s1[i] == s2[j]) {
        dpMemo[i][j] = 1 + lcsMemo(s1, s2, i + 1, j + 1);
    } else {
        dpMemo[i][j] = max(lcsMemo(s1, s2, i + 1, j),
                           lcsMemo(s1, s2, i, j + 1));
    }
    return dpMemo[i][j];
}

// -----------------------------------------------
// OPTIMAL - BOTTOM-UP : O(m*n) temps | O(m*n) espace
// Tableau 2D dp[i][j] = LCS de s1[0..i-1] et s2[0..j-1]
//
// Schema ASCII :
//
//   text1 = "abcde"  (m=5)
//   text2 = "ace"    (n=3)
//
//       ""  a   c   e
//   ""   0   0   0   0
//   a    0  [1]  1   1
//   b    0   1   1   1
//   c    0   1  [2]  2
//   d    0   1   2   2
//   e    0   1   2  [3]   reponse = 3
//
//   Remplissage :
//   si s1[i-1] == s2[j-1] : dp[i][j] = dp[i-1][j-1] + 1
//   sinon                 : dp[i][j] = max(dp[i-1][j], dp[i][j-1])
//
//   dp[1][1] : 'a'=='a'  dp[0][0]+1 = 1
//   dp[3][2] : 'c'=='c'  dp[2][1]+1 = 2
//   dp[5][3] : 'e'=='e'  dp[4][2]+1 = 3
// -----------------------------------------------
int longestCommonSubsequenceOptimal(const string& text1, const string& text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}

// Optimisation espace : O(n) espace (une seule ligne)
int longestCommonSubsequenceEspace(const string& text1, const string& text2) {
    int m = text1.size(), n = text2.size();
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        swap(prev, curr);
    }
    return prev[n];
}

int main() {
    cout << "=== LeetCode #1143 - Longest Common Subsequence ===" << endl;

    // Test 1 : exemple classique
    {
        string t1 = "abcde", t2 = "ace";
        cout << "text1=\"" << t1 << "\", text2=\"" << t2 << "\"" << endl;
        dpMemo.assign(t1.size(), vector<int>(t2.size(), -1));
        cout << "Brute   : " << longestCommonSubsequenceBrute(t1, t2) << endl;
        cout << "TopDown : " << lcsMemo(t1, t2, 0, 0) << endl;
        cout << "Optimal : " << longestCommonSubsequenceOptimal(t1, t2) << endl;
        cout << "Espace  : " << longestCommonSubsequenceEspace(t1, t2) << endl;
        // Attendu : 3
        cout << endl;
    }

    // Test 2 : strings identiques
    {
        string t1 = "abc", t2 = "abc";
        cout << "text1=\"" << t1 << "\", text2=\"" << t2 << "\"" << endl;
        dpMemo.assign(t1.size(), vector<int>(t2.size(), -1));
        cout << "Brute   : " << longestCommonSubsequenceBrute(t1, t2) << endl;
        cout << "Optimal : " << longestCommonSubsequenceOptimal(t1, t2) << endl;
        // Attendu : 3
        cout << endl;
    }

    // Test 3 : pas de sous-sequence commune
    {
        string t1 = "abc", t2 = "def";
        cout << "text1=\"" << t1 << "\", text2=\"" << t2 << "\"" << endl;
        dpMemo.assign(t1.size(), vector<int>(t2.size(), -1));
        cout << "Brute   : " << longestCommonSubsequenceBrute(t1, t2) << endl;
        cout << "Optimal : " << longestCommonSubsequenceOptimal(t1, t2) << endl;
        // Attendu : 0
        cout << endl;
    }

    // Test 4 : un seul caractere commun
    {
        string t1 = "bl", t2 = "yby";
        cout << "text1=\"" << t1 << "\", text2=\"" << t2 << "\"" << endl;
        dpMemo.assign(t1.size(), vector<int>(t2.size(), -1));
        cout << "Optimal : " << longestCommonSubsequenceOptimal(t1, t2) << endl;
        // Attendu : 1
        cout << endl;
    }

    cout << "Complexite Brute   : O(2^(m+n)) temps | O(m+n) espace" << endl;
    cout << "Complexite TopDown : O(m*n)     temps | O(m*n) espace" << endl;
    cout << "Complexite Optimal : O(m*n)     temps | O(m*n) espace" << endl;
    cout << "Complexite Espace  : O(m*n)     temps | O(n)   espace" << endl;

    return 0;
}
