// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// #3 - Longest Substring Without Repeating Characters
//
// Trouver la longueur de la plus longue sous-chaine sans caracteres repetes.
//
// Approche : fenetre glissante (sliding window) avec un hash map.
// Maintenir une fenetre [left, right] sans doublons.
// Si un doublon est trouve, avancer left au-dela de la derniere occurrence.
// Complexite temps : O(n) | Complexite espace : O(min(m,n)) m = taille alphabet

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // map : caractere -> dernier index vu
        unordered_map<char, int> lastSeen;
        int maxLen = 0;
        int left = 0; // debut de la fenetre

        for (int right = 0; right < (int)s.size(); right++) {
            char c = s[right];

            // Si le caractere est dans la fenetre courante, shrink depuis la gauche
            if (lastSeen.count(c) && lastSeen[c] >= left) {
                left = lastSeen[c] + 1;
            }

            lastSeen[c] = right;
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

int main() {
    Solution sol;

    cout << sol.lengthOfLongestSubstring("abcabcbb") << endl; // 3 ("abc")
    cout << sol.lengthOfLongestSubstring("bbbbb")    << endl; // 1 ("b")
    cout << sol.lengthOfLongestSubstring("pwwkew")   << endl; // 3 ("wke")
    cout << sol.lengthOfLongestSubstring("")          << endl; // 0
    cout << sol.lengthOfLongestSubstring("au")        << endl; // 2
    cout << sol.lengthOfLongestSubstring("dvdf")      << endl; // 3

    return 0;
}
