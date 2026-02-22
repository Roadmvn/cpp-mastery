// ============================================================
// Iterateurs — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Algorithmes generiques ecrits avec des iterateurs.
// Ces fonctions fonctionnent sur n'importe quel conteneur compatible.
//
// ============================================================

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>
#include <numeric>
using namespace std;

// ============================================================
// ALGORITHME 1 : myFind — chercher dans n'importe quel range
// ============================================================
//
// Implementation de std::find avec des iterateurs.
// Fonctionne sur vector, list, set, tableau C...
//
// Retourne un iterateur sur l'element trouve, ou last si absent.

template<typename Iterator, typename T>
Iterator myFind(Iterator first, Iterator last, const T& value) {
    while (first != last) {
        if (*first == value) return first;
        ++first;
    }
    return last;
}

// ============================================================
// ALGORITHME 2 : myCount — compter les occurrences
// ============================================================

template<typename Iterator, typename T>
int myCount(Iterator first, Iterator last, const T& value) {
    int count = 0;
    while (first != last) {
        if (*first == value) ++count;
        ++first;
    }
    return count;
}

// ============================================================
// ALGORITHME 3 : myReverse — inverser un range bidirectionnel
// ============================================================
//
// Necessite BidirectionalIterator minimum (pas pour forward-only).

template<typename BidirIterator>
void myReverse(BidirIterator first, BidirIterator last) {
    while (first != last) {
        --last;
        if (first == last) break;  // cas nombre pair d'elements
        swap(*first, *last);
        ++first;
    }
}

// ============================================================
// ALGORITHME 4 : myCopy — copier un range dans un autre
// ============================================================

template<typename InputIt, typename OutputIt>
OutputIt myCopy(InputIt first, InputIt last, OutputIt dest) {
    while (first != last) {
        *dest = *first;
        ++dest;
        ++first;
    }
    return dest;
}

// ============================================================
// ALGORITHME 5 : Rotate Left (LeetCode #189 style)
// ============================================================
//
// Decaler un tableau de k positions vers la gauche.
// Utilise la technique 3 reversals sur des ranges d'iterateurs.
//
// Exemple : [1,2,3,4,5], k=2 -> [3,4,5,1,2]

void rotateLeft(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    if (k == 0) return;

    // Technique : reverse [0,k[, reverse [k,n[, reverse [0,n[
    myReverse(nums.begin(), nums.begin() + k);
    myReverse(nums.begin() + k, nums.end());
    myReverse(nums.begin(), nums.end());
}

// ============================================================
// ALGORITHME 6 : Median de deux vecteurs tries (style iterateur)
// ============================================================
//
// Trouver l'element median d'un vecteur avec nth_element.
// nth_element reordonne en O(n) : element a la position k est
// celui qui serait a la position k si le tableau etait trie.

double findMedian(vector<int> nums) {
    int n = nums.size();
    int mid = n / 2;

    nth_element(nums.begin(), nums.begin() + mid, nums.end());

    if (n % 2 == 1) {
        return nums[mid];
    } else {
        // Pour les vecteurs de taille paire, on a besoin des deux elements centraux
        int right = nums[mid];
        nth_element(nums.begin(), nums.begin() + mid - 1, nums.end());
        int left = nums[mid - 1];
        return (left + right) / 2.0;
    }
}

// ============================================================
// Tests
// ============================================================

void testMyFind() {
    cout << "=== Test myFind (generique) ===" << endl;

    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    auto it = myFind(v.begin(), v.end(), 5);
    cout << "[vector] find(5) -> index " << distance(v.begin(), it)
         << " | " << (*it == 5 ? "PASS" : "FAIL") << endl;

    list<string> l = {"apple", "banana", "cherry"};
    auto it2 = myFind(l.begin(), l.end(), string("banana"));
    cout << "[list] find(\"banana\") -> "
         << (*it2 == "banana" ? "PASS" : "FAIL") << endl;

    // Tableau C : les pointeurs sont des iterateurs random-access
    int arr[] = {10, 20, 30, 40, 50};
    auto it3 = myFind(arr, arr + 5, 30);
    cout << "[array C] find(30) -> index " << distance(arr, it3)
         << " | " << (*it3 == 30 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testMyCount() {
    cout << "=== Test myCount (generique) ===" << endl;

    vector<int> v = {1, 3, 1, 4, 1, 5, 1};
    cout << "Occurrences de 1 dans [1,3,1,4,1,5,1] : " << myCount(v.begin(), v.end(), 1)
         << " | " << (myCount(v.begin(), v.end(), 1) == 4 ? "PASS" : "FAIL") << endl;

    string s = "abracadabra";
    cout << "Occurrences de 'a' dans \"abracadabra\" : " << myCount(s.begin(), s.end(), 'a')
         << " | " << (myCount(s.begin(), s.end(), 'a') == 5 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testMyReverse() {
    cout << "=== Test myReverse (generique) ===" << endl;

    vector<int> v1 = {1, 2, 3, 4, 5};
    myReverse(v1.begin(), v1.end());
    cout << "Reverse [1,2,3,4,5] -> ";
    for (int x : v1) cout << x << " ";
    vector<int> expected1 = {5, 4, 3, 2, 1};
    cout << "| " << (v1 == expected1 ? "PASS" : "FAIL") << endl;

    list<int> l = {10, 20, 30, 40};
    myReverse(l.begin(), l.end());
    cout << "Reverse list [10,20,30,40] -> ";
    for (int x : l) cout << x << " ";
    cout << "| " << (*l.begin() == 40 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testRotateLeft() {
    cout << "=== Test rotateLeft ===" << endl;

    vector<int> v1 = {1, 2, 3, 4, 5};
    rotateLeft(v1, 2);
    cout << "[1,2,3,4,5] rotate left 2 -> ";
    for (int x : v1) cout << x << " ";
    vector<int> expected = {3, 4, 5, 1, 2};
    cout << "| " << (v1 == expected ? "PASS" : "FAIL") << endl;

    vector<int> v2 = {1, 2, 3};
    rotateLeft(v2, 6);  // 6 % 3 = 0, aucun changement
    cout << "[1,2,3] rotate left 6 (= 0 mod 3) -> ";
    for (int x : v2) cout << x << " ";
    vector<int> expected2 = {1, 2, 3};
    cout << "| " << (v2 == expected2 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testFindMedian() {
    cout << "=== Test findMedian ===" << endl;

    vector<int> v1 = {3, 1, 4, 1, 5};
    cout << "Median de [3,1,4,1,5] -> " << findMedian(v1)
         << " | " << (findMedian(v1) == 3.0 ? "PASS" : "FAIL") << endl;

    vector<int> v2 = {1, 2, 3, 4};
    cout << "Median de [1,2,3,4] -> " << findMedian(v2)
         << " | " << (findMedian(v2) == 2.5 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

int main() {
    testMyFind();
    testMyCount();
    testMyReverse();
    testRotateLeft();
    testFindMedian();

    cout << "Patterns utilises :" << endl;
    cout << "- Templates generiques avec iterateurs (fonctionnent sur tout conteneur)" << endl;
    cout << "- Technique 3 reversals pour rotation O(n)" << endl;
    cout << "- nth_element pour median en O(n) au lieu de O(n log n)" << endl;
    cout << "- Pointeurs C comme iterateurs random-access" << endl;

    return 0;
}
