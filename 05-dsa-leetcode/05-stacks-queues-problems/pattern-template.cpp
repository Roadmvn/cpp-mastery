// ============================================
// Stacks & Queues - Templates copier-coller
// ============================================
// Compile : g++ -std=c++17 pattern-template.cpp -o pattern-template

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

// -----------------------------------------------
// TEMPLATE 1 : Validation de parentheses
// O(n) temps | O(n) espace
// -----------------------------------------------
bool isValidParentheses(string s) {
    stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '[')) {
                st.pop();
            } else {
                return false;
            }
        }
    }
    return st.empty();
}

// -----------------------------------------------
// TEMPLATE 2 : Monotonic Stack - Next Greater Element
// O(n) temps | O(n) espace
// -----------------------------------------------
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // indices

    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

// -----------------------------------------------
// TEMPLATE 3 : Monotonic Stack - Previous Smaller Element
// O(n) temps | O(n) espace
// -----------------------------------------------
vector<int> prevSmallerElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] >= nums[i]) {
            st.pop();
        }
        if (!st.empty()) result[i] = nums[st.top()];
        st.push(i);
    }
    return result;
}

// -----------------------------------------------
// TEMPLATE 4 : Evaluation d'expression postfixe (RPN)
// O(n) temps | O(n) espace
// -----------------------------------------------
int evalRPN(vector<string>& tokens) {
    stack<int> st;

    for (string& tok : tokens) {
        if (tok == "+" || tok == "-" || tok == "*" || tok == "/") {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            if (tok == "+") st.push(a + b);
            else if (tok == "-") st.push(a - b);
            else if (tok == "*") st.push(a * b);
            else st.push(a / b);
        } else {
            st.push(stoi(tok));
        }
    }
    return st.top();
}

// -----------------------------------------------
// TEMPLATE 5 : Min Stack (stack avec getMin en O(1))
// -----------------------------------------------
class MinStack {
    stack<int> dataStack;
    stack<int> minStack;
public:
    void push(int val) {
        dataStack.push(val);
        if (minStack.empty() || val <= minStack.top())
            minStack.push(val);
    }
    void pop() {
        if (dataStack.top() == minStack.top())
            minStack.pop();
        dataStack.pop();
    }
    int top() { return dataStack.top(); }
    int getMin() { return minStack.top(); }
};

int main() {
    cout << "=== Stacks & Queues Templates ===" << endl;

    // Test parentheses
    cout << "Valid '()[]{}': " << isValidParentheses("()[]{}") << endl;     // 1
    cout << "Valid '(]': " << isValidParentheses("(]") << endl;             // 0

    // Test next greater
    vector<int> nums = {2, 1, 2, 4, 3};
    auto ng = nextGreaterElement(nums);
    cout << "Next greater [2,1,2,4,3]: ";
    for (int x : ng) cout << x << " ";
    cout << endl; // 4 2 4 -1 -1

    // Test RPN
    vector<string> tokens = {"2", "1", "+", "3", "*"};
    cout << "RPN '2 1 + 3 *': " << evalRPN(tokens) << endl; // 9

    // Test MinStack
    MinStack ms;
    ms.push(-2); ms.push(0); ms.push(-3);
    cout << "MinStack getMin: " << ms.getMin() << endl; // -3
    ms.pop();
    cout << "MinStack top: " << ms.top() << endl;       // 0
    cout << "MinStack getMin: " << ms.getMin() << endl;  // -2

    return 0;
}
