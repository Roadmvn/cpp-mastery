// ============================================
// LeetCode #720 - Longest Word in Dictionary (Medium)
// https://leetcode.com/problems/longest-word-in-dictionary/
// ============================================
// Enonce : Donne un tableau de strings words[], trouver le mot
// le plus long qui peut etre construit lettre par lettre par d'autres
// mots du tableau. Tous les prefixes du mot doivent etre dans le tableau.
// En cas d'egalite, retourner le mot lexicographiquement le plus petit.
//
// Exemple :
//   words=["w","wo","wor","worl","world"] → "world"
//   words=["a","banana","app","appl","ap","apply","apple"] → "apple"
//
// Compile : g++ -std=c++17 04_longest_word_dictionary.cpp -o 04

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n² * L) temps | O(n*L) espace
// Trier par longueur, puis pour chaque mot verifier
// si tous ses prefixes sont dans un set.
// -----------------------------------------------
string longestWordBrute(vector<string>& words) {
    // Trier : longueur croissante, puis lexicographique
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;
    });

    unordered_set<string> built = {""};
    string best = "";

    for (const string& word : words) {
        string prefix = word.substr(0, word.size() - 1);
        if (built.count(prefix)) {
            built.insert(word);
            if (word.size() > best.size() ||
               (word.size() == best.size() && word < best)) {
                best = word;
            }
        }
    }
    return best;
}

// -----------------------------------------------
// OPTIMAL : Trie + BFS/DFS
// O(n*L) temps | O(n*L) espace
//
// Principe :
//   1. Inserer tous les mots dans le Trie.
//   2. Un mot peut etre construit lettre par lettre si et seulement si
//      chaque prefixe est lui-meme un mot (noeud avec isEnd=true).
//   3. Parcourir le Trie en profondeur en ne suivant que les noeuds isEnd.
//      Le chemin le plus long donne la reponse.
//
// Schema ASCII :
//
//   words = ["a","app","ap","appl","apple"]
//
//   Trie (apres insertion) :
//   ROOT
//   └── [a]* ← "a"
//       └── [p]* ← "ap"
//           └── [p]* ← "app"
//               └── [l]* ← "appl"
//                   └── [e]* ← "apple"  ← chemin valide le plus long !
//
//   DFS depuis ROOT :
//   [a] : isEnd=true → explorer
//   [a][p] : isEnd=true → explorer
//   [a][p][p] : isEnd=true → explorer
//   [a][p][p][l] : isEnd=true → explorer
//   [a][p][p][l][e] : isEnd=true, longueur=5 → candidat !
// -----------------------------------------------
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;
    string word; // stocker le mot complet pour faciliter la reconstruction

    TrieNode() : isEnd(false), word("") {
        fill(children, children + 26, nullptr);
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++) delete children[i];
    }
};

string best_word; // variable globale pour le DFS

void dfs(TrieNode* node, const string& current) {
    if (current.size() > best_word.size() ||
       (current.size() == best_word.size() && current < best_word)) {
        best_word = current;
    }

    for (int i = 0; i < 26; i++) {
        TrieNode* child = node->children[i];
        // Ne suivre que les noeuds marques comme fin de mot
        if (child && child->isEnd) {
            dfs(child, child->word);
        }
    }
}

string longestWordOptimal(vector<string>& words) {
    TrieNode* root = new TrieNode();

    // Inserer tous les mots
    for (const string& word : words) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
        node->word = word;
    }

    best_word = "";
    dfs(root, "");

    delete root;
    return best_word;
}

int main() {
    cout << "=== LeetCode #720 - Longest Word in Dictionary ===" << endl;

    // Test 1 : construction lettre par lettre
    {
        vector<string> words = {"w", "wo", "wor", "worl", "world"};
        cout << "words=[\"w\",\"wo\",\"wor\",\"worl\",\"world\"]" << endl;
        cout << "Brute  : \"" << longestWordBrute(words) << "\"" << endl;
        cout << "Optimal: \"" << longestWordOptimal(words) << "\"" << endl;
        // Attendu : "world"
        cout << endl;
    }

    // Test 2 : tie-breaker lexicographique
    {
        vector<string> words = {"a", "banana", "app", "appl", "ap", "apply", "apple"};
        cout << "words=[\"a\",\"banana\",\"app\",\"appl\",\"ap\",\"apply\",\"apple\"]" << endl;
        cout << "Brute  : \"" << longestWordBrute(words) << "\"" << endl;
        cout << "Optimal: \"" << longestWordOptimal(words) << "\"" << endl;
        // Attendu : "apple"
        cout << endl;
    }

    // Test 3 : prefixe manquant
    {
        vector<string> words = {"ab", "abc", "abcd", "b", "bc"};
        cout << "words=[\"ab\",\"abc\",\"abcd\",\"b\",\"bc\"]" << endl;
        cout << "Brute  : \"" << longestWordBrute(words) << "\"" << endl;
        cout << "Optimal: \"" << longestWordOptimal(words) << "\"" << endl;
        // "abcd" n'est pas valide car "a" est absent
        // "bc" : "b" present → valide (longueur 2), vs "b" (longueur 1)
        // Attendu : "bc"
        cout << endl;
    }

    cout << "Complexite Brute  : O(n^2 * L) temps | O(n*L) espace" << endl;
    cout << "Complexite Optimal: O(n * L)   temps | O(n*L) espace" << endl;

    return 0;
}
