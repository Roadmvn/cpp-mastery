// ============================================
// LeetCode #100 - Same Tree (Easy) 🌳
// https://leetcode.com/problems/same-tree/
// ============================================
//
// ENONCE :
// Verifier si deux arbres binaires sont identiques.
// Deux arbres sont identiques si ils ont la meme structure
// et les memes valeurs a chaque noeud.
//
//     [1]      [1]
//    /   \    /   \       -> true (identiques)
//   [2]  [3] [2]  [3]
//
//     [1]      [1]
//    /            \       -> false (structure differente)
//   [2]           [2]
//
// ============================================

#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================
// BRUTE FORCE : BFS iteratif avec deux queues
// On parcourt les deux arbres en parallele
// Temps : O(n) | Espace : O(n)
// ============================================
// bool isSameTree(TreeNode* p, TreeNode* q) {
//     queue<TreeNode*> q1, q2;
//     q1.push(p); q2.push(q);
//     while (!q1.empty() && !q2.empty()) {
//         TreeNode* n1 = q1.front(); q1.pop();
//         TreeNode* n2 = q2.front(); q2.pop();
//         if (!n1 && !n2) continue;
//         if (!n1 || !n2) return false;
//         if (n1->val != n2->val) return false;
//         q1.push(n1->left);  q2.push(n2->left);
//         q1.push(n1->right); q2.push(n2->right);
//     }
//     return q1.empty() && q2.empty();
// }

// ============================================
// SOLUTION OPTIMALE : DFS recursif
// Compare noeud par noeud recursivement
// Temps : O(n) | Espace : O(h)
// ============================================
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    return p->val == q->val
        && isSameTree(p->left, q->left)
        && isSameTree(p->right, q->right);
}

int main() {
    // Test 1 : arbres identiques
    TreeNode* p1 = new TreeNode(1);
    p1->left = new TreeNode(2);
    p1->right = new TreeNode(3);

    TreeNode* q1 = new TreeNode(1);
    q1->left = new TreeNode(2);
    q1->right = new TreeNode(3);

    cout << "Test 1 - identiques: " << (isSameTree(p1, q1) ? "OK" : "FAIL") << endl;

    // Test 2 : structure differente
    TreeNode* p2 = new TreeNode(1);
    p2->left = new TreeNode(2);

    TreeNode* q2 = new TreeNode(1);
    q2->right = new TreeNode(2);

    cout << "Test 2 - structure diff: " << (!isSameTree(p2, q2) ? "OK" : "FAIL") << endl;

    // Test 3 : valeurs differentes
    TreeNode* p3 = new TreeNode(1);
    p3->left = new TreeNode(2);
    p3->right = new TreeNode(1);

    TreeNode* q3 = new TreeNode(1);
    q3->left = new TreeNode(1);
    q3->right = new TreeNode(2);

    cout << "Test 3 - valeurs diff: " << (!isSameTree(p3, q3) ? "OK" : "FAIL") << endl;

    // Test 4 : deux arbres vides
    cout << "Test 4 - deux vides: " << (isSameTree(nullptr, nullptr) ? "OK" : "FAIL") << endl;

    // Test 5 : un vide, un non
    cout << "Test 5 - un vide: " << (!isSameTree(p1, nullptr) ? "OK" : "FAIL") << endl;

    return 0;
}
