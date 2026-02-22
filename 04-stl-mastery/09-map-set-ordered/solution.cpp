// ============================================================
// Map et Set ordonnes — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// PARTIE 1 : Ordre garanti et lower/upper_bound
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Ordre garanti et bounds ===" << endl;

    // 1. Creer le set (ordre automatique a l'insertion)
    set<int> s = {5, 1, 8, 3, 9, 2, 7, 4, 6};

    // 2. Afficher en ordre trie (in-order traversal de l'arbre)
    cout << "Elements tries : ";
    for (int x : s) cout << x << " ";
    cout << endl;

    // 3. lower_bound : premier element >= 4
    auto it_lb = s.lower_bound(4);
    cout << "Premier element >= 4 : " << *it_lb << endl;  // 4

    // 4. upper_bound : premier element > 6
    auto it_ub = s.upper_bound(6);
    cout << "Premier element > 6 : " << *it_ub << endl;   // 7

    // 5. Elements dans [3, 7] inclus
    cout << "Elements dans [3, 7] : ";
    auto lo = s.lower_bound(3);
    auto hi = s.upper_bound(7);
    for (auto it = lo; it != hi; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 6. Minimum et maximum
    cout << "Minimum : " << *s.begin() << endl;   // 1
    cout << "Maximum : " << *s.rbegin() << endl;  // 9

    cout << endl;
}

// ============================================================
// PARTIE 2 : map ordonnee
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : map ordonnee ===" << endl;

    // 1. Creer la map (triee par cle alphabetique automatiquement)
    map<string, int> notes = {
        {"Physique", 14}, {"Maths", 17}, {"Info", 19},
        {"Chimie", 12}, {"Bio", 15}
    };

    // 2. Afficher en ordre alphabetique
    cout << "Matieres (ordre alphabetique) :" << endl;
    for (auto& [matiere, note] : notes) {
        cout << "  " << matiere << " : " << note << endl;
    }

    // 3. Premiere matiere apres "Info" dans l'ordre alphabetique
    auto it = notes.upper_bound("Info");
    if (it != notes.end()) {
        cout << "Premiere matiere apres Info : " << it->first << endl;
    }

    // 4. Moyenne
    double somme = 0;
    for (auto& [matiere, note] : notes) somme += note;
    cout << "Moyenne : " << somme / notes.size() << endl;

    // 5. Matieres avec note >= 15
    cout << "Matieres >= 15 : ";
    for (auto& [matiere, note] : notes) {
        if (note >= 15) cout << matiere << "(" << note << ") ";
    }
    cout << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : multiset — doublons + suppression precise
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : multiset ===" << endl;

    // 1. Creer le multiset avec doublons
    multiset<int> ms = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

    // 2. Afficher tous les elements tries
    cout << "Elements tries (avec doublons) : ";
    for (int x : ms) cout << x << " ";
    cout << endl;

    // 3. Compter les occurrences
    cout << "Occurrences de 1 : " << ms.count(1) << endl;  // 2
    cout << "Occurrences de 5 : " << ms.count(5) << endl;  // 2

    // 4. Supprimer UNE seule occurrence de 1
    //    erase(val) supprimerait TOUT, on passe par l'iterateur
    auto it = ms.find(1);
    if (it != ms.end()) ms.erase(it);
    cout << "Apres suppression d'une occurrence de 1 : ";
    for (int x : ms) cout << x << " ";
    cout << endl;
    cout << "Il reste " << ms.count(1) << " occurrence(s) de 1" << endl;

    // 5. Supprimer TOUTES les occurrences de 5
    ms.erase(5);
    cout << "Apres suppression de toutes les occurrences de 5 : ";
    for (int x : ms) cout << x << " ";
    cout << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
