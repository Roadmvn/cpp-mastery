// ============================================================
// Pairs et Tuples — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================
// PARTIE 1 : Creer et utiliser des pairs
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Pairs ===" << endl;

    // 1. Creer un pair
    pair<string, int> student = {"Alice", 95};

    // 2. Afficher first et second
    cout << "Nom: " << student.first << ", Note: " << student.second << endl;

    // 3. Structured bindings
    auto [name, grade] = student;
    cout << "Bindings -> " << name << " : " << grade << endl;

    // 4. Vector de pairs
    vector<pair<string, int>> students = {
        {"Alice", 95},
        {"Bob", 87},
        {"Charlie", 92},
        {"Diana", 98}
    };

    // 5. Trier par note decroissante
    sort(students.begin(), students.end(),
         [](const pair<string,int>& a, const pair<string,int>& b) {
             return a.second > b.second;
         });

    // 6. Afficher le classement
    cout << "Classement :" << endl;
    int rank = 1;
    for (auto [n, g] : students) {
        cout << "  " << rank++ << ". " << n << " - " << g << endl;
    }

    cout << endl;
}

// ============================================================
// PARTIE 2 : Tuples et structured bindings
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : Tuples ===" << endl;

    // 1. Creer un tuple
    tuple<string, int, double> student = {"Alice", 20, 16.5};

    // 2. Afficher avec get
    cout << "get<> : " << get<0>(student) << ", "
         << get<1>(student) << " ans, moyenne "
         << get<2>(student) << endl;

    // 3. Structured bindings
    auto [name, age, avg] = student;
    cout << "Bindings : " << name << ", " << age << " ans, "
         << avg << "/20" << endl;

    // 4. Vector de tuples
    vector<tuple<string, int, double>> students = {
        {"Alice", 20, 16.5},
        {"Bob", 21, 14.0},
        {"Charlie", 19, 17.8}
    };

    // 5. Trier par moyenne decroissante
    sort(students.begin(), students.end(),
         [](const auto& a, const auto& b) {
             return get<2>(a) > get<2>(b);
         });

    cout << "Classement par moyenne :" << endl;
    for (auto [n, a, m] : students) {
        cout << "  " << n << " (" << a << " ans) - " << m << "/20" << endl;
    }

    cout << endl;
}

// ============================================================
// PARTIE 3 : Pairs dans les structures de donnees
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : Pairs et graphes ===" << endl;

    // 1. Adjacency list
    int n = 4;
    vector<vector<pair<int, int>>> adj(n);

    adj[0].push_back({1, 5});  // 0 -> 1, poids 5
    adj[0].push_back({2, 3});  // 0 -> 2, poids 3
    adj[1].push_back({3, 2});  // 1 -> 3, poids 2
    adj[2].push_back({3, 7});  // 2 -> 3, poids 7

    // 2. Afficher toutes les aretes
    cout << "Aretes du graphe :" << endl;
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) {
            cout << "  " << u << " -> " << v << " (poids " << w << ")" << endl;
        }
    }

    // 3. Trouver l'arete de poids minimum
    int min_weight = INT32_MAX;
    int min_u = -1, min_v = -1;
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) {
            if (w < min_weight) {
                min_weight = w;
                min_u = u;
                min_v = v;
            }
        }
    }
    cout << "Arete min : " << min_u << " -> " << min_v
         << " (poids " << min_weight << ")" << endl;

    // 4. Poids total
    int total = 0;
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : adj[u]) {
            total += w;
        }
    }
    cout << "Poids total : " << total << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
