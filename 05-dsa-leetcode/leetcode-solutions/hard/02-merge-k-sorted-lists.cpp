// https://leetcode.com/problems/merge-k-sorted-lists/
// #23 - Merge k Sorted Lists
//
// Fusionner k listes chainees triees en une seule liste triee.
//
// Approche : min-heap (priority_queue).
// Inserer la tete de chaque liste dans le heap.
// Extraire le minimum, l'ajouter au resultat, et inserer son successeur.
// Complexite temps : O(N log k) N = total noeuds, k = nombre de listes
// Complexite espace : O(k) pour le heap

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Comparateur : min-heap sur la valeur des noeuds
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val; // min-heap
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

        // Initialiser le heap avec la tete de chaque liste non vide
        for (ListNode* head : lists) {
            if (head) pq.push(head);
        }

        ListNode dummy(0);
        ListNode* cur = &dummy;

        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            cur->next = node;
            cur = cur->next;

            // Inserer le successeur dans le heap
            if (node->next) pq.push(node->next);
        }

        return dummy.next;
    }
};

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

    // Test 1 : 3 listes
    vector<ListNode*> lists1 = {
        build({1, 4, 5}),
        build({1, 3, 4}),
        build({2, 6})
    };
    print(sol.mergeKLists(lists1)); // 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6

    // Test 2 : listes vides
    vector<ListNode*> lists2 = {};
    print(sol.mergeKLists(lists2)); // (vide)

    // Test 3 : une liste vide
    vector<ListNode*> lists3 = {nullptr};
    print(sol.mergeKLists(lists3)); // (vide)

    return 0;
}
