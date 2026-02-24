// https://leetcode.com/problems/word-break/
// #139 - Word Break
//
// Determiner si une chaine peut etre segmentee en mots du dictionnaire.
//
// Approche : DP + hash set.
// dp[i] = true si s[0..i-1] peut etre segmente.
// Pour chaque position i, verifier tous les prefixes s[j..i] dans le dictionnaire.
// Hash set pour O(1) lookup.
// Complexite temps : O(n^2 * m) m = longueur max d'un mot | Complexite espace : O(n + d)

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        int n = (int)s.size();

        // dp[i] = true si s[0..i-1] est segmentable
        vector<bool> dp(n + 1, false);
        dp[0] = true; // chaine vide = toujours segmentable

        for (int i = 1; i <= n; i++) {
            // Essayer tous les points de coupure j < i
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break; // pas besoin de continuer
                }
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;

    vector<string> dict1 = {"leet", "code"};
    cout << boolalpha << sol.wordBreak("leetcode", dict1) << endl; // true

    vector<string> dict2 = {"apple", "pen"};
    cout << sol.wordBreak("applepenapple", dict2) << endl; // true

    vector<string> dict3 = {"cats", "dog", "sand", "and", "cat"};
    cout << sol.wordBreak("catsandog", dict3) << endl; // false

    vector<string> dict4 = {"a", "aa", "aaa"};
    cout << sol.wordBreak("aaaaaaa", dict4) << endl; // true

    return 0;
}
