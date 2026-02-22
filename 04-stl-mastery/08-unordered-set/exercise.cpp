// ============================================================
// Unordered Set — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// PARTIE 1 : Operations de base
// ============================================================
// Objectif : maitriser insert, find, count, erase
//
// Instructions :
// 1. Creer un unordered_set<int>
// 2. Inserer : 10, 20, 30, 40, 20 (observer que 20 n'est pas duplique)
// 3. Verifier si 20 existe avec count() et find()
// 4. Verifier si 99 existe avec count() et find()
// 5. Supprimer 30 avec erase
// 6. Afficher la taille et tous les elements

void partie1() {
    cout << "=== PARTIE 1 : Operations de base ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : Detecter les doublons
// ============================================================
// Objectif : utiliser le set pour detecter des elements en double
//
// Instructions :
// 1. Implementer hasDuplicate(vector<int>& nums) -> bool
//    Retourne true si nums contient au moins un doublon
// 2. Implementer findDuplicates(vector<int>& nums) -> vector<int>
//    Retourne tous les elements qui apparaissent plus d'une fois
// 3. Tester avec : {1, 3, 5, 2, 4}       -> false, {}
//                  {1, 3, 5, 2, 1, 4, 3}  -> true, {1, 3}

bool hasDuplicate(vector<int>& nums) {
    // TON CODE ICI
    return false;
}

vector<int> findDuplicates(vector<int>& nums) {
    // TON CODE ICI
    return {};
}

void partie2() {
    cout << "=== PARTIE 2 : Detecter les doublons ===" << endl;

    vector<int> t1 = {1, 3, 5, 2, 4};
    vector<int> t2 = {1, 3, 5, 2, 1, 4, 3};

    cout << "t1 hasDuplicate : " << (hasDuplicate(t1) ? "true" : "false") << endl;
    cout << "t2 hasDuplicate : " << (hasDuplicate(t2) ? "true" : "false") << endl;

    auto dups = findDuplicates(t2);
    cout << "t2 doublons : ";
    for (int x : dups) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : Operations sur ensembles
// ============================================================
// Objectif : calculer intersection et union de deux ensembles
//
// Instructions :
// 1. Implementer intersection(vector<int>& a, vector<int>& b) -> vector<int>
//    Retourne les elements presents dans les deux
// 2. Implementer unionSets(vector<int>& a, vector<int>& b) -> vector<int>
//    Retourne tous les elements sans doublons
// 3. Implementer difference(vector<int>& a, vector<int>& b) -> vector<int>
//    Retourne les elements dans a mais pas dans b
// 4. Tester avec a={1,2,3,4,5}, b={3,4,5,6,7}

vector<int> intersection(vector<int>& a, vector<int>& b) {
    // TON CODE ICI
    return {};
}

vector<int> unionSets(vector<int>& a, vector<int>& b) {
    // TON CODE ICI
    return {};
}

vector<int> difference(vector<int>& a, vector<int>& b) {
    // TON CODE ICI
    return {};
}

void partie3() {
    cout << "=== PARTIE 3 : Operations sur ensembles ===" << endl;

    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {3, 4, 5, 6, 7};

    auto inter = intersection(a, b);
    cout << "Intersection : ";
    for (int x : inter) cout << x << " ";
    cout << endl;

    auto uni = unionSets(a, b);
    cout << "Union : ";
    for (int x : uni) cout << x << " ";
    cout << endl;

    auto diff = difference(a, b);
    cout << "Difference a-b : ";
    for (int x : diff) cout << x << " ";
    cout << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
