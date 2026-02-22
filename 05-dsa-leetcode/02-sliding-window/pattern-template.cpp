// ============================================
// Sliding Window - Templates copier-coller
// ============================================
// Compile : g++ -std=c++17 pattern-template.cpp -o pattern-template

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
using namespace std;

// -----------------------------------------------
// TEMPLATE 1 : Fenetre fixe (taille k)
// Usage : max sum subarray de taille k, moyenne glissante
// -----------------------------------------------
int fixedSlidingWindow(vector<int>& nums, int k) {
    int windowSum = 0;
    int result = INT_MIN;

    for (int i = 0; i < (int)nums.size(); i++) {
        windowSum += nums[i];           // ajouter element a droite

        if (i >= k - 1) {              // fenetre complete
            result = max(result, windowSum);
            windowSum -= nums[i - k + 1]; // retirer element a gauche
        }
    }
    return result;
}

// -----------------------------------------------
// TEMPLATE 2 : Fenetre variable - Plus longue sous condition
// Usage : plus longue substring/subarray avec contrainte
// -----------------------------------------------
int longestVariableWindow(string& s) {
    unordered_set<char> window;
    int left = 0;
    int maxLen = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        // Shrink : tant que la condition est violee
        while (window.count(s[right])) {
            window.erase(s[left]);
            left++;
        }
        // Expand : ajouter l'element courant
        window.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// -----------------------------------------------
// TEMPLATE 3 : Fenetre variable - Plus courte sous condition
// Usage : plus court subarray dont la somme >= target
// -----------------------------------------------
int shortestVariableWindow(vector<int>& nums, int target) {
    int left = 0;
    int windowSum = 0;
    int minLen = INT_MAX;

    for (int right = 0; right < (int)nums.size(); right++) {
        windowSum += nums[right];       // expand

        // Shrink : tant que la condition est satisfaite
        while (windowSum >= target) {
            minLen = min(minLen, right - left + 1);
            windowSum -= nums[left];
            left++;
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}

// -----------------------------------------------
// TEMPLATE 4 : Fenetre avec compteur de frequence
// Usage : anagrammes, permutations, minimum window substring
// -----------------------------------------------
string frequencyWindow(string& s, string& t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0;
    int matched = 0;
    int minLen = INT_MAX;
    int minStart = 0;

    for (int right = 0; right < (int)s.size(); right++) {
        char c = s[right];
        window[c]++;
        if (need.count(c) && window[c] == need[c])
            matched++;

        // Shrink quand tous les caracteres sont matches
        while (matched == (int)need.size()) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }
            char d = s[left];
            if (need.count(d) && window[d] == need[d])
                matched--;
            window[d]--;
            left++;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

int main() {
    cout << "=== Sliding Window Templates ===" << endl;

    // Test template 1
    vector<int> nums1 = {2, 1, 5, 1, 3, 2};
    cout << "Fixed window (k=3): " << fixedSlidingWindow(nums1, 3) << endl;
    // Attendu: 9 (sous-array [5,1,3])

    // Test template 2
    string s1 = "abcabcbb";
    cout << "Longest without repeat: " << longestVariableWindow(s1) << endl;
    // Attendu: 3 ("abc")

    // Test template 3
    vector<int> nums2 = {2, 3, 1, 2, 4, 3};
    cout << "Shortest sum >= 7: " << shortestVariableWindow(nums2, 7) << endl;
    // Attendu: 2 ([4,3])

    // Test template 4
    string s2 = "ADOBECODEBANC";
    string t = "ABC";
    cout << "Min window substring: " << frequencyWindow(s2, t) << endl;
    // Attendu: "BANC"

    return 0;
}
