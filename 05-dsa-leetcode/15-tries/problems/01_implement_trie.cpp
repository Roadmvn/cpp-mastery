// ============================================
// LeetCode #208 - Implement Trie (Prefix Tree) (Medium)
// https://leetcode.com/problems/implement-trie-prefix-tree/
// ============================================
// Enonce : Implementer une structure de donnees Trie avec :
//   - insert(word)    : inserer le mot dans le trie
//   - search(word)    : true si le mot exact existe
//   - startsWith(prefix) : true si un mot avec ce prefixe existe
//
// Exemple :
//   trie.insert("apple")
//   trie.search("apple")    → true
//   trie.search("app")      → false
//   trie.startsWith("app")  → true
//   trie.insert("app")
//   trie.search("app")      → true
//
// Compile : g++ -std=c++17 01_implement_trie.cpp -o 01

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : Avec un vecteur de strings
// O(n*L) pour search et startsWith (n=nb mots, L=longueur)
// Correct mais tres inefficace pour un grand dictionnaire.
// -----------------------------------------------
class TrieBrute {
    vector<string> words;
public:
    void insert(const string& word) {
        words.push_back(word);
    }

    bool search(const string& word) {
        for (const string& w : words) {
            if (w == word) return true;
        }
        return false;
    }

    bool startsWith(const string& prefix) {
        for (const string& w : words) {
            if (w.substr(0, prefix.size()) == prefix) return true;
        }
        return false;
    }
};

// -----------------------------------------------
// OPTIMAL : Trie avec tableau de 26 enfants
// O(L) insert, search, startsWith | O(SIGMA * N * L) espace
//
// Schema ASCII :
//
//   insert("apple"), insert("app"), insert("apply")
//
//          ROOT
//           |
//          [a]
//           |
//          [p]
//           |
//          [p]*  ← isEnd=true (mot "app")
//           |
//          [l]
//         /   \
//       [e]*   [y]*  ← isEnd=true ("apple" et "apply")
//
//   search("app")     → ROOT→a→p→p : isEnd=true → true
//   search("ap")      → ROOT→a→p   : isEnd=false → false
//   startsWith("appl")→ ROOT→a→p→p→l : existe → true
// -----------------------------------------------
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;

    TrieNode() : isEnd(false) {
        fill(children, children + 26, nullptr);
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            delete children[i];
        }
    }
};

class TrieOptimal {
    TrieNode* root;
public:
    TrieOptimal() {
        root = new TrieNode();
    }

    ~TrieOptimal() {
        delete root;
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEnd; // le mot doit finir exactement ici
    }

    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return true; // on ne verifie pas isEnd pour les prefixes
    }
};

int main() {
    cout << "=== LeetCode #208 - Implement Trie ===" << endl;

    cout << "\n-- Brute Force --" << endl;
    {
        TrieBrute trie;
        trie.insert("apple");
        cout << "insert(\"apple\")" << endl;
        cout << "search(\"apple\")    : " << (trie.search("apple") ? "true" : "false") << endl;    // true
        cout << "search(\"app\")      : " << (trie.search("app") ? "true" : "false") << endl;      // false
        cout << "startsWith(\"app\")  : " << (trie.startsWith("app") ? "true" : "false") << endl;  // true
        trie.insert("app");
        cout << "insert(\"app\")" << endl;
        cout << "search(\"app\")      : " << (trie.search("app") ? "true" : "false") << endl;      // true
    }

    cout << "\n-- Optimal (Trie structure) --" << endl;
    {
        TrieOptimal trie;
        trie.insert("apple");
        cout << "insert(\"apple\")" << endl;
        cout << "search(\"apple\")    : " << (trie.search("apple") ? "true" : "false") << endl;    // true
        cout << "search(\"app\")      : " << (trie.search("app") ? "true" : "false") << endl;      // false
        cout << "startsWith(\"app\")  : " << (trie.startsWith("app") ? "true" : "false") << endl;  // true
        trie.insert("app");
        cout << "insert(\"app\")" << endl;
        cout << "search(\"app\")      : " << (trie.search("app") ? "true" : "false") << endl;      // true
        cout << "startsWith(\"xyz\")  : " << (trie.startsWith("xyz") ? "true" : "false") << endl;  // false
    }

    cout << "\nComplexite Brute  : O(n*L) search/startsWith | O(n*L) espace" << endl;
    cout << "Complexite Optimal: O(L)   toutes operations  | O(SIGMA*N*L) espace" << endl;

    return 0;
}
