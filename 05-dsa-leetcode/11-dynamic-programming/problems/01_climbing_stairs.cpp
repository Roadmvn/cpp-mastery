// ============================================
// LeetCode #70 - Climbing Stairs (Easy)
// https://leetcode.com/problems/climbing-stairs/
// ============================================
// Enonce : Tu dois grimper un escalier de n marches. A chaque etape,
// tu peux monter 1 ou 2 marches. De combien de facons distinctes
// peux-tu atteindre le sommet ?
//
// Exemple :
//   n=2 → 2  (1+1 | 2)
//   n=3 → 3  (1+1+1 | 1+2 | 2+1)
//
// Compile : g++ -std=c++17 01_climbing_stairs.cpp -o 01

#include <iostream>
#include <unordered_map>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(2^n) temps | O(n) espace (pile)
// Recursion pure : compter toutes les facons de
// monter. Arbre de recursion exponentiel.
//
// Schema :
//   climb(4)
//   ├── climb(3)      (+1 marche)
//   │   ├── climb(2)  (+1)
//   │   │   ├── climb(1) → 1 facon
//   │   │   └── climb(0) → 1 facon
//   │   └── climb(1)  (+2) → 1 facon
//   └── climb(2)      (+2 marche)
//       ├── climb(1) → 1 facon
//       └── climb(0) → 1 facon
//   Total : 5 facons
// -----------------------------------------------
int climbStairsBrute(int n) {
    if (n <= 1) return 1;
    return climbStairsBrute(n - 1) + climbStairsBrute(n - 2);
}

// -----------------------------------------------
// TOP-DOWN : O(n) temps | O(n) espace
// Recursion + memoization pour eviter les recalculs.
// -----------------------------------------------
unordered_map<int, int> memo;
int climbStairsTopDown(int n) {
    if (n <= 1) return 1;
    if (memo.count(n)) return memo[n];
    memo[n] = climbStairsTopDown(n - 1) + climbStairsTopDown(n - 2);
    return memo[n];
}

// -----------------------------------------------
// OPTIMAL - BOTTOM-UP : O(n) temps | O(1) espace
// C'est exactement Fibonacci ! ways(n) = ways(n-1) + ways(n-2)
// On peut reduire l'espace a 2 variables.
//
// Schema ASCII :
//
//   n=5
//   ┌────┬────┬────┬────┬────┬────┐
//   │ n  │  0 │  1 │  2 │  3 │  4 │  5  │
//   │ways│  1 │  1 │  2 │  3 │  5 │  8  │
//   └────┴────┴────┴────┴────┴────┴─────┘
//
//   ways[i] = ways[i-1] + ways[i-2]
//   ways[2] = ways[1] + ways[0] = 1 + 1 = 2
//   ways[3] = ways[2] + ways[1] = 2 + 1 = 3
//   ways[5] = ways[4] + ways[3] = 5 + 3 = 8
// -----------------------------------------------
int climbStairsOptimal(int n) {
    if (n <= 1) return 1;
    int prev2 = 1; // ways(0)
    int prev1 = 1; // ways(1)

    for (int i = 2; i <= n; i++) {
        int cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int main() {
    cout << "=== LeetCode #70 - Climbing Stairs ===" << endl;

    for (int n : {1, 2, 3, 4, 5, 10, 20}) {
        memo.clear();
        cout << "n=" << n << " → ";
        cout << "Brute=" << climbStairsBrute(n);
        cout << " | TopDown=" << climbStairsTopDown(n);
        cout << " | Optimal=" << climbStairsOptimal(n) << endl;
    }
    // n=1 → 1 | n=2 → 2 | n=3 → 3 | n=4 → 5 | n=5 → 8

    cout << "\nComplexite Brute   : O(2^n) temps | O(n) espace" << endl;
    cout << "Complexite TopDown : O(n)   temps | O(n) espace" << endl;
    cout << "Complexite Optimal : O(n)   temps | O(1) espace" << endl;

    return 0;
}
