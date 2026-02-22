// =============================================================
// Solution : Arrays multidimensionnels
// =============================================================
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// =============================================================

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // ==========================================================
    // PARTIE 1 : Declaration et acces
    // ==========================================================

    // 1.1
    int grid[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // 1.2
    cout << "=== Grille ===" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << setw(3) << grid[i][j];
        }
        cout << endl;
    }

    // 1.3
    cout << "\ngrid[1][2] = " << grid[1][2] << endl;
    cout << "grid[2][0] = " << grid[2][0] << endl;

    // ==========================================================
    // PARTIE 2 : Parcours et calculs
    // ==========================================================

    int matrix[3][3] = {
        {4, 7, 2},
        {3, 8, 5},
        {6, 1, 9}
    };

    // 2.1
    cout << "\n=== Sommes par ligne ===" << endl;
    for (int i = 0; i < 3; i++) {
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += matrix[i][j];
        }
        cout << "Ligne " << i << " : " << sum << endl;
    }

    // 2.2
    cout << "\n=== Sommes par colonne ===" << endl;
    for (int j = 0; j < 3; j++) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += matrix[i][j];
        }
        cout << "Colonne " << j << " : " << sum << endl;
    }

    // 2.3
    int diagSum = 0;
    for (int i = 0; i < 3; i++) {
        diagSum += matrix[i][i];
    }
    cout << "\nDiagonale : " << diagSum << endl;

    // ==========================================================
    // PARTIE 3 : Operations sur matrices
    // ==========================================================

    int matA[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int matB[2][3] = { {7, 8, 9}, {10, 11, 12} };

    // 3.1
    int matC[2][3];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            matC[i][j] = matA[i][j] + matB[i][j];
        }
    }

    cout << "\n=== matA + matB ===" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(4) << matC[i][j];
        }
        cout << endl;
    }

    // 3.2
    int transposee[3][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            transposee[j][i] = matA[i][j];
        }
    }

    cout << "\n=== Transposee de matA ===" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            cout << setw(4) << transposee[i][j];
        }
        cout << endl;
    }

    // 3.3
    int maxVal = matrix[0][0];
    int maxRow = 0, maxCol = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
    cout << "\nMax = " << maxVal << " a la position (" << maxRow << ", " << maxCol << ")" << endl;

    return 0;
}
