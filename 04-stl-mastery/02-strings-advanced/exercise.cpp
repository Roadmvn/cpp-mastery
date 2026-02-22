// ============================================================
// Strings Avancees — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

// ============================================================
// PARTIE 1 : substr, find, replace
// ============================================================
// Objectif : maitriser l'extraction et la recherche dans les strings
//
// Instructions :
// 1. Creer une string "competitive-programming-is-awesome"
// 2. Extraire "programming" avec substr (trouver la position avec find)
// 3. Remplacer "awesome" par "essential" avec find + replace
// 4. Trouver la position de chaque '-' et les afficher
// 5. Compter le nombre de voyelles dans la string

void partie1() {
    cout << "=== PARTIE 1 : substr, find, replace ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : stringstream et parsing
// ============================================================
// Objectif : savoir decouper et reconstruire des strings
//
// Instructions :
// 1. Parser "192.168.1.1" en 4 entiers (utilise getline avec '.')
// 2. Afficher chaque octet individuellement
// 3. Parser "nom:Alice age:30 score:95.5" pour extraire les valeurs
// 4. Construire la string "Alice [30] -> 95.5" avec stringstream

void partie2() {
    cout << "=== PARTIE 2 : stringstream ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : Conversions et manipulation de caracteres
// ============================================================
// Objectif : convertir entre types et manipuler les caracteres
//
// Instructions :
// 1. Convertir "12345" en int, multiplier par 2, reconvertir en string
// 2. Prendre "Hello World 123" et :
//    a. Compter les lettres, chiffres et espaces separement
//    b. Convertir toutes les lettres en majuscules
// 3. Prendre un vector<int> {10, 20, 30} et le convertir en
//    string "10-20-30" (avec tirets entre les nombres)

void partie3() {
    cout << "=== PARTIE 3 : Conversions ===" << endl;

    // TON CODE ICI

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
