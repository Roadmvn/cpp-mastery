/*
 * ============================================
 *  BACKTRACKING - Templates reutilisables 🔙
 * ============================================
 *
 * 3 variantes principales :
 * 1. Subsets / Combinations (avec index start)
 * 2. Permutations (avec tableau used[])
 * 3. Grid Search (4 directions)
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ════════════════════════════════════════════
// Template 1 : Subsets / Combinations
// ════════════════════════════════════════════
// Utiliser quand : generer tous les sous-ensembles ou combinaisons
// Cle : index start pour eviter les doublons

class SubsetTemplate {
public:
    vector<vector<int>> result;

    void backtrack(vector<int>& nums, int start, vector<int>& path) {
        result.push_back(path); // chaque etat est une solution valide

        for (int i = start; i < (int)nums.size(); i++) {
            // Optionnel : skip doublons si nums trie
            // if (i > start && nums[i] == nums[i-1]) continue;

            path.push_back(nums[i]);       // 1. CHOISIR
            backtrack(nums, i + 1, path);   // 2. EXPLORER (i+1 = sans repetition)
            path.pop_back();                // 3. ANNULER
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        backtrack(nums, 0, path);
        return result;
    }
};

// ════════════════════════════════════════════
// Template 2 : Permutations
// ════════════════════════════════════════════
// Utiliser quand : generer tous les arrangements possibles
// Cle : tableau used[] au lieu de start

class PermutationTemplate {
public:
    vector<vector<int>> result;

    void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& used) {
        if ((int)path.size() == (int)nums.size()) {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < (int)nums.size(); i++) {
            if (used[i]) continue;

            // Optionnel : skip doublons si nums trie
            // if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;

            used[i] = true;
            path.push_back(nums[i]);       // 1. CHOISIR
            backtrack(nums, path, used);    // 2. EXPLORER
            path.pop_back();               // 3. ANNULER
            used[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> path;
        vector<bool> used(nums.size(), false);
        backtrack(nums, path, used);
        return result;
    }
};

// ════════════════════════════════════════════
// Template 3 : Combination Sum (avec repetition)
// ════════════════════════════════════════════
// Utiliser quand : somme cible avec elements reutilisables
// Cle : recurser avec i (pas i+1) pour permettre la repetition

class CombSumTemplate {
public:
    vector<vector<int>> result;

    void backtrack(vector<int>& candidates, int start, int target, vector<int>& path) {
        if (target == 0) {
            result.push_back(path);
            return;
        }
        if (target < 0) return; // PRUNING

        for (int i = start; i < (int)candidates.size(); i++) {
            if (candidates[i] > target) break; // PRUNING (si trie)

            path.push_back(candidates[i]);
            backtrack(candidates, i, target - candidates[i], path); // i = repetition OK
            path.pop_back();
        }
    }
};

// ════════════════════════════════════════════
// Template 4 : Grid Search (Word Search style)
// ════════════════════════════════════════════
// Utiliser quand : chercher un chemin dans une grille 2D

class GridSearchTemplate {
public:
    int rows, cols;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    bool backtrack(vector<vector<char>>& board, int r, int c,
                   string& word, int index) {
        if (index == (int)word.size()) return true;

        if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
        if (board[r][c] != word[index]) return false;

        char temp = board[r][c];
        board[r][c] = '#'; // marquer comme visite

        for (int d = 0; d < 4; d++) {
            if (backtrack(board, r + dx[d], c + dy[d], word, index + 1)) {
                board[r][c] = temp;
                return true;
            }
        }

        board[r][c] = temp; // BACKTRACK : restaurer
        return false;
    }
};

int main() {
    // Test Template 1 : Subsets
    cout << "=== Subsets de [1,2,3] ===" << endl;
    SubsetTemplate st;
    vector<int> nums1 = {1, 2, 3};
    auto subsets = st.subsets(nums1);
    for (auto& s : subsets) {
        cout << "[ ";
        for (int x : s) cout << x << " ";
        cout << "]" << endl;
    }

    // Test Template 2 : Permutations
    cout << "\n=== Permutations de [1,2,3] ===" << endl;
    PermutationTemplate pt;
    vector<int> nums2 = {1, 2, 3};
    auto perms = pt.permute(nums2);
    for (auto& p : perms) {
        cout << "[ ";
        for (int x : p) cout << x << " ";
        cout << "]" << endl;
    }

    cout << "\nTemplates prets a copier-coller !" << endl;
    return 0;
}
