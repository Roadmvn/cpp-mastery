// ============================================================
// Strings Avancees — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Trois problemes classiques de strings.
// Preparation directe aux patterns Two Pointers et Sliding Window.
//
// ============================================================

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// ============================================================
// PROBLEME 1 : Reverse Words in a String (LeetCode #151)
// ============================================================
//
// Enonce :
// Etant donne une string s, inverse l'ordre des mots.
// Un mot est une sequence de caracteres non-espaces.
// Les mots sont separes par au moins un espace.
// La string retournee ne doit avoir qu'un seul espace entre les mots,
// sans espaces en debut/fin.
//
// Exemple :
// "  the sky  is blue  " -> "blue is sky the"
// "hello world" -> "world hello"
//
// Complexite attendue : O(n) temps, O(n) espace

string reverseWords(string s) {
    // Technique : utiliser stringstream pour extraire les mots,
    // puis les recombiner en ordre inverse
    stringstream ss(s);
    vector<string> words;
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    string result;
    for (int i = (int)words.size() - 1; i >= 0; i--) {
        result += words[i];
        if (i > 0) result += " ";
    }
    return result;
}

// ============================================================
// PROBLEME 2 : Valid Palindrome (LeetCode #125)
// ============================================================
//
// Enonce :
// Etant donne une string s, determiner si c'est un palindrome
// en ne considerant que les caracteres alphanumeriques et en
// ignorant la casse.
//
// Exemple :
// "A man, a plan, a canal: Panama" -> true
// "race a car" -> false
// " " -> true
//
// Complexite attendue : O(n) temps, O(1) espace

bool isPalindrome(string s) {
    // Technique : Two Pointers — un depuis le debut, un depuis la fin
    // On saute les caracteres non-alphanumeriques
    int left = 0, right = (int)s.size() - 1;

    while (left < right) {
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;

        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// ============================================================
// PROBLEME 3 : String to Integer (atoi) (LeetCode #8)
// ============================================================
//
// Enonce :
// Implementer la fonction atoi qui convertit une string en entier.
// Regles :
// - Ignorer les espaces en debut
// - Optionnel : signe '+' ou '-'
// - Lire les chiffres jusqu'a un non-chiffre ou fin de string
// - Clamper le resultat dans [INT_MIN, INT_MAX]
// - Retourner 0 si aucun chiffre valide
//
// Exemple :
// "42" -> 42
// "   -42" -> -42
// "4193 with words" -> 4193
// "words and 987" -> 0
//
// Complexite attendue : O(n) temps, O(1) espace

int myAtoi(string s) {
    int i = 0;
    int n = (int)s.size();

    // 1. Ignorer les espaces
    while (i < n && s[i] == ' ') i++;

    // 2. Verifier le signe
    int sign = 1;
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    // 3. Lire les chiffres
    long result = 0;
    while (i < n && isdigit(s[i])) {
        result = result * 10 + (s[i] - '0');

        // 4. Clamper si overflow
        if (result * sign > INT32_MAX) return INT32_MAX;
        if (result * sign < INT32_MIN) return INT32_MIN;
        i++;
    }

    return (int)(result * sign);
}

// ============================================================
// Tests
// ============================================================

void testReverseWords() {
    cout << "=== Test reverseWords (LeetCode #151) ===" << endl;

    struct Test { string input; string expected; };
    Test tests[] = {
        {"the sky is blue", "blue is sky the"},
        {"  hello world  ", "world hello"},
        {"a good   example", "example good a"},
        {"single", "single"},
    };

    for (auto& t : tests) {
        string result = reverseWords(t.input);
        cout << "\"" << t.input << "\" -> \"" << result << "\" | "
             << (result == t.expected ? "PASS" : "FAIL") << endl;
    }
    cout << endl;
}

void testIsPalindrome() {
    cout << "=== Test isPalindrome (LeetCode #125) ===" << endl;

    struct Test { string input; bool expected; };
    Test tests[] = {
        {"A man, a plan, a canal: Panama", true},
        {"race a car", false},
        {" ", true},
        {"Was it a car or a cat I saw?", true},
    };

    for (auto& t : tests) {
        bool result = isPalindrome(t.input);
        cout << "\"" << t.input << "\" -> " << (result ? "true" : "false")
             << " | " << (result == t.expected ? "PASS" : "FAIL") << endl;
    }
    cout << endl;
}

void testMyAtoi() {
    cout << "=== Test myAtoi (LeetCode #8) ===" << endl;

    struct Test { string input; int expected; };
    Test tests[] = {
        {"42", 42},
        {"   -42", -42},
        {"4193 with words", 4193},
        {"words and 987", 0},
        {"-91283472332", INT32_MIN},
        {"91283472332", INT32_MAX},
    };

    for (auto& t : tests) {
        int result = myAtoi(t.input);
        cout << "\"" << t.input << "\" -> " << result
             << " | " << (result == t.expected ? "PASS" : "FAIL") << endl;
    }
    cout << endl;
}

int main() {
    testReverseWords();
    testIsPalindrome();
    testMyAtoi();

    cout << "Patterns utilises :" << endl;
    cout << "- Two Pointers : palindrome avec left/right" << endl;
    cout << "- stringstream : parsing et tokenisation" << endl;
    cout << "- Parsing caractere par caractere : atoi" << endl;
    cout << "Ces techniques sont la base de Sliding Window et Two Pointers." << endl;

    return 0;
}
