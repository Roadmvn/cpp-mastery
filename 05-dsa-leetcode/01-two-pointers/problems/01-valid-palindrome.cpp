// ============================================================
// Probleme 01 : Valid Palindrome (Easy)
// LeetCode #125 : https://leetcode.com/problems/valid-palindrome/
// Compile : g++ -std=c++17 -o 01 01-valid-palindrome.cpp && ./01
// ============================================================
//
// Enonce :
// Une phrase est un palindrome si, apres avoir converti toutes les
// lettres en minuscules et retire tous les caracteres non-alphanumeriques,
// elle se lit de la meme facon de gauche a droite et de droite a gauche.
//
// Exemple 1 : "A man, a plan, a canal: Panama" → true
// Exemple 2 : "race a car" → false
// Exemple 3 : " " → true (vide apres nettoyage = palindrome)
//
// Contraintes :
// - 1 <= s.length <= 2 * 10^5
// - s contient uniquement des caracteres ASCII
// ============================================================

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ============================================================
// Solution 1 : Brute force — Construire une string nettoyee
// Complexite : O(n) temps, O(n) espace
// ============================================================
// Approche :
// 1. Creer une nouvelle string avec seulement les caracteres alphanumeriques en minuscule
// 2. Comparer avec sa version inversee

bool isPalindrome_bruteforce(string s) {
    string cleaned = "";

    // Etape 1 : nettoyer
    for (char c : s) {
        if (isalnum(c)) {
            cleaned += tolower(c);
        }
    }

    // Etape 2 : comparer avec l'inverse
    string reversed = string(cleaned.rbegin(), cleaned.rend());

    return cleaned == reversed;
    // O(n) temps pour nettoyer + O(n) pour inverser + O(n) pour comparer
    // O(n) espace pour les deux strings
}

// ============================================================
// Solution 2 : Optimale — Two Pointers opposes
// Complexite : O(n) temps, O(1) espace
// ============================================================
// Approche :
// Deux pointeurs partent des extremites. On skip les caracteres
// non-alphanumeriques. On compare les caracteres en minuscule.
// Si une paire ne match pas, c'est pas un palindrome.

bool isPalindrome_optimal(string s) {
    int left = 0;
    int right = (int)s.size() - 1;

    while (left < right) {
        // Avancer left si le caractere n'est pas alphanum
        while (left < right && !isalnum(s[left])) {
            left++;
        }

        // Reculer right si le caractere n'est pas alphanum
        while (left < right && !isalnum(s[right])) {
            right--;
        }

        // Comparer en minuscule
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }

        left++;
        right--;
    }

    return true;
    // O(n) temps : chaque caractere est visite au plus une fois
    // O(1) espace : aucune allocation supplementaire
}

// ============================================================
// Tests
// ============================================================

void test(const string& input, bool expected) {
    bool result_bf = isPalindrome_bruteforce(input);
    bool result_opt = isPalindrome_optimal(input);

    cout << "Input: \"" << input << "\"" << endl;
    cout << "  Brute force : " << (result_bf ? "true" : "false")
         << " | " << (result_bf == expected ? "PASS" : "FAIL") << endl;
    cout << "  Optimal     : " << (result_opt ? "true" : "false")
         << " | " << (result_opt == expected ? "PASS" : "FAIL") << endl;
}

int main() {
    cout << "=== Valid Palindrome (LeetCode #125) ===" << endl << endl;

    test("A man, a plan, a canal: Panama", true);
    test("race a car", false);
    test(" ", true);
    test("0P", false);
    test("aa", true);
    test("a", true);

    cout << endl;
    cout << "Pattern : Two Pointers opposes" << endl;
    cout << "La cle : skip les non-alphanum, comparer en lowercase" << endl;

    return 0;
}
