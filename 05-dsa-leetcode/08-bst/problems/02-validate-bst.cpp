// ============================================
// LeetCode #98 - Validate Binary Search Tree (Medium) 
// https://leetcode.com/problems/validate-binary-search-tree/
// ============================================
//
// ENONCE :
// Verifier si un arbre binaire est un BST valide.
// Un BST valide :
//   - Sous-arbre gauche contient UNIQUEMENT des valeurs < noeud
//   - Sous-arbre droite contient UNIQUEMENT des valeurs > noeud
//   - Les deux sous-arbres sont aussi des BST
//
//     [2]          [5]
//    /   \        /   \
//  [1]   [3]    [1]   [4]     <- INVALIDE ! 4 < 5 mais a droite
//   VALIDE        [3]   [6]
//                  ^^^ 3 < 5 et dans sous-arbre droit = INVALIDE
//
// PIEGE : ne pas juste comparer parent-enfant !
//     [5]
//    /   \
//  [1]   [6]
//       /   \
//     [3]   [7]    <- 3 < 5 mais 3 est dans le sous-arbre DROIT de 5 = INVALIDE
//
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
// BRUTE FORCE : Inorder traversal puis verifier si trie
// On stocke le parcours inorder et on verifie que c'est croissant
// Temps : O(n) | Espace : O(n)
// ============================================
// bool isValidBST(TreeNode* root) {
//     vector<int> vals;
//     function<void(TreeNode*)> inorder = [&](TreeNode* node) {
//         if (!node) return;
//         inorder(node->left);
//         vals.push_back(node->val);
//         inorder(node->right);
//     };
//     inorder(root);
//     for (int i = 1; i < (int)vals.size(); i++)
//         if (vals[i] <= vals[i-1]) return false;
//     return true;
// }

// ============================================
// SOLUTION OPTIMALE : DFS avec bornes min/max
// Chaque noeud doit etre dans l'intervalle ]min, max[
// Temps : O(n) | Espace : O(h)
// ============================================
bool isValidBST(TreeNode* root, long minVal = LONG_MIN, long maxVal = LONG_MAX) {
    if (!root) return true;
    if (root->val <= minVal || root->val >= maxVal) return false;
    // Gauche : tout doit etre < root->val
    // Droite : tout doit etre > root->val
    return isValidBST(root->left, minVal, root->val)
        && isValidBST(root->right, root->val, maxVal);
}

int main() {
    // Test 1 : BST valide [2,1,3]
    TreeNode* t1 = new TreeNode(2);
    t1->left = new TreeNode(1);
    t1->right = new TreeNode(3);
    cout << "Test 1 - [2,1,3] valide: " << (isValidBST(t1) ? "OK" : "FAIL") << endl;

    // Test 2 : BST invalide [5,1,4,null,null,3,6]
    TreeNode* t2 = new TreeNode(5);
    t2->left = new TreeNode(1);
    t2->right = new TreeNode(4);
    t2->right->left = new TreeNode(3);
    t2->right->right = new TreeNode(6);
    cout << "Test 2 - [5,1,4,_,_,3,6] invalide: " << (!isValidBST(t2) ? "OK" : "FAIL") << endl;

    // Test 3 : piege [5,1,6,_,_,3,7] -> 3 dans sous-arbre droit de 5
    TreeNode* t3 = new TreeNode(5);
    t3->left = new TreeNode(1);
    t3->right = new TreeNode(6);
    t3->right->left = new TreeNode(3);
    t3->right->right = new TreeNode(7);
    cout << "Test 3 - piege [5,1,6,_,_,3,7]: " << (!isValidBST(t3) ? "OK" : "FAIL") << endl;

    // Test 4 : un seul noeud
    TreeNode* t4 = new TreeNode(1);
    cout << "Test 4 - un noeud: " << (isValidBST(t4) ? "OK" : "FAIL") << endl;

    // Test 5 : valeurs egales [1,1]
    TreeNode* t5 = new TreeNode(1);
    t5->left = new TreeNode(1);
    cout << "Test 5 - valeurs egales: " << (!isValidBST(t5) ? "OK" : "FAIL") << endl;

    return 0;
}
