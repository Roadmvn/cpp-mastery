// ============================================================
// Pairs et Tuples — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Problemes utilisant pair/tuple pour preparer les graphes
// et les algorithmes de tri avances.
//
// ============================================================

#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================
// PROBLEME 1 : Merge Intervals (LeetCode #56)
// ============================================================
//
// Enonce :
// Etant donne un vector d'intervalles [start, end],
// fusionner tous les intervalles qui se chevauchent.
//
// Exemple :
// [[1,3],[2,6],[8,10],[15,18]] -> [[1,6],[8,10],[15,18]]
// [[1,4],[4,5]] -> [[1,5]]
//
// Complexite attendue : O(n log n) temps

vector<pair<int,int>> mergeIntervals(vector<pair<int,int>>& intervals) {
    if (intervals.empty()) return {};

    // Trier par debut d'intervalle (pair trie par first automatiquement)
    sort(intervals.begin(), intervals.end());

    vector<pair<int,int>> merged;
    merged.push_back(intervals[0]);

    for (int i = 1; i < (int)intervals.size(); i++) {
        auto& [prev_start, prev_end] = merged.back();
        auto [curr_start, curr_end] = intervals[i];

        if (curr_start <= prev_end) {
            prev_end = max(prev_end, curr_end);
        } else {
            merged.push_back({curr_start, curr_end});
        }
    }
    return merged;
}

// ============================================================
// PROBLEME 2 : K Closest Points to Origin (LeetCode #973)
// ============================================================
//
// Enonce :
// Etant donne un vector de points (x, y) et un entier k,
// retourner les k points les plus proches de l'origine (0,0).
// Distance = x*x + y*y (pas besoin de sqrt)
//
// Exemple :
// points = [[3,3],[5,-1],[-2,4]], k = 2
// -> [[3,3],[-2,4]] (distances: 18, 26, 20)
//
// Complexite attendue : O(n log n) temps

vector<pair<int,int>> kClosest(vector<pair<int,int>>& points, int k) {
    // Stocker (distance, index) dans un vector de tuples
    vector<tuple<int, int, int>> distances;  // (dist, x, y)

    for (auto [x, y] : points) {
        int dist = x * x + y * y;
        distances.push_back({dist, x, y});
    }

    // Trier par distance (tuple trie par premier element)
    sort(distances.begin(), distances.end());

    // Extraire les k premiers
    vector<pair<int,int>> result;
    for (int i = 0; i < k; i++) {
        auto [d, x, y] = distances[i];
        result.push_back({x, y});
    }
    return result;
}

// ============================================================
// PROBLEME 3 : Cheapest Path (Dijkstra simplifie)
// ============================================================
//
// Enonce :
// Etant donne un graphe pondere (adjacency list avec pairs),
// trouver le cout minimum du noeud 0 au noeud destination.
// Utiliser un BFS modifie (pas Dijkstra complet, juste relaxation).
//
// Retourner -1 si pas de chemin.
//
// Complexite : O(V * E) (Bellman-Ford simplifie)

int cheapestPath(vector<vector<pair<int,int>>>& adj, int dest) {
    int n = (int)adj.size();
    vector<int> dist(n, INT_MAX);
    dist[0] = 0;

    // Relaxation V-1 fois (Bellman-Ford)
    for (int iter = 0; iter < n - 1; iter++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX) continue;
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    return dist[dest] == INT_MAX ? -1 : dist[dest];
}

// ============================================================
// Tests
// ============================================================

void testMergeIntervals() {
    cout << "=== Test mergeIntervals (LeetCode #56) ===" << endl;

    // Test 1
    vector<pair<int,int>> t1 = {{1,3},{2,6},{8,10},{15,18}};
    auto r1 = mergeIntervals(t1);
    cout << "Input: [[1,3],[2,6],[8,10],[15,18]] -> [";
    for (int i = 0; i < (int)r1.size(); i++) {
        cout << "[" << r1[i].first << "," << r1[i].second << "]";
        if (i < (int)r1.size() - 1) cout << ",";
    }
    cout << "] | " << (r1.size() == 3 ? "PASS" : "FAIL") << endl;

    // Test 2
    vector<pair<int,int>> t2 = {{1,4},{4,5}};
    auto r2 = mergeIntervals(t2);
    cout << "Input: [[1,4],[4,5]] -> [";
    for (int i = 0; i < (int)r2.size(); i++) {
        cout << "[" << r2[i].first << "," << r2[i].second << "]";
        if (i < (int)r2.size() - 1) cout << ",";
    }
    cout << "] | " << (r2.size() == 1 && r2[0].second == 5 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testKClosest() {
    cout << "=== Test kClosest (LeetCode #973) ===" << endl;

    vector<pair<int,int>> points = {{3,3},{5,-1},{-2,4}};
    auto r = kClosest(points, 2);
    cout << "k=2 closest : [";
    for (int i = 0; i < (int)r.size(); i++) {
        cout << "(" << r[i].first << "," << r[i].second << ")";
        if (i < (int)r.size() - 1) cout << ",";
    }
    cout << "] | " << (r.size() == 2 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testCheapestPath() {
    cout << "=== Test cheapestPath ===" << endl;

    // Graphe :  0 --5--> 1 --2--> 3
    //           0 --3--> 2 --7--> 3
    // Chemin optimal 0->1->3 = 7 (vs 0->2->3 = 10)
    vector<vector<pair<int,int>>> adj(4);
    adj[0].push_back({1, 5});
    adj[0].push_back({2, 3});
    adj[1].push_back({3, 2});
    adj[2].push_back({3, 7});

    int cost = cheapestPath(adj, 3);
    cout << "0 -> 3 : cout " << cost << " | "
         << (cost == 7 ? "PASS" : "FAIL") << endl;

    // Pas de chemin vers 0 depuis 3 (graphe dirige)
    int cost2 = cheapestPath(adj, 0);
    cout << "0 -> 0 : cout " << cost2 << " | "
         << (cost2 == 0 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

int main() {
    testMergeIntervals();
    testKClosest();
    testCheapestPath();

    cout << "Patterns utilises :" << endl;
    cout << "- pair pour intervalles, coordonnees, aretes" << endl;
    cout << "- tuple pour (distance, x, y)" << endl;
    cout << "- Structured bindings pour un code lisible" << endl;
    cout << "- adjacency list = vector<vector<pair<int,int>>>" << endl;

    return 0;
}
