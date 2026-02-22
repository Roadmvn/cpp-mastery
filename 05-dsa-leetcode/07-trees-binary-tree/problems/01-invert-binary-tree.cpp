// ============================================
// LeetCode #226 - Invert Binary Tree (Easy) 
// https://leetcode.com/problems/invert-binary-tree/
// ============================================
//
// ENONCE :
// Inverser un arbre binaire (miroir).
// Chaque noeud : son enfant gauche devient droite et vice versa.
//
//     Entree :        Sortie :
//        4               4
//       / \             / \
//      2   7    ->     7   2
//     / \ / \         / \ / \
//    1  3 6  9       9  6 3  1
//
// ============================================

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================
// BRUTE FORCE : BFS iteratif avec queue
// On parcourt chaque noeud et on swap ses enfants
// Temps : O(n) | Espace : O(n)
// ============================================
// TreeNode* invertTree(TreeNode* root) {
//     if (!root) return nullptr;
//     queue<TreeNode*> q;
//     q.push(root);
//     while (!q.empty()) {
//         TreeNode* node = q.front();
//         q.pop();
//         swap(node->left, node->right);
//         if (node->left) q.push(node->left);
//         if (node->right) q.push(node->right);
//     }
//     return root;
// }

// ============================================
// SOLUTION OPTIMALE : DFS recursif
// Swap les enfants puis recurse sur chaque sous-arbre
// Temps : O(n) | Espace : O(h) ou h = hauteur
// ============================================
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

// --- Helpers ---
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    //        4
    //       / \
    //      2   7
    //     / \ / \
    //    1  3 6  9
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    cout << "Avant inversion (inorder): ";
    printInorder(root);
    cout << endl;

    invertTree(root);

    cout << "Apres inversion (inorder): ";
    printInorder(root);
    cout << endl;
    // Attendu : 9 7 6 4 3 2 1

    // Test arbre vide
    TreeNode* empty = nullptr;
    cout << "Arbre vide: " << (invertTree(empty) == nullptr ? "OK" : "FAIL") << endl;

    // Test un seul noeud
    TreeNode* single = new TreeNode(42);
    invertTree(single);
    cout << "Un noeud: " << (single->val == 42 ? "OK" : "FAIL") << endl;

    return 0;
}
