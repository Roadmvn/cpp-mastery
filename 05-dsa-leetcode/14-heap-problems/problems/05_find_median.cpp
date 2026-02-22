/*
 * ============================================
 *  LeetCode #295 - Find Median from Data Stream (Hard) 🏔
 * ============================================
 *  Lien : https://leetcode.com/problems/find-median-from-data-stream/
 *
 *  Enonce :
 *  Implementer une structure qui supporte :
 *  - addNum(int num) : ajouter un entier
 *  - findMedian() : retourner la mediane des elements ajoutes
 *
 *  Exemple :
 *  addNum(1), addNum(2)  findMedian() = 1.5
 *  addNum(3)  findMedian() = 2.0
 *
 *  Contraintes :
 *  - -10^5 <= num <= 10^5
 *  - Au max 5 * 10^4 appels a addNum/findMedian
 * ============================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * ─── BRUTE FORCE : Tri a chaque findMedian ───────
 *
 * Stocker tous les nombres. A chaque appel de findMedian,
 * trier et retourner l'element du milieu.
 *
 * Complexite :
 *  - addNum     : O(1)
 *  - findMedian : O(n log n)
 *  - Espace     : O(n)
 */
class MedianFinderBrute {
    vector<int> data;
public:
    void addNum(int num) {
        data.push_back(num);
    }

    double findMedian() {
        sort(data.begin(), data.end());
        int n = data.size();
        if (n % 2 == 1) return data[n / 2];
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    }
};

/*
 * ─── SOLUTION OPTIMALE : Deux heaps ──────────────
 *
 * On partitionne les nombres en deux moities :
 * - maxHeap : moitie gauche (les plus petits)  acces au max
 * - minHeap : moitie droite (les plus grands)  acces au min
 *
 *  Invariants :
 *  1. Tout dans maxHeap <= tout dans minHeap
 *  2. |maxHeap.size() - minHeap.size()| <= 1
 *  3. maxHeap a toujours au moins autant d'elements que minHeap
 *
 *  Trace pour addNum(1, 2, 3, 4, 5) :
 *
 *  add(1): maxHeap=[1], minHeap=[]         median=1
 *
 *  add(2): maxHeap=[1], minHeap=[2]        median=(1+2)/2=1.5
 *
 *  add(3): maxHeap push 3[3,1], top(3)>min top(2)
 *          move 3minHeap, rebalance
 *          maxHeap=[2,1], minHeap=[3]       median=2
 *
 *  add(4): maxHeap push 4, rebalance
 *          maxHeap=[2,1], minHeap=[3,4]     median=(2+3)/2=2.5
 *
 *  add(5): maxHeap push 5, rebalance
 *          maxHeap=[3,2,1], minHeap=[4,5]   median=3
 *
 *  ┌──────────────────┐  ┌──────────────────┐
 *  │    MAX-HEAP      │  │    MIN-HEAP      │
 *  │   (petits)       │  │   (grands)       │
 *  │                  │  │                  │
 *  │     [3]          │  │     [4]          │
 *  │    /   \         │  │    /             │
 *  │  [2]   [1]       │  │  [5]             │
 *  │                  │  │                  │
 *  │  top = 3 ────────┼──┼ top = 4         │
 *  └──────────────────┘  └──────────────────┘
 *            mediane = 3 (maxHeap a 1 de plus)
 *
 * Complexite :
 *  - addNum     : O(log n)
 *  - findMedian : O(1)
 *  - Espace     : O(n)
 */
class MedianFinderOptimal {
    priority_queue<int> maxHeap;                              // moitie gauche
    priority_queue<int, vector<int>, greater<int>> minHeap;   // moitie droite

public:
    void addNum(int num) {
        maxHeap.push(num);

        // Assurer que max des petits <= min des grands
        if (!minHeap.empty() && maxHeap.top() > minHeap.top()) {
            int val = maxHeap.top(); maxHeap.pop();
            minHeap.push(val);
        }

        // Equilibrer : maxHeap peut avoir au plus 1 element de plus
        if ((int)maxHeap.size() > (int)minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if ((int)minHeap.size() > (int)maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if ((int)maxHeap.size() > (int)minHeap.size()) {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};

int main() {
    // Test 1 : Brute Force
    cout << "=== Test 1 : Brute Force ===" << endl;
    MedianFinderBrute bf;
    bf.addNum(1);
    bf.addNum(2);
    cout << "Apres [1,2]   : median = " << bf.findMedian() << " (attendu 1.5)" << endl;
    bf.addNum(3);
    cout << "Apres [1,2,3] : median = " << bf.findMedian() << " (attendu 2.0)" << endl;

    // Test 2 : Optimal
    cout << "\n=== Test 2 : Optimal ===" << endl;
    MedianFinderOptimal opt;
    opt.addNum(1);
    cout << "Apres [1]       : median = " << opt.findMedian() << " (attendu 1.0)" << endl;
    opt.addNum(2);
    cout << "Apres [1,2]     : median = " << opt.findMedian() << " (attendu 1.5)" << endl;
    opt.addNum(3);
    cout << "Apres [1,2,3]   : median = " << opt.findMedian() << " (attendu 2.0)" << endl;
    opt.addNum(4);
    cout << "Apres [1,2,3,4] : median = " << opt.findMedian() << " (attendu 2.5)" << endl;
    opt.addNum(5);
    cout << "Apres [1..5]    : median = " << opt.findMedian() << " (attendu 3.0)" << endl;

    // Test 3 : Nombres negatifs
    cout << "\n=== Test 3 : Nombres negatifs ===" << endl;
    MedianFinderOptimal opt2;
    opt2.addNum(-1);
    cout << "Apres [-1]      : median = " << opt2.findMedian() << " (attendu -1.0)" << endl;
    opt2.addNum(-2);
    cout << "Apres [-2,-1]   : median = " << opt2.findMedian() << " (attendu -1.5)" << endl;
    opt2.addNum(-3);
    cout << "Apres [-3,-2,-1]: median = " << opt2.findMedian() << " (attendu -2.0)" << endl;

    // Test 4 : Doublons
    cout << "\n=== Test 4 : Doublons ===" << endl;
    MedianFinderOptimal opt3;
    opt3.addNum(5);
    opt3.addNum(5);
    opt3.addNum(5);
    cout << "Apres [5,5,5]   : median = " << opt3.findMedian() << " (attendu 5.0)" << endl;

    return 0;
}
