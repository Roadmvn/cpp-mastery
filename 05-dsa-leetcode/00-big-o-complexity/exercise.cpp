// ============================================
// Big O Complexity - Exercices d'identification
// ============================================
// Objectif : Identifier la complexite de chaque fonction
// Ecris ta reponse en commentaire a cote de chaque fonction
// Compile : g++ -std=c++17 exercise.cpp -o exercise

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// EXERCICE 1 : Quelle est la complexite ? -> ???
// -----------------------------------------------
int exercise1(vector<int>& arr) {
    return arr[0] + arr[arr.size() - 1];
}

// -----------------------------------------------
// EXERCICE 2 : Quelle est la complexite ? -> ???
// -----------------------------------------------
int exercise2(vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// -----------------------------------------------
// EXERCICE 3 : Quelle est la complexite ? -> ???
// -----------------------------------------------
bool exercise3(vector<int>& arr) {
    for (int i = 0; i < (int)arr.size(); i++) {
        for (int j = i + 1; j < (int)arr.size(); j++) {
            if (arr[i] == arr[j]) return true;
        }
    }
    return false;
}

// -----------------------------------------------
// EXERCICE 4 : Quelle est la complexite ? -> ???
// -----------------------------------------------
int exercise4(int n) {
    int count = 0;
    while (n > 1) {
        n /= 2;
        count++;
    }
    return count;
}

// -----------------------------------------------
// EXERCICE 5 : Quelle est la complexite ? -> ???
// -----------------------------------------------
void exercise5(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}

// -----------------------------------------------
// EXERCICE 6 : Quelle est la complexite ? -> ???
// -----------------------------------------------
int exercise6(int n) {
    if (n <= 1) return n;
    return exercise6(n - 1) + exercise6(n - 2);
}

// -----------------------------------------------
// EXERCICE 7 : Quelle est la complexite ? -> ???
// -----------------------------------------------
void exercise7(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                // operation O(1)
            }
        }
    }
}

// -----------------------------------------------
// EXERCICE 8 : Quelle est la complexite ? -> ???
// -----------------------------------------------
bool exercise8(vector<int>& sortedArr, int target) {
    int lo = 0, hi = sortedArr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (sortedArr[mid] == target) return true;
        else if (sortedArr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}

// -----------------------------------------------
// EXERCICE 9 : Quelle est la complexite ? -> ???
// (Attention : deux boucles mais PAS imbriquees)
// -----------------------------------------------
int exercise9(vector<int>& arr) {
    int sum = 0;
    for (int x : arr) sum += x;

    int maxVal = arr[0];
    for (int x : arr) maxVal = max(maxVal, x);

    return sum + maxVal;
}

// -----------------------------------------------
// EXERCICE 10 : Quelle est la complexite ? -> ???
// -----------------------------------------------
bool exercise10(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    for (auto& [key, val] : freq) {
        if (val > 1) return true;
    }
    return false;
}

int main() {
    cout << "=== Big O - Exercices ===" << endl;
    cout << "Analyse chaque fonction et determine sa complexite." << endl;
    cout << "Ecris ta reponse a cote de -> ???" << endl;
    cout << endl;

    vector<int> arr = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    vector<int> sorted_arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "Exercise 1: " << exercise1(arr) << endl;
    cout << "Exercise 2: " << exercise2(arr, 7) << endl;
    cout << "Exercise 3: " << exercise3(arr) << endl;
    cout << "Exercise 4: " << exercise4(1024) << endl;
    cout << "Exercise 5: (sort in place)" << endl;
    exercise5(arr);
    cout << "Exercise 6: " << exercise6(10) << endl;
    cout << "Exercise 7: (triple loop)" << endl;
    vector<int> small = {1, 2, 3};
    exercise7(small);
    cout << "Exercise 8: " << exercise8(sorted_arr, 5) << endl;
    cout << "Exercise 9: " << exercise9(sorted_arr) << endl;
    cout << "Exercise 10: " << exercise10(sorted_arr) << endl;

    cout << endl;
    cout << "Verifie tes reponses dans solution.cpp !" << endl;

    return 0;
}
