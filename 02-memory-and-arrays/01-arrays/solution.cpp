// =============================================================
// Solution : Les Arrays en C++
// =============================================================
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// =============================================================

#include <iostream>
using namespace std;

int main() {
    // ==========================================================
    // PARTIE 1 : Declaration et initialisation
    // ==========================================================

    // 1.1
    int scores[5] = {85, 92, 78, 95, 88};

    // 1.2
    double temperatures[3];

    // 1.3
    int fibonacci[] = {1, 1, 2, 3, 5, 8, 13};

    // ==========================================================
    // PARTIE 2 : Acces et modification
    // ==========================================================

    // 2.1
    cout << "Premier: " << scores[0] << ", Dernier: " << scores[4] << endl;

    // 2.2
    scores[2] = 100;

    // 2.3
    int nbElements = sizeof(scores) / sizeof(scores[0]);
    cout << "Nombre d'elements: " << nbElements << endl;

    // ==========================================================
    // PARTIE 3 : Calculs sur array
    // ==========================================================

    // 3.1
    int somme = 0;
    for (int i = 0; i < nbElements; i++) {
        somme += scores[i];
    }
    cout << "Somme: " << somme << endl;

    // 3.2
    double moyenne = static_cast<double>(somme) / nbElements;
    cout << "Moyenne: " << moyenne << endl;

    // 3.3
    int maximum = scores[0];
    for (int i = 1; i < nbElements; i++) {
        if (scores[i] > maximum) {
            maximum = scores[i];
        }
    }
    cout << "Maximum: " << maximum << endl;

    return 0;
}
