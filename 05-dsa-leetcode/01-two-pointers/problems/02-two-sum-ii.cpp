// ============================================================
// Probleme 02 : Two Sum II - Input Array Is Sorted (Medium)
// LeetCode #167 : https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
// Compile : g++ -std=c++17 -o 02 02-two-sum-ii.cpp && ./02
// ============================================================
//
// Enonce :
// Etant donne un array d'entiers TRIE par ordre croissant (1-indexed),
// trouver deux nombres dont la somme egale target.
// Retourner les indices (1-indexed) [index1, index2] avec index1 < index2.
//
// Exemple 1 : numbers = [2,7,11,15], target = 9 → [1,2]
// Exemple 2 : numbers = [2,3,4], target = 6 → [1,3]
// Exemple 3 : numbers = [-1,0], target = -1 → [1,2]
//
// Contraintes :
// - 2 <= numbers.length <= 3 * 10^4
// - -1000 <= numbers[i] <= 1000
// - numbers est trie par ordre croissant
// - Exactement UNE solution existe
// - Tu ne peux pas utiliser le meme element deux fois
// - Solution en O(1) espace supplementaire
// ============================================================

#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// Solution 1 : Brute force — Double boucle
// Complexite : O(n^2) temps, O(1) espace
// ============================================================
// On teste toutes les paires possibles. Simple mais lent.

vector<int> twoSum_bruteforce(vector<int>& numbers, int target) {
    for (int i = 0; i < (int)numbers.size(); i++) {
        for (int j = i + 1; j < (int)numbers.size(); j++) {
            if (numbers[i] + numbers[j] == target) {
                return {i + 1, j + 1}; // 1-indexed
            }
        }
    }
    return {}; // Ne devrait jamais arriver (une solution existe toujours)
}

// ============================================================
// Solution 2 : Optimale — Two Pointers opposes
// Complexite : O(n) temps, O(1) espace
// ============================================================
// L'array est TRIE, c'est la cle. Avec deux pointeurs :
// - Si la somme est trop petite → left++ (augmenter la somme)
// - Si la somme est trop grande → right-- (diminuer la somme)
// - Si la somme == target → on a trouve
//
// Pourquoi ca marche :
// Quand on fait left++, on augmente forcement la somme car l'array est trie.
// Quand on fait right--, on diminue forcement la somme.
// On converge vers la solution unique en O(n).

vector<int> twoSum_optimal(vector<int>& numbers, int target) {
    int left = 0;
    int right = (int)numbers.size() - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];

        if (sum == target) {
            return {left + 1, right + 1}; // 1-indexed
        } else if (sum < target) {
            left++;   // Somme trop petite, on avance left
        } else {
            right--;  // Somme trop grande, on recule right
        }
    }

    return {}; // Ne devrait jamais arriver
}

// ============================================================
// Tests
// ============================================================

void printResult(const vector<int>& result) {
    cout << "[" << result[0] << ", " << result[1] << "]";
}

void test(vector<int> numbers, int target, vector<int> expected) {
    vector<int> nums_copy = numbers;
    vector<int> result_bf = twoSum_bruteforce(numbers, target);
    vector<int> result_opt = twoSum_optimal(nums_copy, target);

    cout << "Target: " << target << endl;
    cout << "  Brute force : ";
    printResult(result_bf);
    cout << " | " << (result_bf == expected ? "PASS" : "FAIL") << endl;

    cout << "  Optimal     : ";
    printResult(result_opt);
    cout << " | " << (result_opt == expected ? "PASS" : "FAIL") << endl;
}

int main() {
    cout << "=== Two Sum II (LeetCode #167) ===" << endl << endl;

    test({2, 7, 11, 15}, 9, {1, 2});
    test({2, 3, 4}, 6, {1, 3});
    test({-1, 0}, -1, {1, 2});
    test({1, 2, 3, 4, 5, 6, 7, 8, 9}, 17, {8, 9});

    cout << endl;
    cout << "Pattern : Two Pointers opposes sur array trie" << endl;
    cout << "La cle : l'array est trie, donc deplacer left/right" << endl;
    cout << "controle de facon deterministe si la somme augmente ou diminue" << endl;

    return 0;
}
