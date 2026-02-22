// ============================================
// LeetCode #105 - Construct Binary Tree from Preorder and Inorder (Medium) 🌳
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// ============================================
//
// ENONCE :
// Construire un arbre binaire a partir de son parcours preorder et inorder.
//
// preorder = [3,9,20,15,7]   (R-G-D)
// inorder  = [9,3,15,20,7]   (G-R-D)
//
// Resultat :
//        3
//       / \
//      9  20
//        /  \
//       15   7
//
// ASTUCE :
// - preorder[0] = racine
// - Dans inorder, tout ce qui est a gauche de la racine = sous-arbre gauche
// - Tout ce qui est a droite = sous-arbre droite
//
//   inorder:  [9 | 3 | 15, 20, 7]
//              G    R      D
// ============================================

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================
// BRUTE FORCE : Recherche lineaire dans inorder a chaque appel
// On cherche la racine dans inorder avec find()
// Temps : O(n^2) | Espace : O(n)
// ============================================
// TreeNode* build(vector<int>& preorder, int& preIdx,
//                 vector<int>& inorder, int inLeft, int inRight) {
//     if (inLeft > inRight) return nullptr;
//     int rootVal = preorder[preIdx++];
//     TreeNode* root = new TreeNode(rootVal);
//     // Recherche lineaire O(n)
//     int mid = inLeft;
//     while (inorder[mid] != rootVal) mid++;
//     root->left = build(preorder, preIdx, inorder, inLeft, mid - 1);
//     root->right = build(preorder, preIdx, inorder, mid + 1, inRight);
//     return root;
// }
// TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//     int preIdx = 0;
//     return build(preorder, preIdx, inorder, 0, inorder.size() - 1);
// }

// ============================================
// SOLUTION OPTIMALE : HashMap pour lookup O(1) dans inorder
// On stocke valeur -> index dans une map
// Temps : O(n) | Espace : O(n)
// ============================================
class Solution {
    unordered_map<int, int> inMap; // val -> index dans inorder
    int preIdx = 0;

    TreeNode* build(vector<int>& preorder, int inLeft, int inRight) {
        if (inLeft > inRight) return nullptr;

        int rootVal = preorder[preIdx++];
        TreeNode* root = new TreeNode(rootVal);

        int mid = inMap[rootVal]; // O(1) au lieu de O(n)

        root->left = build(preorder, inLeft, mid - 1);
        root->right = build(preorder, mid + 1, inRight);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        preIdx = 0;
        inMap.clear();
        for (int i = 0; i < (int)inorder.size(); i++) {
            inMap[inorder[i]] = i;
        }
        return build(preorder, 0, inorder.size() - 1);
    }
};

// --- Helpers ---
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

void printPreorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

int main() {
    Solution sol;

    // Test 1
    vector<int> preorder1 = {3, 9, 20, 15, 7};
    vector<int> inorder1 = {9, 3, 15, 20, 7};

    TreeNode* root1 = sol.buildTree(preorder1, inorder1);
    cout << "Test 1 - preorder: ";
    printPreorder(root1);
    cout << endl;
    cout << "Test 1 - inorder:  ";
    printInorder(root1);
    cout << endl;
    // Attendu preorder: 3 9 20 15 7
    // Attendu inorder:  9 3 15 20 7

    bool ok1 = root1->val == 3
            && root1->left->val == 9
            && root1->right->val == 20;
    cout << "  -> " << (ok1 ? "OK" : "FAIL") << endl;

    // Test 2 : un seul noeud
    vector<int> pre2 = {-1};
    vector<int> in2 = {-1};
    TreeNode* root2 = sol.buildTree(pre2, in2);
    cout << "Test 2 - un noeud: " << (root2->val == -1 && !root2->left && !root2->right ? "OK" : "FAIL") << endl;

    // Test 3 : arbre en ligne
    // preorder = [1,2,3] -> 1 est racine, 2 est gauche, 3 est gauche de 2
    vector<int> pre3 = {1, 2, 3};
    vector<int> in3 = {3, 2, 1};
    TreeNode* root3 = sol.buildTree(pre3, in3);
    cout << "Test 3 - en ligne: " << (root3->val == 1 && root3->left->val == 2 ? "OK" : "FAIL") << endl;

    return 0;
}
