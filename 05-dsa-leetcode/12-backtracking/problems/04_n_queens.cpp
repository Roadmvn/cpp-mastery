/*
 * ============================================
 *  LeetCode #51 - N-Queens (Hard) 🔙
 * ============================================
 *  Lien : https://leetcode.com/problems/n-queens/
 *
 *  Enonce :
 *  Placer n reines sur un echiquier n x n de sorte qu'aucune
 *  reine ne puisse en attaquer une autre (meme ligne, colonne, diagonale).
 *  Retourner toutes les configurations valides.
 *
 *  Exemple :
 *  Input:  n = 4
 *  Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 *
 *  Contraintes :
 *  - 1 <= n <= 9
 * ============================================
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * ─── BRUTE FORCE : Generer toutes les positions ──
 *
 * Placer une reine par ligne. Pour chaque placement,
 * verifier si la position est valide en scannant toutes
 * les reines deja placees.
 *
 *  Attaques d'une reine en (r,c) :
 *  . . X . X . .
 *  . . . X . . .      ↖ ↑ ↗
 *  X . . Q . . X       ← Q →    (ligne = meme r)
 *  . . . X . . .      ↙ ↓ ↘
 *  . . X . X . .
 *
 * Complexite :
 *  - Temps  : O(n! * n) - n! placements, O(n) verification
 *  - Espace : O(n^2) - echiquier
 */
class BruteForce {
public:
    vector<vector<string>> result;

    bool isValid(vector<string>& board, int row, int col, int n) {
        // Verifier la colonne au-dessus
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }
        // Diagonale haut-gauche
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }
        // Diagonale haut-droite
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }
        return true;
    }

    void backtrack(vector<string>& board, int row, int n) {
        if (row == n) {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col, n)) {
                board[row][col] = 'Q';
                backtrack(board, row + 1, n);
                board[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0, n);
        return result;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Sets pour O(1) validation ─
 *
 * Au lieu de scanner l'echiquier pour verifier les conflits,
 * on maintient 3 sets :
 *  - cols       : colonnes occupees
 *  - diag1      : diagonales ↘ (row - col = constante)
 *  - diag2      : diagonales ↗ (row + col = constante)
 *
 *  Visualisation des diagonales :
 *
 *  diag1 (row-col)     diag2 (row+col)
 *  0  -1  -2  -3       0   1   2   3
 *  1   0  -1  -2       1   2   3   4
 *  2   1   0  -1       2   3   4   5
 *  3   2   1   0       3   4   5   6
 *
 * Complexite :
 *  - Temps  : O(n!) - chaque ligne reduit les choix
 *  - Espace : O(n) - sets + recursion
 */
class Optimal {
public:
    vector<vector<string>> result;
    vector<bool> cols, diag1, diag2;

    void backtrack(vector<string>& board, int row, int n) {
        if (row == n) {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            int d1 = row - col + n; // decalage pour eviter indices negatifs
            int d2 = row + col;

            if (cols[col] || diag1[d1] || diag2[d2]) continue;

            cols[col] = diag1[d1] = diag2[d2] = true;
            board[row][col] = 'Q';

            backtrack(board, row + 1, n);

            board[row][col] = '.';
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        cols.assign(n, false);
        diag1.assign(2 * n, false);
        diag2.assign(2 * n, false);
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0, n);
        return result;
    }
};

void printBoards(vector<vector<string>>& boards) {
    cout << boards.size() << " solution(s) :" << endl;
    for (auto& board : boards) {
        for (auto& row : board) {
            cout << "  " << row << endl;
        }
        cout << endl;
    }
}

int main() {
    // Test 1 : n = 4
    cout << "=== Test 1 : n = 4 ===" << endl;

    BruteForce bf;
    auto r1 = bf.solveNQueens(4);
    cout << "Brute Force : ";
    printBoards(r1);

    Optimal opt;
    auto r2 = opt.solveNQueens(4);
    cout << "Optimal : ";
    printBoards(r2);

    // Test 2 : n = 1
    cout << "=== Test 2 : n = 1 ===" << endl;

    Optimal opt2;
    auto r3 = opt2.solveNQueens(1);
    cout << "Optimal : ";
    printBoards(r3);

    // Test 3 : n = 8 (nombre de solutions)
    cout << "=== Test 3 : n = 8 ===" << endl;
    Optimal opt3;
    auto r4 = opt3.solveNQueens(8);
    cout << "Nombre de solutions : " << r4.size() << endl;
    cout << "Attendu             : 92" << endl;

    return 0;
}
