// ============================================
// LeetCode #104 - Maximum Depth of Binary Tree (Easy) 
// https://leetcode.com/problems/maximum-depth-of-binary-tree/
// ============================================
//
// ENONCE :
// Trouver la profondeur maximale d'un arbre binaire.
// La profondeur max = nombre de noeuds sur le plus long chemin
// de la racine jusqu'a la feuille la plus eloignee.
//
//        3          profondeur = 3
//       / \
//      9  20
//        /  \
//       15   7
//
// ============================================

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================
// BRUTE FORCE : BFS iteratif (compter les niveaux)
// On parcourt niveau par niveau et on compte
// Temps : O(n) | Espace : O(n)
// ============================================
// int maxDepth(TreeNode* root) {
//     if (!root) return 0;
//     queue<TreeNode*> q;
//     q.push(root);
//     int depth = 0;
//     while (!q.empty()) {
//         int size = q.size();
//         depth++;
//         for (int i = 0; i < size; i++) {
//             TreeNode* node = q.front(); q.pop();
//             if (node->left) q.push(node->left);
//             if (node->right) q.push(node->right);
//         }
//     }
//     return depth;
// }

// ============================================
// SOLUTION OPTIMALE : DFS recursif
// La profondeur = 1 + max(profondeur gauche, profondeur droite)
// Temps : O(n) | Espace : O(h)
// ============================================
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

int main() {
    //        3
    //       / \
    //      9  20
    //        /  \
    //       15   7
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    cout << "Test 1 - profondeur 3: " << (maxDepth(root) == 3 ? "OK" : "FAIL")
         << " (got " << maxDepth(root) << ")" << endl;

    // Test arbre vide
    cout << "Test 2 - arbre vide: " << (maxDepth(nullptr) == 0 ? "OK" : "FAIL") << endl;

    // Test un noeud
    TreeNode* single = new TreeNode(1);
    cout << "Test 3 - un noeud: " << (maxDepth(single) == 1 ? "OK" : "FAIL") << endl;

    // Test arbre degenere (liste)
    //  1
    //   \
    //    2
    //     \
    //      3
    TreeNode* line = new TreeNode(1);
    line->right = new TreeNode(2);
    line->right->right = new TreeNode(3);
    cout << "Test 4 - arbre degenere: " << (maxDepth(line) == 3 ? "OK" : "FAIL") << endl;

    return 0;
}
