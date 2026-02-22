// ============================================
// LeetCode #20 - Valid Parentheses (Easy)
// https://leetcode.com/problems/valid-parentheses/
// ============================================
// Enonce : Verifier si une string de parentheses est valide.
// Chaque ouvrante doit etre fermee par le meme type dans le bon ordre.
//
// Exemple : s = "()[]{}" -> Output: true
// Exemple : s = "(]"     -> Output: false
//
// Compile : g++ -std=c++17 01_valid_parentheses.cpp -o 01

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n²) temps | O(n) espace
// Remplacer iterativement les paires "()", "[]", "{}"
// jusqu'a ce que la string soit vide (ou ne change plus)
// -----------------------------------------------
bool isValidBrute(string s) {
    string prev;
    while (s != prev) {
        prev = s;
        string next;
        for (int i = 0; i < (int)s.size(); i++) {
            if (i + 1 < (int)s.size() &&
                ((s[i] == '(' && s[i+1] == ')') ||
                 (s[i] == '[' && s[i+1] == ']') ||
                 (s[i] == '{' && s[i+1] == '}'))) {
                i++; // skip la paire
            } else {
                next += s[i];
            }
        }
        s = next;
    }
    return s.empty();
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(n) espace
// Stack : push les ouvrantes, pop et compare pour les fermantes
//
// Schema pour "({[]})":
//   '(' -> push   stack: [(]
//   '{' -> push   stack: [(, {]
//   '[' -> push   stack: [(, {, []
//   ']' -> pop [  stack: [(, {]    match!
//   '}' -> pop {  stack: [(]       match!
//   ')' -> pop (  stack: []        match!
//   Stack vide -> VALIDE
// -----------------------------------------------
bool isValidOptimal(string s) {
    stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;

            char top = st.top();
            if ((c == ')' && top == '(') ||
                (c == ']' && top == '[') ||
                (c == '}' && top == '{')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    return st.empty();
}

int main() {
    cout << "=== #20 Valid Parentheses ===" << endl;

    cout << "\"()\"     -> Brute: " << isValidBrute("()")
         << " Optimal: " << isValidOptimal("()") << " (attendu: 1)" << endl;

    cout << "\"()[]{}\" -> Brute: " << isValidBrute("()[]{}")
         << " Optimal: " << isValidOptimal("()[]{}") << " (attendu: 1)" << endl;

    cout << "\"(]\"     -> Brute: " << isValidBrute("(]")
         << " Optimal: " << isValidOptimal("(]") << " (attendu: 0)" << endl;

    cout << "\"({[]})\" -> Brute: " << isValidBrute("({[]})")
         << " Optimal: " << isValidOptimal("({[]})") << " (attendu: 1)" << endl;

    cout << "\"]\"      -> Optimal: " << isValidOptimal("]") << " (attendu: 0)" << endl;

    cout << "\"\"       -> Optimal: " << isValidOptimal("") << " (attendu: 1)" << endl;

    return 0;
}
