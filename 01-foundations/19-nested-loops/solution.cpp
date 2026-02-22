// ============================================================
// SOLUTION : Boucles Imbriquees
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Rectangle d'etoiles
    // --------------------------------------------------------
    int largeur, hauteur;
    cout << "Largeur : ";
    cin >> largeur;
    cout << "Hauteur : ";
    cin >> hauteur;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            cout << "* ";
        }
        cout << endl;
    }

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 2 : Table de multiplication
    // --------------------------------------------------------
    // En-tete
    cout << "    ";
    for (int j = 1; j <= 9; j++) {
        cout << setw(4) << j;
    }
    cout << endl;

    // Lignes
    for (int i = 1; i <= 9; i++) {
        cout << setw(3) << i << " ";
        for (int j = 1; j <= 9; j++) {
            cout << setw(4) << (i * j);
        }
        cout << endl;
    }

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 3 : Recherche dans une matrice
    // --------------------------------------------------------
    int matrix[4][5] = {
        {10, 20, 30, 40, 50},
        {11, 22, 33, 44, 55},
        {12, 24, 42, 48, 60},
        {13, 26, 39, 52, 65}
    };

    bool found = false;
    for (int i = 0; i < 4 && !found; i++) {
        for (int j = 0; j < 5 && !found; j++) {
            if (matrix[i][j] == 42) {
                cout << "42 trouve a la position (" << i << ", " << j << ")" << endl;
                found = true;
            }
        }
    }
    if (!found) {
        cout << "42 non trouve dans la matrice." << endl;
    }

    return 0;
}
