// ============================================================
// Chapitre 09 : Adresses Memoire - Exercices
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
using namespace std;

// ============================================================
// PARTIE 1 : Afficher les adresses de variables
// ============================================================
// Declare 4 variables de types differents (int, double, char, bool)
// Affiche la valeur ET l'adresse de chacune
// Note : pour char et bool, caste l'adresse avec (void*)

void partie1() {
    cout << "=== PARTIE 1 : Adresses de variables ===" << endl;

    // TODO: Declare un int, double, char, bool avec des valeurs
    // TODO: Affiche "Valeur de X : ..." et "Adresse de X : ..." pour chacun
    // TODO: Pour char et bool, utilise (void*)&variable pour afficher l'adresse

    cout << endl;
}

// ============================================================
// PARTIE 2 : Adresses d'un array
// ============================================================
// Cree un array de 6 int, affiche l'adresse de chaque element
// Calcule et affiche l'ecart en octets entre chaque element

void partie2() {
    cout << "=== PARTIE 2 : Adresses d'un array ===" << endl;

    // TODO: Declare un array de 6 int avec des valeurs
    // TODO: Boucle pour afficher valeur + adresse de chaque element
    // TODO: Calcule l'ecart entre deux adresses consecutives
    //       Utilise : (char*)&arr[i+1] - (char*)&arr[i]
    //       Ca donne l'ecart en octets

    cout << endl;
}

// ============================================================
// PARTIE 3 : Comparaison stack vs differents types
// ============================================================
// Declare des variables de types differents et observe
// comment elles sont disposees sur la stack

void partie3() {
    cout << "=== PARTIE 3 : Disposition sur la stack ===" << endl;

    // TODO: Declare dans cet ordre : int a, double b, char c, int d, bool e
    // TODO: Affiche l'adresse de chacun
    // TODO: Observe : sont-elles dans l'ordre ? Les ecarts correspondent-ils
    //       aux sizeof de chaque type ? (padding/alignement possible)

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
