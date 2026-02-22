// ============================================
// Binary Search - Templates copier-coller
// ============================================
// Compile : g++ -std=c++17 pattern-template.cpp -o pattern-template

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// TEMPLATE 1 : Recherche exacte
// Retourne l'index de target, ou -1 si absent
// Condition : lo <= hi (inclusif des deux cotes)
// -----------------------------------------------
int exactSearch(vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;  // evite l'overflow
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// -----------------------------------------------
// TEMPLATE 2 : Lower bound (premier element >= target)
// Equivalent a std::lower_bound
// Condition : lo < hi (hi est exclusif)
// -----------------------------------------------
int lowerBound(vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size();

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid;
    }
    return lo; // premier index ou arr[lo] >= target
}

// -----------------------------------------------
// TEMPLATE 3 : Upper bound (premier element > target)
// Equivalent a std::upper_bound
// -----------------------------------------------
int upperBound(vector<int>& arr, int target) {
    int lo = 0, hi = (int)arr.size();

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= target) lo = mid + 1;
        else hi = mid;
    }
    return lo; // premier index ou arr[lo] > target
}

// -----------------------------------------------
// TEMPLATE 4 : Binary search sur la reponse
// "Quel est le minimum X tel que condition(X) est vraie ?"
// -----------------------------------------------
bool condition(int value) {
    // A adapter selon le probleme
    return value >= 5;
}

int searchOnAnswer(int lo, int hi) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (condition(mid)) hi = mid;     // condition vraie -> chercher plus petit
        else lo = mid + 1;               // condition fausse -> chercher plus grand
    }
    return lo;
}

// -----------------------------------------------
// TEMPLATE 5 : Binary search dans un array 2D
// Traiter la matrice m x n comme un array 1D de taille m*n
// -----------------------------------------------
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int lo = 0, hi = m * n - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = matrix[mid / n][mid % n]; // conversion index 1D -> 2D
        if (val == target) return true;
        else if (val < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}

int main() {
    cout << "=== Binary Search Templates ===" << endl;

    vector<int> arr = {1, 3, 5, 7, 9, 11, 13};

    // Test exact search
    cout << "Exact search (7): index " << exactSearch(arr, 7) << endl;   // 3
    cout << "Exact search (4): index " << exactSearch(arr, 4) << endl;   // -1

    // Test lower bound
    cout << "Lower bound (5): index " << lowerBound(arr, 5) << endl;    // 2
    cout << "Lower bound (6): index " << lowerBound(arr, 6) << endl;    // 3

    // Test upper bound
    cout << "Upper bound (5): index " << upperBound(arr, 5) << endl;    // 3
    cout << "Upper bound (7): index " << upperBound(arr, 7) << endl;    // 4

    // Test search on answer
    cout << "Min value >= 5: " << searchOnAnswer(0, 100) << endl;       // 5

    // Test matrix search
    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    cout << "Matrix search (3): " << searchMatrix(matrix, 3) << endl;    // 1
    cout << "Matrix search (13): " << searchMatrix(matrix, 13) << endl;  // 0

    return 0;
}
