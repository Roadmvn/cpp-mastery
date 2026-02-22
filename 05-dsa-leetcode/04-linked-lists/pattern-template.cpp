// ============================================
// Linked Lists - Templates copier-coller
// ============================================
// Compile : g++ -std=c++17 pattern-template.cpp -o pattern-template

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Helper : creer une liste depuis un vector
ListNode* buildList(vector<int>& vals) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    for (int v : vals) {
        curr->next = new ListNode(v);
        curr = curr->next;
    }
    return dummy.next;
}

// Helper : afficher une liste
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL" << endl;
}

// -----------------------------------------------
// TEMPLATE 1 : Reverse iteratif
// O(n) temps | O(1) espace
// -----------------------------------------------
ListNode* reverseIterative(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr) {
        ListNode* next = curr->next;  // sauvegarder
        curr->next = prev;            // inverser le lien
        prev = curr;                  // avancer prev
        curr = next;                  // avancer curr
    }
    return prev; // nouveau head
}

// -----------------------------------------------
// TEMPLATE 2 : Reverse recursif
// O(n) temps | O(n) espace (call stack)
// -----------------------------------------------
ListNode* reverseRecursive(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* newHead = reverseRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

// -----------------------------------------------
// TEMPLATE 3 : Fast/Slow - Trouver le milieu
// O(n) temps | O(1) espace
// -----------------------------------------------
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; // milieu (ou 2eme milieu si pair)
}

// -----------------------------------------------
// TEMPLATE 4 : Detecter un cycle
// O(n) temps | O(1) espace
// -----------------------------------------------
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// -----------------------------------------------
// TEMPLATE 5 : Merge deux listes triees
// O(n + m) temps | O(1) espace
// -----------------------------------------------
ListNode* mergeSorted(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* curr = &dummy;

    while (l1 && l2) {
        if (l1->val <= l2->val) {
            curr->next = l1;
            l1 = l1->next;
        } else {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }
    curr->next = l1 ? l1 : l2;
    return dummy.next;
}

// -----------------------------------------------
// TEMPLATE 6 : Dummy node pour simplifier
// Utile quand le head peut changer
// -----------------------------------------------
ListNode* removeElements(ListNode* head, int val) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;
    ListNode* curr = head;

    while (curr) {
        if (curr->val == val) {
            prev->next = curr->next;
        } else {
            prev = curr;
        }
        curr = curr->next;
    }
    return dummy.next;
}

int main() {
    cout << "=== Linked List Templates ===" << endl;

    // Test reverse
    vector<int> v1 = {1, 2, 3, 4, 5};
    ListNode* list1 = buildList(v1);
    cout << "Original: "; printList(list1);
    list1 = reverseIterative(list1);
    cout << "Reversed: "; printList(list1);

    // Test find middle
    vector<int> v2 = {1, 2, 3, 4, 5};
    ListNode* list2 = buildList(v2);
    cout << "Middle of [1,2,3,4,5]: " << findMiddle(list2)->val << endl; // 3

    // Test merge
    vector<int> v3 = {1, 3, 5};
    vector<int> v4 = {2, 4, 6};
    ListNode* l3 = buildList(v3);
    ListNode* l4 = buildList(v4);
    cout << "Merged: "; printList(mergeSorted(l3, l4));

    // Test remove
    vector<int> v5 = {1, 2, 6, 3, 6};
    ListNode* list5 = buildList(v5);
    cout << "Remove 6 from [1,2,6,3,6]: ";
    printList(removeElements(list5, 6));

    return 0;
}
