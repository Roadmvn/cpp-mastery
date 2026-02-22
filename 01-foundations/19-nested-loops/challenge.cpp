// ============================================================
// CHALLENGE OFFENSIVE : Generateur de combinaisons
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// Generation de toutes les combinaisons possibles d'un charset
// pour des mots de passe de 2 a 3 caracteres.
//
// C'est la base du brute-force pur (par opposition au dictionnaire).
// En vrai, des outils comme Hashcat font ca sur GPU a des milliards
// de combinaisons par seconde.
//
// Exercice PEDAGOGIQUE pour comprendre les boucles imbriquees
// et la combinatoire.
//
// Usage educatif uniquement.
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    string charset = "abc123";  // Charset reduit pour la demo

    cout << "========================================" << endl;
    cout << "  Brute-Force Combination Generator" << endl;
    cout << "========================================" << endl;
    cout << "Charset : \"" << charset << "\"" << endl;
    cout << "Taille  : " << charset.length() << " caracteres" << endl;

    int len = charset.length();

    // --- Combinaisons de 2 caracteres ---
    int count_2 = 0;
    cout << "\n--- Combinaisons 2 chars (" << (len * len) << " total) ---" << endl;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            cout << charset[i] << charset[j] << " ";
            count_2++;
        }
        cout << endl;
    }
    cout << "Total 2 chars : " << count_2 << endl;

    // --- Combinaisons de 3 caracteres ---
    int count_3 = 0;
    cout << "\n--- Combinaisons 3 chars (" << (len * len * len) << " total) ---" << endl;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < len; k++) {
                string combo = "";
                combo += charset[i];
                combo += charset[j];
                combo += charset[k];
                cout << combo << " ";
                count_3++;
            }
        }
        cout << endl;
    }
    cout << "Total 3 chars : " << count_3 << endl;

    // --- Statistiques ---
    cout << "\n========================================" << endl;
    cout << "  Statistiques de complexite" << endl;
    cout << "========================================" << endl;
    cout << "Charset de " << len << " caracteres :" << endl;
    cout << "  2 chars : " << (len * len) << " combinaisons" << endl;
    cout << "  3 chars : " << (len * len * len) << " combinaisons" << endl;
    cout << "  4 chars : " << (len * len * len * len) << " combinaisons" << endl;
    cout << "  8 chars : ";
    long long total_8 = 1;
    for (int i = 0; i < 8; i++) total_8 *= len;
    cout << total_8 << " combinaisons" << endl;

    cout << "\nAvec l'alphabet complet (26 lettres + chiffres = 36) :" << endl;
    cout << "  4 chars : 1 679 616 combinaisons" << endl;
    cout << "  6 chars : 2 176 782 336 combinaisons" << endl;
    cout << "  8 chars : 2 821 109 907 456 combinaisons" << endl;
    cout << "\nC'est pour ca qu'un mot de passe long est plus sur." << endl;
    cout << "========================================" << endl;

    return 0;
}
