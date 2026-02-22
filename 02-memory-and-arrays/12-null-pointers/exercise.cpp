// ============================================================
// Chapitre 12 : Null Pointers - Exercices
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// ============================================================
// PARTIE 1 : Verifications null basiques
// ============================================================
// Cree des pointeurs, verifie s'ils sont null avant de les utiliser

void partie1() {
    cout << "=== PARTIE 1 : Verification null ===" << endl;

    // TODO: Declare int* p1 = nullptr
    // TODO: Declare int val = 42; int* p2 = &val;
    // TODO: Pour chaque pointeur, verifie s'il est null avant d'afficher *p
    //       Si null, affiche "Pointeur null, pas de donnee"
    //       Sinon, affiche la valeur

    cout << endl;
}

// ============================================================
// PARTIE 2 : Safe delete
// ============================================================
// Alloue dynamiquement, delete proprement, et montre le pattern safe

void partie2() {
    cout << "=== PARTIE 2 : Safe delete ===" << endl;

    // TODO: Alloue un int avec new : int* p = new int(99);
    // TODO: Affiche *p
    // TODO: delete p;
    // TODO: p = nullptr;   (empeche le dangling)
    // TODO: Essaie d'afficher *p avec verification null
    //        doit dire "Pointeur null"

    cout << endl;
}

// ============================================================
// PARTIE 3 : Fonction avec pointeur optionnel
// ============================================================
// Implemente une fonction qui prend un pointeur qui peut etre null
// et gere les deux cas (donnee presente vs absente)

// TODO: Implemente void afficherNote(const string& nom, const int* note)
//       - Si note est null  affiche "Nom : pas de note"
//       - Si note est valide  affiche "Nom : note/20"

void partie3() {
    cout << "=== PARTIE 3 : Pointeur optionnel ===" << endl;

    // TODO: Appelle afficherNote("Alice", &uneNote)  // avec note
    // TODO: Appelle afficherNote("Bob", nullptr)       // sans note

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
