// ============================================================
// MINI-PROJET : Pierre-Feuille-Ciseaux
// Compile : g++ -std=c++17 -o rps main.cpp
// ============================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Prototypes
string choice_name(int choice);
int determine_winner(int player, int computer);
void print_scoreboard(int p_score, int c_score, int target);

int main() {
    srand(time(0));
    char rejouer;

    cout << "========================================" << endl;
    cout << "  Pierre - Feuille - Ciseaux" << endl;
    cout << "========================================" << endl;

    do {
        // Choix du mode
        int mode;
        cout << "\nMode de jeu :" << endl;
        cout << "1. Meilleur des 3 (premier a 2)" << endl;
        cout << "2. Meilleur des 5 (premier a 3)" << endl;
        cout << "Choix : ";
        cin >> mode;

        int target = (mode == 2) ? 3 : 2;

        int player_score = 0;
        int computer_score = 0;
        int round = 0;

        cout << "\nPremier a " << target << " victoires !" << endl;

        while (player_score < target && computer_score < target) {
            round++;
            cout << "\n--- Manche " << round << " ---" << endl;
            print_scoreboard(player_score, computer_score, target);

            // Choix du joueur
            int player_choice;
            cout << "1. Pierre" << endl;
            cout << "2. Feuille" << endl;
            cout << "3. Ciseaux" << endl;
            cout << "Ton choix : ";
            cin >> player_choice;

            if (player_choice < 1 || player_choice > 3) {
                cout << "Choix invalide ! Manche perdue." << endl;
                computer_score++;
                continue;
            }

            // Choix de l'ordinateur
            int computer_choice = rand() % 3 + 1;

            cout << "\nToi       : " << choice_name(player_choice) << endl;
            cout << "Ordi      : " << choice_name(computer_choice) << endl;

            // Resultat
            int result = determine_winner(player_choice, computer_choice);

            if (result == 0) {
                cout << "Egalite ! On recommence la manche." << endl;
                round--;  // L'egalite ne compte pas
            } else if (result == 1) {
                cout << "Tu gagnes cette manche !" << endl;
                player_score++;
            } else {
                cout << "L'ordinateur gagne cette manche." << endl;
                computer_score++;
            }
        }

        // Resultat final
        cout << "\n========================================" << endl;
        print_scoreboard(player_score, computer_score, target);

        if (player_score >= target) {
            cout << "VICTOIRE ! Tu as gagne " << player_score
                 << " a " << computer_score << " !" << endl;
        } else {
            cout << "DEFAITE. L'ordinateur gagne " << computer_score
                 << " a " << player_score << "." << endl;
        }
        cout << "Manches jouees : " << round << endl;
        cout << "========================================" << endl;

        cout << "\nRejouer ? (o/n) : ";
        cin >> rejouer;

    } while (rejouer == 'o' || rejouer == 'O');

    cout << "\nMerci d'avoir joue !" << endl;

    return 0;
}

// Retourne le nom du choix
string choice_name(int choice) {
    switch (choice) {
        case 1: return "Pierre";
        case 2: return "Feuille";
        case 3: return "Ciseaux";
        default: return "???";
    }
}

// 0 = egalite, 1 = joueur gagne, -1 = ordi gagne
int determine_winner(int player, int computer) {
    if (player == computer) return 0;

    // Pierre (1) bat Ciseaux (3)
    // Feuille (2) bat Pierre (1)
    // Ciseaux (3) bat Feuille (2)
    if ((player == 1 && computer == 3) ||
        (player == 2 && computer == 1) ||
        (player == 3 && computer == 2)) {
        return 1;
    }
    return -1;
}

// Affiche le score
void print_scoreboard(int p_score, int c_score, int target) {
    cout << "  [Toi " << p_score << " - " << c_score << " Ordi]"
         << "  (objectif: " << target << ")" << endl;
}
