// ============================================================
// Probleme 03 : 3Sum (Medium)
// LeetCode #15 : https://leetcode.com/problems/3sum/
// Compile : g++ -std=c++17 -o 03 03-three-sum.cpp && ./03
// ============================================================
//
// Enonce :
// Etant donne un array d'entiers nums, retourner tous les triplets
// [nums[i], nums[j], nums[k]] tels que i != j != k
// et nums[i] + nums[j] + nums[k] == 0.
// La solution NE DOIT PAS contenir de triplets en double.
//
// Exemple 1 : nums = [-1,0,1,2,-1,-4] → [[-1,-1,2],[-1,0,1]]
// Exemple 2 : nums = [0,1,1] → []
// Exemple 3 : nums = [0,0,0] → [[0,0,0]]
//
// Contraintes :
// - 3 <= nums.length <= 3000
// - -10^5 <= nums[i] <= 10^5
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// Solution 1 : Brute force — Triple boucle
// Complexite : O(n^3) temps, O(1) espace (hors resultat)
// ============================================================
// On teste toutes les combinaisons de 3 elements.
// On utilise sort + set pour eviter les doublons.
// Beaucoup trop lent pour les gros inputs mais utile pour comprendre.

vector<vector<int>> threeSum_bruteforce(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end()); // Trier pour detecter les doublons
    vector<vector<int>> result;

    for (int i = 0; i < n - 2; i++) {
        // Skip les doublons pour i
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        for (int j = i + 1; j < n - 1; j++) {
            // Skip les doublons pour j
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;

            for (int k = j + 1; k < n; k++) {
                // Skip les doublons pour k
                if (k > j + 1 && nums[k] == nums[k - 1]) continue;

                if (nums[i] + nums[j] + nums[k] == 0) {
                    result.push_back({nums[i], nums[j], nums[k]});
                }
            }
        }
    }

    return result;
}

// ============================================================
// Solution 2 : Optimale — Sort + Two Pointers
// Complexite : O(n^2) temps, O(1) espace (hors resultat)
// ============================================================
// L'idee geniale :
// 1. Trier l'array
// 2. Fixer un element (nums[i])
// 3. Utiliser Two Pointers sur le reste pour trouver une paire
//    dont la somme = -nums[i]
//
// C'est Two Sum II applique n fois avec un target qui change.
// La gestion des doublons est cruciale : on skip les valeurs identiques.

vector<vector<int>> threeSum_optimal(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;

    sort(nums.begin(), nums.end()); // O(n log n)

    for (int i = 0; i < n - 2; i++) {
        // Optimisation : si nums[i] > 0, impossible d'avoir sum=0
        // car tout le reste est >= nums[i] > 0
        if (nums[i] > 0) break;

        // Skip les doublons pour i
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        // Two Pointers sur la portion [i+1, n-1]
        int left = i + 1;
        int right = n - 1;
        int target = -nums[i]; // On cherche left + right == -nums[i]

        while (left < right) {
            int sum = nums[left] + nums[right];

            if (sum == target) {
                result.push_back({nums[i], nums[left], nums[right]});

                // Skip les doublons pour left et right
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;

                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    return result;
}

// ============================================================
// Tests
// ============================================================

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (int i = 0; i < (int)result.size(); i++) {
        cout << "[";
        for (int j = 0; j < (int)result[i].size(); j++) {
            cout << result[i][j];
            if (j < (int)result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < (int)result.size() - 1) cout << ", ";
    }
    cout << "]";
}

void test(vector<int> nums, int expected_count) {
    vector<int> nums_copy = nums;
    auto result_bf = threeSum_bruteforce(nums);
    auto result_opt = threeSum_optimal(nums_copy);

    cout << "Input: [";
    for (int i = 0; i < (int)nums.size(); i++) {
        cout << nums[i];
        if (i < (int)nums.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    cout << "  Brute force (" << result_bf.size() << " triplets) : ";
    printResult(result_bf);
    cout << " | " << ((int)result_bf.size() == expected_count ? "PASS" : "FAIL") << endl;

    cout << "  Optimal     (" << result_opt.size() << " triplets) : ";
    printResult(result_opt);
    cout << " | " << ((int)result_opt.size() == expected_count ? "PASS" : "FAIL") << endl;
}

int main() {
    cout << "=== 3Sum (LeetCode #15) ===" << endl << endl;

    test({-1, 0, 1, 2, -1, -4}, 2);  // [[-1,-1,2],[-1,0,1]]
    test({0, 1, 1}, 0);               // []
    test({0, 0, 0}, 1);               // [[0,0,0]]
    test({-2, 0, 0, 2, 2}, 1);        // [[-2,0,2]]

    cout << endl;
    cout << "Pattern : Fixer un element + Two Pointers sur le reste" << endl;
    cout << "La cle : trier d'abord, puis skip les doublons a chaque niveau" << endl;
    cout << "On passe de O(n^3) brute force a O(n^2) avec two pointers" << endl;

    return 0;
}
