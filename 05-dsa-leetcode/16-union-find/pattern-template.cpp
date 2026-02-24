#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

// ============================================================
//  UNION-FIND (DISJOINT SET UNION) -- Template
// ============================================================
//
//  Cas d'utilisation :
//    - Composantes connexes (statique ou dynamique)
//    - Detection de cycle dans un graphe non-oriente
//    - Fusion de groupes avec queries de connectivite
//
//  Complexite : O(alpha(n)) par operation -- quasi-O(1)
// ============================================================

class UnionFind {
    vector<int> parent;
    vector<int> rank_;  // "rank" est un mot reserve dans certains contextes
    int components;     // nombre de composantes connexes

public:
    // Initialise n elements, chacun dans son propre ensemble
    UnionFind(int n) : parent(n), rank_(n, 0), components(n) {
        iota(parent.begin(), parent.end(), 0);  // parent[i] = i
    }

    // Trouve la racine de x avec path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // compression recursive
        return parent[x];
    }

    // Version iterative de find (evite le stack overflow sur tres grands n)
    int find_iter(int x) {
        int root = x;
        while (parent[root] != root)
            root = parent[root];
        // path compression
        while (parent[x] != root) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        return root;
    }

    // Fusionne les ensembles de x et y
    // Retourne true si une fusion a eu lieu (x et y etaient dans des ensembles distincts)
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;  // deja connectes -> cycle si on insere une arete

        // union by rank : le petit arbre va sous le grand
        if (rank_[rx] < rank_[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry]) rank_[rx]++;

        components--;
        return true;
    }

    // Retourne true si x et y sont dans le meme ensemble
    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int getComponents() const {
        return components;
    }
};

// ============================================================
//  VARIANTE : Union-Find avec poids/distance
//  Utile pour : "Evaluate Division" (LC #399), chemins relatifs
// ============================================================

class WeightedUnionFind {
    vector<int> parent;
    vector<double> weight;  // weight[x] = rapport x / parent[x]

public:
    WeightedUnionFind(int n) : parent(n), weight(n, 1.0) {
        iota(parent.begin(), parent.end(), 0);
    }

    pair<int, double> find(int x) {
        if (parent[x] == x) return {x, 1.0};
        auto [root, w] = find(parent[x]);
        parent[x] = root;
        weight[x] *= w;
        return {root, weight[x]};
    }

    void unite(int x, int y, double ratio) {  // ratio = x / y
        auto [rx, wx] = find(x);
        auto [ry, wy] = find(y);
        if (rx == ry) return;
        parent[rx] = ry;
        weight[rx] = ratio * wy / wx;
    }
};

// ============================================================
//  TESTS
// ============================================================

int main() {
    // --- Test basique ---
    UnionFind uf(6);
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);

    cout << "connected(0,2): " << uf.connected(0, 2) << "\n";  // 1
    cout << "connected(0,3): " << uf.connected(0, 3) << "\n";  // 0
    cout << "components: "     << uf.getComponents() << "\n";   // 3

    // --- Detection de cycle ---
    UnionFind uf2(4);
    vector<pair<int,int>> edges = {{0,1},{1,2},{2,3},{3,0}};
    for (auto [u, v] : edges) {
        bool merged = uf2.unite(u, v);
        if (!merged) {
            cout << "Cycle detecte entre " << u << " et " << v << "\n";
        }
    }

    // --- Path compression verification ---
    UnionFind uf3(10);
    for (int i = 1; i < 10; i++) uf3.unite(i-1, i);  // chaine 0-1-2-...-9
    cout << "find(9) apres compression: " << uf3.find(9) << "\n";  // racine = 0
    cout << "connected(0,9): " << uf3.connected(0, 9) << "\n";     // 1

    return 0;
}
