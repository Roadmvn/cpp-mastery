// ============================================
// LeetCode #210 - Course Schedule II (Medium) 📊
// https://leetcode.com/problems/course-schedule-ii/
// ============================================
//
// ENONCE :
// Meme probleme que Course Schedule, mais retourner l'ORDRE
// dans lequel suivre les cours (topological sort).
// Si impossible (cycle) -> retourner tableau vide.
//
//   numCourses = 4, prereqs = [[1,0],[2,0],[3,1],[3,2]]
//
//        0
//       / \
//      1   2       Ordre possible : [0, 1, 2, 3] ou [0, 2, 1, 3]
//       \ /
//        3
//
// ============================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ============================================
// BRUTE FORCE : DFS postorder (inverser le resultat)
// On fait un DFS et on ajoute les noeuds en postorder
// Puis on inverse pour avoir l'ordre topologique
// Temps : O(V + E) | Espace : O(V + E)
// ============================================
// bool dfs(int node, vector<vector<int>>& adj, vector<int>& color, vector<int>& order) {
//     color[node] = 1;
//     for (int nb : adj[node]) {
//         if (color[nb] == 1) return false;
//         if (color[nb] == 0 && !dfs(nb, adj, color, order)) return false;
//     }
//     color[node] = 2;
//     order.push_back(node);
//     return true;
// }
// vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
//     vector<vector<int>> adj(numCourses);
//     for (auto& p : prerequisites) adj[p[1]].push_back(p[0]);
//     vector<int> color(numCourses, 0), order;
//     for (int i = 0; i < numCourses; i++)
//         if (color[i] == 0 && !dfs(i, adj, color, order)) return {};
//     reverse(order.begin(), order.end());
//     return order;
// }

// ============================================
// SOLUTION OPTIMALE : BFS Kahn's Algorithm
// Meme logique que Course Schedule I, mais on stocke l'ordre
// Temps : O(V + E) | Espace : O(V + E)
// ============================================
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]);
        indegree[p[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> order;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        order.push_back(course);
        for (int next : adj[course]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    if ((int)order.size() != numCourses) return {}; // cycle
    return order;
}

// --- Helper ---
void printVec(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i < (int)v.size() - 1) cout << ",";
    }
    cout << "]";
}

int main() {
    // Test 1 : ordre valide
    vector<vector<int>> p1 = {{1,0},{2,0},{3,1},{3,2}};
    auto r1 = findOrder(4, p1);
    cout << "Test 1 - ordre: ";
    printVec(r1);
    cout << " -> " << (r1.size() == 4 && r1[0] == 0 ? "OK" : "FAIL") << endl;

    // Test 2 : 2 cours
    vector<vector<int>> p2 = {{1,0}};
    auto r2 = findOrder(2, p2);
    cout << "Test 2 - [0,1]: ";
    printVec(r2);
    cout << " -> " << (r2 == vector<int>({0,1}) ? "OK" : "FAIL") << endl;

    // Test 3 : cycle -> vide
    vector<vector<int>> p3 = {{1,0},{0,1}};
    auto r3 = findOrder(2, p3);
    cout << "Test 3 - cycle: ";
    printVec(r3);
    cout << " -> " << (r3.empty() ? "OK" : "FAIL") << endl;

    // Test 4 : pas de prereqs
    vector<vector<int>> p4 = {};
    auto r4 = findOrder(3, p4);
    cout << "Test 4 - sans prereqs: " << (r4.size() == 3 ? "OK" : "FAIL") << endl;

    // Test 5 : un seul cours
    vector<vector<int>> p5 = {};
    auto r5 = findOrder(1, p5);
    cout << "Test 5 - un cours: " << (r5 == vector<int>({0}) ? "OK" : "FAIL") << endl;

    return 0;
}
