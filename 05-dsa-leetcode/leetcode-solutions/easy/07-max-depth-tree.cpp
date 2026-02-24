// https://leetcode.com/problems/maximum-depth-of-binary-tree/
// #104 - Maximum Depth of Binary Tree
//
// Trouver la profondeur maximale d'un arbre binaire.
// La profondeur = nombre de noeuds sur le chemin le plus long racine -> feuille.
//
// Approche : DFS recursif — profondeur = 1 + max(gauche, droite).
// Complexite temps : O(n) | Complexite espace : O(h) ou h = hauteur (O(n) pire cas)

#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        // Arbre vide : profondeur 0
        if (!root) return 0;

        // Profondeur = 1 (noeud courant) + max des sous-arbres
        int leftDepth  = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);

        return 1 + max(leftDepth, rightDepth);
    }
};

int main() {
    Solution sol;

    // Arbre : [3,9,20,null,null,15,7]
    //        3
    //       / \
    //      9  20
    //        /  \
    //       15   7
    TreeNode* root1 = new TreeNode(3);
    root1->left  = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left  = new TreeNode(15);
    root1->right->right = new TreeNode(7);
    cout << sol.maxDepth(root1) << endl; // 3

    // Arbre : [1,null,2]
    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    cout << sol.maxDepth(root2) << endl; // 2

    // Arbre vide
    cout << sol.maxDepth(nullptr) << endl; // 0

    // Noeud unique
    TreeNode* root3 = new TreeNode(1);
    cout << sol.maxDepth(root3) << endl; // 1

    return 0;
}
