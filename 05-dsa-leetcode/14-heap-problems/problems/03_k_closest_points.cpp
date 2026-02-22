/*
 * ============================================
 *  LeetCode #973 - K Closest Points (Medium) 🏔️
 * ============================================
 *  Lien : https://leetcode.com/problems/k-closest-points-to-origin/
 *
 *  Enonce :
 *  Etant donne un tableau de points sur le plan et un entier k,
 *  retourner les k points les plus proches de l'origine (0,0).
 *  Distance = sqrt(x^2 + y^2) (pas besoin de sqrt pour comparer).
 *
 *  Exemple :
 *  Input:  points = [[1,3],[-2,2]], k = 1
 *  Output: [[-2,2]]
 *  Explication : dist(1,3)=sqrt(10), dist(-2,2)=sqrt(8) < sqrt(10)
 *
 *  Contraintes :
 *  - 1 <= k <= points.length <= 10^4
 *  - -10^4 <= xi, yi <= 10^4
 * ============================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * ─── BRUTE FORCE : Tri par distance ──────────────
 *
 * Calculer la distance pour chaque point, trier, prendre les k premiers.
 *
 * Complexite :
 *  - Temps  : O(n log n)
 *  - Espace : O(1) si tri in-place
 */
class BruteForce {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        sort(points.begin(), points.end(), [](auto& a, auto& b) {
            return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
        });
        return vector<vector<int>>(points.begin(), points.begin() + k);
    }
};

/*
 * ─── SOLUTION OPTIMALE : Max-heap de taille k ────
 *
 * Utiliser un max-heap de taille k.
 * On stocke les distances (negatives pour min → max-heap trick
 * ou on utilise directement un max-heap et on pop quand taille > k).
 *
 *  Trace pour points=[[1,3],[-2,2],[5,8],[0,1]], k=2 :
 *
 *  Distances : (1,3)=10, (-2,2)=8, (5,8)=89, (0,1)=1
 *
 *  Max-heap (par distance) :
 *  push (10,[1,3])   → heap: [(10,[1,3])]
 *  push (8,[-2,2])   → heap: [(10,[1,3]), (8,[-2,2])]
 *  push (89,[5,8])   → taille 3 > k=2, pop max(89) → [(10,[1,3]), (8,[-2,2])]
 *  push (1,[0,1])    → taille 3 > k=2, pop max(10) → [(8,[-2,2]), (1,[0,1])]
 *
 *  Resultat : [[-2,2], [0,1]]
 *
 * Complexite :
 *  - Temps  : O(n log k)
 *  - Espace : O(k)
 */
class Optimal {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // max-heap : (distance, index)
        using P = pair<int, int>;
        priority_queue<P> maxHeap;

        for (int i = 0; i < (int)points.size(); i++) {
            int dist = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            maxHeap.push({dist, i});

            if ((int)maxHeap.size() > k) {
                maxHeap.pop(); // virer le plus loin
            }
        }

        vector<vector<int>> result;
        while (!maxHeap.empty()) {
            result.push_back(points[maxHeap.top().second]);
            maxHeap.pop();
        }
        return result;
    }
};

void printPoints(vector<vector<int>>& pts) {
    cout << "[";
    for (int i = 0; i < (int)pts.size(); i++) {
        cout << "[" << pts[i][0] << "," << pts[i][1] << "]";
        if (i < (int)pts.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    // Test 1
    vector<vector<int>> pts1 = {{1, 3}, {-2, 2}};
    cout << "=== Test 1 : [[1,3],[-2,2]], k=1 ===" << endl;

    BruteForce bf;
    vector<vector<int>> pts1a = pts1;
    auto r1 = bf.kClosest(pts1a, 1);
    cout << "Brute Force : ";
    printPoints(r1);

    Optimal opt;
    auto r2 = opt.kClosest(pts1, 1);
    cout << "Optimal     : ";
    printPoints(r2);
    cout << "Attendu     : [[-2,2]]" << endl;

    // Test 2
    vector<vector<int>> pts2 = {{3, 3}, {5, -1}, {-2, 4}};
    cout << "\n=== Test 2 : [[3,3],[5,-1],[-2,4]], k=2 ===" << endl;

    Optimal opt2;
    auto r3 = opt2.kClosest(pts2, 2);
    cout << "Optimal     : ";
    printPoints(r3);
    cout << "Attendu     : [[3,3],[-2,4]] (dist 18 et 20)" << endl;

    // Test 3
    vector<vector<int>> pts3 = {{0, 1}, {1, 0}};
    cout << "\n=== Test 3 : [[0,1],[1,0]], k=2 ===" << endl;

    Optimal opt3;
    auto r4 = opt3.kClosest(pts3, 2);
    cout << "Optimal     : ";
    printPoints(r4);
    cout << "Attendu     : [[0,1],[1,0]]" << endl;

    return 0;
}
