// ============================================================
// Unordered Map — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// PARTIE 1 : Operations de base
// ============================================================
// Objectif : maitriser insert, [], find, count, erase
//
// Instructions :
// 1. Creer une unordered_map<string, int> pour des scores
// 2. Inserer : "Alice"->95, "Bob"->87, "Charlie"->92
// 3. Acceder au score de "Bob" avec []
// 4. Verifier si "Diana" existe avec count() et find()
// 5. Ajouter "Diana"->88, modifier "Bob" a 90
// 6. Supprimer "Charlie" avec erase
// 7. Iterer et afficher tous les elements

void partie1() {
    cout << "=== PARTIE 1 : Operations de base ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : Frequency counter
// ============================================================
// Objectif : compter les occurrences de chaque element
//
// Instructions :
// 1. Etant donne le string "abracadabra"
// 2. Compter la frequence de chaque caractere avec une unordered_map
// 3. Afficher chaque caractere et sa frequence
// 4. Trouver le caractere le plus frequent
// 5. Etant donne {"apple","banana","apple","cherry","banana","apple"}
//    Compter la frequence de chaque mot

void partie2() {
    cout << "=== PARTIE 2 : Frequency counter ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : Grouper par propriete
// ============================================================
// Objectif : utiliser la map pour grouper des donnees
//
// Instructions :
// 1. Etant donne un vector<pair<string, string>> representant des
//    etudiants et leur filiere :
//    {{"Alice","Info"}, {"Bob","Math"}, {"Charlie","Info"},
//     {"Diana","Math"}, {"Eve","Info"}}
// 2. Grouper les etudiants par filiere dans une
//    unordered_map<string, vector<string>>
// 3. Afficher chaque filiere avec ses etudiants

void partie3() {
    cout << "=== PARTIE 3 : Grouper ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
