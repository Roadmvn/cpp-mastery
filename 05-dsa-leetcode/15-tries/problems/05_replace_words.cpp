// ============================================
// LeetCode #648 - Replace Words (Medium)
// https://leetcode.com/problems/replace-words/
// ============================================
// Enonce : Donne un dictionnaire de racines et une phrase,
// remplacer chaque mot de la phrase par la racine la plus courte
// qui le commence (prefixe). Si plusieurs racines matchent,
// utiliser la plus courte. Si aucune racine ne matche, garder le mot.
//
// Exemple :
//   dictionary=["cat","bat","rat"]
//   sentence="the cattle was rattled by the battery"
//   Output: "the cat was rat by the bat"
//
// Compile : g++ -std=c++17 05_replace_words.cpp -o 05

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <algorithm>
using namespace std;

// Utilitaire : decoupe une string en mots
vector<string> splitWords(const string& sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) words.push_back(word);
    return words;
}

// -----------------------------------------------
// BRUTE FORCE : O(W * D * L) temps | O(D*L) espace
// Pour chaque mot de la phrase, tester toutes les racines
// du dictionnaire et garder la plus courte qui matche.
// W = nb mots, D = taille dictionnaire, L = longueur max
// -----------------------------------------------
string replaceWordsBrute(vector<string>& dictionary, const string& sentence) {
    vector<string> words = splitWords(sentence);

    for (string& word : words) {
        string best = word; // par defaut, garder le mot original
        bool found = false;

        for (const string& root : dictionary) {
            if (word.substr(0, root.size()) == root) {
                if (!found || root.size() < best.size()) {
                    best = root;
                    found = true;
                }
            }
        }
        word = best;
    }

    // Reassembler la phrase
    string result = "";
    for (int i = 0; i < (int)words.size(); i++) {
        if (i > 0) result += " ";
        result += words[i];
    }
    return result;
}

// -----------------------------------------------
// OPTIMAL : Trie pour chercher le prefixe le plus court
// O((W*L + D*L)) temps | O(D*L) espace
//
// Principe :
//   1. Inserer toutes les racines dans le Trie.
//   2. Pour chaque mot, parcourir le Trie lettre par lettre.
//      Des qu'on rencontre un noeud isEnd=true, on a trouve
//      la racine la plus courte (car on avance lettre par lettre).
//
// Schema ASCII :
//
//   dictionary = ["cat", "bat", "rat"]
//
//   Trie :
//   ROOT
//   ├── [b]
//   │   └── [a]
//   │       └── [t]*   ← "bat"
//   ├── [c]
//   │   └── [a]
//   │       └── [t]*   ← "cat"
//   └── [r]
//       └── [a]
//           └── [t]*   ← "rat"
//
//   Mot "cattle" :
//   ROOT → [c] → [a] → [t]*  ← isEnd=true → retourner "cat" !
//   (on s'arrete des la premiere racine trouvee)
//
//   Mot "rattled" :
//   ROOT → [r] → [a] → [t]*  ← isEnd=true → retourner "rat" !
//
//   Mot "the" :
//   ROOT → pas de [t] → retourner "the" (inchange)
// -----------------------------------------------
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;
    string root; // stocker la racine complete

    TrieNode() : isEnd(false), root("") {
        fill(children, children + 26, nullptr);
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++) delete children[i];
    }
};

class TrieReplace {
    TrieNode* trieRoot;
public:
    TrieReplace() { trieRoot = new TrieNode(); }
    ~TrieReplace() { delete trieRoot; }

    void insertRoot(const string& word) {
        TrieNode* node = trieRoot;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
            if (node->isEnd) return; // racine encore plus courte existe deja
        }
        node->isEnd = true;
        node->root = word;
    }

    // Trouver la racine la plus courte qui matche le mot
    string findShortestRoot(const string& word) {
        TrieNode* node = trieRoot;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) break; // pas de racine qui matche
            node = node->children[idx];
            if (node->isEnd) return node->root; // racine trouvee !
        }
        return word; // aucune racine trouvee → retourner le mot original
    }
};

string replaceWordsOptimal(vector<string>& dictionary, const string& sentence) {
    TrieReplace trie;
    for (const string& root : dictionary) trie.insertRoot(root);

    vector<string> words = splitWords(sentence);
    for (string& word : words) {
        word = trie.findShortestRoot(word);
    }

    string result = "";
    for (int i = 0; i < (int)words.size(); i++) {
        if (i > 0) result += " ";
        result += words[i];
    }
    return result;
}

int main() {
    cout << "=== LeetCode #648 - Replace Words ===" << endl;

    // Test 1 : exemple classique
    {
        vector<string> dict = {"cat", "bat", "rat"};
        string sentence = "the cattle was rattled by the battery";
        cout << "dictionary: [\"cat\",\"bat\",\"rat\"]" << endl;
        cout << "sentence  : \"" << sentence << "\"" << endl;
        cout << "Brute  : \"" << replaceWordsBrute(dict, sentence) << "\"" << endl;
        cout << "Optimal: \"" << replaceWordsOptimal(dict, sentence) << "\"" << endl;
        // Attendu : "the cat was rat by the bat"
        cout << endl;
    }

    // Test 2 : racines multiples pour un mot (prendre la plus courte)
    {
        vector<string> dict = {"a", "aa", "aaa", "aaaa"};
        string sentence = "a aa aaa aaaa";
        cout << "dictionary: [\"a\",\"aa\",\"aaa\",\"aaaa\"]" << endl;
        cout << "sentence  : \"" << sentence << "\"" << endl;
        cout << "Optimal: \"" << replaceWordsOptimal(dict, sentence) << "\"" << endl;
        // Attendu : "a a a a" (racine "a" remplace tout)
        cout << endl;
    }

    // Test 3 : aucune racine ne matche
    {
        vector<string> dict = {"xyz"};
        string sentence = "the dog ate food";
        cout << "dictionary: [\"xyz\"]" << endl;
        cout << "sentence  : \"" << sentence << "\"" << endl;
        cout << "Optimal: \"" << replaceWordsOptimal(dict, sentence) << "\"" << endl;
        // Attendu : "the dog ate food" (inchange)
        cout << endl;
    }

    // Test 4 : mot qui est exactement une racine
    {
        vector<string> dict = {"cat", "bat"};
        string sentence = "cat concatenate batman battery";
        cout << "dictionary: [\"cat\",\"bat\"]" << endl;
        cout << "sentence  : \"" << sentence << "\"" << endl;
        cout << "Brute  : \"" << replaceWordsBrute(dict, sentence) << "\"" << endl;
        cout << "Optimal: \"" << replaceWordsOptimal(dict, sentence) << "\"" << endl;
        // Attendu : "cat cat bat bat"
        cout << endl;
    }

    cout << "Complexite Brute  : O(W * D * L) temps | O(D*L) espace" << endl;
    cout << "Complexite Optimal: O(W*L + D*L) temps | O(D*L) espace" << endl;

    return 0;
}
