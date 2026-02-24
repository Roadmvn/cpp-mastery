// https://leetcode.com/problems/course-schedule/
// #207 - Course Schedule
//
// Verifier si tous les cours peuvent etre completés etant donne des prerequis.
// [a, b] signifie : pour suivre a, il faut avoir suivi b.
// Revient a : le graphe oriente a-t-il un cycle ?
//
// Approche : tri topologique avec DFS (detection de cycle).
// Etats : 0 = non visite, 1 = en cours de visite, 2 = visite termine.
// Si on revisit un noeud en cours (etat 1) : cycle detecte.
// Complexite temps : O(V+E) | Complexite espace : O(V+E)

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Construction du graphe d'adjacence
        vector<vector<int>> adj(numCourses);
        for (auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
        }

        // 0 = non visite, 1 = en visite (dans la pile), 2 = visite termine
        vector<int> state(numCourses, 0);

        for (int i = 0; i < numCourses; i++) {
            if (state[i] == 0 && hasCycle(adj, state, i)) {
                return false;
            }
        }

        return true;
    }

private:
    bool hasCycle(vector<vector<int>>& adj, vector<int>& state, int node) {
        state[node] = 1; // marquer comme "en visite"

        for (int neighbor : adj[node]) {
            if (state[neighbor] == 1) return true;  // cycle !
            if (state[neighbor] == 0 && hasCycle(adj, state, neighbor)) return true;
        }

        state[node] = 2; // marquer comme "termine"
        return false;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> pre1 = {{1, 0}};
    cout << boolalpha << sol.canFinish(2, pre1) << endl; // true (0 -> 1)

    vector<vector<int>> pre2 = {{1, 0}, {0, 1}};
    cout << sol.canFinish(2, pre2) << endl; // false (cycle : 0->1->0)

    vector<vector<int>> pre3 = {{1,0},{2,0},{3,1},{3,2}};
    cout << sol.canFinish(4, pre3) << endl; // true

    vector<vector<int>> pre4 = {};
    cout << sol.canFinish(1, pre4) << endl; // true

    return 0;
}
