// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
// #297 - Serialize and Deserialize Binary Tree
//
// Concevoir un algorithme pour serialiser et deserialiser un arbre binaire.
// Pas de contrainte sur le format, seulement que encode(decode(s)) == s.
//
// Approche : BFS level-order.
// Serialisation : parcours BFS, "null" pour les noeuds absents, valeurs separees par ','.
// Deserialisation : reconstruire niveau par niveau depuis la queue.
// Complexite temps : O(n) | Complexite espace : O(n)

#include <iostream>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    // Serialise l'arbre en string via BFS
    string serialize(TreeNode* root) {
        if (!root) return "";

        string result;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            if (!result.empty()) result += ',';

            if (node) {
                result += to_string(node->val);
                q.push(node->left);
                q.push(node->right);
            } else {
                result += "null";
            }
        }

        return result;
    }

    // Reconstruit l'arbre depuis la string
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;

        // Decouper la string en tokens
        vector<string> tokens;
        stringstream ss(data);
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        TreeNode* root = new TreeNode(stoi(tokens[0]));
        queue<TreeNode*> q;
        q.push(root);

        int i = 1;
        while (!q.empty() && i < (int)tokens.size()) {
            TreeNode* node = q.front();
            q.pop();

            // Enfant gauche
            if (i < (int)tokens.size() && tokens[i] != "null") {
                node->left = new TreeNode(stoi(tokens[i]));
                q.push(node->left);
            }
            i++;

            // Enfant droit
            if (i < (int)tokens.size() && tokens[i] != "null") {
                node->right = new TreeNode(stoi(tokens[i]));
                q.push(node->right);
            }
            i++;
        }

        return root;
    }
};

// Serialisation inorder pour verifier l'egalite
void inorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorder(root->left, result);
    result.push_back(root->val);
    inorder(root->right, result);
}

int main() {
    Codec codec;

    // Arbre : [1,2,3,null,null,4,5]
    TreeNode* root1 = new TreeNode(1);
    root1->left  = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->right->left  = new TreeNode(4);
    root1->right->right = new TreeNode(5);

    string serialized = codec.serialize(root1);
    cout << "Serialise : " << serialized << endl;

    TreeNode* restored = codec.deserialize(serialized);
    cout << "Re-serialise : " << codec.serialize(restored) << endl;

    // Verifier avec inorder
    vector<int> v1, v2;
    inorder(root1, v1);
    inorder(restored, v2);
    cout << "Inorders identiques : " << boolalpha << (v1 == v2) << endl;

    // Test arbre vide
    cout << "Vide : '" << codec.serialize(nullptr) << "'" << endl;
    cout << "Deserialise vide : " << (codec.deserialize("") == nullptr) << endl;

    // Test noeud unique
    TreeNode* single = new TreeNode(42);
    string s2 = codec.serialize(single);
    cout << "Noeud unique : " << s2 << endl;
    cout << "Restaure val : " << codec.deserialize(s2)->val << endl;

    return 0;
}
