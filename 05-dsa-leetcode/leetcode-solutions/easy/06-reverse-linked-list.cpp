// https://leetcode.com/problems/reverse-linked-list/
// #206 - Reverse Linked List
//
// Inverser une liste chainee simplement.
//
// Approche 1 (iteratif) : 3 pointeurs — prev, curr, next.
// Approche 2 (recursif) : inverser le reste puis relinker.
// Complexite temps : O(n) | Complexite espace : O(1) iter, O(n) recur (pile)

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    // Version iterative
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr) {
            ListNode* next = curr->next; // sauvegarder le suivant
            curr->next = prev;           // inverser le lien
            prev = curr;                 // avancer prev
            curr = next;                 // avancer curr
        }

        return prev; // nouveau head
    }

    // Version recursive
    ListNode* reverseListRecursive(ListNode* head) {
        // Cas de base : liste vide ou un seul noeud
        if (!head || !head->next) return head;

        // Inverser le reste de la liste
        ListNode* newHead = reverseListRecursive(head->next);

        // head->next pointe vers le dernier noeud inverse,
        // faire pointer ce noeud en retour vers head
        head->next->next = head;
        head->next = nullptr;

        return newHead;
    }
};

// Utilitaires pour les tests
ListNode* build(initializer_list<int> vals) {
    ListNode dummy(0);
    ListNode* cur = &dummy;
    for (int v : vals) {
        cur->next = new ListNode(v);
        cur = cur->next;
    }
    return dummy.next;
}

void print(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Solution sol;

    // Test iteratif
    ListNode* l1 = build({1, 2, 3, 4, 5});
    print(sol.reverseList(l1)); // 5 -> 4 -> 3 -> 2 -> 1

    ListNode* l2 = build({1, 2});
    print(sol.reverseList(l2)); // 2 -> 1

    // Test recursif
    ListNode* l3 = build({1, 2, 3, 4, 5});
    print(sol.reverseListRecursive(l3)); // 5 -> 4 -> 3 -> 2 -> 1

    return 0;
}
