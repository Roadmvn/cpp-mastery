/*
 * ============================================
 *  LeetCode #1046 - Last Stone Weight (Easy) 🏔
 * ============================================
 *  Lien : https://leetcode.com/problems/last-stone-weight/
 *
 *  Enonce :
 *  On a des pierres avec des poids. A chaque tour, on prend les
 *  2 pierres les plus lourdes (x, y avec x <= y) :
 *  - Si x == y : les deux sont detruites
 *  - Si x != y : la pierre de poids y-x reste
 *  Retourner le poids de la derniere pierre (0 si aucune).
 *
 *  Exemple :
 *  Input:  stones = [2,7,4,1,8,1]
 *  Output: 1
 *  Trace : [2,7,4,1,8,1]  8 vs 7  [2,4,1,1,1]  4 vs 2  [1,1,2]
 *           2 vs 1  [1,1]  1 vs 1  [0]  resultat = 1... wait
 *          [2,7,4,1,8,1]  8,71 [2,4,1,1,1]  4,22 [1,1,2]
 *           2,11 [1,1]  1,10 []  1 (la derniere)
 *
 *  Contraintes :
 *  - 1 <= stones.length <= 30
 *  - 1 <= stones[i] <= 1000
 * ============================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * ─── BRUTE FORCE : Tri a chaque etape ────────────
 *
 * A chaque tour, trier le tableau, prendre les 2 derniers,
 * les detruire et recommencer.
 *
 * Complexite :
 *  - Temps  : O(n^2 log n) - n tours * tri O(n log n)
 *  - Espace : O(1) si tri in-place
 */
class BruteForce {
public:
    int lastStoneWeight(vector<int>& stones) {
        while (stones.size() > 1) {
            sort(stones.begin(), stones.end());
            int y = stones.back(); stones.pop_back();
            int x = stones.back(); stones.pop_back();

            if (x != y) {
                stones.push_back(y - x);
            }
        }
        return stones.empty() ? 0 : stones[0];
    }
};

/*
 * ─── SOLUTION OPTIMALE : Max-heap ────────────────
 *
 * Un max-heap permet d'acceder aux 2 plus grands en O(log n).
 *
 *  Trace pour [2,7,4,1,8,1] :
 *
 *  Max-heap initial : [8, 7, 4, 2, 1, 1]
 *
 *  Tour 1: pop 8, pop 7  push 1    heap: [4, 2, 1, 1, 1]
 *  Tour 2: pop 4, pop 2  push 2    heap: [2, 1, 1, 1]
 *  Tour 3: pop 2, pop 1  push 1    heap: [1, 1, 1]
 *  Tour 4: pop 1, pop 1  rien      heap: [1]
 *
 *  Resultat : 1
 *
 * Complexite :
 *  - Temps  : O(n log n) - n tours * O(log n) par pop/push
 *  - Espace : O(n) - le heap
 */
class Optimal {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> maxHeap(stones.begin(), stones.end());

        while (maxHeap.size() > 1) {
            int y = maxHeap.top(); maxHeap.pop();
            int x = maxHeap.top(); maxHeap.pop();

            if (x != y) {
                maxHeap.push(y - x);
            }
        }
        return maxHeap.empty() ? 0 : maxHeap.top();
    }
};

int main() {
    // Test 1
    vector<int> s1 = {2, 7, 4, 1, 8, 1};
    cout << "=== Test 1 : [2,7,4,1,8,1] ===" << endl;

    BruteForce bf;
    vector<int> s1a = s1;
    cout << "Brute Force : " << bf.lastStoneWeight(s1a) << endl;

    Optimal opt;
    cout << "Optimal     : " << opt.lastStoneWeight(s1) << endl;
    cout << "Attendu     : 1" << endl;

    // Test 2 : une seule pierre
    vector<int> s2 = {1};
    cout << "\n=== Test 2 : [1] ===" << endl;

    Optimal opt2;
    cout << "Optimal     : " << opt2.lastStoneWeight(s2) << endl;
    cout << "Attendu     : 1" << endl;

    // Test 3 : pierres egales
    vector<int> s3 = {3, 3};
    cout << "\n=== Test 3 : [3,3] ===" << endl;

    Optimal opt3;
    cout << "Optimal     : " << opt3.lastStoneWeight(s3) << endl;
    cout << "Attendu     : 0" << endl;

    // Test 4
    vector<int> s4 = {10, 4, 2, 10};
    cout << "\n=== Test 4 : [10,4,2,10] ===" << endl;

    Optimal opt4;
    cout << "Optimal     : " << opt4.lastStoneWeight(s4) << endl;
    cout << "Attendu     : 2" << endl;

    return 0;
}
