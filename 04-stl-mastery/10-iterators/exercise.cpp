// ============================================================
// Iterateurs — Exercices
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

// ============================================================
// PARTIE 1 : begin, end, rbegin, rend
// ============================================================
// Objectif : maitriser les 4 iterateurs de base
//
// Instructions :
// 1. Creer un vector<int> = {10, 20, 30, 40, 50}
// 2. Afficher tous les elements avec un iterateur (for classique avec it)
// 3. Afficher tous les elements en sens inverse avec rbegin/rend
// 4. Modifier le premier et le dernier element via *begin() et *rbegin()
// 5. Afficher la distance entre begin() et end()

void partie1() {
    cout << "=== PARTIE 1 : begin, end, rbegin, rend ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 2 : advance, next, prev, distance
// ============================================================
// Objectif : naviguer avec precision dans un conteneur
//
// Instructions :
// 1. Creer un vector<int> = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
// 2. Obtenir un iterateur sur le 3eme element avec advance
// 3. Obtenir un iterateur sur le 7eme element avec next(begin, 6)
// 4. Depuis le 7eme, reculer de 2 avec prev
// 5. Calculer la distance entre le 3eme et le 7eme element
// 6. Repeter les etapes 2-4 avec une list<int> (meme valeurs)
//    Observer que le code est identique malgre la structure interne differente

void partie2() {
    cout << "=== PARTIE 2 : advance, next, prev, distance ===" << endl;

    // TON CODE ICI

    cout << endl;
}

// ============================================================
// PARTIE 3 : Iterateurs speciaux et algorithmes
// ============================================================
// Objectif : utiliser back_inserter et combiner iterateurs + algos
//
// Instructions :
// 1. Implementer copierPairs(vector<int>& src) -> vector<int>
//    Copier uniquement les nombres pairs de src dans un nouveau vecteur
//    en utilisant copy_if et back_inserter
// 2. Implementer inverserMots(string& s) -> string
//    Inverser l'ordre des mots dans une phrase
//    Exemple : "hello world foo" -> "foo world hello"
//    Indice : vector<string> + reverse(begin, end)
// 3. Tester avec src = {1,2,3,4,5,6,7,8,9,10}
//    et s = "le chat mange la souris"

vector<int> copierPairs(vector<int>& src) {
    // TON CODE ICI
    return {};
}

string inverserMots(string& s) {
    // TON CODE ICI
    return "";
}

void partie3() {
    cout << "=== PARTIE 3 : back_inserter et algorithmes ===" << endl;

    vector<int> src = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto pairs = copierPairs(src);
    cout << "Nombres pairs : ";
    for (int x : pairs) cout << x << " ";
    cout << endl;

    string phrase = "le chat mange la souris";
    cout << "Original  : " << phrase << endl;
    cout << "Inverse   : " << inverserMots(phrase) << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
