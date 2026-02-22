// ============================================================
// SOLUTION : Break & Continue
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Trouver un element
    // --------------------------------------------------------
    int data[] = {10, 25, 33, 7, 42, 88, 99, 42, 15};
    int data_size = 9;
    bool found = false;

    for (int i = 0; i < data_size; i++) {
        if (data[i] == 42) {
            cout << "42 trouve a la position " << i << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Non trouve" << endl;
    }

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 2 : Filtrer les negatifs
    // --------------------------------------------------------
    int values[] = {15, -3, 22, -7, 8, -1, 30, -12, 5, -4};
    int values_size = 10;
    int somme_positifs = 0;

    cout << "Positifs : ";
    for (int i = 0; i < values_size; i++) {
        if (values[i] < 0) continue;  // Skip les negatifs
        cout << values[i] << " ";
        somme_positifs += values[i];
    }
    cout << endl;
    cout << "Somme des positifs : " << somme_positifs << endl;

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 3 : Premier nombre premier
    // --------------------------------------------------------
    int count = 0;
    cout << "20 premiers nombres premiers : ";

    for (int n = 2; count < 20; n++) {
        bool is_prime = true;

        for (int d = 2; d * d <= n; d++) {
            if (n % d == 0) {
                is_prime = false;
                break;  // Pas premier, pas besoin de continuer
            }
        }

        if (is_prime) {
            cout << n << " ";
            count++;
        }
    }
    cout << endl;

    return 0;
}
