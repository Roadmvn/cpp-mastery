// ============================================================
// Map et Set ordonnes — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// PARTIE 1 : Ordre garanti et lower/upper_bound
// ============================================================
// Objectif : constater l'ordre automatique, utiliser lower_bound
//
// Instructions :
// 1. Creer un set<int> avec {5, 1, 8, 3, 9, 2, 7, 4, 6}
// 2. Afficher tous les elements (observer l'ordre trie)
// 3. Utiliser lower_bound pour trouver le premier element >= 4
// 4. Utiliser upper_bound pour trouver le premier element > 6
// 5. Afficher les elements dans l'intervalle [3, 7] inclus
// 6. Trouver et afficher le minimum et le maximum

void partie1() {
    cout << "=== PARTIE 1 : Ordre garanti et bounds ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : map ordonnee
// ============================================================
// Objectif : utiliser map pour un dictionnaire ordonne
//
// Instructions :
// 1. Creer une map<string, int> avec des notes par matiere :
//    {"Physique",14}, {"Maths",17}, {"Info",19}, {"Chimie",12}, {"Bio",15}
// 2. Afficher toutes les matieres dans l'ordre alphabetique avec leur note
// 3. Trouver la premiere matiere apres "Info" dans l'ordre alphabetique
//    avec upper_bound
// 4. Calculer la moyenne de toutes les notes en iterant sur la map
// 5. Afficher les matieres dont la note >= 15

void partie2() {
    cout << "=== PARTIE 2 : map ordonnee ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : multiset — doublons + suppression precise
// ============================================================
// Objectif : gerer les doublons avec multiset
//
// Instructions :
// 1. Creer un multiset<int> avec {3, 1, 4, 1, 5, 9, 2, 6, 5, 3}
// 2. Afficher tous les elements tries (avec doublons)
// 3. Afficher le nombre d'occurrences de 1 et 5
// 4. Supprimer UNE seule occurrence de 1 (pas toutes !)
//    Indice : utiliser find() puis erase() sur l'iterateur
// 5. Supprimer TOUTES les occurrences de 5 avec erase(valeur)
// 6. Afficher le resultat final

void partie3() {
    cout << "=== PARTIE 3 : multiset ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
