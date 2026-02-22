/*
 * ============================================
 *  LeetCode #79 - Word Search (Medium) 🔙
 * ============================================
 *  Lien : https://leetcode.com/problems/word-search/
 *
 *  Enonce :
 *  Etant donne une grille m x n de caracteres et un mot,
 *  retourner true si le mot peut etre construit a partir
 *  de lettres adjacentes (horizontalement ou verticalement).
 *  Chaque cellule ne peut etre utilisee qu'une seule fois.
 *
 *  Exemple :
 *  Input:  board = [["A","B","C","E"],
 *                   ["S","F","C","S"],
 *                   ["A","D","E","E"]], word = "ABCCED"
 *  Output: true
 *
 *  Contraintes :
 *  - m,n : 1..6
 *  - word.length : 1..15
 * ============================================
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * ─── BRUTE FORCE : DFS sans optimisation ─────────
 *
 * Pour chaque cellule de la grille, lancer un DFS.
 * Pas de pruning : on explore toutes les directions
 * meme si le caractere ne correspond pas (on verifie apres).
 *
 *  Grille :
 *  A B C E
 *  S F C S
 *  A D E E
 *
 *  Recherche "ABCCED" :
 *  A → B → C → C → E → D ✓
 *       ↓   ↓   ↓   ↓
 *     droite bas bas gauche
 *
 * Complexite :
 *  - Temps  : O(m * n * 4^L) - L = longueur du mot
 *  - Espace : O(L) - profondeur recursion
 */
class BruteForce {
public:
    int rows, cols;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    bool dfs(vector<vector<char>>& board, string& word, int r, int c, int idx) {
        if (idx == (int)word.size()) return true;
        if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
        if (board[r][c] != word[idx]) return false;

        char temp = board[r][c];
        board[r][c] = '#'; // marquer visite

        for (int d = 0; d < 4; d++) {
            if (dfs(board, word, r + dx[d], c + dy[d], idx + 1)) {
                board[r][c] = temp;
                return true;
            }
        }

        board[r][c] = temp; // backtrack
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size();
        cols = board[0].size();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (dfs(board, word, i, j, 0)) return true;
            }
        }
        return false;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Backtracking + pruning ──
 *
 * Optimisations :
 * 1. Verifier que le board contient tous les caracteres du mot
 * 2. Si le dernier caractere du mot est plus frequent que le premier,
 *    inverser le mot (commencer par le bout le plus rare)
 * 3. Early termination des que le caractere ne match pas
 *
 *  Pruning visuel :
 *
 *  Mot = "SEE"
 *  A B C E          On ne demarre le DFS que
 *  S F C S   →      depuis les cellules 'S'
 *  A D E E          (2 cellules au lieu de 12)
 *
 *  Depuis S(1,0) : S→? F≠E ✗
 *  Depuis S(1,3) : S→E(2,3)→E(2,2) ✓
 *
 * Complexite :
 *  - Temps  : O(m * n * 3^L) - 3 au lieu de 4 car on ne revient pas
 *  - Espace : O(L) - profondeur recursion
 */
class Optimal {
public:
    int rows, cols;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    bool dfs(vector<vector<char>>& board, string& word, int r, int c, int idx) {
        if (idx == (int)word.size()) return true;
        if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
        if (board[r][c] != word[idx]) return false;

        char temp = board[r][c];
        board[r][c] = '#';

        for (int d = 0; d < 4; d++) {
            if (dfs(board, word, r + dx[d], c + dy[d], idx + 1)) {
                board[r][c] = temp;
                return true;
            }
        }

        board[r][c] = temp;
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        rows = board.size();
        cols = board[0].size();

        // Pruning : compter les frequences
        int freq[128] = {};
        for (auto& row : board)
            for (char c : row) freq[(int)c]++;

        for (char c : word) {
            if (--freq[(int)c] < 0) return false; // caractere manquant
        }

        // Optimisation : inverser le mot si le dernier char est plus rare
        int firstCount = 0, lastCount = 0;
        for (auto& row : board)
            for (char c : row) {
                if (c == word[0]) firstCount++;
                if (c == word.back()) lastCount++;
            }
        if (firstCount > lastCount) {
            reverse(word.begin(), word.end());
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == word[0]) {
                    if (dfs(board, word, i, j, 0)) return true;
                }
            }
        }
        return false;
    }
};

int main() {
    // Test 1 : "ABCCED"
    vector<vector<char>> board1 = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    cout << "=== Test 1 : word = \"ABCCED\" ===" << endl;

    BruteForce bf;
    cout << "Brute Force : " << (bf.exist(board1, "ABCCED") ? "true" : "false") << endl;

    vector<vector<char>> board1b = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    Optimal opt;
    cout << "Optimal     : " << (opt.exist(board1b, "ABCCED") ? "true" : "false") << endl;
    cout << "Attendu     : true" << endl;

    // Test 2 : "SEE"
    vector<vector<char>> board2 = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    cout << "\n=== Test 2 : word = \"SEE\" ===" << endl;

    Optimal opt2;
    cout << "Optimal     : " << (opt2.exist(board2, "SEE") ? "true" : "false") << endl;
    cout << "Attendu     : true" << endl;

    // Test 3 : "ABCB"
    vector<vector<char>> board3 = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    cout << "\n=== Test 3 : word = \"ABCB\" ===" << endl;

    Optimal opt3;
    cout << "Optimal     : " << (opt3.exist(board3, "ABCB") ? "true" : "false") << endl;
    cout << "Attendu     : false" << endl;

    return 0;
}
