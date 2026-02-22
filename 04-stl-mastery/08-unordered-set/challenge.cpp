// ============================================================
// Unordered Set — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Problemes classiques uses en competition et LeetCode.
// Chaque probleme illustre un pattern cle du set non ordonne.
//
// ============================================================

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// PROBLEME 1 : Contains Duplicate (LeetCode #217)
// ============================================================
//
// Enonce :
// Etant donne un tableau nums, retourner true si un element
// apparait au moins deux fois, false sinon.
//
// Exemple :
// [1,2,3,1]       -> true
// [1,2,3,4]       -> false
// [1,1,1,3,3,4,3,2,4,2] -> true
//
// Complexite : O(n) temps, O(n) espace

bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int num : nums) {
        if (seen.count(num)) return true;
        seen.insert(num);
    }
    return false;
}

// ============================================================
// PROBLEME 2 : Intersection of Two Arrays (LeetCode #349)
// ============================================================
//
// Enonce :
// Etant donne deux tableaux, retourner leur intersection.
// Chaque element du resultat est unique.
//
// Exemple :
// [1,2,2,1] et [2,2] -> [2]
// [4,9,5]   et [9,4,9,8,4] -> [9,4]
//
// Complexite : O(n + m) temps, O(min(n,m)) espace

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> setA(nums1.begin(), nums1.end());
    unordered_set<int> result;
    for (int x : nums2) {
        if (setA.count(x)) {
            result.insert(x);
        }
    }
    return vector<int>(result.begin(), result.end());
}

// ============================================================
// PROBLEME 3 : Longest Consecutive Sequence (LeetCode #128)
// ============================================================
//
// Enonce :
// Etant donne un tableau non trie, trouver la longueur de la
// plus longue sequence d'entiers consecutifs.
// Complexite attendue : O(n)
//
// Exemple :
// [100,4,200,1,3,2] -> 4  (sequence : 1,2,3,4)
// [0,3,7,2,5,8,4,6,0,1] -> 9 (sequence : 0..8)
//
// Technique :
// Pour chaque debut de sequence (num-1 absent), on compte
// combien d'elements consecutifs suivent.
// Chaque element n'est visite qu'une seule fois => O(n)

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int maxLen = 0;

    for (int num : s) {
        // On ne commence un comptage que si c'est un debut de sequence
        if (!s.count(num - 1)) {
            int len = 1;
            while (s.count(num + len)) len++;
            maxLen = max(maxLen, len);
        }
    }
    return maxLen;
}

// ============================================================
// PROBLEME 4 : Happy Number (LeetCode #202)
// ============================================================
//
// Enonce :
// Un "happy number" est defini par :
// - Remplacer le nombre par la somme des carres de ses chiffres
// - Repeter jusqu'a obtenir 1 (happy) ou entrer dans un cycle (not happy)
//
// Exemple :
// 19 -> 1^2 + 9^2 = 82 -> 8^2 + 2^2 = 68 -> 36 -> 45 -> 41 -> 17 -> 50 -> 25 -> 29 -> 85 -> 89 -> 145 -> 42 -> 20 -> 4 -> 16 -> 37 -> 58 -> 89 (cycle!)
// 7  -> 49 -> 97 -> 130 -> 10 -> 1 (happy !)
//
// Technique : detecter le cycle avec un set

int sumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
        int d = n % 10;
        sum += d * d;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    unordered_set<int> seen;
    while (n != 1) {
        if (seen.count(n)) return false;  // cycle detecte
        seen.insert(n);
        n = sumOfSquares(n);
    }
    return true;
}

// ============================================================
// Tests
// ============================================================

void testContainsDuplicate() {
    cout << "=== Test containsDuplicate (LC #217) ===" << endl;

    vector<int> t1 = {1, 2, 3, 1};
    cout << "[1,2,3,1] -> " << (containsDuplicate(t1) ? "true" : "false")
         << " | " << (containsDuplicate(t1) == true ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {1, 2, 3, 4};
    cout << "[1,2,3,4] -> " << (containsDuplicate(t2) ? "true" : "false")
         << " | " << (containsDuplicate(t2) == false ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testIntersection() {
    cout << "=== Test intersection (LC #349) ===" << endl;

    vector<int> a1 = {1, 2, 2, 1}, b1 = {2, 2};
    auto r1 = intersection(a1, b1);
    cout << "[1,2,2,1] & [2,2] -> ";
    for (int x : r1) cout << x << " ";
    cout << "| " << (r1.size() == 1 && r1[0] == 2 ? "PASS" : "FAIL") << endl;

    vector<int> a2 = {4, 9, 5}, b2 = {9, 4, 9, 8, 4};
    auto r2 = intersection(a2, b2);
    cout << "[4,9,5] & [9,4,9,8,4] -> ";
    for (int x : r2) cout << x << " ";
    cout << "| " << (r2.size() == 2 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testLongestConsecutive() {
    cout << "=== Test longestConsecutive (LC #128) ===" << endl;

    vector<int> t1 = {100, 4, 200, 1, 3, 2};
    cout << "[100,4,200,1,3,2] -> " << longestConsecutive(t1)
         << " | " << (longestConsecutive(t1) == 4 ? "PASS" : "FAIL") << endl;

    vector<int> t2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << "[0,3,7,2,5,8,4,6,0,1] -> " << longestConsecutive(t2)
         << " | " << (longestConsecutive(t2) == 9 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testIsHappy() {
    cout << "=== Test isHappy (LC #202) ===" << endl;

    cout << "7 -> " << (isHappy(7) ? "happy" : "not happy")
         << " | " << (isHappy(7) == true ? "PASS" : "FAIL") << endl;

    // 1^2 + 9^2 = 82 -> ... -> 1 => 19 EST happy
    cout << "19 -> " << (isHappy(19) ? "happy" : "not happy")
         << " | " << (isHappy(19) == true ? "PASS" : "FAIL") << endl;

    // 2 -> 4 -> 16 -> 37 -> 58 -> 89 -> cycle => NOT happy
    cout << "2 -> " << (isHappy(2) ? "happy" : "not happy")
         << " | " << (isHappy(2) == false ? "PASS" : "FAIL") << endl;

    cout << "1 -> " << (isHappy(1) ? "happy" : "not happy")
         << " | " << (isHappy(1) == true ? "PASS" : "FAIL") << endl;

    cout << endl;
}

int main() {
    testContainsDuplicate();
    testIntersection();
    testLongestConsecutive();
    testIsHappy();

    cout << "Patterns utilises :" << endl;
    cout << "- Insertion + lookup O(1) pour detection de cycle/doublons" << endl;
    cout << "- Construction depuis iterateurs pour intersection" << endl;
    cout << "- Debut de sequence pour Longest Consecutive (O(n) total)" << endl;

    return 0;
}
