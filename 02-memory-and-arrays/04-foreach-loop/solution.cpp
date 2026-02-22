// =============================================================
// Solution : Range-based for (foreach)
// =============================================================
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// =============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    // ==========================================================
    // PARTIE 1 : Lecture avec range-based for
    // ==========================================================

    int values[] = {12, 45, 7, 89, 23, 56, 34, 78, 1, 90};

    // 1.1
    for (const auto& v : values) {
        cout << v << " ";
    }
    cout << endl;

    // 1.2
    int count = 0;
    for (const auto& v : values) {
        if (v > 50) count++;
    }
    cout << "Elements > 50 : " << count << endl;

    // 1.3
    int maximum = values[0];
    for (const auto& v : values) {
        if (v > maximum) maximum = v;
    }
    cout << "Maximum : " << maximum << endl;

    // ==========================================================
    // PARTIE 2 : Modification avec range-based for
    // ==========================================================

    double prices[] = {10.5, 20.3, 15.7, 8.9, 25.0};

    // 2.1
    for (auto& p : prices) {
        p *= 1.10;
    }

    // 2.2
    cout << "Prix: ";
    for (const auto& p : prices) {
        cout << p << " ";
    }
    cout << endl;

    // 2.3
    for (auto& p : prices) {
        if (p > 25.0) p = 25.0;
    }
    cout << "Prix plafonnes: ";
    for (const auto& p : prices) {
        cout << p << " ";
    }
    cout << endl;

    // ==========================================================
    // PARTIE 3 : Strings et range-based for
    // ==========================================================

    string mots[] = {"hello", "world", "foo", "bar", "cpp", "is", "fast"};

    // 3.1
    for (const auto& m : mots) {
        cout << m << " (" << m.length() << ")" << endl;
    }

    // 3.2
    int totalChars = 0;
    for (const auto& m : mots) {
        totalChars += m.length();
    }
    cout << "Total caracteres: " << totalChars << endl;

    // 3.3
    cout << "Mots courts: ";
    for (const auto& m : mots) {
        if (m.length() <= 3) {
            cout << m << " ";
        }
    }
    cout << endl;

    return 0;
}
