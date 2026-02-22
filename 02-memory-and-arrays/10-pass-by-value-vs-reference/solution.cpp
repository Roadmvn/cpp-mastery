// ============================================================
// Chapitre 10 : Passage par Valeur vs Reference - Solutions
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// --- PARTIE 1 ---

void incrementByValue(int x) {
    x += 10;  // modifie la copie locale
}

void incrementByRef(int& x) {
    x += 10;  // modifie l'original
}

void partie1() {
    cout << "=== PARTIE 1 : Valeur vs Reference ===" << endl;

    int n = 5;

    cout << "Avant incrementByValue : n = " << n << endl;
    incrementByValue(n);
    cout << "Apres incrementByValue : n = " << n << " (inchange)" << endl;

    cout << "Avant incrementByRef : n = " << n << endl;
    incrementByRef(n);
    cout << "Apres incrementByRef : n = " << n << " (modifie!)" << endl;

    cout << endl;
}

// --- PARTIE 2 ---

void swapInts(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void partie2() {
    cout << "=== PARTIE 2 : Swap ===" << endl;

    int x = 42, y = 99;

    cout << "Avant swap : x = " << x << ", y = " << y << endl;
    swapInts(x, y);
    cout << "Apres swap : x = " << x << ", y = " << y << endl;

    cout << endl;
}

// --- PARTIE 3 ---

struct Etudiant {
    string nom;
    int notes[5];
    double moyenne;
};

void calculerMoyenne(Etudiant& e) {
    double total = 0;
    for (int i = 0; i < 5; i++) {
        total += e.notes[i];
    }
    e.moyenne = total / 5.0;
}

void afficherEtudiant(const Etudiant& e) {
    cout << "Nom : " << e.nom << endl;
    cout << "Notes : ";
    for (int i = 0; i < 5; i++) {
        cout << e.notes[i];
        if (i < 4) cout << ", ";
    }
    cout << endl;
    cout << "Moyenne : " << e.moyenne << endl;
    // e.moyenne = 0;  // Impossible : const& empeche la modification
}

void partie3() {
    cout << "=== PARTIE 3 : const reference ===" << endl;

    Etudiant alice = {"Alice", {15, 18, 12, 16, 14}, 0.0};

    calculerMoyenne(alice);
    afficherEtudiant(alice);

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
