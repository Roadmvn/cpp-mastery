// ============================================
// LeetCode #143 - Reorder List (Medium)
// https://leetcode.com/problems/reorder-list/
// ============================================
// Enonce : Reordonner la liste L0 -> L1 -> ... -> Ln
// en L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> ...
// Modifier la liste in-place.
//
// Exemple : [1,2,3,4] -> [1,4,2,3]
// Exemple : [1,2,3,4,5] -> [1,5,2,4,3]
//
// Compile : g++ -std=c++17 05_reorder_list.cpp -o 05

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
// Stocker les noeuds dans un vector, reconstruire
// -----------------------------------------------
void reorderListBrute(ListNode* head) {
    if (!head) return;

    vector<ListNode*> nodes;
    ListNode* curr = head;
    while (curr) {
        nodes.push_back(curr);
        curr = curr->next;
    }

    int i = 0, j = nodes.size() - 1;
    while (i < j) {
        nodes[i]->next = nodes[j];
        i++;
        if (i == j) break;
        nodes[j]->next = nodes[i];
        j--;
    }
    nodes[i]->next = nullptr;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(1) espace
// 3 etapes :
// 1. Trouver le milieu (slow/fast)
// 2. Reverser la 2eme moitie
// 3. Merger les deux moities en alternant
//
// Schema pour [1, 2, 3, 4, 5] :
//
// Etape 1 : Trouver le milieu
//   [1] -> [2] -> [3] -> [4] -> [5]
//                  ^
//                 mid (slow)
//
// Etape 2 : Reverser la 2eme moitie (apres mid)
//   Premiere moitie : [1] -> [2] -> [3]
//   Deuxieme moitie : [5] -> [4]  (reversed)
//
// Etape 3 : Merge en alternant
//   [1] -> [5] -> [2] -> [4] -> [3] -> NULL
// -----------------------------------------------
void reorderListOptimal(ListNode* head) {
    if (!head || !head->next) return;

    // Etape 1 : Trouver le milieu
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Etape 2 : Reverser la 2eme moitie
    ListNode* prev = nullptr;
    ListNode* curr = slow->next;
    slow->next = nullptr; // couper la liste

    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    // prev = head de la 2eme moitie reversed

    // Etape 3 : Merger en alternant
    ListNode* first = head;
    ListNode* second = prev;

    while (second) {
        ListNode* tmp1 = first->next;
        ListNode* tmp2 = second->next;

        first->next = second;
        second->next = tmp1;

        first = tmp1;
        second = tmp2;
    }
}

int main() {
    cout << "=== #143 Reorder List ===" << endl;

    vector<int> v1 = {1, 2, 3, 4};
    ListNode* list1 = buildList(v1);
    cout << "Input:   "; printList(list1);
    reorderListOptimal(list1);
    cout << "Reorder: "; printList(list1);
    cout << "(attendu: 1 -> 4 -> 2 -> 3 -> NULL)" << endl;
    cout << endl;

    vector<int> v2 = {1, 2, 3, 4, 5};
    ListNode* list2 = buildList(v2);
    cout << "Input:   "; printList(list2);
    reorderListOptimal(list2);
    cout << "Reorder: "; printList(list2);
    cout << "(attendu: 1 -> 5 -> 2 -> 4 -> 3 -> NULL)" << endl;
    cout << endl;

    vector<int> v3 = {1};
    ListNode* list3 = buildList(v3);
    cout << "Input:   "; printList(list3);
    reorderListOptimal(list3);
    cout << "Reorder: "; printList(list3);
    cout << "(attendu: 1 -> NULL)" << endl;
    cout << endl;

    // Test brute force
    vector<int> v4 = {1, 2, 3, 4, 5};
    ListNode* list4 = buildList(v4);
    reorderListBrute(list4);
    cout << "Brute force [1,2,3,4,5]: "; printList(list4);
    cout << "(attendu: 1 -> 5 -> 2 -> 4 -> 3 -> NULL)" << endl;

    return 0;
}
