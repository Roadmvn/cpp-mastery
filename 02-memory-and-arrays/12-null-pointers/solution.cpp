// ============================================================
// Chapitre 12 : Null Pointers - Solutions
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// --- PARTIE 1 ---

void partie1() {
    cout << "=== PARTIE 1 : Verification null ===" << endl;

    int* p1 = nullptr;
    int val = 42;
    int* p2 = &val;

    cout << "p1 : ";
    if (p1 != nullptr) {
        cout << *p1 << endl;
    } else {
        cout << "Pointeur null, pas de donnee" << endl;
    }

    cout << "p2 : ";
    if (p2) {  // version courte
        cout << *p2 << endl;
    } else {
        cout << "Pointeur null, pas de donnee" << endl;
    }

    cout << endl;
}

// --- PARTIE 2 ---

void partie2() {
    cout << "=== PARTIE 2 : Safe delete ===" << endl;

    int* p = new int(99);
    cout << "Avant delete : *p = " << *p << endl;
    cout << "Adresse : " << p << endl;

    delete p;
    p = nullptr;  // CRUCIAL : empeche le dangling pointer

    cout << "Apres delete + nullptr :" << endl;
    if (p) {
        cout << "*p = " << *p << endl;
    } else {
        cout << "Pointeur null — acces interdit (et c'est bien !)" << endl;
    }

    cout << endl;
}

// --- PARTIE 3 ---

void afficherNote(const string& nom, const int* note) {
    if (note) {
        cout << nom << " : " << *note << "/20" << endl;
    } else {
        cout << nom << " : pas de note" << endl;
    }
}

void partie3() {
    cout << "=== PARTIE 3 : Pointeur optionnel ===" << endl;

    int noteAlice = 17;
    int noteCharlie = 12;

    afficherNote("Alice", &noteAlice);
    afficherNote("Bob", nullptr);
    afficherNote("Charlie", &noteCharlie);
    afficherNote("Diana", nullptr);

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
