// ============================================================
// SOLUTION : Boucles While
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Compte a rebours
    // --------------------------------------------------------
    int countdown = 10;
    while (countdown >= 1) {
        cout << countdown << endl;
        countdown--;
    }
    cout << "LANCEMENT !" << endl;

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 2 : Somme avec sentinelle
    // --------------------------------------------------------
    int nombre;
    int somme = 0;

    cout << "Entre un nombre (-1 pour arreter) : ";
    cin >> nombre;

    while (nombre != -1) {
        somme += nombre;
        cout << "Entre un nombre (-1 pour arreter) : ";
        cin >> nombre;
    }

    cout << "Somme totale : " << somme << endl;

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 3 : Puissance de 2
    // --------------------------------------------------------
    int puissance = 1;
    while (puissance < 10000) {
        cout << puissance;
        puissance *= 2;
        if (puissance < 10000) cout << ", ";
    }
    cout << endl;

    return 0;
}
