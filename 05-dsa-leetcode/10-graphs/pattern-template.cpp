// ============================================
// PATTERN : Graphs - Templates 
// ============================================
// Squelettes copier-coller pour les graphes
// Compile : g++ -std=c++17 -o pattern pattern-template.cpp
// ============================================

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
using namespace std;

// ============================================
// TEMPLATE 1 : Construire un graphe (adjacency list)
// ============================================
vector<vector<int>> buildGraph(int n, vector<vector<int>>& edges, bool directed = false) {
    vector<vector<int>> adj(n);
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        if (!directed) adj[e[1]].push_back(e[0]);
    }
    return adj;
}

// ============================================
// TEMPLATE 2 : DFS sur graphe
// ============================================
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

// ============================================
// TEMPLATE 3 : BFS sur graphe
// ============================================
void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// ============================================
// TEMPLATE 4 : Compter composantes connexes
// ============================================
int countComponents(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited);
            count++;
        }
    }
    return count;
}

// ============================================
// TEMPLATE 5 : Topological Sort (Kahn's - BFS)
// ============================================
vector<int> topologicalSort(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0);
    for (int i = 0; i < n; i++)
        for (int nb : adj[i])
            indegree[nb]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);
        for (int nb : adj[node]) {
            if (--indegree[nb] == 0) q.push(nb);
        }
    }
    return order; // si order.size() < n -> cycle detecte
}

// ============================================
// TEMPLATE 6 : Union-Find (Disjoint Set)
// ============================================
class UnionFind {
    vector<int> parent, rank_;
public:
    UnionFind(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false; // deja connectes
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

// ============================================
// TEMPLATE 7 : Dijkstra (plus court chemin pondere)
// ============================================
vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int start) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();
        if (d > dist[node]) continue;
        for (auto [neighbor, weight] : adj[node]) {
            if (dist[node] + weight < dist[neighbor]) {
                dist[neighbor] = dist[node] + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }
    return dist;
}

int main() {
    // Test Union-Find
    UnionFind uf(5);
    uf.unite(0, 1);
    uf.unite(2, 3);
    cout << "0-1 connectes: " << (uf.connected(0, 1) ? "OUI" : "NON") << endl;
    cout << "0-2 connectes: " << (uf.connected(0, 2) ? "OUI" : "NON") << endl;
    uf.unite(1, 3);
    cout << "0-3 connectes apres union: " << (uf.connected(0, 3) ? "OUI" : "NON") << endl;

    // Test Topological Sort
    // 0 -> 1 -> 3
    // 0 -> 2 -> 3
    int n = 4;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2};
    adj[1] = {3};
    adj[2] = {3};
    auto order = topologicalSort(n, adj);
    cout << "Topological order: ";
    for (int v : order) cout << v << " ";
    cout << endl;

    // Test Dijkstra
    // 0 --(1)--> 1 --(2)--> 2
    // 0 --(4)--> 2
    vector<vector<pair<int,int>>> wadj(3);
    wadj[0] = {{1, 1}, {2, 4}};
    wadj[1] = {{2, 2}};
    auto dists = dijkstra(3, wadj, 0);
    cout << "Dijkstra depuis 0: ";
    for (int d : dists) cout << d << " ";
    cout << endl; // 0 1 3

    return 0;
}
