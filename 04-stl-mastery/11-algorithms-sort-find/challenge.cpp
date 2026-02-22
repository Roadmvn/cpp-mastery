// ============================================================
// Algorithmes STL — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Problemes classiques resolus avec les algorithmes STL.
// L'objectif : code concis, lisible, performant.
//
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

// ============================================================
// PROBLEME 1 : Kth Largest Element (LeetCode #215)
// ============================================================
//
// Enonce :
// Etant donne un tableau non trie, trouver le k-eme plus grand element.
//
// Exemple :
// nums=[3,2,1,5,6,4], k=2 -> 5
// nums=[3,2,3,1,2,4,5,5,6], k=4 -> 4
//
// Technique 1 : sort O(n log n) -> trop lent
// Technique 2 : nth_element O(n) -> parfait
// Le k-eme plus grand = (n-k)-eme dans l'ordre croissant

int findKthLargest(vector<int> nums, int k) {
    int n = nums.size();
    // nth_element place le bon element a la position n-k
    nth_element(nums.begin(), nums.begin() + (n - k), nums.end());
    return nums[n - k];
}

// ============================================================
// PROBLEME 2 : Sort Colors / Dutch Flag (LeetCode #75)
// ============================================================
//
// Enonce :
// Etant donne un tableau de 0, 1 et 2, trier en place
// (rouge=0, blanc=1, bleu=2). Un seul passage.
//
// Exemple :
// [2,0,2,1,1,0] -> [0,0,1,1,2,2]
//
// Technique : partition two-way avec stable_partition ou
//             partition manuelle (algorithme de Dijkstra / Dutch Flag)

void sortColors(vector<int>& nums) {
    // Deux partitions successives :
    // 1. partition : 0 avant les non-0
    // 2. stable_partition : 1 avant les 2 dans la partie non-0
    auto mid1 = partition(nums.begin(), nums.end(), [](int x) { return x == 0; });
    partition(mid1, nums.end(), [](int x) { return x == 1; });
}

// ============================================================
// PROBLEME 3 : Remove Duplicates from Sorted Array (LeetCode #26)
// ============================================================
//
// Enonce :
// Supprimer les doublons d'un tableau trie en place.
// Retourner la nouvelle longueur.
//
// Exemple :
// [1,1,2] -> [1,2,_], retourner 2
// [0,0,1,1,1,2,2,3,3,4] -> [0,1,2,3,4,_,...], retourner 5
//
// One-liner STL : unique + distance

int removeDuplicates(vector<int>& nums) {
    auto new_end = unique(nums.begin(), nums.end());
    int k = distance(nums.begin(), new_end);
    nums.erase(new_end, nums.end());
    return k;
}

// ============================================================
// PROBLEME 4 : Maximum Product Subarray helper (LeetCode #152)
// ============================================================
//
// Enonce simplifie :
// Etant donne un tableau, retourner la somme maximale
// d'un sous-tableau contigu (Kadane avec accumulate-like).
//
// Technique STL : partial_sum pour les prefix sums, puis
//                 max_element et min_element pour trouver le range

int maxSubarraySum(vector<int>& nums) {
    int maxSum = nums[0];
    int currentSum = 0;

    // Version avec STL : on peut aussi l'ecrire avec accumulate
    // mais Kadane reste plus lisible
    for (int num : nums) {
        currentSum = max(num, currentSum + num);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

// Version STL pure avec accumulate (pour illustrer le pattern)
int maxSubarraySumSTL(vector<int>& nums) {
    int maxSum = nums[0];
    accumulate(nums.begin(), nums.end(), 0, [&](int cur, int x) {
        int next = max(x, cur + x);
        maxSum = max(maxSum, next);
        return next;
    });
    return maxSum;
}

// ============================================================
// PROBLEME 5 : Product of Array Except Self (LeetCode #238)
// ============================================================
//
// Enonce :
// Etant donne nums, retourner un tableau output ou output[i]
// est le produit de tous les elements sauf nums[i].
// O(n) temps, O(1) espace extra (hors output).
//
// Exemple :
// [1,2,3,4] -> [24,12,8,6]
//
// Technique : partial_product de gauche, puis de droite

vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 1);

    // Pass gauche : result[i] = produit de nums[0..i-1]
    partial_sum(nums.begin(), nums.end() - 1, result.begin() + 1, multiplies<int>());

    // Pass droite : multiplier par produit de nums[i+1..n-1]
    int right = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= right;
        right *= nums[i];
    }
    return result;
}

// ============================================================
// Tests
// ============================================================

void testKthLargest() {
    cout << "=== Test findKthLargest (LC #215) ===" << endl;

    vector<int> t1 = {3, 2, 1, 5, 6, 4};
    cout << "[3,2,1,5,6,4] k=2 -> " << findKthLargest(t1, 2)
         << " | " << (findKthLargest(t1, 2) == 5 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << "[3,2,3,1,2,4,5,5,6] k=4 -> " << findKthLargest(t2, 4)
         << " | " << (findKthLargest(t2, 4) == 4 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testSortColors() {
    cout << "=== Test sortColors (LC #75) ===" << endl;

    vector<int> t1 = {2, 0, 2, 1, 1, 0};
    sortColors(t1);
    vector<int> exp1 = {0, 0, 1, 1, 2, 2};
    cout << "[2,0,2,1,1,0] -> ";
    for (int x : t1) cout << x << " ";
    cout << "| " << (t1 == exp1 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {2, 0, 1};
    sortColors(t2);
    vector<int> exp2 = {0, 1, 2};
    cout << "[2,0,1] -> ";
    for (int x : t2) cout << x << " ";
    cout << "| " << (t2 == exp2 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testRemoveDuplicates() {
    cout << "=== Test removeDuplicates (LC #26) ===" << endl;

    vector<int> t1 = {1, 1, 2};
    int k1 = removeDuplicates(t1);
    cout << "[1,1,2] -> k=" << k1 << " ";
    for (int x : t1) cout << x << " ";
    cout << "| " << (k1 == 2 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int k2 = removeDuplicates(t2);
    cout << "[0,0,1,1,1,2,2,3,3,4] -> k=" << k2 << " ";
    for (int x : t2) cout << x << " ";
    cout << "| " << (k2 == 5 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testMaxSubarray() {
    cout << "=== Test maxSubarraySum (LC #53 style) ===" << endl;

    vector<int> t1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "[-2,1,-3,4,-1,2,1,-5,4] -> " << maxSubarraySum(t1)
         << " | " << (maxSubarraySum(t1) == 6 ? "PASS" : "FAIL") << endl;

    cout << "STL version -> " << maxSubarraySumSTL(t1)
         << " | " << (maxSubarraySumSTL(t1) == 6 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testProductExceptSelf() {
    cout << "=== Test productExceptSelf (LC #238) ===" << endl;

    vector<int> t1 = {1, 2, 3, 4};
    auto r1 = productExceptSelf(t1);
    vector<int> exp1 = {24, 12, 8, 6};
    cout << "[1,2,3,4] -> ";
    for (int x : r1) cout << x << " ";
    cout << "| " << (r1 == exp1 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {-1, 1, 0, -3, 3};
    auto r2 = productExceptSelf(t2);
    cout << "[-1,1,0,-3,3] -> ";
    for (int x : r2) cout << x << " ";
    cout << endl;

    cout << endl;
}

int main() {
    testKthLargest();
    testSortColors();
    testRemoveDuplicates();
    testMaxSubarray();
    testProductExceptSelf();

    cout << "Patterns utilises :" << endl;
    cout << "- nth_element O(n) pour k-eme element (mieux que sort)" << endl;
    cout << "- partition pour Dutch Flag problem" << endl;
    cout << "- unique + erase pour dedupliquer en une expression" << endl;
    cout << "- accumulate avec lambda pour reduire avec effet de bord" << endl;
    cout << "- partial_sum pour prefix products" << endl;

    return 0;
}
