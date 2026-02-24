// https://leetcode.com/problems/word-ladder/
// #127 - Word Ladder
//
// Transformer beginWord en endWord en changeant une lettre a la fois.
// Chaque mot intermediaire doit etre dans wordList.
// Retourner la longueur de la sequence la plus courte (0 si impossible).
//
// Approche : BFS + hash set.
// BFS garantit le chemin le plus court.
// A chaque etape, generer tous les voisins (1 lettre de difference),
// verifier dans le set et ajouter a la queue si non visite.
// Complexite temps : O(M^2 * N) M = longueur des mots, N = taille du dictionnaire
// Complexite espace : O(M^2 * N)

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // endWord doit etre dans le dictionnaire
        if (!wordSet.count(endWord)) return 0;

        queue<string> q;
        q.push(beginWord);
        wordSet.erase(beginWord); // marquer comme visite
        int steps = 1;

        while (!q.empty()) {
            int size = (int)q.size();

            // Traiter tous les mots du niveau courant
            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();

                // Generer tous les voisins a 1 lettre de distance
                for (int j = 0; j < (int)word.size(); j++) {
                    char original = word[j];

                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original) continue;
                        word[j] = c;

                        if (word == endWord) return steps + 1;

                        if (wordSet.count(word)) {
                            q.push(word);
                            wordSet.erase(word); // eviter de revisiter
                        }
                    }

                    word[j] = original; // restaurer
                }
            }

            steps++;
        }

        return 0; // pas de chemin trouve
    }
};

int main() {
    Solution sol;

    vector<string> list1 = {"hot","dot","dog","lot","log","cog"};
    cout << sol.ladderLength("hit", "cog", list1) << endl; // 5

    vector<string> list2 = {"hot","dot","dog","lot","log"};
    cout << sol.ladderLength("hit", "cog", list2) << endl; // 0 (cog absent)

    vector<string> list3 = {"a", "b"};
    cout << sol.ladderLength("a", "b", list3) << endl; // 2

    return 0;
}
