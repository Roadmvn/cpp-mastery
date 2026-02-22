// ============================================
// LeetCode #133 - Clone Graph (Medium) 🔄
// https://leetcode.com/problems/clone-graph/
// ============================================
//
// ENONCE :
// Cloner un graphe non dirige. Chaque noeud contient une valeur
// et une liste de voisins. Retourner une copie profonde du graphe.
//
//   1 --- 2          1' --- 2'
//   |     |    ->    |      |      (copie profonde)
//   4 --- 3          4' --- 3'
//
// Le clone ne doit partager AUCUN noeud avec l'original.
//
// ============================================

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

struct Node {
    int val;
    vector<Node*> neighbors;
    Node(int v) : val(v) {}
};

// ============================================
// BRUTE FORCE : BFS avec hashmap old->new
// On parcourt le graphe en BFS, on cree les clones au fur et a mesure
// Temps : O(V + E) | Espace : O(V)
// ============================================
// Node* cloneGraph(Node* node) {
//     if (!node) return nullptr;
//     unordered_map<Node*, Node*> cloned;
//     queue<Node*> q;
//     q.push(node);
//     cloned[node] = new Node(node->val);
//     while (!q.empty()) {
//         Node* curr = q.front(); q.pop();
//         for (Node* neighbor : curr->neighbors) {
//             if (cloned.find(neighbor) == cloned.end()) {
//                 cloned[neighbor] = new Node(neighbor->val);
//                 q.push(neighbor);
//             }
//             cloned[curr]->neighbors.push_back(cloned[neighbor]);
//         }
//     }
//     return cloned[node];
// }

// ============================================
// SOLUTION OPTIMALE : DFS recursif avec hashmap
// Plus elegant, meme complexite
// Temps : O(V + E) | Espace : O(V)
// ============================================
unordered_map<Node*, Node*> cloned;

Node* cloneGraph(Node* node) {
    if (!node) return nullptr;

    // Deja clone ? retourner le clone
    if (cloned.count(node)) return cloned[node];

    // Creer le clone
    Node* clone = new Node(node->val);
    cloned[node] = clone;

    // Cloner les voisins recursivement
    for (Node* neighbor : node->neighbors) {
        clone->neighbors.push_back(cloneGraph(neighbor));
    }
    return clone;
}

int main() {
    // Construire : 1-2, 2-3, 3-4, 4-1
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    n1->neighbors = {n2, n4};
    n2->neighbors = {n1, n3};
    n3->neighbors = {n2, n4};
    n4->neighbors = {n3, n1};

    cloned.clear();
    Node* c1 = cloneGraph(n1);

    // Test 1 : valeurs correctes
    cout << "Test 1 - val clone: " << (c1->val == 1 ? "OK" : "FAIL") << endl;

    // Test 2 : pas le meme pointeur
    cout << "Test 2 - pointeur diff: " << (c1 != n1 ? "OK" : "FAIL") << endl;

    // Test 3 : bon nombre de voisins
    cout << "Test 3 - 2 voisins: " << (c1->neighbors.size() == 2 ? "OK" : "FAIL") << endl;

    // Test 4 : voisins sont des clones, pas les originaux
    bool neighborsCloned = true;
    for (Node* nb : c1->neighbors) {
        if (nb == n2 || nb == n4) neighborsCloned = false;
    }
    cout << "Test 4 - voisins clones: " << (neighborsCloned ? "OK" : "FAIL") << endl;

    // Test 5 : graphe vide
    cloned.clear();
    cout << "Test 5 - vide: " << (cloneGraph(nullptr) == nullptr ? "OK" : "FAIL") << endl;

    return 0;
}
