// ============================================================
// Stack — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// PARTIE 1 : Operations de base
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Operations de base ===" << endl;

    // 1. Creer un stack
    stack<int> s;

    // 2-3. Empiler et observer
    int values[] = {10, 20, 30, 40, 50};
    for (int val : values) {
        s.push(val);
        cout << "Push " << val << " | top: " << s.top()
             << " | size: " << s.size() << endl;
    }

    // 4. Depiler tout (ordre LIFO)
    cout << "Depilage (LIFO) : ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    // 5. Verifier vide
    cout << "Stack vide ? " << (s.empty() ? "oui" : "non") << endl;

    cout << endl;
}

// ============================================================
// PARTIE 2 : Inverser une string avec un stack
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : Inverser une string ===" << endl;

    string original = "Hello World";
    stack<char> s;

    // Empiler chaque caractere
    for (char c : original) {
        s.push(c);
    }

    // Depiler pour construire l'inverse
    string reversed;
    while (!s.empty()) {
        reversed += s.top();
        s.pop();
    }

    cout << "Original : " << original << endl;
    cout << "Inversee : " << reversed << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : Simuler l'historique d'un navigateur
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : Historique navigateur ===" << endl;

    stack<string> history;

    // Navigation
    string pages[] = {"google.com", "github.com", "stackoverflow.com", "leetcode.com"};
    for (const string& page : pages) {
        history.push(page);
        cout << "Visite : " << page << endl;
    }

    cout << "Page courante : " << history.top() << endl;

    // Back 2 fois
    for (int i = 0; i < 2; i++) {
        cout << "Back <- quitte " << history.top() << endl;
        history.pop();
    }

    cout << "Page courante apres 2 back : " << history.top() << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
