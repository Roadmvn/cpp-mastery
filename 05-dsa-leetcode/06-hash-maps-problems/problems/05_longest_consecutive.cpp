// ============================================
// LeetCode #128 - Longest Consecutive Sequence (Medium)
// https://leetcode.com/problems/longest-consecutive-sequence/
// ============================================
// Enonce : Donne un tableau non trie nums[], retourner la longueur de
// la plus longue sequence d'entiers consecutifs.
// Contrainte : algorithme en O(n).
//
// Exemple :
//   Input : nums=[100,4,200,1,3,2]  Output: 4  (sequence: 1,2,3,4)
//   Input : nums=[0,3,7,2,5,8,4,6,0,1]  Output: 9  (0..8)
//
// Compile : g++ -std=c++17 05_longest_consecutive.cpp -o 05

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n³) temps | O(1) espace extra
// Pour chaque element n, chercher si n+1, n+2, ...
// existent dans le tableau (recherche lineaire).
// Conserver la longueur maximale trouvee.
// -----------------------------------------------
bool existsInArray(const vector<int>& nums, int target) {
    for (int x : nums) {
        if (x == target) return true;
    }
    return false;
}

int longestConsecutiveBrute(vector<int>& nums) {
    if (nums.empty()) return 0;
    int best = 1;

    for (int n : nums) {
        // Ne commencer que depuis le debut potentiel d'une sequence
        // (optimisation legere : ne pas recompter depuis le milieu)
        int cur = n;
        int length = 1;
        while (existsInArray(nums, cur + 1)) {
            cur++;
            length++;
        }
        best = max(best, length);
    }
    return best;
}

// -----------------------------------------------
// OPTIMAL : O(n) temps | O(n) espace
// Hash Set + demarrer uniquement depuis le debut d'une sequence.
//
// Principe :
//   1. Mettre tous les elements dans un hash set (O(1) lookup).
//   2. Pour chaque element n, verifier si (n-1) est dans le set.
//      Si OUI  n n'est pas le debut, on saute (evite le recomptage).
//      Si NON  n est le debut d'une sequence  compter.
//
// Schema ASCII :
//
//   nums = [100, 4, 200, 1, 3, 2]
//   set  = {100, 4, 200, 1, 3, 2}
//
//   n=100 : 99 absent  debut ! 100, 101? non  longueur=1
//   n=4   : 3 present  PAS debut, skip
//   n=200 : 199 absent  debut ! 200, 201? non  longueur=1
//   n=1   : 0 absent  debut !
//              12345? non  longueur=4    MAX
//   n=3   : 2 present  PAS debut, skip
//   n=2   : 1 present  PAS debut, skip
//
//   Resultat : 4
//
//   Pourquoi O(n) ?
//   Chaque element est visite au plus 2 fois :
//   - une fois dans la boucle principale
//   - une fois dans le while (comme successeur d'un debut)
// -----------------------------------------------
int longestConsecutiveOptimal(vector<int>& nums) {
    if (nums.empty()) return 0;

    unordered_set<int> numSet(nums.begin(), nums.end());
    int best = 0;

    for (int n : numSet) {
        // Ne demarrer que depuis le debut d'une sequence
        if (!numSet.count(n - 1)) {
            int cur = n;
            int length = 1;

            while (numSet.count(cur + 1)) {
                cur++;
                length++;
            }
            best = max(best, length);
        }
    }
    return best;
}

int main() {
    cout << "=== LeetCode #128 - Longest Consecutive Sequence ===" << endl;

    // Test 1 : exemple classique
    {
        vector<int> nums = {100, 4, 200, 1, 3, 2};
        cout << "Input : [100,4,200,1,3,2]" << endl;
        cout << "Brute  : " << longestConsecutiveBrute(nums) << endl;
        cout << "Optimal: " << longestConsecutiveOptimal(nums) << endl;
        // Attendu : 4
        cout << endl;
    }

    // Test 2 : longue sequence
    {
        vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
        cout << "Input : [0,3,7,2,5,8,4,6,0,1]" << endl;
        cout << "Brute  : " << longestConsecutiveBrute(nums) << endl;
        cout << "Optimal: " << longestConsecutiveOptimal(nums) << endl;
        // Attendu : 9
        cout << endl;
    }

    // Test 3 : un seul element
    {
        vector<int> nums = {5};
        cout << "Input : [5]" << endl;
        cout << "Brute  : " << longestConsecutiveBrute(nums) << endl;
        cout << "Optimal: " << longestConsecutiveOptimal(nums) << endl;
        // Attendu : 1
        cout << endl;
    }

    // Test 4 : tableau vide
    {
        vector<int> nums = {};
        cout << "Input : []" << endl;
        cout << "Brute  : " << longestConsecutiveBrute(nums) << endl;
        cout << "Optimal: " << longestConsecutiveOptimal(nums) << endl;
        // Attendu : 0
        cout << endl;
    }

    // Test 5 : doublons
    {
        vector<int> nums = {1, 2, 0, 1};
        cout << "Input : [1,2,0,1]" << endl;
        cout << "Brute  : " << longestConsecutiveBrute(nums) << endl;
        cout << "Optimal: " << longestConsecutiveOptimal(nums) << endl;
        // Attendu : 3 (0,1,2)
        cout << endl;
    }

    cout << "Complexite Brute  : O(n^3) temps | O(1) espace" << endl;
    cout << "Complexite Optimal: O(n)   temps | O(n) espace" << endl;

    return 0;
}
