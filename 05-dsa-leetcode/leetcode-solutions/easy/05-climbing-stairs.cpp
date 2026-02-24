// https://leetcode.com/problems/climbing-stairs/
// #70 - Climbing Stairs
//
// Monter n marches, 1 ou 2 a la fois. Combien de facons distinctes ?
//
// Approche : DP avec espace O(1).
// Observation : f(n) = f(n-1) + f(n-2) — c'est Fibonacci.
// Garder seulement les deux derniers etats suffit.
// Complexite temps : O(n) | Complexite espace : O(1)

#include <iostream>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;

        int prev2 = 1; // f(1)
        int prev1 = 2; // f(2)

        for (int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

int main() {
    Solution sol;

    cout << sol.climbStairs(1)  << endl; // 1
    cout << sol.climbStairs(2)  << endl; // 2
    cout << sol.climbStairs(3)  << endl; // 3
    cout << sol.climbStairs(4)  << endl; // 5
    cout << sol.climbStairs(5)  << endl; // 8
    cout << sol.climbStairs(10) << endl; // 89
    cout << sol.climbStairs(45) << endl; // 1836311903

    return 0;
}
