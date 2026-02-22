// ============================================
// LeetCode #743 - Network Delay Time (Medium) 
// https://leetcode.com/problems/network-delay-time/
// ============================================
//
// ENONCE :
// n noeuds (1 a n), aretes dirigees avec poids (temps de transmission).
// Un signal est envoye depuis le noeud k.
// Retourner le temps pour que TOUS les noeuds recoivent le signal.
// Si impossible -> retourner -1.
//
// C'est le probleme du PLUS COURT CHEMIN PONDERE -> DIJKSTRA !
//
//   times = [[2,1,1],[2,3,1],[3,4,1]], n=4, k=2
//
//   1 <--(1)-- 2 --(1)--> 3 --(1)--> 4
//
//   Depuis 2 : dist[1]=1, dist[3]=1, dist[4]=2
//   Max = 2 -> reponse = 2
//
// ============================================

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// ============================================
// BRUTE FORCE : Bellman-Ford
// Relaxer toutes les aretes n-1 fois
// Temps : O(V * E) | Espace : O(V)
// ============================================
// int networkDelayTime(vector<vector<int>>& times, int n, int k) {
//     vector<int> dist(n + 1, INT_MAX);
//     dist[k] = 0;
//     for (int i = 0; i < n - 1; i++) {
//         for (auto& t : times) {
//             int u = t[0], v = t[1], w = t[2];
//             if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
//                 dist[v] = dist[u] + w;
//             }
//         }
//     }
//     int maxDist = *max_element(dist.begin() + 1, dist.end());
//     return maxDist == INT_MAX ? -1 : maxDist;
// }

// ============================================
// SOLUTION OPTIMALE : Dijkstra avec priority queue
// Plus court chemin depuis k vers tous les noeuds
// Le resultat = max de toutes les distances
// Temps : O((V + E) * log V) | Espace : O(V + E)
// ============================================
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    // Construire adjacency list avec poids
    vector<vector<pair<int, int>>> adj(n + 1); // {voisin, poids}
    for (auto& t : times) {
        adj[t[0]].push_back({t[1], t[2]});
    }

    // Dijkstra
    vector<int> dist(n + 1, INT_MAX);
    // min-heap : {distance, noeud}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[k] = 0;
    pq.push({0, k});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();
        if (d > dist[node]) continue; // deja traite avec une meilleure distance
        for (auto [neighbor, weight] : adj[node]) {
            int newDist = dist[node] + weight;
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                pq.push({newDist, neighbor});
            }
        }
    }

    int maxDist = *max_element(dist.begin() + 1, dist.end());
    return maxDist == INT_MAX ? -1 : maxDist;
}

int main() {
    // Test 1 : reponse 2
    vector<vector<int>> t1 = {{2,1,1},{2,3,1},{3,4,1}};
    cout << "Test 1 - delai 2: " << (networkDelayTime(t1, 4, 2) == 2 ? "OK" : "FAIL")
         << " (got " << networkDelayTime(t1, 4, 2) << ")" << endl;

    // Test 2 : impossible
    vector<vector<int>> t2 = {{1,2,1}};
    cout << "Test 2 - impossible: " << (networkDelayTime(t2, 2, 2) == -1 ? "OK" : "FAIL") << endl;

    // Test 3 : un seul noeud
    vector<vector<int>> t3 = {};
    cout << "Test 3 - un noeud: " << (networkDelayTime(t3, 1, 1) == 0 ? "OK" : "FAIL") << endl;

    // Test 4 : chemin plus long optimal
    //  1 --(100)--> 2
    //  1 --(1)----> 3 --(1)--> 2
    vector<vector<int>> t4 = {{1,2,100},{1,3,1},{3,2,1}};
    cout << "Test 4 - chemin court via 3: " << (networkDelayTime(t4, 3, 1) == 2 ? "OK" : "FAIL")
         << " (got " << networkDelayTime(t4, 3, 1) << ")" << endl;

    return 0;
}
