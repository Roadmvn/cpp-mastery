// ============================================================
// Chapitre 10 : Passage par Valeur vs Reference - Exercices
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ============================================================
// PARTIE 1 : Comprendre la difference
// ============================================================
// Implemente deux fonctions :
// - incrementByValue(int x) : incremente x de 10 (par valeur)
// - incrementByRef(int& x)  : incremente x de 10 (par reference)
// Appelle les deux dans partie1() et affiche les resultats

void partie1() {
    cout << "=== PARTIE 1 : Valeur vs Reference ===" << endl;

    // TODO: Declare un int n = 5
    // TODO: Appelle incrementByValue(n), affiche n (doit etre 5)
    // TODO: Appelle incrementByRef(n), affiche n (doit etre 15)

    cout << endl;
}

// ============================================================
// PARTIE 2 : Swap generique
// ============================================================
// Implemente une fonction swapInts(int& a, int& b) qui echange
// deux entiers. Teste-la dans partie2().

void partie2() {
    cout << "=== PARTIE 2 : Swap ===" << endl;

    // TODO: Declare int x = 42, y = 99
    // TODO: Affiche avant swap
    // TODO: Appelle swapInts(x, y)
    // TODO: Affiche apres swap (x=99, y=42)

    cout << endl;
}

// ============================================================
// PARTIE 3 : const& pour la lecture
// ============================================================
// Cree une struct Etudiant { string nom; int notes[5]; double moyenne; }
// Implemente :
// - calculerMoyenne(Etudiant& e) : calcule et stocke la moyenne dans e
// - afficherEtudiant(const Etudiant& e) : affiche les infos (en lecture seule)

void partie3() {
    cout << "=== PARTIE 3 : const reference ===" << endl;

    // TODO: Cree un Etudiant avec un nom et 5 notes
    // TODO: Appelle calculerMoyenne() pour calculer sa moyenne
    // TODO: Appelle afficherEtudiant() pour afficher ses infos

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
