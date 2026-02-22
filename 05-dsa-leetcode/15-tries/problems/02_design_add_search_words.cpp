// ============================================
// LeetCode #211 - Design Add and Search Words Data Structure (Medium)
// https://leetcode.com/problems/design-add-and-search-words-data-structure/
// ============================================
// Enonce : Implementer une structure WordDictionary avec :
//   - addWord(word)    : ajouter le mot
//   - search(word)    : true si un mot matche. Le mot peut contenir '.'
//                       qui correspond a n'importe quelle lettre.
//
// Exemple :
//   addWord("bad"), addWord("dad"), addWord("mad")
//   search("pad")  false
//   search("bad")  true
//   search(".ad")  true  (bad, dad ou mad)
//   search("b..")  true  (bad)
//
// Compile : g++ -std=c++17 02_design_add_search_words.cpp -o 02

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : stocker tous les mots et matcher
// O(n * L) pour search sans wildcard
// O(n * L) pour search avec wildcard (regex-like)
// -----------------------------------------------
class WordDictionaryBrute {
    vector<string> words;

    bool matches(const string& pattern, const string& word) {
        if (pattern.size() != word.size()) return false;
        for (int i = 0; i < (int)pattern.size(); i++) {
            if (pattern[i] != '.' && pattern[i] != word[i]) return false;
        }
        return true;
    }

public:
    void addWord(const string& word) {
        words.push_back(word);
    }

    bool search(const string& word) {
        for (const string& w : words) {
            if (matches(word, w)) return true;
        }
        return false;
    }
};

// -----------------------------------------------
// OPTIMAL : Trie + DFS pour les wildcards '.'
//
// Schema ASCII :
//
//   Mots inseres : "bad", "dad", "mad"
//
//         ROOT
//        / | \
//      [b][d][m]
//       |  |  |
//      [a][a][a]
//       |  |  |
//      [d]*[d]*[d]*
//
//   search(".ad") :
//   pos=0, c='.', tester tous les enfants de ROOT
//     Essayer [b] : pos=1, c='a'  [a] existe
//       pos=2, c='d'  [d] existe, isEnd=true  TROUVE !
//
//   search("b..") :
//   pos=0, c='b'  [b] existe
//   pos=1, c='.'  tester tous les enfants de [b]
//     Essayer [a] : pos=2, c='.'  tester tous enfants de [a]
//       Essayer [d] : isEnd=true  TROUVE !
// -----------------------------------------------
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;

    TrieNode() : isEnd(false) {
        fill(children, children + 26, nullptr);
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++) delete children[i];
    }
};

class WordDictionaryOptimal {
    TrieNode* root;

    bool dfs(TrieNode* node, const string& word, int pos) {
        if (pos == (int)word.size()) return node->isEnd;

        char c = word[pos];
        if (c == '.') {
            // Tenter tous les enfants existants
            for (int i = 0; i < 26; i++) {
                if (node->children[i] && dfs(node->children[i], word, pos + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            return dfs(node->children[idx], word, pos + 1);
        }
    }

public:
    WordDictionaryOptimal() {
        root = new TrieNode();
    }

    ~WordDictionaryOptimal() {
        delete root;
    }

    void addWord(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        return dfs(root, word, 0);
    }
};

int main() {
    cout << "=== LeetCode #211 - Design Add and Search Words ===" << endl;

    cout << "\n-- Brute Force --" << endl;
    {
        WordDictionaryBrute wd;
        wd.addWord("bad");
        wd.addWord("dad");
        wd.addWord("mad");
        cout << "Apres addWord(\"bad\"), addWord(\"dad\"), addWord(\"mad\")" << endl;
        cout << "search(\"pad\") : " << (wd.search("pad") ? "true" : "false") << endl; // false
        cout << "search(\"bad\") : " << (wd.search("bad") ? "true" : "false") << endl; // true
        cout << "search(\".ad\") : " << (wd.search(".ad") ? "true" : "false") << endl; // true
        cout << "search(\"b..\") : " << (wd.search("b..") ? "true" : "false") << endl; // true
    }

    cout << "\n-- Optimal (Trie + DFS) --" << endl;
    {
        WordDictionaryOptimal wd;
        wd.addWord("bad");
        wd.addWord("dad");
        wd.addWord("mad");
        cout << "Apres addWord(\"bad\"), addWord(\"dad\"), addWord(\"mad\")" << endl;
        cout << "search(\"pad\") : " << (wd.search("pad") ? "true" : "false") << endl; // false
        cout << "search(\"bad\") : " << (wd.search("bad") ? "true" : "false") << endl; // true
        cout << "search(\".ad\") : " << (wd.search(".ad") ? "true" : "false") << endl; // true
        cout << "search(\"b..\") : " << (wd.search("b..") ? "true" : "false") << endl; // true
        cout << "search(\"...\") : " << (wd.search("...") ? "true" : "false") << endl; // true
        cout << "search(\"....\") : " << (wd.search("....") ? "true" : "false") << endl; // false
    }

    cout << "\nComplexite Brute  : O(n*L) search | O(n*L) espace" << endl;
    cout << "Complexite Optimal: O(L) sans wildcard | O(26^L) pire cas wildcard" << endl;

    return 0;
}
