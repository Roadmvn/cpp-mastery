// ============================================================
// Priority Queue et Heap — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// PARTIE 1 : Max-Heap basique
// ============================================================
// Objectif : comprendre push, pop, top sur un max-heap
//
// Instructions :
// 1. Creer un priority_queue<int> (max-heap par defaut)
// 2. Inserer : 15, 30, 10, 45, 20, 5
// 3. Afficher le top() apres chaque insertion
// 4. Extraire tous les elements un par un (top + pop)
//    Observer : ils sortent en ordre DECROISSANT

void partie1() {
    cout << "=== PARTIE 1 : Max-Heap ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : Min-Heap
// ============================================================
// Objectif : creer et utiliser un min-heap
//
// Instructions :
// 1. Creer un min-heap : priority_queue<int, vector<int>, greater<int>>
// 2. Inserer les memes valeurs : 15, 30, 10, 45, 20, 5
// 3. Extraire tous les elements
//    Observer : ils sortent en ordre CROISSANT
// 4. Comparer avec le max-heap de la partie 1

void partie2() {
    cout << "=== PARTIE 2 : Min-Heap ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : Heap avec pairs et custom comparator
// ============================================================
// Objectif : trier des donnees complexes avec un heap
//
// Instructions :
// 1. Creer un vector de pair<string, int> representant des taches :
//    {"Bug fix", 3}, {"Feature", 1}, {"Refactor", 2}, {"Deploy", 5}, {"Test", 4}
//    (string = nom, int = priorite, 5 = plus urgent)
// 2. Inserer dans un max-heap de pairs
//    (pair trie par first par defaut — on veut trier par second)
// 3. Utiliser un comparateur custom pour trier par priorite decroissante
// 4. Extraire et afficher dans l'ordre de priorite

void partie3() {
    cout << "=== PARTIE 3 : Custom comparator ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
