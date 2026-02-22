// ============================================
// LeetCode #206 - Reverse Linked List (Easy)
// https://leetcode.com/problems/reverse-linked-list/
// ============================================
// Enonce : Inverser une singly linked list.
//
// Exemple : head = [1,2,3,4,5] -> Output: [5,4,3,2,1]
//
// Compile : g++ -std=c++17 01_reverse_linked_list.cpp -o 01

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
// BRUTE FORCE : O(n) temps | O(n) espace
// Stocker les valeurs dans un vector, reconstruire en sens inverse
// -----------------------------------------------
ListNode* reverseListBrute(ListNode* head) {
    vector<int> vals;
    ListNode* curr = head;
    while (curr) {
        vals.push_back(curr->val);
        curr = curr->next;
    }

    curr = head;
    for (int i = vals.size() - 1; i >= 0; i--) {
        curr->val = vals[i];
        curr = curr->next;
    }
    return head;
}

// -----------------------------------------------
// OPTIMAL ITERATIF : O(n) temps | O(1) espace
// Trois pointeurs : prev, curr, next
//
// Schema :
//   NULL   1 -> 2 -> 3 -> 4 -> 5 -> NULL
//   prev  curr
//
//   NULL <- 1    2 -> 3 -> 4 -> 5 -> NULL
//          prev curr
//
//   NULL <- 1 <- 2    3 -> 4 -> 5 -> NULL
//               prev curr
//
//   ... continue jusqu'a curr == NULL
//   prev pointe vers le nouveau head
// -----------------------------------------------
ListNode* reverseListIterative(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr) {
        ListNode* next = curr->next;  // sauvegarder le suivant
        curr->next = prev;            // inverser le pointeur
        prev = curr;                  // avancer prev
        curr = next;                  // avancer curr
    }
    return prev;
}

// -----------------------------------------------
// OPTIMAL RECURSIF : O(n) temps | O(n) espace (call stack)
// -----------------------------------------------
ListNode* reverseListRecursive(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* newHead = reverseListRecursive(head->next);
    head->next->next = head;  // le suivant pointe vers moi
    head->next = nullptr;     // je pointe vers null
    return newHead;
}

int main() {
    cout << "=== #206 Reverse Linked List ===" << endl;

    vector<int> v1 = {1, 2, 3, 4, 5};
    ListNode* list1 = buildList(v1);
    cout << "Original:  "; printList(list1);
    list1 = reverseListIterative(list1);
    cout << "Reversed (iteratif): "; printList(list1);

    vector<int> v2 = {1, 2, 3, 4, 5};
    ListNode* list2 = buildList(v2);
    list2 = reverseListRecursive(list2);
    cout << "Reversed (recursif): "; printList(list2);

    vector<int> v3 = {1, 2};
    ListNode* list3 = buildList(v3);
    list3 = reverseListIterative(list3);
    cout << "Reversed [1,2]: "; printList(list3);

    vector<int> v4 = {};
    ListNode* list4 = buildList(v4);
    list4 = reverseListIterative(list4);
    cout << "Reversed []: "; printList(list4);

    return 0;
}
