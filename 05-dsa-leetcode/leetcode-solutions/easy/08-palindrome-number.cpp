// https://leetcode.com/problems/palindrome-number/
// #9 - Palindrome Number
//
// Determiner si un entier est un palindrome (lit pareil dans les deux sens).
// Contrainte : ne pas convertir en string.
//
// Approche : inverser seulement la moitie du nombre.
// Cas negatifs et multiples de 10 (sauf 0) : non palindrome.
// Comparer la moitie inversee avec la premiere moitie.
// Complexite temps : O(log n) | Complexite espace : O(1)

#include <iostream>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        // Nombres negatifs ou multiples de 10 non nuls : jamais palindromes
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;

        int reversed = 0;

        // Inverser la moitie droite jusqu'a ce que reversed >= x
        while (x > reversed) {
            reversed = reversed * 10 + x % 10;
            x /= 10;
        }

        // Nombre pair de chiffres : x == reversed
        // Nombre impair de chiffres : x == reversed / 10 (ignorer le chiffre du milieu)
        return x == reversed || x == reversed / 10;
    }
};

int main() {
    Solution sol;

    cout << boolalpha;
    cout << sol.isPalindrome(121)    << endl; // true
    cout << sol.isPalindrome(-121)   << endl; // false
    cout << sol.isPalindrome(10)     << endl; // false
    cout << sol.isPalindrome(0)      << endl; // true
    cout << sol.isPalindrome(1001)   << endl; // true
    cout << sol.isPalindrome(12321)  << endl; // true
    cout << sol.isPalindrome(123321) << endl; // true
    cout << sol.isPalindrome(1231)   << endl; // false

    return 0;
}
