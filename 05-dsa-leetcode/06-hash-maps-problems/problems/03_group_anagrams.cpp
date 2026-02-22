// ============================================
// LeetCode #49 - Group Anagrams (Medium)
// https://leetcode.com/problems/group-anagrams/
// ============================================
// Enonce : Donne un tableau de strings, grouper les anagrammes ensemble.
// Retourner les groupes dans n'importe quel ordre.
//
// Exemple :
//   Input : ["eat","tea","tan","ate","nat","bat"]
//   Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
//
// Compile : g++ -std=c++17 03_group_anagrams.cpp -o 03

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n² * K log K) temps | O(n*K) espace
// Comparer chaque paire de strings pour savoir
// si ce sont des anagrammes (en les triant).
// Marquer les strings deja groupees avec un visited[].
// K = longueur max d'une string
// -----------------------------------------------
vector<vector<string>> groupAnagramsBrute(vector<string>& strs) {
    int n = strs.size();
    vector<bool> visited(n, false);
    vector<vector<string>> result;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        vector<string> group = {strs[i]};
        visited[i] = true;

        string si = strs[i];
        sort(si.begin(), si.end());

        for (int j = i + 1; j < n; j++) {
            if (visited[j]) continue;
            string sj = strs[j];
            sort(sj.begin(), sj.end());
            if (si == sj) {
                group.push_back(strs[j]);
                visited[j] = true;
            }
        }
        result.push_back(group);
    }
    return result;
}

// -----------------------------------------------
// OPTIMAL : O(n * K log K) temps | O(n * K) espace
// HashMap : cle = version triee de la string
// Toutes les strings avec la meme cle sont des anagrammes.
//
// Schema ASCII :
//
//   Input : ["eat","tea","tan","ate","nat","bat"]
//
//   "eat"  sort  "aet"  ─┐
//   "tea"  sort  "aet"  ─┼─ groupe  ["eat","tea","ate"]
//   "ate"  sort  "aet"  ─┘
//
//   "tan"  sort  "ant"  ─┬─ groupe  ["tan","nat"]
//   "nat"  sort  "ant"  ─┘
//
//   "bat"  sort  "abt"  ───── groupe  ["bat"]
//
//   HashMap :
//   ┌──────┬──────────────────────────────┐
//   │ cle  │ valeur (groupe)              │
//   ├──────┼──────────────────────────────┤
//   │"aet" │ ["eat", "tea", "ate"]        │
//   │"ant" │ ["tan", "nat"]               │
//   │"abt" │ ["bat"]                      │
//   └──────┴──────────────────────────────┘
// -----------------------------------------------
vector<vector<string>> groupAnagramsOptimal(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    for (const string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& [key, group] : groups) {
        result.push_back(group);
    }
    return result;
}

// Variante ultra-optimale : O(n * K) avec signature de frequences
// Cle = tableau de 26 compteurs convertis en string
vector<vector<string>> groupAnagramsUltra(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;

    for (const string& s : strs) {
        int freq[26] = {};
        for (char c : s) freq[c - 'a']++;

        // Encoder le tableau de frequences comme cle unique
        string key = "";
        for (int i = 0; i < 26; i++) {
            key += '#';
            key += (char)freq[i];
        }
        groups[key].push_back(s);
    }

    vector<vector<string>> result;
    for (auto& [key, group] : groups) {
        result.push_back(group);
    }
    return result;
}

void printGroups(const vector<vector<string>>& groups, const string& label) {
    cout << label << " [" << endl;
    for (const auto& group : groups) {
        cout << "  [";
        for (int i = 0; i < (int)group.size(); i++) {
            cout << "\"" << group[i] << "\"";
            if (i + 1 < (int)group.size()) cout << ", ";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== LeetCode #49 - Group Anagrams ===" << endl;

    // Test 1 : exemple classique
    {
        vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
        cout << "Input : [\"eat\",\"tea\",\"tan\",\"ate\",\"nat\",\"bat\"]" << endl;
        auto brute   = groupAnagramsBrute(strs);
        auto optimal = groupAnagramsOptimal(strs);
        auto ultra   = groupAnagramsUltra(strs);
        printGroups(brute,   "Brute  :");
        printGroups(optimal, "Optimal:");
        printGroups(ultra,   "Ultra  :");
        cout << endl;
    }

    // Test 2 : un seul element
    {
        vector<string> strs = {"a"};
        cout << "Input : [\"a\"]" << endl;
        auto optimal = groupAnagramsOptimal(strs);
        printGroups(optimal, "Optimal:");
        // Attendu : [["a"]]
        cout << endl;
    }

    // Test 3 : strings vides
    {
        vector<string> strs = {"", ""};
        cout << "Input : [\"\",\"\"]" << endl;
        auto optimal = groupAnagramsOptimal(strs);
        printGroups(optimal, "Optimal:");
        // Attendu : [["",""]]
        cout << endl;
    }

    cout << "Complexite Brute  : O(n^2 * K log K) temps | O(n*K) espace" << endl;
    cout << "Complexite Optimal: O(n * K log K)   temps | O(n*K) espace" << endl;
    cout << "Complexite Ultra  : O(n * K)          temps | O(n*K) espace" << endl;

    return 0;
}
