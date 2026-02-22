// ============================================
// LeetCode #242 - Valid Anagram (Easy)
// https://leetcode.com/problems/valid-anagram/
// ============================================
// Enonce : Determiner si la string t est un anagramme de s.
// Un anagramme utilise exactement les memes lettres, dans n'importe quel ordre.
//
// Exemple :
//   Input : s="anagram", t="nagaram" → Output: true
//   Input : s="rat",     t="car"     → Output: false
//
// Compile : g++ -std=c++17 02_valid_anagram.cpp -o 02

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n log n) temps | O(1) espace
// Trier les deux strings et comparer.
// Si elles sont identiques apres tri → anagramme.
// -----------------------------------------------
bool isAnagramBrute(string s, string t) {
    if (s.size() != t.size()) return false;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(1) espace (alphabet fixe)
// Frequency Counter avec tableau de 26 cases
// (ou unordered_map pour alphabet Unicode).
//
// Schema ASCII :
//
//   s = "anagram"    t = "nagaram"
//
//   Etape 1 : freq[c]++ pour chaque c dans s
//   ┌─────────────────────────────────────────┐
//   │ a:3  g:1  m:1  n:1  r:1                │
//   └─────────────────────────────────────────┘
//
//   Etape 2 : freq[c]-- pour chaque c dans t
//   ┌─────────────────────────────────────────┐
//   │ a:0  g:0  m:0  n:0  r:0                │
//   └─────────────────────────────────────────┘
//
//   Etape 3 : verifier que toutes les valeurs sont 0
//   → OUI → Anagramme valide !
// -----------------------------------------------
bool isAnagramOptimal(const string& s, const string& t) {
    if (s.size() != t.size()) return false;

    int freq[26] = {};
    for (char c : s) freq[c - 'a']++;
    for (char c : t) freq[c - 'a']--;

    for (int count : freq) {
        if (count != 0) return false;
    }
    return true;
}

// Variante avec unordered_map (supporte Unicode/alphabet quelconque)
bool isAnagramHashMap(const string& s, const string& t) {
    if (s.size() != t.size()) return false;

    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;
    for (char c : t) {
        if (--freq[c] < 0) return false;
    }
    return true;
}

int main() {
    cout << "=== LeetCode #242 - Valid Anagram ===" << endl;

    // Test 1 : anagramme valide
    {
        string s = "anagram", t = "nagaram";
        cout << "s=\"" << s << "\", t=\"" << t << "\"" << endl;
        cout << "Brute  : " << (isAnagramBrute(s, t) ? "true" : "false") << endl;
        cout << "Optimal: " << (isAnagramOptimal(s, t) ? "true" : "false") << endl;
        // Attendu : true
        cout << endl;
    }

    // Test 2 : pas un anagramme
    {
        string s = "rat", t = "car";
        cout << "s=\"" << s << "\", t=\"" << t << "\"" << endl;
        cout << "Brute  : " << (isAnagramBrute(s, t) ? "true" : "false") << endl;
        cout << "Optimal: " << (isAnagramOptimal(s, t) ? "true" : "false") << endl;
        // Attendu : false
        cout << endl;
    }

    // Test 3 : longueurs differentes
    {
        string s = "hello", t = "hell";
        cout << "s=\"" << s << "\", t=\"" << t << "\"" << endl;
        cout << "Brute  : " << (isAnagramBrute(s, t) ? "true" : "false") << endl;
        cout << "Optimal: " << (isAnagramOptimal(s, t) ? "true" : "false") << endl;
        // Attendu : false
        cout << endl;
    }

    // Test 4 : string vide
    {
        string s = "", t = "";
        cout << "s=\"\", t=\"\"" << endl;
        cout << "Brute  : " << (isAnagramBrute(s, t) ? "true" : "false") << endl;
        cout << "Optimal: " << (isAnagramOptimal(s, t) ? "true" : "false") << endl;
        // Attendu : true
        cout << endl;
    }

    // Test 5 : meme lettre repetee differemment
    {
        string s = "aab", t = "abb";
        cout << "s=\"" << s << "\", t=\"" << t << "\"" << endl;
        cout << "Brute  : " << (isAnagramBrute(s, t) ? "true" : "false") << endl;
        cout << "Optimal: " << (isAnagramOptimal(s, t) ? "true" : "false") << endl;
        // Attendu : false
        cout << endl;
    }

    cout << "Complexite Brute  : O(n log n) temps | O(1) espace" << endl;
    cout << "Complexite Optimal: O(n)       temps | O(1) espace (alphabet fixe)" << endl;

    return 0;
}
