// ============================================================
// Pairs et Tuples — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================
// PARTIE 1 : Creer et utiliser des pairs
// ============================================================
// Objectif : maitriser pair, make_pair, structured bindings
//
// Instructions :
// 1. Creer un pair<string, int> avec {"Alice", 95}
// 2. Afficher first et second
// 3. Utiliser structured bindings pour decomposer le pair
// 4. Creer un vector<pair<string,int>> avec 4 etudiants et leurs notes
// 5. Trier le vector par note decroissante
// 6. Afficher le classement

void partie1() {
    cout << "=== PARTIE 1 : Pairs ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : Tuples et structured bindings
// ============================================================
// Objectif : utiliser tuple pour grouper 3+ valeurs
//
// Instructions :
// 1. Creer un tuple<string, int, double> pour un etudiant
//    (nom, age, moyenne)
// 2. Afficher avec get<0>, get<1>, get<2>
// 3. Decomposer avec structured bindings et afficher
// 4. Creer un vector de tuples pour 3 etudiants
// 5. Trier par moyenne decroissante et afficher

void partie2() {
    cout << "=== PARTIE 2 : Tuples ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : Pairs dans les structures de donnees
// ============================================================
// Objectif : utiliser pair avec des conteneurs STL
//
// Instructions :
// 1. Creer une adjacency list pour ce graphe pondere :
//    0 --5--> 1
//    0 --3--> 2
//    1 --2--> 3
//    2 --7--> 3
//    Utiliser vector<vector<pair<int,int>>> adj(4)
// 2. Afficher toutes les aretes : "noeud -> voisin (poids X)"
// 3. Trouver l'arete de poids minimum
// 4. Calculer le poids total de toutes les aretes

void partie3() {
    cout << "=== PARTIE 3 : Pairs et graphes ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
