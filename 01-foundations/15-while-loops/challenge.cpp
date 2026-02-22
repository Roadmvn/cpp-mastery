// ============================================================
// CHALLENGE OFFENSIVE : Simulateur de brute-force
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// Simulation d'une attaque par dictionnaire sur un mot de passe.
// Le programme teste des mots de passe depuis un "dictionnaire"
// (tableau de strings) jusqu'a trouver le bon ou epuiser la liste.
//
// C'est un exercice PEDAGOGIQUE pour comprendre les boucles while.
// En vrai, les outils de brute-force (Hydra, John) font ca en parallele
// sur des milliers de threads avec des optimisations avancees.
//
// Usage educatif uniquement.
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Le mot de passe "cible" a trouver
    string target_password = "dragon";

    // Dictionnaire fictif de mots de passe courants
    string dictionary[] = {
        "123456", "password", "admin", "letmein", "welcome",
        "monkey", "master", "qwerty", "login", "abc123",
        "starwars", "dragon", "passw0rd", "shadow", "trustno1"
    };
    int dict_size = 15;

    cout << "========================================" << endl;
    cout << "  Brute-Force Simulator (Dictionary)" << endl;
    cout << "========================================" << endl;
    cout << "Cible    : ********" << endl;
    cout << "Methode  : Dictionnaire (" << dict_size << " entrees)" << endl;
    cout << "----------------------------------------" << endl;

    int index = 0;
    int attempts = 0;
    bool found = false;

    while (index < dict_size && !found) {
        attempts++;
        string attempt = dictionary[index];

        cout << "[Tentative " << attempts << "] "
             << "Essai : " << attempt;

        if (attempt == target_password) {
            found = true;
            cout << "  << MATCH !" << endl;
        } else {
            cout << "  -- echec" << endl;
        }

        index++;
    }

    cout << "----------------------------------------" << endl;

    if (found) {
        cout << "[+] Mot de passe trouve : " << target_password << endl;
        cout << "[+] Tentatives : " << attempts << "/" << dict_size << endl;
        cout << "[!] Taux de reussite : "
             << (attempts * 100 / dict_size) << "% du dictionnaire parcouru" << endl;
    } else {
        cout << "[-] Mot de passe non trouve dans le dictionnaire." << endl;
        cout << "[-] Tentatives : " << attempts << endl;
        cout << "[*] Prochaine etape : essayer le brute-force pur (toutes les combinaisons)" << endl;
    }

    cout << "========================================" << endl;
    cout << "Note : En production, un rate limiter ou" << endl;
    cout << "un lockout bloquerait ce type d'attaque" << endl;
    cout << "apres quelques tentatives echouees." << endl;
    cout << "========================================" << endl;

    return 0;
}
