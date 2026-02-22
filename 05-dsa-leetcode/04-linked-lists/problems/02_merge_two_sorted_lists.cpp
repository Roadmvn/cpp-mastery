// ============================================
// LeetCode #21 - Merge Two Sorted Lists (Easy)
// https://leetcode.com/problems/merge-two-sorted-lists/
// ============================================
// Enonce : Fusionner deux listes triees en une seule liste triee.
//
// Exemple : l1 = [1,2,4], l2 = [1,3,4] -> Output: [1,1,2,3,4,4]
//
// Compile : g++ -std=c++17 02_merge_two_sorted_lists.cpp -o 02

#include <iostream>
#include <vector>
#include <algorithm>
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
// BRUTE FORCE : O((n+m) log(n+m)) temps | O(n+m) espace
// Collecter toutes les valeurs, trier, reconstruire
// -----------------------------------------------
ListNode* mergeTwoListsBrute(ListNode* l1, ListNode* l2) {
    vector<int> vals;
    while (l1) { vals.push_back(l1->val); l1 = l1->next; }
    while (l2) { vals.push_back(l2->val); l2 = l2->next; }
    sort(vals.begin(), vals.end());

    ListNode dummy(0);
    ListNode* curr = &dummy;
    for (int v : vals) { curr->next = new ListNode(v); curr = curr->next; }
    return dummy.next;
}

// -----------------------------------------------
// OPTIMAL ITERATIF : O(n + m) temps | O(1) espace
// Merge avec dummy node
//
// Schema :
//   l1: 1 -> 2 -> 4
//   l2: 1 -> 3 -> 4
//
//   dummy -> 1(l1) -> 1(l2) -> 2(l1) -> 3(l2) -> 4(l1) -> 4(l2)
//
//   A chaque etape, on compare les heads et on prend le plus petit
// -----------------------------------------------
ListNode* mergeTwoListsIterative(ListNode* l1, ListNode* l2) {
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

    // Attacher le reste
    curr->next = l1 ? l1 : l2;
    return dummy.next;
}

// -----------------------------------------------
// OPTIMAL RECURSIF : O(n + m) temps | O(n + m) espace (call stack)
// -----------------------------------------------
ListNode* mergeTwoListsRecursive(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->val <= l2->val) {
        l1->next = mergeTwoListsRecursive(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoListsRecursive(l1, l2->next);
        return l2;
    }
}

int main() {
    cout << "=== #21 Merge Two Sorted Lists ===" << endl;

    vector<int> v1 = {1, 2, 4}, v2 = {1, 3, 4};
    cout << "l1: "; printList(buildList(v1));
    cout << "l2: "; printList(buildList(v2));

    ListNode* res1 = mergeTwoListsIterative(buildList(v1), buildList(v2));
    cout << "Merged (iteratif): "; printList(res1);

    ListNode* res2 = mergeTwoListsRecursive(buildList(v1), buildList(v2));
    cout << "Merged (recursif): "; printList(res2);
    cout << endl;

    vector<int> v3 = {}, v4 = {0};
    cout << "l1=[], l2=[0]" << endl;
    ListNode* res3 = mergeTwoListsIterative(buildList(v3), buildList(v4));
    cout << "Merged: "; printList(res3);
    cout << endl;

    vector<int> v5 = {}, v6 = {};
    cout << "l1=[], l2=[]" << endl;
    ListNode* res4 = mergeTwoListsIterative(buildList(v5), buildList(v6));
    cout << "Merged: "; printList(res4);

    return 0;
}
