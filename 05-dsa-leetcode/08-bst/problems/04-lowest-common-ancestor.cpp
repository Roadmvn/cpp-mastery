// ============================================
// LeetCode #235 - Lowest Common Ancestor of a BST (Medium) 🔍
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// ============================================
//
// ENONCE :
// Trouver le plus proche ancetre commun (LCA) de deux noeuds dans un BST.
// Le LCA est le noeud le plus profond qui est ancetre des deux noeuds.
// Un noeud peut etre son propre ancetre.
//
//          6
//         / \
//        2   8
//       / \ / \
//      0  4 7  9
//        / \
//       3   5
//
// LCA(2, 8) = 6  (split point)
// LCA(2, 4) = 2  (2 est ancetre de 4)
// LCA(0, 5) = 2
//
// ASTUCE BST :
// - Si p et q sont tous les deux < root -> LCA est a gauche
// - Si p et q sont tous les deux > root -> LCA est a droite
// - Sinon (split) -> root EST le LCA !
//
// ============================================

#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================
// BRUTE FORCE : DFS generique (comme pour un arbre binaire normal)
// Ne profite pas de la propriete BST
// Temps : O(n) | Espace : O(h)
// ============================================
// TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//     if (!root || root == p || root == q) return root;
//     TreeNode* left = lowestCommonAncestor(root->left, p, q);
//     TreeNode* right = lowestCommonAncestor(root->right, p, q);
//     if (left && right) return root;
//     return left ? left : right;
// }

// ============================================
// SOLUTION OPTIMALE : Exploiter la propriete BST
// On suit le chemin de la racine vers le split point
// Temps : O(h) = O(log n) si equilibre | Espace : O(1) iteratif
// ============================================
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val) {
            root = root->left;   // les deux a gauche
        } else if (p->val > root->val && q->val > root->val) {
            root = root->right;  // les deux a droite
        } else {
            return root;         // split point = LCA
        }
    }
    return nullptr;
}

int main() {
    //          6
    //         / \
    //        2   8
    //       / \ / \
    //      0  4 7  9
    //        / \
    //       3   5
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);

    TreeNode* n0 = root->left->left;       // 0
    TreeNode* n2 = root->left;             // 2
    TreeNode* n4 = root->left->right;      // 4
    TreeNode* n5 = root->left->right->right; // 5
    TreeNode* n8 = root->right;            // 8

    // Test 1 : LCA(2, 8) = 6
    auto r1 = lowestCommonAncestor(root, n2, n8);
    cout << "Test 1 - LCA(2,8)=6: " << (r1->val == 6 ? "OK" : "FAIL") << endl;

    // Test 2 : LCA(2, 4) = 2
    auto r2 = lowestCommonAncestor(root, n2, n4);
    cout << "Test 2 - LCA(2,4)=2: " << (r2->val == 2 ? "OK" : "FAIL") << endl;

    // Test 3 : LCA(0, 5) = 2
    auto r3 = lowestCommonAncestor(root, n0, n5);
    cout << "Test 3 - LCA(0,5)=2: " << (r3->val == 2 ? "OK" : "FAIL") << endl;

    // Test 4 : LCA(0, 4) = 2
    auto r4 = lowestCommonAncestor(root, n0, n4);
    cout << "Test 4 - LCA(0,4)=2: " << (r4->val == 2 ? "OK" : "FAIL") << endl;

    return 0;
}
