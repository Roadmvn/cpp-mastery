// ============================================================
// Algorithmes STL — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

// ============================================================
// PARTIE 1 : Tri et recherche
// ============================================================
// Objectif : maitriser sort, binary_search, lower/upper_bound
//
// Instructions :
// 1. Creer un vector<int> = {5, 2, 8, 1, 9, 3, 7, 4, 6, 10}
// 2. Trier avec sort, afficher le resultat
// 3. Verifier si 7 et 11 existent avec binary_search
// 4. Trouver la position d'insertion de 5.5 (entre 5 et 6) avec lower_bound
//    (chercher la position du premier element > 5)
// 5. Afficher tous les elements dans [4, 7] avec lower/upper_bound
// 6. Utiliser partial_sort pour obtenir les 3 plus petits elements

void partie1() {
    cout << "=== PARTIE 1 : Tri et recherche ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : Comptage et conditions
// ============================================================
// Objectif : count_if, all_of, any_of, none_of
//
// Instructions :
// 1. Etant donne {3, 7, 1, 8, 2, 9, 4, 6, 5, 10}
// 2. Compter les elements pairs avec count_if
// 3. Compter les elements > 5 avec count_if
// 4. Verifier avec all_of si tous les elements sont > 0
// 5. Verifier avec any_of si au moins un element est > 8
// 6. Verifier avec none_of si aucun element n'est negatif
// 7. Trouver le premier element pair avec find_if

void partie2() {
    cout << "=== PARTIE 2 : Comptage et conditions ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : Transform, accumulate et erase-remove
// ============================================================
// Objectif : transformer, reduire et filtrer
//
// Instructions :
// 1. Etant donne {1, 2, 3, 4, 5}
//    Doubler chaque element avec transform (in-place)
// 2. Calculer la somme avec accumulate
// 3. Calculer le produit avec accumulate et un operateur custom
// 4. Etant donne {"hello", "world", "foo", "bar", "baz"}
//    Supprimer les mots de longueur < 4 avec erase + remove_if
// 5. Afficher le resultat final

void partie3() {
    cout << "=== PARTIE 3 : transform, accumulate, erase-remove ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
