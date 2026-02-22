// ============================================
// LeetCode #150 - Evaluate Reverse Polish Notation (Medium)
// https://leetcode.com/problems/evaluate-reverse-polish-notation/
// ============================================
// Enonce : Evaluer une expression en notation polonaise inverse (postfixe).
// Operateurs valides : +, -, *, /. Division entiere tronquee vers zero.
//
// Exemple : tokens = ["2","1","+","3","*"] -> Output: 9
//           ((2 + 1) * 3) = 9
//
// Compile : g++ -std=c++17 03_eval_reverse_polish_notation.cpp -o 03

#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n²) temps | O(n) espace
// Parcourir, trouver un operateur avec 2 nombres avant,
// calculer et remplacer. Repeter.
// -----------------------------------------------
int evalRPNBrute(vector<string> tokens) {
    while (tokens.size() > 1) {
        for (int i = 0; i < (int)tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" ||
                tokens[i] == "*" || tokens[i] == "/") {
                int a = stoi(tokens[i - 2]);
                int b = stoi(tokens[i - 1]);
                int result;
                if (tokens[i] == "+") result = a + b;
                else if (tokens[i] == "-") result = a - b;
                else if (tokens[i] == "*") result = a * b;
                else result = a / b;

                tokens[i - 2] = to_string(result);
                tokens.erase(tokens.begin() + i - 1, tokens.begin() + i + 1);
                break;
            }
        }
    }
    return stoi(tokens[0]);
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(n) espace
// Stack : push les nombres, pop 2 pour chaque operateur
//
// Schema pour ["2", "1", "+", "3", "*"] :
//
//   "2" -> push 2       stack: [2]
//   "1" -> push 1       stack: [2, 1]
//   "+" -> pop 1, pop 2 -> 2+1=3 -> push 3   stack: [3]
//   "3" -> push 3       stack: [3, 3]
//   "*" -> pop 3, pop 3 -> 3*3=9 -> push 9   stack: [9]
//
//   Resultat : 9
// -----------------------------------------------
int evalRPNOptimal(vector<string>& tokens) {
    stack<int> st;

    for (string& tok : tokens) {
        if (tok == "+" || tok == "-" || tok == "*" || tok == "/") {
            int b = st.top(); st.pop();  // deuxieme operande
            int a = st.top(); st.pop();  // premier operande

            if (tok == "+")      st.push(a + b);
            else if (tok == "-") st.push(a - b);
            else if (tok == "*") st.push(a * b);
            else                 st.push(a / b); // troncature vers zero
        } else {
            st.push(stoi(tok));
        }
    }
    return st.top();
}

int main() {
    cout << "=== #150 Evaluate Reverse Polish Notation ===" << endl;

    vector<string> test1 = {"2", "1", "+", "3", "*"};
    cout << "Input: [\"2\",\"1\",\"+\",\"3\",\"*\"]" << endl;
    cout << "Brute force: " << evalRPNBrute(test1) << " (attendu: 9)" << endl;
    cout << "Optimal:     " << evalRPNOptimal(test1) << " (attendu: 9)" << endl;
    cout << endl;

    vector<string> test2 = {"4", "13", "5", "/", "+"};
    cout << "Input: [\"4\",\"13\",\"5\",\"/\",\"+\"]" << endl;
    cout << "Brute force: " << evalRPNBrute(test2) << " (attendu: 6)" << endl;
    cout << "Optimal:     " << evalRPNOptimal(test2) << " (attendu: 6)" << endl;
    cout << endl;

    vector<string> test3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    cout << "Input: [\"10\",\"6\",\"9\",\"3\",\"+\",\"-11\",\"*\",\"/\",\"*\",\"17\",\"+\",\"5\",\"+\"]" << endl;
    cout << "Optimal: " << evalRPNOptimal(test3) << " (attendu: 22)" << endl;

    return 0;
}
