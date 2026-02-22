// ============================================================
// Stack — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// PARTIE 1 : Operations de base
// ============================================================
// Objectif : maitriser push, pop, top, empty, size
//
// Instructions :
// 1. Creer un stack<int>
// 2. Empiler 10, 20, 30, 40, 50
// 3. Afficher le sommet et la taille apres chaque push
// 4. Depiler tous les elements en affichant chacun
//    (observer l'ordre LIFO)
// 5. Verifier que le stack est vide

void partie1() {
    cout << "=== PARTIE 1 : Operations de base ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : Inverser une string avec un stack
// ============================================================
// Objectif : utiliser le LIFO pour inverser
//
// Instructions :
// 1. Prendre la string "Hello World"
// 2. Empiler chaque caractere dans un stack<char>
// 3. Depiler tout pour construire la string inversee
// 4. Afficher le resultat

void partie2() {
    cout << "=== PARTIE 2 : Inverser une string ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : Simuler l'historique d'un navigateur
// ============================================================
// Objectif : comprendre le stack comme historique (back/forward)
//
// Instructions :
// 1. Creer un stack<string> pour l'historique
// 2. Simuler la navigation : "google.com" -> "github.com" ->
//    "stackoverflow.com" -> "leetcode.com"
// 3. Faire "back" 2 fois (depiler et afficher la page courante)
// 4. Afficher la page actuelle (top)

void partie3() {
    cout << "=== PARTIE 3 : Historique navigateur ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
