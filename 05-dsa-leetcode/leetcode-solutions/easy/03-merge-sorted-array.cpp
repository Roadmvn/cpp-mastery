// https://leetcode.com/problems/merge-sorted-array/
// #88 - Merge Sorted Array
//
// Fusionner deux tableaux tries nums1 (taille m+n, m valides) et nums2 (taille n).
// Le resultat doit etre in-place dans nums1.
//
// Approche : 3 pointeurs depuis la fin - evite de decaler des elements.
// Partir de la fin de chaque tableau et ecrire dans la fin de nums1.
// Complexite temps : O(m+n) | Complexite espace : O(1)

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;        // dernier element valide de nums1
        int j = n - 1;        // dernier element de nums2
        int k = m + n - 1;    // position d'ecriture (fin de nums1)

        // Remplir de droite a gauche avec le plus grand des deux
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }

        // Copier les elements restants de nums2 (si nums1 epuise en premier)
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
        // Pas besoin de copier nums1 restant : deja en place
    }
};

void print(const vector<int>& v) {
    for (int i = 0; i < (int)v.size(); i++) {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << endl;
}

int main() {
    Solution sol;

    // Test 1 : cas classique
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    sol.merge(nums1, 3, nums2, 3);
    print(nums1); // 1, 2, 2, 3, 5, 6

    // Test 2 : nums1 vide
    vector<int> nums1b = {0};
    vector<int> nums2b = {1};
    sol.merge(nums1b, 0, nums2b, 1);
    print(nums1b); // 1

    // Test 3 : nums2 vide
    vector<int> nums1c = {1};
    vector<int> nums2c = {};
    sol.merge(nums1c, 1, nums2c, 0);
    print(nums1c); // 1

    return 0;
}
