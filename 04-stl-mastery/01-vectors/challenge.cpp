// ============================================================
// Vectors — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Deux problemes classiques qui utilisent des vectors.
// Tu dois implementer les fonctions, puis lancer le programme
// pour verifier tes resultats avec les tests.
//
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// PROBLEME 1 : Remove Element (LeetCode #27)
// https://leetcode.com/problems/remove-element/
// ============================================================
//
// Enonce :
// Etant donne un vector nums et un entier val, retire toutes
// les occurrences de val IN-PLACE. Retourne le nombre d'elements
// restants (k). Les k premiers elements de nums doivent contenir
// les elements qui ne sont pas egaux a val.
//
// Exemple :
// nums = [3,2,2,3], val = 3  →  k=2, nums = [2,2,...]
// nums = [0,1,2,2,3,0,4,2], val = 2  →  k=5, nums = [0,1,3,0,4,...]
//
// Contrainte : modifier nums in-place, pas de vector supplementaire
//
// Complexite attendue : O(n) temps, O(1) espace

int removeElement(vector<int>& nums, int val) {
    // Technique : un pointeur lent (k) qui avance seulement
    // quand on trouve un element a garder
    int k = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] != val) {
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
    // Complexite : O(n) temps, O(1) espace
}

// ============================================================
// PROBLEME 2 : Remove Duplicates from Sorted Array (LeetCode #26)
// https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// ============================================================
//
// Enonce :
// Etant donne un vector TRIE nums, retire les doublons in-place
// de sorte que chaque element n'apparaisse qu'une fois.
// Retourne le nombre d'elements uniques (k).
//
// Exemple :
// nums = [1,1,2]  →  k=2, nums = [1,2,...]
// nums = [0,0,1,1,1,2,2,3,3,4]  →  k=5, nums = [0,1,2,3,4,...]
//
// Contrainte : le vector est DEJA TRIE. Modifier in-place.
//
// Complexite attendue : O(n) temps, O(1) espace

int removeDuplicates(vector<int>& sorted_nums) {
    if (sorted_nums.empty()) return 0;

    // Technique : puisque le vector est trie, les doublons sont
    // cote a cote. On utilise un pointeur lent (k) qui marque
    // la position du prochain element unique.
    int k = 1;  // Le premier element est toujours unique
    for (int i = 1; i < (int)sorted_nums.size(); i++) {
        if (sorted_nums[i] != sorted_nums[i - 1]) {
            sorted_nums[k] = sorted_nums[i];
            k++;
        }
    }
    return k;
    // Complexite : O(n) temps, O(1) espace
}

// ============================================================
// Tests
// ============================================================

void printVector(const vector<int>& v, int k) {
    cout << "[";
    for (int i = 0; i < k; i++) {
        cout << v[i];
        if (i < k - 1) cout << ", ";
    }
    cout << "]";
}

void testRemoveElement() {
    cout << "=== Test removeElement (LeetCode #27) ===" << endl;

    // Test 1
    vector<int> t1 = {3, 2, 2, 3};
    int k1 = removeElement(t1, 3);
    cout << "Input: [3,2,2,3], val=3 | k=" << k1 << " result=";
    printVector(t1, k1);
    cout << " | " << (k1 == 2 ? "PASS" : "FAIL") << endl;

    // Test 2
    vector<int> t2 = {0, 1, 2, 2, 3, 0, 4, 2};
    int k2 = removeElement(t2, 2);
    cout << "Input: [0,1,2,2,3,0,4,2], val=2 | k=" << k2 << " result=";
    printVector(t2, k2);
    cout << " | " << (k2 == 5 ? "PASS" : "FAIL") << endl;

    // Test 3 : vector vide
    vector<int> t3 = {};
    int k3 = removeElement(t3, 1);
    cout << "Input: [], val=1 | k=" << k3 << " result=";
    printVector(t3, k3);
    cout << " | " << (k3 == 0 ? "PASS" : "FAIL") << endl;

    // Test 4 : tous les elements a supprimer
    vector<int> t4 = {4, 4, 4, 4};
    int k4 = removeElement(t4, 4);
    cout << "Input: [4,4,4,4], val=4 | k=" << k4 << " result=";
    printVector(t4, k4);
    cout << " | " << (k4 == 0 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testRemoveDuplicates() {
    cout << "=== Test removeDuplicates (LeetCode #26) ===" << endl;

    // Test 1
    vector<int> t1 = {1, 1, 2};
    int k1 = removeDuplicates(t1);
    cout << "Input: [1,1,2] | k=" << k1 << " result=";
    printVector(t1, k1);
    cout << " | " << (k1 == 2 ? "PASS" : "FAIL") << endl;

    // Test 2
    vector<int> t2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int k2 = removeDuplicates(t2);
    cout << "Input: [0,0,1,1,1,2,2,3,3,4] | k=" << k2 << " result=";
    printVector(t2, k2);
    cout << " | " << (k2 == 5 ? "PASS" : "FAIL") << endl;

    // Test 3 : un seul element
    vector<int> t3 = {7};
    int k3 = removeDuplicates(t3);
    cout << "Input: [7] | k=" << k3 << " result=";
    printVector(t3, k3);
    cout << " | " << (k3 == 1 ? "PASS" : "FAIL") << endl;

    // Test 4 : vide
    vector<int> t4 = {};
    int k4 = removeDuplicates(t4);
    cout << "Input: [] | k=" << k4 << " result=";
    printVector(t4, k4);
    cout << " | " << (k4 == 0 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

int main() {
    testRemoveElement();
    testRemoveDuplicates();

    cout << "Les deux problemes utilisent la technique du 'slow pointer':" << endl;
    cout << "un index qui avance seulement quand on garde un element." << endl;
    cout << "C'est la base du pattern Two Pointers." << endl;

    return 0;
}
