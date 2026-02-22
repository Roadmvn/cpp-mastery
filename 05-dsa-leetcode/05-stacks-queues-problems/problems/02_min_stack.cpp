// ============================================
// LeetCode #155 - Min Stack (Medium)
// https://leetcode.com/problems/min-stack/
// ============================================
// Enonce : Designer une stack qui supporte push, pop, top, et getMin
// en temps constant O(1).
//
// Exemple : push(-2), push(0), push(-3), getMin() -> -3
//           pop(), top() -> 0, getMin() -> -2
//
// Compile : g++ -std=c++17 02_min_stack.cpp -o 02

#include <iostream>
#include <stack>
#include <climits>
using namespace std;

// -----------------------------------------------
// BRUTE FORCE : O(n) pour getMin | O(n) espace
// Parcourir toute la stack pour trouver le min
// -----------------------------------------------
class MinStackBrute {
    stack<int> st;
public:
    void push(int val) {
        st.push(val);
    }

    void pop() {
        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        stack<int> temp = st;
        int minVal = INT_MAX;
        while (!temp.empty()) {
            minVal = min(minVal, temp.top());
            temp.pop();
        }
        return minVal;
    }
};

// -----------------------------------------------
// OPTIMAL : O(1) pour TOUTES les operations | O(n) espace
// Deux stacks : une pour les donnees, une pour les minimums
//
// Schema :
//   Operation     dataStack    minStack
//   push(-2)      [-2]         [-2]
//   push(0)       [-2, 0]     [-2]        (0 > -2, pas push dans minStack)
//   push(-3)      [-2, 0, -3] [-2, -3]    (-3 <= -2, push dans minStack)
//   getMin()                               -> minStack.top() = -3
//   pop()         [-2, 0]     [-2]        (-3 == minStack.top(), pop minStack)
//   top()                                  -> 0
//   getMin()                               -> minStack.top() = -2
// -----------------------------------------------
class MinStackOptimal {
    stack<int> dataStack;
    stack<int> minStack;

public:
    void push(int val) {
        dataStack.push(val);
        // Push si minStack est vide OU val <= min actuel
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }

    void pop() {
        // Si on pop le min actuel, le retirer aussi de minStack
        if (dataStack.top() == minStack.top()) {
            minStack.pop();
        }
        dataStack.pop();
    }

    int top() {
        return dataStack.top();
    }

    int getMin() {
        return minStack.top(); // O(1)
    }
};

// -----------------------------------------------
// OPTIMAL V2 : Avec une seule stack de pairs
// Chaque element stocke la valeur ET le min a ce moment
// -----------------------------------------------
class MinStackV2 {
    stack<pair<int, int>> st; // {value, current_min}

public:
    void push(int val) {
        int currMin = st.empty() ? val : min(val, st.top().second);
        st.push({val, currMin});
    }

    void pop() {
        st.pop();
    }

    int top() {
        return st.top().first;
    }

    int getMin() {
        return st.top().second;
    }
};

int main() {
    cout << "=== #155 Min Stack ===" << endl;

    // Test Optimal
    cout << "--- MinStack Optimal (deux stacks) ---" << endl;
    MinStackOptimal ms;
    ms.push(-2);
    ms.push(0);
    ms.push(-3);
    cout << "getMin(): " << ms.getMin() << " (attendu: -3)" << endl;
    ms.pop();
    cout << "top():    " << ms.top() << " (attendu: 0)" << endl;
    cout << "getMin(): " << ms.getMin() << " (attendu: -2)" << endl;
    cout << endl;

    // Test V2
    cout << "--- MinStack V2 (stack de pairs) ---" << endl;
    MinStackV2 ms2;
    ms2.push(-2);
    ms2.push(0);
    ms2.push(-3);
    cout << "getMin(): " << ms2.getMin() << " (attendu: -3)" << endl;
    ms2.pop();
    cout << "top():    " << ms2.top() << " (attendu: 0)" << endl;
    cout << "getMin(): " << ms2.getMin() << " (attendu: -2)" << endl;
    cout << endl;

    // Test supplementaire
    cout << "--- Test supplementaire ---" << endl;
    MinStackOptimal ms3;
    ms3.push(0);
    ms3.push(1);
    ms3.push(0);
    cout << "getMin(): " << ms3.getMin() << " (attendu: 0)" << endl;
    ms3.pop();
    cout << "getMin(): " << ms3.getMin() << " (attendu: 0)" << endl;

    return 0;
}
