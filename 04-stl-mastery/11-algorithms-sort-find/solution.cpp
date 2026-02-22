// ============================================================
// Algorithmes STL — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

// ============================================================
// PARTIE 1 : Tri et recherche
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Tri et recherche ===" << endl;

    // 1. Creer le vecteur
    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6, 10};

    // 2. Trier
    sort(v.begin(), v.end());
    cout << "Apres sort : ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 3. binary_search (necessite tableau trie !)
    cout << "7 existe ? " << (binary_search(v.begin(), v.end(), 7) ? "oui" : "non") << endl;
    cout << "11 existe ? " << (binary_search(v.begin(), v.end(), 11) ? "oui" : "non") << endl;

    // 4. lower_bound pour trouver le premier element > 5
    auto it = upper_bound(v.begin(), v.end(), 5);
    cout << "Premier element > 5 : " << *it
         << " (index " << distance(v.begin(), it) << ")" << endl;

    // 5. Elements dans [4, 7]
    auto lo = lower_bound(v.begin(), v.end(), 4);
    auto hi = upper_bound(v.begin(), v.end(), 7);
    cout << "Elements dans [4, 7] : ";
    for (auto jt = lo; jt != hi; ++jt) cout << *jt << " ";
    cout << endl;

    // 6. partial_sort : 3 plus petits en position [0,2]
    vector<int> v2 = {5, 2, 8, 1, 9, 3, 7, 4, 6, 10};
    partial_sort(v2.begin(), v2.begin() + 3, v2.end());
    cout << "3 plus petits (partial_sort) : ";
    for (int i = 0; i < 3; i++) cout << v2[i] << " ";
    cout << endl;

    cout << endl;
}

// ============================================================
// PARTIE 2 : Comptage et conditions
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : Comptage et conditions ===" << endl;

    vector<int> v = {3, 7, 1, 8, 2, 9, 4, 6, 5, 10};

    // 2. Compter les pairs
    int pairs = count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    cout << "Nombre de pairs : " << pairs << endl;  // 4

    // 3. Compter > 5
    int gt5 = count_if(v.begin(), v.end(), [](int x) { return x > 5; });
    cout << "Nombre > 5 : " << gt5 << endl;  // 4

    // 4. all_of
    bool allPos = all_of(v.begin(), v.end(), [](int x) { return x > 0; });
    cout << "Tous > 0 ? " << (allPos ? "oui" : "non") << endl;  // oui

    // 5. any_of
    bool anyGt8 = any_of(v.begin(), v.end(), [](int x) { return x > 8; });
    cout << "Au moins un > 8 ? " << (anyGt8 ? "oui" : "non") << endl;  // oui (9, 10)

    // 6. none_of
    bool noneNeg = none_of(v.begin(), v.end(), [](int x) { return x < 0; });
    cout << "Aucun negatif ? " << (noneNeg ? "oui" : "non") << endl;  // oui

    // 7. Premier element pair
    auto it = find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    if (it != v.end()) {
        cout << "Premier pair : " << *it << " (index " << distance(v.begin(), it) << ")" << endl;
    }

    cout << endl;
}

// ============================================================
// PARTIE 3 : Transform, accumulate et erase-remove
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : transform, accumulate, erase-remove ===" << endl;

    // 1. Doubler avec transform in-place
    vector<int> v = {1, 2, 3, 4, 5};
    transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 2; });
    cout << "Apres doublement : ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 2. Somme avec accumulate
    int sum = accumulate(v.begin(), v.end(), 0);
    cout << "Somme : " << sum << endl;  // 2+4+6+8+10 = 30

    // 3. Produit avec accumulate et lambda
    int prod = accumulate(v.begin(), v.end(), 1, [](int acc, int x) { return acc * x; });
    cout << "Produit : " << prod << endl;  // 2*4*6*8*10 = 3840

    // 4. erase-remove pattern pour supprimer mots courts
    vector<string> words = {"hello", "world", "foo", "bar", "baz"};
    words.erase(
        remove_if(words.begin(), words.end(),
                  [](const string& s) { return s.size() < 4; }),
        words.end()
    );

    // 5. Afficher
    cout << "Mots de longueur >= 4 : ";
    for (const string& w : words) cout << w << " ";
    cout << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
