// ============================================
// PATTERN : Arbre Binaire - Templates 
// ============================================
// Squelettes copier-coller pour arbres binaires
// Compile : g++ -std=c++17 -o pattern pattern-template.cpp
// ============================================

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// --- Structure de base ---
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================
// TEMPLATE 1 : Parcours Inorder (G-R-D)
// ============================================
void inorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorder(root->left, result);
    result.push_back(root->val);
    inorder(root->right, result);
}

// ============================================
// TEMPLATE 2 : Parcours Preorder (R-G-D)
// ============================================
void preorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preorder(root->left, result);
    preorder(root->right, result);
}

// ============================================
// TEMPLATE 3 : Parcours Postorder (G-D-R)
// ============================================
void postorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postorder(root->left, result);
    postorder(root->right, result);
    result.push_back(root->val);
}

// ============================================
// TEMPLATE 4 : BFS - Level Order Traversal
// ============================================
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
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

// ============================================
// TEMPLATE 5 : Hauteur d'un arbre
// ============================================
int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// ============================================
// TEMPLATE 6 : Inverser un arbre (miroir)
// ============================================
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

// ============================================
// TEMPLATE 7 : Comparer deux arbres
// ============================================
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    return p->val == q->val
        && isSameTree(p->left, q->left)
        && isSameTree(p->right, q->right);
}

// ============================================
// TEMPLATE 8 : Construire arbre depuis vector (helper pour tests)
// ============================================
TreeNode* buildTree(const vector<int>& vals, int index = 0) {
    if (index >= (int)vals.size() || vals[index] == -1) return nullptr;
    TreeNode* node = new TreeNode(vals[index]);
    node->left = buildTree(vals, 2 * index + 1);
    node->right = buildTree(vals, 2 * index + 2);
    return node;
}

// --- Helper affichage ---
void printVec(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i < (int)v.size() - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    vector<int> res;

    inorder(root, res);
    cout << "Inorder:   "; printVec(res); cout << endl;

    res.clear();
    preorder(root, res);
    cout << "Preorder:  "; printVec(res); cout << endl;

    res.clear();
    postorder(root, res);
    cout << "Postorder: "; printVec(res); cout << endl;

    cout << "Hauteur:   " << height(root) << endl;

    auto levels = levelOrder(root);
    cout << "BFS:       ";
    for (auto& lv : levels) { printVec(lv); cout << " "; }
    cout << endl;

    return 0;
}
