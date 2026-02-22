// ============================================================
// Vectors — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// PARTIE 1 : Creation, ajout, taille et capacite
// ============================================================
// Objectif : comprendre push_back, size() et capacity()
//
// Instructions :
// 1. Creer un vector<int> vide
// 2. Ajouter les valeurs 10, 20, 30, 40, 50 avec push_back
// 3. Afficher la taille et la capacite apres chaque ajout
// 4. Supprimer le dernier element avec pop_back
// 5. Afficher le premier (front) et dernier (back) element

void partie1() {
    cout << "=== PARTIE 1 : Creation et manipulation ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : Trois facons d'iterer
// ============================================================
// Objectif : maitriser les 3 methodes d'iteration
//
// Instructions :
// 1. Creer un vector<string> avec {"C++", "Python", "Rust", "Go"}
// 2. Afficher avec une boucle par index
// 3. Afficher avec un range-based for
// 4. Afficher avec des iterateurs
// 5. Utiliser un range-based for par reference pour mettre
//    chaque string en majuscules (juste ajouter " (cool)" a la fin)

void partie2() {
    cout << "=== PARTIE 2 : Iteration ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : Vector 2D (matrice)
// ============================================================
// Objectif : manipuler un vector de vectors
//
// Instructions :
// 1. Creer une matrice 3x3 initialisee a 0
// 2. Remplir la diagonale avec des 1 (matrice identite)
// 3. Afficher la matrice de facon formatee
// 4. Ajouter une 4eme ligne {7, 8, 9}
// 5. Afficher la nouvelle matrice

void partie3() {
    cout << "=== PARTIE 3 : Vector 2D ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 4 : reserve() et observation de capacity
// ============================================================
// Objectif : comprendre l'impact de reserve() sur les reallocations
//
// Instructions :
// 1. Creer un vector<int> SANS reserve
//    - Ajouter 100 elements (0 a 99) avec push_back
//    - Compter combien de fois la capacity change
// 2. Creer un vector<int> AVEC reserve(100)
//    - Ajouter 100 elements (0 a 99) avec push_back
//    - Compter combien de fois la capacity change
// 3. Afficher la comparaison

void partie4() {
    cout << "=== PARTIE 4 : reserve() ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    partie4();

    return 0;
}
