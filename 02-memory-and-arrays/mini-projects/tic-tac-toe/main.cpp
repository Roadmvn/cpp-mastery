// ============================================================
// Mini-projet : Morpion (Tic-Tac-Toe)
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o tictactoe main.cpp && ./tictactoe
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// Plateau 3x3 : ' ' = vide, 'X' ou 'O' = joue
char board[3][3];

// Initialise le plateau avec des cases vides
void resetBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Affiche le plateau avec les numeros de cases pour guide
void displayBoard() {
    // Guide des numeros a gauche
    cout << "\n";
    cout << "  Plateau        Guide" << endl;
    cout << "  -------        -----" << endl;

    for (int i = 0; i < 3; i++) {
        // Ligne du plateau
        cout << "   " << board[i][0] << " | " << board[i][1] << " | " << board[i][2];
        // Guide numerote
        cout << "       " << (i * 3 + 1) << " | " << (i * 3 + 2) << " | " << (i * 3 + 3);
        cout << endl;

        if (i < 2) {
            cout << "  ---+---+---    ---+---+---" << endl;
        }
    }
    cout << endl;
}

// Verifie si le joueur 'player' a gagne
bool checkWin(char player) {
    // Lignes
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    // Colonnes
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;
    }
    // Diagonale principale
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    // Diagonale anti-principale
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

// Verifie si le plateau est plein (match nul)
bool isBoardFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return false;
    return true;
}

// Joue un coup : case 1-9 -> ligne/colonne
// Retourne true si le coup est valide
bool makeMove(int cell, char player) {
    if (cell < 1 || cell > 9) return false;
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    if (board[row][col] != ' ') return false;
    board[row][col] = player;
    return true;
}

// Demande et valide un coup pour le joueur
int askMove(const string& playerName, char symbol) {
    int cell = 0;
    while (true) {
        cout << playerName << " (" << symbol << "), choisissez une case (1-9) : ";
        if (!(cin >> cell)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Saisie invalide." << endl;
            continue;
        }
        if (cell < 1 || cell > 9) {
            cout << "Case invalide. Entrez un nombre entre 1 et 9." << endl;
            continue;
        }
        int row = (cell - 1) / 3;
        int col = (cell - 1) % 3;
        if (board[row][col] != ' ') {
            cout << "Cette case est deja occupee. Choisissez-en une autre." << endl;
            continue;
        }
        break;
    }
    return cell;
}

// Lance une partie complete
void playGame() {
    resetBoard();

    string players[2] = { "Joueur 1", "Joueur 2" };
    char   symbols[2] = { 'X', 'O' };
    int    scores[2]  = { 0, 0 };
    int    games_played = 0;

    cout << "\n=============================" << endl;
    cout << "  MORPION - 2 joueurs" << endl;
    cout << "=============================" << endl;
    cout << "Joueur 1 = X | Joueur 2 = O" << endl;

    char again = 'o';
    while (again == 'o' || again == 'O') {
        resetBoard();
        games_played++;
        int turn = 0; // 0 = joueur 1, 1 = joueur 2

        cout << "\n--- Partie " << games_played << " ---" << endl;

        while (true) {
            displayBoard();

            int cell = askMove(players[turn], symbols[turn]);
            makeMove(cell, symbols[turn]);

            if (checkWin(symbols[turn])) {
                displayBoard();
                cout << "*** " << players[turn] << " (" << symbols[turn] << ") a gagne ! ***" << endl;
                scores[turn]++;
                break;
            }

            if (isBoardFull()) {
                displayBoard();
                cout << "*** Match nul ! ***" << endl;
                break;
            }

            // Alterner les joueurs
            turn = 1 - turn;
        }

        cout << "\nScore : " << players[0] << "=" << scores[0]
             << "  " << players[1] << "=" << scores[1] << endl;

        cout << "Rejouer ? (o/n) : ";
        cin >> again;
        cin.ignore(1000, '\n');
    }

    cout << "\n=============================" << endl;
    cout << "  Score final" << endl;
    cout << "=============================" << endl;
    cout << players[0] << " (X) : " << scores[0] << " victoire(s)" << endl;
    cout << players[1] << " (O) : " << scores[1] << " victoire(s)" << endl;
    if (scores[0] > scores[1])
        cout << "Grand vainqueur : " << players[0] << " !" << endl;
    else if (scores[1] > scores[0])
        cout << "Grand vainqueur : " << players[1] << " !" << endl;
    else
        cout << "Egalite parfaite !" << endl;
}

int main() {
    playGame();
    return 0;
}
