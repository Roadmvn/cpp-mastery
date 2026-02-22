// ============================================================
// Queue et Deque — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// PARTIE 1 : Queue — FIFO basique
// ============================================================
// Objectif : comprendre push, pop, front, back
//
// Instructions :
// 1. Creer une queue<string> pour simuler une file d'attente
// 2. Ajouter : "Alice", "Bob", "Charlie", "Diana"
// 3. Afficher front() et back() apres chaque ajout
// 4. Servir (pop) les 2 premiers clients et afficher qui est servi
// 5. Afficher le prochain client a servir (front)

void partie1() {
    cout << "=== PARTIE 1 : Queue FIFO ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : Deque — Double-ended
// ============================================================
// Objectif : maitriser push_front, push_back, pop_front, pop_back
//
// Instructions :
// 1. Creer un deque<int>
// 2. Ajouter a la fin : 10, 20, 30
// 3. Ajouter au debut : 5, 1
// 4. Afficher le deque avec un range-for (ou index)
//    Attendu : 1, 5, 10, 20, 30
// 5. Retirer du debut et de la fin, afficher le resultat

void partie2() {
    cout << "=== PARTIE 2 : Deque ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : BFS simple avec queue
// ============================================================
// Objectif : implementer un parcours BFS basique
//
// Instructions :
// Etant donne un graphe sous forme d'adjacency list :
//   0 -> {1, 2}
//   1 -> {3}
//   2 -> {3, 4}
//   3 -> {5}
//   4 -> {5}
//   5 -> {}
//
// 1. Implementer un BFS depuis le noeud 0
// 2. Afficher les noeuds dans l'ordre de visite BFS
// 3. Afficher le niveau (distance) de chaque noeud depuis 0

void partie3() {
    cout << "=== PARTIE 3 : BFS simple ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
