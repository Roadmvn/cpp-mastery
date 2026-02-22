// ============================================
// Pattern Template - Tries (Prefix Trees)
// ============================================
// Ce fichier regroupe les templates complets
// pour implementer et utiliser un Trie.
//
// Compile : g++ -std=c++17 pattern-template.cpp -o pattern

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// ==============================================
// TEMPLATE 1 : TrieNode avec tableau fixe
// Pour alphabet de 26 lettres minuscules (a-z)
// Insert  : O(L) | Search  : O(L) | StartsWith : O(L)
// L = longueur du mot
// ==============================================
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;

    TrieNode() : isEnd(false) {
        fill(children, children + 26, nullptr);
    }
};

struct Trie {
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // Inserer un mot dans le trie
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

    // Verifier si un mot est dans le trie (exact)
    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }

    // Verifier si un prefixe existe dans le trie
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return true; // pas besoin de verifier isEnd
    }
};

// ==============================================
// TEMPLATE 2 : TrieNode avec unordered_map
// Pour alphabet quelconque (Unicode, chiffres, etc.)
// Plus flexible, mais plus de memoire et latence
// ==============================================
struct TrieNodeMap {
    unordered_map<char, TrieNodeMap*> children;
    bool isEnd = false;
};

struct TrieMap {
    TrieNodeMap* root;

    TrieMap() {
        root = new TrieNodeMap();
    }

    void insert(const string& word) {
        TrieNodeMap* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNodeMap();
            }
            node = node->children[c];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        TrieNodeMap* node = root;
        for (char c : word) {
            if (!node->children.count(c)) return false;
            node = node->children[c];
        }
        return node->isEnd;
    }

    bool startsWith(const string& prefix) {
        TrieNodeMap* node = root;
        for (char c : prefix) {
            if (!node->children.count(c)) return false;
            node = node->children[c];
        }
        return true;
    }
};

// ==============================================
// TEMPLATE 3 : Trie avec wildcard '.' (DFS)
// Utile pour LeetCode #211 (Design Add Search Words)
// '.' peut matcher n'importe quel caractere
// ==============================================
struct TrieWildcard {
    TrieNode* root;

    TrieWildcard() {
        root = new TrieNode();
    }

    void addWord(const string& word) {
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

    // DFS pour supporter le wildcard '.'
    bool searchHelper(TrieNode* node, const string& word, int pos) {
        if (pos == (int)word.size()) return node->isEnd;

        char c = word[pos];
        if (c == '.') {
            // Essayer tous les enfants possibles
            for (int i = 0; i < 26; i++) {
                if (node->children[i] && searchHelper(node->children[i], word, pos + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            return searchHelper(node->children[idx], word, pos + 1);
        }
    }

    bool search(const string& word) {
        return searchHelper(root, word, 0);
    }
};

// ==============================================
// TEMPLATE 4 : Compter les mots avec un prefixe
// Extension courante pour les problemes d'autocompletion
// ==============================================
struct TrieWithCount {
    struct NodeCount {
        NodeCount* children[26];
        int count = 0;  // nombre de mots passant par ce noeud
        bool isEnd = false;

        NodeCount() {
            fill(children, children + 26, nullptr);
        }
    };

    NodeCount* root;
    TrieWithCount() { root = new NodeCount(); }

    void insert(const string& word) {
        NodeCount* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new NodeCount();
            node = node->children[idx];
            node->count++;
        }
        node->isEnd = true;
    }

    // Combien de mots ont ce prefixe ?
    int countPrefix(const string& prefix) {
        NodeCount* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return 0;
            node = node->children[idx];
        }
        return node->count;
    }
};

// -----------------------------------------------
// Demonstration de tous les templates
// -----------------------------------------------
int main() {
    cout << "=== Trie Patterns ===" << endl;

    // Template 1 : Trie de base
    {
        cout << "\n[1] Trie de base (tableau 26 cases)" << endl;
        Trie trie;
        trie.insert("apple");
        trie.insert("app");
        trie.insert("banana");

        cout << "  search(\"apple\")     : " << (trie.search("apple") ? "true" : "false") << endl;
        cout << "  search(\"app\")       : " << (trie.search("app") ? "true" : "false") << endl;
        cout << "  search(\"ap\")        : " << (trie.search("ap") ? "true" : "false") << endl;
        cout << "  startsWith(\"app\")   : " << (trie.startsWith("app") ? "true" : "false") << endl;
        cout << "  startsWith(\"ban\")   : " << (trie.startsWith("ban") ? "true" : "false") << endl;
        cout << "  startsWith(\"xyz\")   : " << (trie.startsWith("xyz") ? "true" : "false") << endl;
    }

    // Template 2 : Trie avec map
    {
        cout << "\n[2] Trie avec unordered_map (alphabet quelconque)" << endl;
        TrieMap trieMap;
        trieMap.insert("hello");
        trieMap.insert("world");

        cout << "  search(\"hello\")  : " << (trieMap.search("hello") ? "true" : "false") << endl;
        cout << "  search(\"hell\")   : " << (trieMap.search("hell") ? "true" : "false") << endl;
        cout << "  startsWith(\"hel\"): " << (trieMap.startsWith("hel") ? "true" : "false") << endl;
    }

    // Template 3 : Wildcard '.'
    {
        cout << "\n[3] Trie avec wildcard '.'" << endl;
        TrieWildcard tw;
        tw.addWord("bad");
        tw.addWord("dad");
        tw.addWord("mad");

        cout << "  search(\"pad\") : " << (tw.search("pad") ? "true" : "false") << endl;  // false
        cout << "  search(\"bad\") : " << (tw.search("bad") ? "true" : "false") << endl;  // true
        cout << "  search(\".ad\") : " << (tw.search(".ad") ? "true" : "false") << endl;  // true
        cout << "  search(\"b..\") : " << (tw.search("b..") ? "true" : "false") << endl;  // true
    }

    // Template 4 : Comptage de prefixes
    {
        cout << "\n[4] Trie avec comptage de prefixes" << endl;
        TrieWithCount tc;
        tc.insert("apple");
        tc.insert("app");
        tc.insert("application");
        tc.insert("apply");
        tc.insert("banana");

        cout << "  countPrefix(\"app\")  : " << tc.countPrefix("app") << endl;   // 4
        cout << "  countPrefix(\"appl\") : " << tc.countPrefix("appl") << endl;  // 3
        cout << "  countPrefix(\"ban\")  : " << tc.countPrefix("ban") << endl;   // 1
        cout << "  countPrefix(\"xyz\")  : " << tc.countPrefix("xyz") << endl;   // 0
    }

    return 0;
}
