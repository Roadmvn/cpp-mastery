// ============================================
// LeetCode #450 - Delete Node in a BST (Medium) 🔍
// https://leetcode.com/problems/delete-node-in-a-bst/
// ============================================
//
// ENONCE :
// Supprimer un noeud avec la valeur donnee dans un BST.
// Retourner la racine du BST modifie.
//
// 3 CAS de suppression :
//
// CAS 1 : Noeud est une feuille -> juste supprimer
//      5              5
//     / \    del 2   / \
//    3   6   ->     3   6
//   / \              \
//  2   4              4
//
// CAS 2 : Noeud a un seul enfant -> remplacer par l'enfant
//      5              5
//     / \    del 3   / \
//    3   6   ->     4   6
//     \
//      4
//
// CAS 3 : Noeud a deux enfants -> remplacer par successeur inorder
//      5              6
//     / \    del 5   / \
//    3   8   ->     3   8
//       / \            /
//      6   9          9     (6 = successeur inorder de 5)
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
// BRUTE FORCE : Inorder traversal, reconstruire sans le noeud
// Collecter tous les elements sauf celui a supprimer, reconstruire
// Temps : O(n) | Espace : O(n)
// ============================================
// (Trop complexe et inefficace, voir approche optimale)

// ============================================
// SOLUTION OPTIMALE : Suppression recursive avec 3 cas
// 1. Chercher le noeud dans le BST
// 2. Gerer les 3 cas (feuille, 1 enfant, 2 enfants)
// Temps : O(h) | Espace : O(h)
// ============================================
TreeNode* findMin(TreeNode* root) {
    while (root->left) root = root->left;
    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;

    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
        // Noeud trouve ! Gerer les 3 cas

        // Cas 1 & 2 : pas d'enfant gauche -> retourner droite
        if (!root->left) {
            TreeNode* right = root->right;
            delete root;
            return right;
        }
        // Cas 2 : pas d'enfant droit -> retourner gauche
        if (!root->right) {
            TreeNode* left = root->left;
            delete root;
            return left;
        }
        // Cas 3 : deux enfants
        // Trouver le successeur inorder (plus petit du sous-arbre droit)
        TreeNode* successor = findMin(root->right);
        root->val = successor->val;
        // Supprimer le successeur du sous-arbre droit
        root->right = deleteNode(root->right, successor->val);
    }
    return root;
}

// --- Helper ---
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    //        5
    //       / \
    //      3   6
    //     / \   \
    //    2   4   7
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(7);

    cout << "Avant: ";
    printInorder(root);
    cout << endl;

    // Test 1 : supprimer feuille (2)
    root = deleteNode(root, 2);
    cout << "Apres del 2 (feuille): ";
    printInorder(root);
    cout << endl;
    // Attendu: 3 4 5 6 7

    // Test 2 : supprimer noeud avec un enfant (6 -> a 7 a droite)
    root = deleteNode(root, 6);
    cout << "Apres del 6 (1 enfant): ";
    printInorder(root);
    cout << endl;
    // Attendu: 3 4 5 7

    // Test 3 : supprimer noeud avec deux enfants (3 -> a 4)
    // Reconstruire pour ce test
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(3);
    root2->right = new TreeNode(6);
    root2->left->left = new TreeNode(2);
    root2->left->right = new TreeNode(4);
    root2->right->right = new TreeNode(7);

    root2 = deleteNode(root2, 3);
    cout << "Apres del 3 (2 enfants): ";
    printInorder(root2);
    cout << endl;
    // Attendu: 2 4 5 6 7

    // Test 4 : supprimer racine
    root2 = deleteNode(root2, 5);
    cout << "Apres del 5 (racine): ";
    printInorder(root2);
    cout << endl;
    // Attendu: 2 4 6 7

    // Test 5 : supprimer inexistant
    root2 = deleteNode(root2, 99);
    cout << "Apres del 99 (inexistant): ";
    printInorder(root2);
    cout << endl;
    // Attendu: 2 4 6 7 (inchange)

    return 0;
}
