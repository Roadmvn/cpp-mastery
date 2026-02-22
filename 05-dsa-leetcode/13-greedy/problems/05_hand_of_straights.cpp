/*
 * ============================================
 *  LeetCode #846 - Hand of Straights (Medium) 🤑
 * ============================================
 *  Lien : https://leetcode.com/problems/hand-of-straights/
 *
 *  Enonce :
 *  Alice a des cartes (tableau hand). Elle veut les rearanger
 *  en groupes de taille groupSize, ou chaque groupe contient
 *  groupSize cartes consecutives. Retourner si c'est possible.
 *
 *  Exemple :
 *  Input:  hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
 *  Output: true → [1,2,3], [2,3,4], [6,7,8]
 *
 *  Contraintes :
 *  - 1 <= hand.length <= 10^4
 *  - 0 <= hand[i] <= 10^9
 *  - 1 <= groupSize <= hand.length
 * ============================================
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/*
 * ─── BRUTE FORCE : Tri + simulation ──────────────
 *
 * Trier les cartes. A chaque iteration, prendre la plus
 * petite carte et essayer de former un groupe consecutif.
 *
 * Complexite :
 *  - Temps  : O(n * groupSize * log n)
 *  - Espace : O(n)
 */
class BruteForce {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if (n % groupSize != 0) return false;

        sort(hand.begin(), hand.end());
        vector<bool> used(n, false);

        for (int i = 0; i < n; i++) {
            if (used[i]) continue;

            int prev = hand[i];
            used[i] = true;
            int count = 1;

            for (int j = i + 1; j < n && count < groupSize; j++) {
                if (!used[j] && hand[j] == prev + 1) {
                    used[j] = true;
                    prev = hand[j];
                    count++;
                }
            }
            if (count < groupSize) return false;
        }
        return true;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Map ordonnee (TreeMap) ──
 *
 * Utiliser une map ordonnee pour compter les frequences.
 * A chaque iteration, prendre la plus petite cle et
 * decrementer count pour groupSize valeurs consecutives.
 *
 *  Trace pour [1,2,3,6,2,3,4,7,8], groupSize=3 :
 *
 *  Map: {1:1, 2:2, 3:2, 4:1, 6:1, 7:1, 8:1}
 *
 *  Iteration 1: start=1, groupe [1,2,3]
 *  Map: {2:1, 3:1, 4:1, 6:1, 7:1, 8:1}
 *
 *  Iteration 2: start=2, groupe [2,3,4]
 *  Map: {6:1, 7:1, 8:1}
 *
 *  Iteration 3: start=6, groupe [6,7,8]
 *  Map: {} → true
 *
 * Complexite :
 *  - Temps  : O(n log n) - operations sur la map
 *  - Espace : O(n) - map des frequences
 */
class Optimal {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if ((int)hand.size() % groupSize != 0) return false;

        map<int, int> freq; // ordonnee par cle
        for (int card : hand) freq[card]++;

        while (!freq.empty()) {
            int start = freq.begin()->first; // plus petite carte

            for (int i = 0; i < groupSize; i++) {
                int card = start + i;
                if (freq.find(card) == freq.end()) return false;

                freq[card]--;
                if (freq[card] == 0) freq.erase(card);
            }
        }
        return true;
    }
};

int main() {
    // Test 1
    vector<int> hand1 = {1, 2, 3, 6, 2, 3, 4, 7, 8};
    cout << "=== Test 1 : hand=[1,2,3,6,2,3,4,7,8], groupSize=3 ===" << endl;

    BruteForce bf;
    cout << "Brute Force : " << (bf.isNStraightHand(hand1, 3) ? "true" : "false") << endl;

    Optimal opt;
    vector<int> hand1b = {1, 2, 3, 6, 2, 3, 4, 7, 8};
    cout << "Optimal     : " << (opt.isNStraightHand(hand1b, 3) ? "true" : "false") << endl;
    cout << "Attendu     : true" << endl;

    // Test 2
    vector<int> hand2 = {1, 2, 3, 4, 5};
    cout << "\n=== Test 2 : hand=[1,2,3,4,5], groupSize=4 ===" << endl;

    Optimal opt2;
    cout << "Optimal     : " << (opt2.isNStraightHand(hand2, 4) ? "true" : "false") << endl;
    cout << "Attendu     : false" << endl;

    // Test 3
    vector<int> hand3 = {8, 10, 12};
    cout << "\n=== Test 3 : hand=[8,10,12], groupSize=3 ===" << endl;

    Optimal opt3;
    cout << "Optimal     : " << (opt3.isNStraightHand(hand3, 3) ? "true" : "false") << endl;
    cout << "Attendu     : false" << endl;

    // Test 4
    vector<int> hand4 = {1, 1, 2, 2, 3, 3};
    cout << "\n=== Test 4 : hand=[1,1,2,2,3,3], groupSize=3 ===" << endl;

    Optimal opt4;
    cout << "Optimal     : " << (opt4.isNStraightHand(hand4, 3) ? "true" : "false") << endl;
    cout << "Attendu     : true" << endl;

    return 0;
}
