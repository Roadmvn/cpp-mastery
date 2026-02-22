// =============================================================
// Exercice : Arrays multidimensionnels
// =============================================================
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// =============================================================

#include <iostream>
using namespace std;

int main() {
    // ==========================================================
    // PARTIE 1 : Declaration et acces
    // ==========================================================

    // TODO 1.1 : Declare un array 2D de 3 lignes x 4 colonnes appele 'grid'
    //            initialise avec les valeurs :
    //            { {1,2,3,4}, {5,6,7,8}, {9,10,11,12} }


    // TODO 1.2 : Affiche la matrice sous forme de grille
    //            Format:
    //            1  2  3  4
    //            5  6  7  8
    //            9  10 11 12


    // TODO 1.3 : Affiche l'element en ligne 1, colonne 2
    //            et l'element en ligne 2, colonne 0
    //            Format: "grid[1][2] = X"


    // ==========================================================
    // PARTIE 2 : Parcours et calculs
    // ==========================================================

    int matrix[3][3] = {
        {4, 7, 2},
        {3, 8, 5},
        {6, 1, 9}
    };

    // TODO 2.1 : Calcule et affiche la somme de chaque ligne
    //            Format: "Ligne 0 : X"


    // TODO 2.2 : Calcule et affiche la somme de chaque colonne
    //            Format: "Colonne 0 : X"


    // TODO 2.3 : Calcule et affiche la somme de la diagonale principale
    //            (elements ou i == j)
    //            Format: "Diagonale : X"


    // ==========================================================
    // PARTIE 3 : Operations sur matrices
    // ==========================================================

    int matA[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int matB[2][3] = { {7, 8, 9}, {10, 11, 12} };

    // TODO 3.1 : Calcule la matrice somme matC = matA + matB
    //            et affiche le resultat


    // TODO 3.2 : Calcule la transposee de matA (2x3 -> 3x2)
    //            et affiche le resultat
    //            Rappel: transposee[j][i] = original[i][j]


    // TODO 3.3 : Trouve l'element maximum et sa position (ligne, colonne)
    //            dans 'matrix' (3x3)
    //            Format: "Max = X a la position (i, j)"


    return 0;
}
