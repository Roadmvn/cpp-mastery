// ============================================
// LeetCode #141 - Linked List Cycle (Easy)
// https://leetcode.com/problems/linked-list-cycle/
// ============================================
// Enonce : Determiner si une linked list a un cycle.
// Un cycle existe si un noeud peut etre atteint a nouveau en suivant next.
//
// Exemple : head = [3,2,0,-4], pos = 1 -> Output: true
//           (le dernier noeud pointe vers le noeud d'index 1)
//
// Compile : g++ -std=c++17 03_linked_list_cycle.cpp -o 03

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Helper : creer une liste avec cycle a la position pos (-1 = pas de cycle)
ListNode* buildListWithCycle(vector<int>& vals, int pos) {
    if (vals.empty()) return nullptr;
    vector<ListNode*> nodes;
    for (int v : vals) nodes.push_back(new ListNode(v));
    for (int i = 0; i < (int)nodes.size() - 1; i++) nodes[i]->next = nodes[i + 1];
    if (pos >= 0) nodes.back()->next = nodes[pos]; // creer le cycle
    return nodes[0];
}

// -----------------------------------------------
// BRUTE FORCE : O(n) temps | O(n) espace
// HashSet pour stocker les noeuds visites
// -----------------------------------------------
bool hasCycleBrute(ListNode* head) {
    unordered_set<ListNode*> visited;
    ListNode* curr = head;

    while (curr) {
        if (visited.count(curr)) return true; // deja visite -> cycle
        visited.insert(curr);
        curr = curr->next;
    }
    return false;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(1) espace
// Floyd's Cycle Detection (Tortue et Lievre)
//
// Schema :
//   [3] -> [2] -> [0] -> [-4]
//           ^               |
//           |_______________|
//
//   slow (1 pas) : 3 -> 2 -> 0 -> -4 -> 2 -> 0
//   fast (2 pas) : 3 -> 0 -> 2 -> -4 -> 0 -> 2
//
//   Quand slow == fast -> CYCLE DETECTE
//
//   Pourquoi ca marche ?
//   - Si pas de cycle, fast atteint NULL
//   - Si cycle, fast "rattrape" slow (1 pas de plus par tour)
//   - Ils se rencontrent forcement dans le cycle
// -----------------------------------------------
bool hasCycleOptimal(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;         // 1 pas
        fast = fast->next->next;   // 2 pas

        if (slow == fast) return true; // rencontre -> cycle
    }
    return false; // fast a atteint NULL -> pas de cycle
}

int main() {
    cout << "=== #141 Linked List Cycle ===" << endl;

    // Test 1 : cycle a pos 1
    vector<int> v1 = {3, 2, 0, -4};
    ListNode* list1 = buildListWithCycle(v1, 1);
    cout << "Input: [3,2,0,-4], pos=1" << endl;
    cout << "Brute force: " << hasCycleBrute(list1) << " (attendu: 1)" << endl;
    cout << "Optimal:     " << hasCycleOptimal(list1) << " (attendu: 1)" << endl;
    cout << endl;

    // Test 2 : cycle a pos 0
    vector<int> v2 = {1, 2};
    ListNode* list2 = buildListWithCycle(v2, 0);
    cout << "Input: [1,2], pos=0" << endl;
    cout << "Brute force: " << hasCycleBrute(list2) << " (attendu: 1)" << endl;
    cout << "Optimal:     " << hasCycleOptimal(list2) << " (attendu: 1)" << endl;
    cout << endl;

    // Test 3 : pas de cycle
    vector<int> v3 = {1};
    ListNode* list3 = buildListWithCycle(v3, -1);
    cout << "Input: [1], pos=-1" << endl;
    cout << "Brute force: " << hasCycleBrute(list3) << " (attendu: 0)" << endl;
    cout << "Optimal:     " << hasCycleOptimal(list3) << " (attendu: 0)" << endl;

    return 0;
}
