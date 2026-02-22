// ============================================
// LeetCode #207 - Course Schedule (Medium) 📊
// https://leetcode.com/problems/course-schedule/
// ============================================
//
// ENONCE :
// n cours (0 a n-1). prerequisites[i] = [a, b] signifie :
// tu dois suivre le cours b AVANT le cours a.
// Retourner true si tu peux finir tous les cours (pas de cycle).
//
//   numCourses = 2, prereqs = [[1,0]]
//   -> 0 avant 1, OK -> true
//
//   numCourses = 2, prereqs = [[1,0],[0,1]]
//   -> 0 avant 1 ET 1 avant 0 = CYCLE -> false
//
// C'EST UN PROBLEME DE DETECTION DE CYCLE dans un graphe DIRIGE !
// Si le graphe a un cycle -> impossible de finir tous les cours.
//
//   0 -> 1 -> 2        0 -> 1
//        |              ^    |
//        v              |    v
//        3              3 <- 2    <- CYCLE !
//   OK (pas de cycle)   Impossible
//
// ============================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ============================================
// BRUTE FORCE : DFS avec 3 couleurs pour detecter un cycle
// blanc=0 (pas visite), gris=1 (en cours), noir=2 (fini)
// Si on tombe sur un noeud gris -> cycle !
// Temps : O(V + E) | Espace : O(V + E)
// ============================================
// bool hasCycle(int node, vector<vector<int>>& adj, vector<int>& color) {
//     color[node] = 1; // gris
//     for (int nb : adj[node]) {
//         if (color[nb] == 1) return true; // cycle !
//         if (color[nb] == 0 && hasCycle(nb, adj, color)) return true;
//     }
//     color[node] = 2; // noir
//     return false;
// }
// bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
//     vector<vector<int>> adj(numCourses);
//     for (auto& p : prerequisites) adj[p[1]].push_back(p[0]);
//     vector<int> color(numCourses, 0);
//     for (int i = 0; i < numCourses; i++)
//         if (color[i] == 0 && hasCycle(i, adj, color)) return false;
//     return true;
// }

// ============================================
// SOLUTION OPTIMALE : BFS Topological Sort (Kahn's Algorithm)
// Si on peut traiter tous les noeuds -> pas de cycle
// Si il reste des noeuds non traites -> cycle !
// Temps : O(V + E) | Espace : O(V + E)
// ============================================
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]); // b -> a (b avant a)
        indegree[p[0]]++;
    }

    // Ajouter tous les noeuds sans prerequis
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    int processed = 0;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        processed++;
        for (int next : adj[course]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    return processed == numCourses; // tous traites = pas de cycle
}

int main() {
    // Test 1 : possible
    vector<vector<int>> p1 = {{1, 0}};
    cout << "Test 1 - [1,0] possible: " << (canFinish(2, p1) ? "OK" : "FAIL") << endl;

    // Test 2 : cycle
    vector<vector<int>> p2 = {{1, 0}, {0, 1}};
    cout << "Test 2 - cycle: " << (!canFinish(2, p2) ? "OK" : "FAIL") << endl;

    // Test 3 : chaine
    vector<vector<int>> p3 = {{1, 0}, {2, 1}, {3, 2}};
    cout << "Test 3 - chaine: " << (canFinish(4, p3) ? "OK" : "FAIL") << endl;

    // Test 4 : pas de prereqs
    vector<vector<int>> p4 = {};
    cout << "Test 4 - pas de prereqs: " << (canFinish(3, p4) ? "OK" : "FAIL") << endl;

    // Test 5 : cycle complexe
    vector<vector<int>> p5 = {{1, 0}, {2, 1}, {0, 2}};
    cout << "Test 5 - cycle 0->1->2->0: " << (!canFinish(3, p5) ? "OK" : "FAIL") << endl;

    return 0;
}
