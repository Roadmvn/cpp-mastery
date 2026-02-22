// ============================================================
// Priority Queue et Heap — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// PARTIE 1 : Max-Heap basique
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Max-Heap ===" << endl;

    priority_queue<int> maxHeap;

    int values[] = {15, 30, 10, 45, 20, 5};
    for (int val : values) {
        maxHeap.push(val);
        cout << "Push " << val << " | top: " << maxHeap.top() << endl;
    }

    // Extraire en ordre decroissant
    cout << "Extraction (decroissant) : ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    cout << endl;
}

// ============================================================
// PARTIE 2 : Min-Heap
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : Min-Heap ===" << endl;

    priority_queue<int, vector<int>, greater<int>> minHeap;

    int values[] = {15, 30, 10, 45, 20, 5};
    for (int val : values) {
        minHeap.push(val);
        cout << "Push " << val << " | top: " << minHeap.top() << endl;
    }

    // Extraire en ordre croissant
    cout << "Extraction (croissant) : ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : Heap avec pairs et custom comparator
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : Custom comparator ===" << endl;

    vector<pair<string, int>> tasks = {
        {"Bug fix", 3}, {"Feature", 1}, {"Refactor", 2},
        {"Deploy", 5}, {"Test", 4}
    };

    // Comparateur : max-heap par priorite (second)
    auto cmp = [](const pair<string,int>& a, const pair<string,int>& b) {
        return a.second < b.second;  // '<' pour max-heap
    };

    priority_queue<pair<string,int>, vector<pair<string,int>>, decltype(cmp)> pq(cmp);

    for (auto& task : tasks) {
        pq.push(task);
    }

    // Extraire par priorite decroissante
    cout << "Taches par priorite :" << endl;
    while (!pq.empty()) {
        auto [name, priority] = pq.top();
        pq.pop();
        cout << "  [" << priority << "] " << name << endl;
    }

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
