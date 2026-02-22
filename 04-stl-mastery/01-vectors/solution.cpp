// ============================================================
// Vectors — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// PARTIE 1 : Creation, ajout, taille et capacite
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Creation et manipulation ===" << endl;

    // 1. Creer un vector vide
    vector<int> v;

    // 2. Ajouter des valeurs et observer size/capacity
    int values[] = {10, 20, 30, 40, 50};
    for (int val : values) {
        v.push_back(val);
        cout << "Ajout de " << val
             << " | size: " << v.size()
             << " | capacity: " << v.capacity() << endl;
    }
    // On voit que capacity double quand elle est depassee (1 -> 2 -> 4 -> 8)

    // 3. Supprimer le dernier element
    v.pop_back();
    cout << "Apres pop_back | size: " << v.size()
         << " | capacity: " << v.capacity() << endl;
    // capacity ne diminue PAS apres pop_back

    // 4. Premier et dernier element
    cout << "front(): " << v.front() << endl;  // 10
    cout << "back(): " << v.back() << endl;     // 40

    cout << endl;
}

// ============================================================
// PARTIE 2 : Trois facons d'iterer
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : Iteration ===" << endl;

    // 1. Creer le vector
    vector<string> langs = {"C++", "Python", "Rust", "Go"};

    // 2. Boucle par index
    cout << "Par index : ";
    for (size_t i = 0; i < langs.size(); i++) {
        cout << langs[i];
        if (i < langs.size() - 1) cout << ", ";
    }
    cout << endl;

    // 3. Range-based for (par copie, lecture seule)
    cout << "Range-for : ";
    for (string lang : langs) {
        cout << lang << " ";
    }
    cout << endl;

    // 4. Iterateurs
    cout << "Iterateurs : ";
    for (auto it = langs.begin(); it != langs.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 5. Modification par reference
    for (string& lang : langs) {
        lang += " (cool)";
    }

    cout << "Apres modification : ";
    for (const string& lang : langs) {
        cout << lang << " | ";
    }
    cout << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : Vector 2D (matrice)
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : Vector 2D ===" << endl;

    // 1. Matrice 3x3 initialisee a 0
    vector<vector<int>> matrix(3, vector<int>(3, 0));

    // 2. Remplir la diagonale (matrice identite)
    for (int i = 0; i < 3; i++) {
        matrix[i][i] = 1;
    }

    // 3. Affichage formate
    cout << "Matrice identite 3x3 :" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    // 4. Ajouter une 4eme ligne
    matrix.push_back({7, 8, 9});

    // 5. Afficher la nouvelle matrice
    cout << "Matrice 4x3 :" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << endl;
}

// ============================================================
// PARTIE 4 : reserve() et observation de capacity
// ============================================================

void partie4() {
    cout << "=== PARTIE 4 : reserve() ===" << endl;

    // 1. SANS reserve
    vector<int> v1;
    int realloc_count_1 = 0;
    size_t prev_cap = v1.capacity();

    for (int i = 0; i < 100; i++) {
        v1.push_back(i);
        if (v1.capacity() != prev_cap) {
            realloc_count_1++;
            prev_cap = v1.capacity();
        }
    }

    // 2. AVEC reserve
    vector<int> v2;
    v2.reserve(100);
    int realloc_count_2 = 0;
    prev_cap = v2.capacity();

    for (int i = 0; i < 100; i++) {
        v2.push_back(i);
        if (v2.capacity() != prev_cap) {
            realloc_count_2++;
            prev_cap = v2.capacity();
        }
    }

    // 3. Comparaison
    cout << "SANS reserve :" << endl;
    cout << "  Reallocations : " << realloc_count_1 << endl;
    cout << "  Capacity finale : " << v1.capacity() << endl;

    cout << "AVEC reserve(100) :" << endl;
    cout << "  Reallocations : " << realloc_count_2 << endl;
    cout << "  Capacity finale : " << v2.capacity() << endl;

    // On voit clairement : sans reserve = ~7 reallocations
    // Avec reserve = 0 reallocation. Enorme difference en perf.

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    partie4();

    return 0;
}
