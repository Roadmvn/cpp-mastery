// ============================================================
// Chapitre 15 : Function Templates - Exercices
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
using namespace std;

// ============================================================
// PARTIE 1 : Templates basiques
// ============================================================
// Implemente des fonctions templates simples

// TODO: template<typename T> T maxVal(T a, T b)
//       Retourne le plus grand des deux

// TODO: template<typename T> T minVal(T a, T b)
//       Retourne le plus petit des deux

// TODO: template<typename T> void swapVal(T& a, T& b)
//       Echange les deux valeurs

void partie1() {
    cout << "=== PARTIE 1 : Templates basiques ===" << endl;

    // TODO: Teste maxVal avec int, double, char
    // TODO: Teste minVal avec int, double
    // TODO: Teste swapVal avec int, string

    cout << endl;
}

// ============================================================
// PARTIE 2 : Template sur array
// ============================================================
// Cree des fonctions templates qui travaillent sur des arrays

// TODO: template<typename T> T somme(const T arr[], int size)
// TODO: template<typename T> void afficher(const T arr[], int size)

void partie2() {
    cout << "=== PARTIE 2 : Templates sur array ===" << endl;

    // TODO: Teste avec int arr[] et double arr[]

    cout << endl;
}

// ============================================================
// PARTIE 3 : Template multi-types
// ============================================================
// Cree une fonction template qui accepte deux types differents

// TODO: template<typename T, typename U>
//       void afficherPaire(T premier, U second)
//       Affiche "premier | second"

void partie3() {
    cout << "=== PARTIE 3 : Multi-types ===" << endl;

    // TODO: Teste afficherPaire(42, "hello")
    // TODO: Teste afficherPaire(3.14, true)
    // TODO: Teste afficherPaire('A', 100)

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
