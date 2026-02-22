// ============================================================
// Chapitre 13 : Memoire Dynamique - Exercices
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
using namespace std;

// ============================================================
// PARTIE 1 : new et delete basiques
// ============================================================
// Alloue un int et un double sur le heap, utilise-les, libere-les

void partie1() {
    cout << "=== PARTIE 1 : new / delete basiques ===" << endl;

    // TODO: Alloue un int* avec new, initialise a 42
    // TODO: Alloue un double* avec new, initialise a 3.14
    // TODO: Affiche les valeurs et les adresses
    // TODO: delete les deux et mets a nullptr

    cout << endl;
}

// ============================================================
// PARTIE 2 : Tableau dynamique
// ============================================================
// Cree un tableau dynamique de taille variable, remplis-le,
// affiche-le, libere-le

void partie2() {
    cout << "=== PARTIE 2 : Tableau dynamique ===" << endl;

    // TODO: Demande la taille a l'utilisateur (ou utilise int n = 5;)
    int n = 5;

    // TODO: Alloue un tableau de n int avec new[]
    // TODO: Remplis le tableau (arr[i] = (i+1) * 10)
    // TODO: Affiche tous les elements
    // TODO: Calcule et affiche la somme
    // TODO: delete[] et nullptr

    cout << endl;
}

// ============================================================
// PARTIE 3 : Copie profonde d'un tableau
// ============================================================
// Alloue un tableau, copie-le dans un nouveau tableau (deep copy),
// modifie la copie pour prouver que les deux sont independants

void partie3() {
    cout << "=== PARTIE 3 : Copie profonde ===" << endl;

    // TODO: Cree int* original = new int[4]{10, 20, 30, 40}
    // TODO: Cree int* copie = new int[4]
    // TODO: Copie element par element (boucle)
    // TODO: Modifie copie[0] = 999
    // TODO: Affiche les deux tableaux (original doit etre intact)
    // TODO: delete[] les deux

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
