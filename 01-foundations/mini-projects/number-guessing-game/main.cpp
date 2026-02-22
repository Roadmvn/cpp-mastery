// ============================================================
// MINI-PROJET : Jeu de Devinette (1-100)
// Compile : g++ -std=c++17 -o guessing-game main.cpp
// ============================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Evalue la performance du joueur
string evaluate_score(int attempts) {
    if (attempts <= 3)  return "Incroyable ! Tu lis dans les pensees.";
    if (attempts <= 5)  return "Excellent ! Tres bon instinct.";
    if (attempts <= 7)  return "Bien joue ! Strategie solide.";
    if (attempts <= 10) return "Pas mal. Tu peux faire mieux.";
    return "Hmm... essaie la recherche dichotomique !";
}

int main() {
    srand(time(0));
    char rejouer;

    cout << "========================================" << endl;
    cout << "  Jeu de Devinette" << endl;
    cout << "========================================" << endl;

    do {
        int secret = rand() % 100 + 1;  // 1 a 100
        int guess;
        int attempts = 0;
        int min_range = 1;
        int max_range = 100;

        cout << "\nJ'ai choisi un nombre entre 1 et 100." << endl;
        cout << "A toi de deviner !" << endl;

        do {
            cout << "\n[" << min_range << "-" << max_range << "] Ta proposition : ";
            cin >> guess;

            if (guess < 1 || guess > 100) {
                cout << "Hors limites ! Entre un nombre entre 1 et 100." << endl;
                continue;
            }

            attempts++;

            if (guess < secret) {
                cout << "Plus haut ! (" << guess << " est trop petit)" << endl;
                if (guess >= min_range) min_range = guess + 1;
            } else if (guess > secret) {
                cout << "Plus bas ! (" << guess << " est trop grand)" << endl;
                if (guess <= max_range) max_range = guess - 1;
            } else {
                cout << "\nBravo ! C'etait bien " << secret << " !" << endl;
                cout << "Trouve en " << attempts << " essai"
                     << (attempts > 1 ? "s" : "") << "." << endl;
                cout << evaluate_score(attempts) << endl;
            }

        } while (guess != secret);

        // Statistiques optimales
        cout << "\n(Info : en theorie, le minimum est ~7 essais" << endl;
        cout << " avec une recherche dichotomique pour 1-100)" << endl;

        cout << "\nRejouer ? (o/n) : ";
        cin >> rejouer;

    } while (rejouer == 'o' || rejouer == 'O');

    cout << "\nMerci d'avoir joue !" << endl;

    return 0;
}
