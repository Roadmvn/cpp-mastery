// ============================================
// LeetCode #212 - Word Search II (Hard)
// https://leetcode.com/problems/word-search-ii/
// ============================================
// Enonce : Donne une grille de caracteres board et une liste de mots words,
// retourner tous les mots qui peuvent etre formes dans la grille.
// On peut aller dans les 4 directions, chaque cellule utilisable une seule fois.
//
// Exemple :
//   board = [["o","a","a","n"],
//            ["e","t","a","e"],
//            ["i","h","k","r"],
//            ["i","f","l","v"]]
//   words = ["oath","pea","eat","rain"]
//   Output: ["eat","oath"]
//
// Compile : g++ -std=c++17 03_word_search_ii.cpp -o 03

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(M*N * 4^L * W) temps
// Pour chaque mot, faire un DFS complet depuis chaque cellule.
// M,N = dimensions grille, L = longueur max mot, W = nb mots
// -----------------------------------------------
bool dfsBrute(vector<vector<char>>& board, const string& word, int r, int c, int pos) {
    if (pos == (int)word.size()) return true;
    if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[0].size()) return false;
    if (board[r][c] != word[pos]) return false;

    char temp = board[r][c];
    board[r][c] = '#'; // marquer comme visite

    bool found = dfsBrute(board, word, r + 1, c, pos + 1) ||
                 dfsBrute(board, word, r - 1, c, pos + 1) ||
                 dfsBrute(board, word, r, c + 1, pos + 1) ||
                 dfsBrute(board, word, r, c - 1, pos + 1);

    board[r][c] = temp; // restaurer
    return found;
}

vector<string> findWordsBrute(vector<vector<char>>& board, vector<string>& words) {
    int rows = board.size(), cols = board[0].size();
    unordered_set<string> result;

    for (const string& word : words) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (dfsBrute(board, word, r, c, 0)) {
                    result.insert(word);
                    break;
                }
            }
        }
    }
    return vector<string>(result.begin(), result.end());
}

// -----------------------------------------------
// OPTIMAL : Trie + DFS sur la grille
// O(M*N * 4^L) temps | O(W*L) espace (pour le trie)
//
// Principe :
//   1. Construire un Trie avec tous les mots du dictionnaire.
//   2. DFS depuis chaque cellule : avancer dans le Trie en meme temps.
//   3. Si on arrive sur un noeud isEnd : le mot est trouve.
//   4. Optimisation : supprimer les feuilles du Trie une fois le mot trouve
//      (evite de chercher deux fois le meme mot).
//
// Schema ASCII :
//
//   words = ["eat", "oath"]
//   Trie :
//     ROOT
//     ├── [e]
//     │   └── [a]
//     │       └── [t]*   ← "eat"
//     └── [o]
//         └── [a]
//             └── [t]
//                 └── [h]*  ← "oath"
//
//   DFS depuis board[1][0]='e' :
//   'e' → noeud [e] dans trie
//     voisin (1,1)='t' → pas dans enfants de [e]
//     voisin (0,0)='o' → pas dans enfants de [e]
//     voisin (1,2)='a' → dans enfants de [e] !
//       'a' → noeud [a]
//         voisin (1,3)='e' → pas dans enfants de [a]
//         voisin (0,2)='a' → pas dans enfants de [a]
//         voisin (2,2)='k' → pas dans enfants de [a]
//         voisin (1,1)='t' → dans enfants de [a] !
//           't' → noeud [t], isEnd=true → "eat" TROUVE !
// -----------------------------------------------
struct TrieNode {
    TrieNode* children[26];
    string word; // stocker le mot entier si c'est une fin

    TrieNode() : word("") {
        fill(children, children + 26, nullptr);
    }
};

void insertTrie(TrieNode* root, const string& word) {
    TrieNode* node = root;
    for (char c : word) {
        int idx = c - 'a';
        if (!node->children[idx]) node->children[idx] = new TrieNode();
        node = node->children[idx];
    }
    node->word = word; // stocker le mot complet
}

void dfsOptimal(vector<vector<char>>& board, int r, int c,
                TrieNode* node, vector<string>& result) {
    if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[0].size()) return;

    char ch = board[r][c];
    if (ch == '#') return; // deja visite

    int idx = ch - 'a';
    if (!node->children[idx]) return; // pas dans le trie

    TrieNode* next = node->children[idx];

    if (!next->word.empty()) {
        result.push_back(next->word);
        next->word = ""; // eviter les doublons
    }

    board[r][c] = '#'; // marquer visite
    dfsOptimal(board, r + 1, c, next, result);
    dfsOptimal(board, r - 1, c, next, result);
    dfsOptimal(board, r, c + 1, next, result);
    dfsOptimal(board, r, c - 1, next, result);
    board[r][c] = ch; // restaurer
}

vector<string> findWordsOptimal(vector<vector<char>>& board, vector<string>& words) {
    TrieNode* root = new TrieNode();
    for (const string& w : words) insertTrie(root, w);

    int rows = board.size(), cols = board[0].size();
    vector<string> result;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            dfsOptimal(board, r, c, root, result);
        }
    }
    return result;
}

void printWords(const vector<string>& words, const string& label) {
    cout << label << " [";
    for (int i = 0; i < (int)words.size(); i++) {
        cout << "\"" << words[i] << "\"";
        if (i + 1 < (int)words.size()) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== LeetCode #212 - Word Search II ===" << endl;

    // Test 1 : exemple classique
    {
        vector<vector<char>> board = {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
        };
        vector<string> words = {"oath", "pea", "eat", "rain"};
        cout << "words=[\"oath\",\"pea\",\"eat\",\"rain\"]" << endl;

        // Copie pour brute force (modifie la grille)
        auto boardCopy = board;
        auto brute = findWordsBrute(boardCopy, words);
        sort(brute.begin(), brute.end());
        printWords(brute, "Brute  :");

        auto optimal = findWordsOptimal(board, words);
        sort(optimal.begin(), optimal.end());
        printWords(optimal, "Optimal:");
        // Attendu : ["eat","oath"]
        cout << endl;
    }

    // Test 2 : un seul mot
    {
        vector<vector<char>> board = {{'a','b'},{'c','d'}};
        vector<string> words = {"ab", "cd", "ca", "bd"};
        cout << "board=[[a,b],[c,d]], words=[\"ab\",\"cd\",\"ca\",\"bd\"]" << endl;

        auto boardCopy = board;
        auto brute = findWordsBrute(boardCopy, words);
        sort(brute.begin(), brute.end());
        printWords(brute, "Brute  :");

        auto optimal = findWordsOptimal(board, words);
        sort(optimal.begin(), optimal.end());
        printWords(optimal, "Optimal:");
        cout << endl;
    }

    cout << "Complexite Brute  : O(M*N * 4^L * W) temps" << endl;
    cout << "Complexite Optimal: O(M*N * 4^L)     temps | O(W*L) espace (trie)" << endl;

    return 0;
}
