// ============================================
// LeetCode #700 - Search in a Binary Search Tree (Easy) 🔍
// https://leetcode.com/problems/search-in-a-binary-search-tree/
// ============================================
//
// ENONCE :
// Trouver un noeud avec la valeur donnee dans un BST.
// Retourner le sous-arbre enracine a ce noeud. Si pas trouve -> null.
//
//        4
//       / \
//      2   7       chercher val=2 -> retourner sous-arbre [2,1,3]
//     / \
//    1   3
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
// BRUTE FORCE : Parcours DFS classique (ignore la propriete BST)
// On visite chaque noeud sans exploiter l'ordre
// Temps : O(n) | Espace : O(h)
// ============================================
// TreeNode* searchBST(TreeNode* root, int val) {
//     if (!root) return nullptr;
//     if (root->val == val) return root;
//     TreeNode* left = searchBST(root->left, val);
//     if (left) return left;
//     return searchBST(root->right, val);
// }

// ============================================
// SOLUTION OPTIMALE : Exploiter la propriete BST
// Si val < root, aller a gauche. Si val > root, aller a droite.
// Temps : O(log n) en moyenne, O(n) pire cas | Espace : O(h)
// ============================================
TreeNode* searchBST(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    if (val < root->val) return searchBST(root->left, val);
    return searchBST(root->right, val);
}

int main() {
    //        4
    //       / \
    //      2   7
    //     / \
    //    1   3
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    // Test 1 : chercher 2
    TreeNode* res1 = searchBST(root, 2);
    cout << "Test 1 - chercher 2: " << (res1 && res1->val == 2 ? "OK" : "FAIL") << endl;

    // Test 2 : sous-arbre correct
    cout << "Test 2 - sous-arbre: "
         << (res1->left->val == 1 && res1->right->val == 3 ? "OK" : "FAIL") << endl;

    // Test 3 : chercher 5 (inexistant)
    TreeNode* res3 = searchBST(root, 5);
    cout << "Test 3 - inexistant: " << (res3 == nullptr ? "OK" : "FAIL") << endl;

    // Test 4 : chercher la racine
    TreeNode* res4 = searchBST(root, 4);
    cout << "Test 4 - racine: " << (res4 && res4->val == 4 ? "OK" : "FAIL") << endl;

    // Test 5 : arbre vide
    cout << "Test 5 - vide: " << (searchBST(nullptr, 1) == nullptr ? "OK" : "FAIL") << endl;

    return 0;
}
