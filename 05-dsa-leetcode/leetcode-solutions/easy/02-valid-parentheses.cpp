// https://leetcode.com/problems/valid-parentheses/
// #20 - Valid Parentheses
//
// Verifier si une chaine de parentheses '(', ')', '{', '}', '[', ']' est valide.
// Valide = chaque ouvrant est ferme dans le bon ordre.
//
// Approche : pile - empiler les ouvrants, verifier la correspondance sur les fermants.
// Complexite temps : O(n) | Complexite espace : O(n)

#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;

        // Map : fermant -> ouvrant correspondant
        unordered_map<char, char> matching = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        for (char c : s) {
            if (matching.count(c)) {
                // Caractere fermant : verifier le sommet de la pile
                if (stk.empty() || stk.top() != matching[c]) {
                    return false;
                }
                stk.pop();
            } else {
                // Caractere ouvrant : empiler
                stk.push(c);
            }
        }

        // La pile doit etre vide si tout est bien ferme
        return stk.empty();
    }
};

int main() {
    Solution sol;

    cout << boolalpha;
    cout << sol.isValid("()")      << endl; // true
    cout << sol.isValid("()[]{}")  << endl; // true
    cout << sol.isValid("(]")      << endl; // false
    cout << sol.isValid("([)]")    << endl; // false
    cout << sol.isValid("{[]}")    << endl; // true
    cout << sol.isValid("")        << endl; // true (vide = valide)
    cout << sol.isValid("(")       << endl; // false (non ferme)

    return 0;
}
