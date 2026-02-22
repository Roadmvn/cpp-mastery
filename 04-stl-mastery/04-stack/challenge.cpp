// ============================================================
// Stack — Challenge LeetCode
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// ============================================================
//
// Problemes classiques de stack.
// Preparation directe aux Stack problems de LeetCode.
//
// ============================================================

#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// PROBLEME 1 : Valid Parentheses (LeetCode #20)
// ============================================================
//
// Enonce :
// Etant donne une string contenant '(', ')', '{', '}', '[', ']',
// determiner si la string est valide.
// Valide = chaque ouvrante a une fermante correspondante dans le bon ordre.
//
// Exemple :
// "()" -> true
// "()[]{}" -> true
// "(]" -> false
// "([)]" -> false
// "{[]}" -> true
//
// Complexite attendue : O(n) temps, O(n) espace

bool isValid(string s) {
    stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            st.pop();
            if (c == ')' && top != '(') return false;
            if (c == '}' && top != '{') return false;
            if (c == ']' && top != '[') return false;
        }
    }
    return st.empty();
}

// ============================================================
// PROBLEME 2 : Min Stack (LeetCode #155)
// ============================================================
//
// Enonce :
// Implementer un stack qui supporte push, pop, top ET getMin en O(1).
//
// Astuce : utiliser un second stack pour tracker les minimums.

class MinStack {
    stack<int> data;
    stack<int> mins;  // sommet = minimum actuel

public:
    void push(int val) {
        data.push(val);
        if (mins.empty() || val <= mins.top()) {
            mins.push(val);
        }
    }

    void pop() {
        if (data.top() == mins.top()) {
            mins.pop();
        }
        data.pop();
    }

    int top() {
        return data.top();
    }

    int getMin() {
        return mins.top();
    }
};

// ============================================================
// PROBLEME 3 : Next Greater Element (LeetCode #496 simplifie)
// ============================================================
//
// Enonce :
// Etant donne un vector nums, pour chaque element trouver le
// prochain element plus grand a droite. S'il n'existe pas, mettre -1.
//
// Exemple :
// [2, 1, 2, 4, 3] -> [4, 2, 4, -1, -1]
// [1, 3, 2, 4] -> [3, 4, 4, -1]
//
// Complexite attendue : O(n) temps, O(n) espace
// Technique : Monotonic Stack (stack decroissant)

vector<int> nextGreaterElement(vector<int>& nums) {
    int n = (int)nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // contient des INDICES, pas des valeurs

    for (int i = 0; i < n; i++) {
        // Tant que l'element courant est plus grand que l'element
        // au sommet du stack, on a trouve le "next greater"
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}

// ============================================================
// Tests
// ============================================================

void testIsValid() {
    cout << "=== Test isValid (LeetCode #20) ===" << endl;

    struct Test { string input; bool expected; };
    Test tests[] = {
        {"()", true},
        {"()[]{}", true},
        {"(]", false},
        {"([)]", false},
        {"{[]}", true},
        {"", true},
        {"((((", false},
        {"))))", false},
    };

    for (auto& t : tests) {
        bool result = isValid(t.input);
        cout << "\"" << t.input << "\" -> " << (result ? "true" : "false")
             << " | " << (result == t.expected ? "PASS" : "FAIL") << endl;
    }
    cout << endl;
}

void testMinStack() {
    cout << "=== Test MinStack (LeetCode #155) ===" << endl;

    MinStack ms;
    ms.push(-2);
    ms.push(0);
    ms.push(-3);
    cout << "getMin() = " << ms.getMin() << " (attendu: -3) | "
         << (ms.getMin() == -3 ? "PASS" : "FAIL") << endl;

    ms.pop();
    cout << "top() = " << ms.top() << " (attendu: 0) | "
         << (ms.top() == 0 ? "PASS" : "FAIL") << endl;
    cout << "getMin() = " << ms.getMin() << " (attendu: -2) | "
         << (ms.getMin() == -2 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

void testNextGreater() {
    cout << "=== Test nextGreaterElement (LeetCode #496) ===" << endl;

    auto print = [](const vector<int>& v) {
        cout << "[";
        for (int i = 0; i < (int)v.size(); i++) {
            cout << v[i];
            if (i < (int)v.size() - 1) cout << ",";
        }
        cout << "]";
    };

    // Test 1
    vector<int> t1 = {2, 1, 2, 4, 3};
    vector<int> expected1 = {4, 2, 4, -1, -1};
    auto r1 = nextGreaterElement(t1);
    cout << "Input: "; print(t1); cout << " -> "; print(r1);
    cout << " | " << (r1 == expected1 ? "PASS" : "FAIL") << endl;

    // Test 2
    vector<int> t2 = {1, 3, 2, 4};
    vector<int> expected2 = {3, 4, 4, -1};
    auto r2 = nextGreaterElement(t2);
    cout << "Input: "; print(t2); cout << " -> "; print(r2);
    cout << " | " << (r2 == expected2 ? "PASS" : "FAIL") << endl;

    cout << endl;
}

int main() {
    testIsValid();
    testMinStack();
    testNextGreater();

    cout << "Patterns utilises :" << endl;
    cout << "- Stack pour matching de parentheses" << endl;
    cout << "- Double stack pour min en O(1)" << endl;
    cout << "- Monotonic stack pour next greater element" << endl;

    return 0;
}
