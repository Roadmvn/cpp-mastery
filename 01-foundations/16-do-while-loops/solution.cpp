// ============================================================
// SOLUTION : Boucles Do-While
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Validation d'entree
    // --------------------------------------------------------
    int nombre;
    do {
        cout << "Entre un nombre (1-100) : ";
        cin >> nombre;
        if (nombre < 1 || nombre > 100) {
            cout << "Hors limites ! Reessaie." << endl;
        }
    } while (nombre < 1 || nombre > 100);

    cout << "Nombre accepte : " << nombre << endl;

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 2 : Devine le nombre
    // --------------------------------------------------------
    int secret = 42;
    int guess;

    do {
        cout << "Devine le nombre (1-100) : ";
        cin >> guess;

        if (guess < secret) {
            cout << "Trop bas !" << endl;
        } else if (guess > secret) {
            cout << "Trop haut !" << endl;
        } else {
            cout << "Bravo ! C'etait bien " << secret << " !" << endl;
        }
    } while (guess != secret);

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 3 : Mot de passe
    // --------------------------------------------------------
    string password;
    string correct = "access2024";
    int tentatives = 0;
    int max_tentatives = 3;
    bool acces = false;

    do {
        cout << "Mot de passe (" << (max_tentatives - tentatives)
             << " tentatives restantes) : ";
        cin >> password;
        tentatives++;

        if (password == correct) {
            acces = true;
        } else if (tentatives < max_tentatives) {
            cout << "Incorrect. Reessaie." << endl;
        }
    } while (!acces && tentatives < max_tentatives);

    if (acces) {
        cout << "Acces autorise." << endl;
    } else {
        cout << "Compte bloque. 3 tentatives echouees." << endl;
    }

    return 0;
}
