// ============================================================
// Chapitre 14 : Recursion - Exercices
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
using namespace std;

// ============================================================
// PARTIE 1 : Factorielle et somme recursive
// ============================================================
// Implemente factorielle(n) et somme(n) recursivement

// TODO: int factorielle(int n)
// TODO: int somme(int n) — retourne 1 + 2 + ... + n

void partie1() {
    cout << "=== PARTIE 1 : Factorielle et somme ===" << endl;

    // TODO: Teste factorielle(0), factorielle(5), factorielle(10)
    // TODO: Teste somme(0), somme(5), somme(100)

    cout << endl;
}

// ============================================================
// PARTIE 2 : Recursion sur array
// ============================================================
// Implemente des fonctions recursives qui operent sur un array

// TODO: int sommeArray(const int arr[], int size)
//       Cas de base : size == 0  return 0
//       Cas recursif : arr[size-1] + sommeArray(arr, size-1)

// TODO: int maxArray(const int arr[], int size)
//       Trouve le max d'un array recursivement

void partie2() {
    cout << "=== PARTIE 2 : Recursion sur array ===" << endl;

    // TODO: Teste avec int arr[] = {3, 7, 2, 9, 4, 1}
    // TODO: Affiche sommeArray et maxArray

    cout << endl;
}

// ============================================================
// PARTIE 3 : Affichage recursif
// ============================================================
// Affiche un compteur de n a 1 puis de 1 a n recursivement

// TODO: void countdown(int n) — affiche n, n-1, ..., 1
// TODO: void countup(int n) — affiche 1, 2, ..., n
//       (Indice : affiche APRES l'appel recursif)

void partie3() {
    cout << "=== PARTIE 3 : Affichage recursif ===" << endl;

    // TODO: countdown(5)   5 4 3 2 1
    // TODO: countup(5)     1 2 3 4 5

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
