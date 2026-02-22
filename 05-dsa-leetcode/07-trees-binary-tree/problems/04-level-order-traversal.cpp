// ============================================
// LeetCode #102 - Binary Tree Level Order Traversal (Medium) 🌳
// https://leetcode.com/problems/binary-tree-level-order-traversal/
// ============================================
//
// ENONCE :
// Retourner le parcours niveau par niveau d'un arbre binaire.
// (de gauche a droite, niveau par niveau)
//
//        3
//       / \
//      9  20        -> [[3], [9, 20], [15, 7]]
//        /  \
//       15   7
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
// BRUTE FORCE : DFS recursif avec profondeur
// On passe la profondeur en parametre et on ajoute au bon niveau
// Temps : O(n) | Espace : O(n)
// ============================================
// void dfs(TreeNode* root, int depth, vector<vector<int>>& result) {
//     if (!root) return;
//     if (depth == (int)result.size()) result.push_back({});
//     result[depth].push_back(root->val);
//     dfs(root->left, depth + 1, result);
//     dfs(root->right, depth + 1, result);
// }
// vector<vector<int>> levelOrder(TreeNode* root) {
//     vector<vector<int>> result;
//     dfs(root, 0, result);
//     return result;
// }

// ============================================
// SOLUTION OPTIMALE : BFS avec queue
// On utilise la taille de la queue pour delimiter chaque niveau
// Temps : O(n) | Espace : O(n)
// ============================================
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();        // nombre de noeuds a CE niveau
        vector<int> level;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}

// --- Helper ---
void printResult(const vector<vector<int>>& res) {
    cout << "[";
    for (int i = 0; i < (int)res.size(); i++) {
        cout << "[";
        for (int j = 0; j < (int)res[i].size(); j++) {
            cout << res[i][j];
            if (j < (int)res[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < (int)res.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
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

    auto res1 = levelOrder(root);
    cout << "Test 1: ";
    printResult(res1);
    // Attendu : [[3], [9,20], [15,7]]

    bool ok1 = res1.size() == 3
            && res1[0] == vector<int>{3}
            && res1[1] == vector<int>({9, 20})
            && res1[2] == vector<int>({15, 7});
    cout << "  -> " << (ok1 ? "OK" : "FAIL") << endl;

    // Test arbre vide
    auto res2 = levelOrder(nullptr);
    cout << "Test 2 - vide: " << (res2.empty() ? "OK" : "FAIL") << endl;

    // Test un noeud
    TreeNode* single = new TreeNode(1);
    auto res3 = levelOrder(single);
    cout << "Test 3 - un noeud: " << (res3.size() == 1 && res3[0][0] == 1 ? "OK" : "FAIL") << endl;

    return 0;
}
