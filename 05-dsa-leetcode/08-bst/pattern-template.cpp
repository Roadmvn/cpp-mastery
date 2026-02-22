// ============================================
// PATTERN : BST (Binary Search Tree) - Templates 
// ============================================
// Squelettes copier-coller pour BST
// Compile : g++ -std=c++17 -o pattern pattern-template.cpp
// ============================================

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================
// TEMPLATE 1 : Recherche dans un BST
// ============================================
TreeNode* searchBST(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    if (val < root->val) return searchBST(root->left, val);
    return searchBST(root->right, val);
}

// ============================================
// TEMPLATE 2 : Insertion dans un BST
// ============================================
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

// ============================================
// TEMPLATE 3 : Validation BST avec bornes
// ============================================
bool isValidBST(TreeNode* root, long minVal = LONG_MIN, long maxVal = LONG_MAX) {
    if (!root) return true;
    if (root->val <= minVal || root->val >= maxVal) return false;
    return isValidBST(root->left, minVal, root->val)
        && isValidBST(root->right, root->val, maxVal);
}

// ============================================
// TEMPLATE 4 : Inorder traversal (donne tri croissant)
// ============================================
void inorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorder(root->left, result);
    result.push_back(root->val);
    inorder(root->right, result);
}

// ============================================
// TEMPLATE 5 : Kth Smallest
// ============================================
void kthSmallestHelper(TreeNode* root, int& k, int& result) {
    if (!root || k <= 0) return;
    kthSmallestHelper(root->left, k, result);
    if (--k == 0) { result = root->val; return; }
    kthSmallestHelper(root->right, k, result);
}

int kthSmallest(TreeNode* root, int k) {
    int result = -1;
    kthSmallestHelper(root, k, result);
    return result;
}

// ============================================
// TEMPLATE 6 : LCA dans un BST
// ============================================
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val < root->val && q->val < root->val)
        return lowestCommonAncestor(root->left, p, q);
    if (p->val > root->val && q->val > root->val)
        return lowestCommonAncestor(root->right, p, q);
    return root; // split point = LCA
}

// ============================================
// TEMPLATE 7 : Suppression dans un BST
// ============================================
TreeNode* findMin(TreeNode* root) {
    while (root->left) root = root->left;
    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->val) root->left = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        // Cas 1 : feuille ou un seul enfant
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        // Cas 2 : deux enfants -> remplacer par successeur inorder
        TreeNode* successor = findMin(root->right);
        root->val = successor->val;
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
    //      3   7
    //     / \   \
    //    2   4   8
    TreeNode* root = nullptr;
    for (int v : {5, 3, 7, 2, 4, 8})
        root = insertBST(root, v);

    cout << "Inorder (tri croissant): ";
    printInorder(root);
    cout << endl;

    cout << "BST valide: " << (isValidBST(root) ? "OUI" : "NON") << endl;

    cout << "Recherche 4: " << (searchBST(root, 4) ? "TROUVE" : "PAS TROUVE") << endl;
    cout << "Recherche 9: " << (searchBST(root, 9) ? "TROUVE" : "PAS TROUVE") << endl;

    cout << "3eme plus petit: " << kthSmallest(root, 3) << endl; // 4

    root = deleteNode(root, 3);
    cout << "Apres suppression de 3: ";
    printInorder(root);
    cout << endl;

    return 0;
}
