// ============================================================
// Queue et Deque — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// PARTIE 1 : Queue — FIFO basique
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Queue FIFO ===" << endl;

    queue<string> q;

    // Ajouter des clients
    string clients[] = {"Alice", "Bob", "Charlie", "Diana"};
    for (const string& client : clients) {
        q.push(client);
        cout << "Ajout: " << client << " | front: " << q.front()
             << " | back: " << q.back() << " | size: " << q.size() << endl;
    }

    // Servir les 2 premiers
    for (int i = 0; i < 2; i++) {
        cout << "Servi : " << q.front() << endl;
        q.pop();
    }

    // Prochain a servir
    cout << "Prochain : " << q.front() << endl;

    cout << endl;
}

// ============================================================
// PARTIE 2 : Deque — Double-ended
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : Deque ===" << endl;

    deque<int> d;

    // Ajouter a la fin
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);

    // Ajouter au debut
    d.push_front(5);
    d.push_front(1);

    // Afficher
    cout << "Deque : ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;
    // Resultat : 1 5 10 20 30

    // Acces par index
    cout << "d[0]=" << d[0] << " d[2]=" << d[2] << " d[4]=" << d[4] << endl;

    // Retirer du debut et de la fin
    d.pop_front();
    d.pop_back();
    cout << "Apres pop_front + pop_back : ";
    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;
    // Resultat : 5 10 20

    cout << endl;
}

// ============================================================
// PARTIE 3 : BFS simple avec queue
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : BFS simple ===" << endl;

    int n = 6;
    vector<vector<int>> adj(n);
    adj[0] = {1, 2};
    adj[1] = {3};
    adj[2] = {3, 4};
    adj[3] = {5};
    adj[4] = {5};

    // BFS depuis 0
    vector<bool> visited(n, false);
    vector<int> distance(n, -1);
    queue<int> q;

    q.push(0);
    visited[0] = true;
    distance[0] = 0;

    cout << "Ordre BFS : ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[node] + 1;
                q.push(neighbor);
            }
        }
    }
    cout << endl;

    // Afficher les distances
    cout << "Distances depuis 0 :" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  Noeud " << i << " : distance " << distance[i] << endl;
    }

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
