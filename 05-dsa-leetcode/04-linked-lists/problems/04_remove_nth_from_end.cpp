// ============================================
// LeetCode #19 - Remove Nth Node From End of List (Medium)
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/
// ============================================
// Enonce : Supprimer le n-ieme noeud depuis la FIN de la liste.
// Faire en un seul passage.
//
// Exemple : head = [1,2,3,4,5], n = 2 -> Output: [1,2,3,5]
//           (on retire le 4, qui est 2eme depuis la fin)
//
// Compile : g++ -std=c++17 04_remove_nth_from_end.cpp -o 04

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* buildList(vector<int>& vals) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    for (int v : vals) { curr->next = new ListNode(v); curr = curr->next; }
    return dummy.next;
}

void printList(ListNode* head) {
    while (head) { cout << head->val; if (head->next) cout << " -> "; head = head->next; }
    cout << " -> NULL" << endl;
}

// -----------------------------------------------
// BRUTE FORCE : O(n) temps (2 passes) | O(1) espace
// 1er passage : compter les noeuds
// 2eme passage : supprimer le (length - n)ieme
// -----------------------------------------------
ListNode* removeNthFromEndBrute(ListNode* head, int n) {
    // Compter
    int length = 0;
    ListNode* curr = head;
    while (curr) { length++; curr = curr->next; }

    // Si on supprime le head
    if (n == length) return head->next;

    // Aller au noeud juste AVANT celui a supprimer
    curr = head;
    for (int i = 0; i < length - n - 1; i++) {
        curr = curr->next;
    }
    curr->next = curr->next->next;
    return head;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps (1 passe) | O(1) espace
// Two pointers avec ecart de n noeuds
//
// Schema pour [1,2,3,4,5], n=2 :
//
//   dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL
//   fast                                       (avance n+1 pas)
//
//   dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL
//   slow                    fast               (avance ensemble)
//
//   dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL
//                       slow               fast
//
//   slow.next = slow.next.next  ->  3 pointe vers 5
//   Resultat : 1 -> 2 -> 3 -> 5
// -----------------------------------------------
ListNode* removeNthFromEndOptimal(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;

    ListNode* fast = &dummy;
    ListNode* slow = &dummy;

    // Avancer fast de n+1 pas pour creer l'ecart
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }

    // Avancer les deux ensemble jusqu'a ce que fast atteigne NULL
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }

    // slow est juste AVANT le noeud a supprimer
    slow->next = slow->next->next;
    return dummy.next;
}

int main() {
    cout << "=== #19 Remove Nth Node From End of List ===" << endl;

    vector<int> v1 = {1, 2, 3, 4, 5};
    cout << "Input: [1,2,3,4,5], n=2" << endl;
    cout << "Brute:   "; printList(removeNthFromEndBrute(buildList(v1), 2));
    cout << "Optimal: "; printList(removeNthFromEndOptimal(buildList(v1), 2));
    cout << "(attendu: 1 -> 2 -> 3 -> 5 -> NULL)" << endl;
    cout << endl;

    vector<int> v2 = {1};
    cout << "Input: [1], n=1" << endl;
    cout << "Optimal: "; printList(removeNthFromEndOptimal(buildList(v2), 1));
    cout << "(attendu: NULL)" << endl;
    cout << endl;

    vector<int> v3 = {1, 2};
    cout << "Input: [1,2], n=1" << endl;
    cout << "Optimal: "; printList(removeNthFromEndOptimal(buildList(v3), 1));
    cout << "(attendu: 1 -> NULL)" << endl;
    cout << endl;

    vector<int> v4 = {1, 2};
    cout << "Input: [1,2], n=2" << endl;
    cout << "Optimal: "; printList(removeNthFromEndOptimal(buildList(v4), 2));
    cout << "(attendu: 2 -> NULL)" << endl;

    return 0;
}
