// LeetCode #721 -- Accounts Merge
// https://leetcode.com/problems/accounts-merge/
// Difficulte : Medium
//
// Enonce :
//   On te donne une liste de comptes. Chaque compte est une liste de strings :
//   le premier element est le nom, les suivants sont des emails.
//   Deux comptes appartiennent a la meme personne s'ils partagent au moins un email.
//   Fusionne les comptes. Dans la sortie, le premier element est le nom,
//   suivi de tous les emails tries dans l'ordre lexicographique.
//
// Exemple :
//   accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],
//                ["John","johnsmith@mail.com","john00@mail.com"],
//                ["Mary","mary@mail.com"],
//                ["John","johnnybravo@mail.com"]]
//   ->  [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
//         ["Mary","mary@mail.com"],
//         ["John","johnnybravo@mail.com"]]

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

// ============================================================
//  BRUTE FORCE : O(n^2 * k) -- comparer chaque paire de comptes
//  et fusionner iterativement via set_intersection.
// ============================================================

// vector<vector<string>> accountsMerge_brute(vector<vector<string>>& accounts) {
//     int n = accounts.size();
//     vector<bool> merged(n, false);
//     vector<vector<string>> result;
//
//     for (int i = 0; i < n; i++) {
//         if (merged[i]) continue;
//         set<string> emails(accounts[i].begin() + 1, accounts[i].end());
//         bool changed = true;
//         while (changed) {
//             changed = false;
//             for (int j = 0; j < n; j++) {
//                 if (merged[j] || j == i) continue;
//                 for (int k = 1; k < (int)accounts[j].size(); k++) {
//                     if (emails.count(accounts[j][k])) {
//                         emails.insert(accounts[j].begin() + 1, accounts[j].end());
//                         merged[j] = true;
//                         changed = true;
//                         break;
//                     }
//                 }
//             }
//         }
//         vector<string> acc = {accounts[i][0]};
//         acc.insert(acc.end(), emails.begin(), emails.end());
//         result.push_back(acc);
//     }
//     return result;
// }

// ============================================================
//  SOLUTION OPTIMALE : Union-Find sur les emails -- O(nk log(nk))
//
//  Chaque email est un noeud. Pour chaque compte, on unit tous
//  ses emails avec le premier email du compte (representant).
//  Ensuite, on regroupe les emails par racine Union-Find,
//  on trie, et on reconstruit les comptes.
//
//  Complexite : O(nk * alpha(nk) + nk log(nk)) temps, O(nk) espace
//  n = nombre de comptes, k = emails max par compte
// ============================================================

class UnionFind {
    unordered_map<string, string> parent;
public:
    string find(const string& x) {
        if (parent.find(x) == parent.end()) parent[x] = x;
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(const string& x, const string& y) {
        string rx = find(x), ry = find(y);
        if (rx != ry) parent[rx] = ry;
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        UnionFind uf;
        unordered_map<string, string> emailToName;

        // Etape 1 : unir tous les emails d'un meme compte
        for (auto& acc : accounts) {
            const string& name = acc[0];
            for (int i = 1; i < (int)acc.size(); i++) {
                emailToName[acc[i]] = name;
                uf.unite(acc[1], acc[i]);  // on unit avec le premier email
            }
        }

        // Etape 2 : regrouper les emails par racine
        unordered_map<string, vector<string>> groups;
        for (auto& [email, name] : emailToName)
            groups[uf.find(email)].push_back(email);

        // Etape 3 : construire la sortie
        vector<vector<string>> result;
        for (auto& [root, emails] : groups) {
            sort(emails.begin(), emails.end());
            vector<string> acc = {emailToName[root]};
            acc.insert(acc.end(), emails.begin(), emails.end());
            result.push_back(acc);
        }
        return result;
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    Solution sol;

    vector<vector<string>> accounts = {
        {"John","johnsmith@mail.com","john_newyork@mail.com"},
        {"John","johnsmith@mail.com","john00@mail.com"},
        {"Mary","mary@mail.com"},
        {"John","johnnybravo@mail.com"}
    };

    auto result = sol.accountsMerge(accounts);

    for (auto& acc : result) {
        for (int i = 0; i < (int)acc.size(); i++) {
            if (i > 0) cout << ",";
            cout << acc[i];
        }
        cout << "\n";
    }
    // attendu (ordre peut varier entre comptes) :
    // John,john00@mail.com,john_newyork@mail.com,johnsmith@mail.com
    // Mary,mary@mail.com
    // John,johnnybravo@mail.com

    return 0;
}
