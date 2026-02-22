// ============================================
// LeetCode #74 - Search a 2D Matrix (Medium)
// https://leetcode.com/problems/search-a-2d-matrix/
// ============================================
// Enonce : Matrice m x n triee (chaque ligne triee, premier element
// de chaque ligne > dernier element de la ligne precedente).
// Chercher si target existe.
//
// Exemple : matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
//           -> Output: true
//
// Compile : g++ -std=c++17 02_search_2d_matrix.cpp -o 02

#include <iostream>
#include <vector>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(m * n) temps | O(1) espace
// Parcourir chaque element
// -----------------------------------------------
bool searchMatrixBrute(vector<vector<int>>& matrix, int target) {
    for (auto& row : matrix) {
        for (int val : row) {
            if (val == target) return true;
        }
    }
    return false;
}

// -----------------------------------------------
// OPTIMAL : O(log(m * n)) temps | O(1) espace
// Traiter la matrice comme un array 1D et binary search
//
// Schema :
//   [[1,  3,  5,  7],     Index 1D:
//    [10, 11, 16, 20],    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
//    [23, 30, 34, 60]]
//
//   Conversion : index -> row = index / cols, col = index % cols
//
//   target = 3, lo=0, hi=11
//   mid=5 -> matrix[5/4][5%4] = matrix[1][1] = 11 > 3 -> hi=4
//   mid=2 -> matrix[2/4][2%4] = matrix[0][2] = 5 > 3 -> hi=1
//   mid=0 -> matrix[0][0] = 1 < 3 -> lo=1
//   mid=1 -> matrix[0][1] = 3 == 3 -> TROUVE!
// -----------------------------------------------
bool searchMatrixOptimal(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    int lo = 0, hi = m * n - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = matrix[mid / n][mid % n]; // conversion 1D -> 2D

        if (val == target) return true;
        else if (val < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}

int main() {
    cout << "=== #74 Search a 2D Matrix ===" << endl;

    vector<vector<int>> matrix1 = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    cout << "Matrix: [[1,3,5,7],[10,11,16,20],[23,30,34,60]]" << endl;

    cout << "target=3  -> Brute: " << searchMatrixBrute(matrix1, 3)
         << " Optimal: " << searchMatrixOptimal(matrix1, 3)
         << " (attendu: 1)" << endl;

    cout << "target=13 -> Brute: " << searchMatrixBrute(matrix1, 13)
         << " Optimal: " << searchMatrixOptimal(matrix1, 13)
         << " (attendu: 0)" << endl;

    cout << "target=23 -> Optimal: " << searchMatrixOptimal(matrix1, 23)
         << " (attendu: 1)" << endl;

    cout << "target=60 -> Optimal: " << searchMatrixOptimal(matrix1, 60)
         << " (attendu: 1)" << endl;

    vector<vector<int>> matrix2 = {{1}};
    cout << "\nMatrix: [[1]]" << endl;
    cout << "target=1 -> Optimal: " << searchMatrixOptimal(matrix2, 1)
         << " (attendu: 1)" << endl;
    cout << "target=0 -> Optimal: " << searchMatrixOptimal(matrix2, 0)
         << " (attendu: 0)" << endl;

    return 0;
}
