// ============================================
// LeetCode #230 - Kth Smallest Element in a BST (Medium) 🔍
// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
// ============================================
//
// ENONCE :
// Trouver le k-eme plus petit element dans un BST.
// k est 1-indexed (k=1 = le plus petit).
//
//        3
//       / \
//      1   4       k=1 -> 1 (le plus petit)
//       \
//        2
//
// ASTUCE CLE :
// Inorder traversal d'un BST = elements tries en ordre croissant !
// Inorder: [1, 2, 3, 4] -> k=1 retourne 1, k=3 retourne 3
//
// ============================================

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================
// BRUTE FORCE : Inorder complet puis retourner k-1
// On stocke tout le parcours inorder dans un vecteur
// Temps : O(n) | Espace : O(n)
// ============================================
// int kthSmallest(TreeNode* root, int k) {
//     vector<int> vals;
//     function<void(TreeNode*)> inorder = [&](TreeNode* node) {
//         if (!node) return;
//         inorder(node->left);
//         vals.push_back(node->val);
//         inorder(node->right);
//     };
//     inorder(root);
//     return vals[k - 1];
// }

// ============================================
// SOLUTION OPTIMALE : Inorder avec arret precoce
// On decremente k a chaque visite et on s'arrete des que k == 0
// Temps : O(h + k) | Espace : O(h)
// ============================================
void inorder(TreeNode* root, int& k, int& result) {
    if (!root || k <= 0) return;
    inorder(root->left, k, result);
    if (--k == 0) {
        result = root->val;
        return;
    }
    inorder(root->right, k, result);
}

int kthSmallest(TreeNode* root, int k) {
    int result = -1;
    inorder(root, k, result);
    return result;
}

int main() {
    //        3
    //       / \
    //      1   4
    //       \
    //        2
    TreeNode* t1 = new TreeNode(3);
    t1->left = new TreeNode(1);
    t1->right = new TreeNode(4);
    t1->left->right = new TreeNode(2);

    cout << "Test 1 - k=1: " << (kthSmallest(t1, 1) == 1 ? "OK" : "FAIL")
         << " (got " << kthSmallest(t1, 1) << ")" << endl;

    cout << "Test 2 - k=2: " << (kthSmallest(t1, 2) == 2 ? "OK" : "FAIL")
         << " (got " << kthSmallest(t1, 2) << ")" << endl;

    //        5
    //       / \
    //      3   6
    //     / \
    //    2   4
    //   /
    //  1
    TreeNode* t2 = new TreeNode(5);
    t2->left = new TreeNode(3);
    t2->right = new TreeNode(6);
    t2->left->left = new TreeNode(2);
    t2->left->right = new TreeNode(4);
    t2->left->left->left = new TreeNode(1);

    cout << "Test 3 - k=3: " << (kthSmallest(t2, 3) == 3 ? "OK" : "FAIL")
         << " (got " << kthSmallest(t2, 3) << ")" << endl;

    cout << "Test 4 - k=6 (max): " << (kthSmallest(t2, 6) == 6 ? "OK" : "FAIL")
         << " (got " << kthSmallest(t2, 6) << ")" << endl;

    cout << "Test 5 - k=1 (min): " << (kthSmallest(t2, 1) == 1 ? "OK" : "FAIL")
         << " (got " << kthSmallest(t2, 1) << ")" << endl;

    return 0;
}
