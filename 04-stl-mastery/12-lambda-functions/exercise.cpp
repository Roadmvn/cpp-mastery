// ============================================================
// Lambdas — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

// ============================================================
// PARTIE 1 : Syntaxe de base et captures
// ============================================================
// Objectif : comprendre les captures et la syntaxe lambda
//
// Instructions :
// 1. Creer une lambda 'double' qui retourne x * 2
//    Stocker dans auto, l'appeler avec 5 et 10
// 2. Creer une lambda qui capture un entier 'threshold' par valeur
//    et retourne vrai si x > threshold
//    Tester avec threshold = 5 et les valeurs 3, 7, 5
// 3. Creer une lambda qui capture un compteur 'count' par reference
//    et l'incremente chaque fois qu'elle est appelee
//    Appeler 5 fois et verifier que count == 5
// 4. Creer une lambda 'mutable' qui capture une valeur 'n' par valeur
//    et peut incrementer sa copie locale sans modifier l'original
//    Appeler 3 fois et verifier que n original reste inchange

void partie1() {
    cout << "=== PARTIE 1 : Syntaxe et captures ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : Lambdas avec algorithmes STL
// ============================================================
// Objectif : utiliser des lambdas comme predicats et comparateurs
//
// Instructions :
// 1. Etant donne v = {3, 7, 1, 8, 2, 9, 4, 6, 5, 10}
// 2. Trier en ordre decroissant avec sort + lambda
// 3. Trouver le premier element > 6 avec find_if + lambda
// 4. Compter les elements impairs avec count_if + lambda
// 5. Calculer la somme des carres avec accumulate + lambda
//    (somme de x*x pour chaque x)
// 6. Supprimer tous les elements entre 4 et 7 (inclus)
//    avec erase + remove_if + lambda

void partie2() {
    cout << "=== PARTIE 2 : Lambdas + algorithmes STL ===" << endl;

    vector<int> v = {3, 7, 1, 8, 2, 9, 4, 6, 5, 10};

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : std::function et lambdas avancees
// ============================================================
// Objectif : stocker et passer des lambdas
//
// Instructions :
// 1. Creer un vecteur<function<int(int)>> avec 3 operations :
//    - x + 10
//    - x * 3
//    - x * x
//    Appliquer chacune sur la valeur 4 et afficher
// 2. Implementer applyAll(int x, vector<function<int(int)>>& ops) -> vector<int>
//    qui retourne le resultat de chaque operation sur x
// 3. Creer une lambda recursive avec std::function
//    qui calcule la factorielle de n
//    Calculer 0! 1! 5! et 10!

vector<int> applyAll(int x, vector<function<int(int)>>& ops) {
    // TON CODE ICI
    return {};
}

void partie3() {
    cout << "=== PARTIE 3 : std::function et lambdas avancees ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
