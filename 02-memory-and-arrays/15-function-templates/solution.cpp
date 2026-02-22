// ============================================================
// Chapitre 15 : Function Templates - Solutions
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// --- PARTIE 1 ---

template<typename T>
T maxVal(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
T minVal(T a, T b) {
    return (a < b) ? a : b;
}

template<typename T>
void swapVal(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

void partie1() {
    cout << "=== PARTIE 1 : Templates basiques ===" << endl;

    cout << "maxVal(10, 20)      = " << maxVal(10, 20) << endl;
    cout << "maxVal(3.14, 2.71)  = " << maxVal(3.14, 2.71) << endl;
    cout << "maxVal('a', 'z')    = " << maxVal('a', 'z') << endl;

    cout << "minVal(10, 20)      = " << minVal(10, 20) << endl;
    cout << "minVal(3.14, 2.71)  = " << minVal(3.14, 2.71) << endl;

    int x = 42, y = 99;
    cout << "Avant swap : x=" << x << " y=" << y << endl;
    swapVal(x, y);
    cout << "Apres swap : x=" << x << " y=" << y << endl;

    string s1 = "hello", s2 = "world";
    cout << "Avant swap : s1=" << s1 << " s2=" << s2 << endl;
    swapVal(s1, s2);
    cout << "Apres swap : s1=" << s1 << " s2=" << s2 << endl;

    cout << endl;
}

// --- PARTIE 2 ---

template<typename T>
T somme(const T arr[], int size) {
    T total = T();
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
}

template<typename T>
void afficher(const T arr[], int size) {
    cout << "[ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

void partie2() {
    cout << "=== PARTIE 2 : Templates sur array ===" << endl;

    int entiers[] = {1, 2, 3, 4, 5};
    double decimaux[] = {1.5, 2.5, 3.5, 4.5};

    cout << "Entiers  : ";
    afficher(entiers, 5);
    cout << "Somme    : " << somme(entiers, 5) << endl;

    cout << "Decimaux : ";
    afficher(decimaux, 4);
    cout << "Somme    : " << somme(decimaux, 4) << endl;

    cout << endl;
}

// --- PARTIE 3 ---

template<typename T, typename U>
void afficherPaire(T premier, U second) {
    cout << premier << " | " << second << endl;
}

void partie3() {
    cout << "=== PARTIE 3 : Multi-types ===" << endl;

    afficherPaire(42, "hello");
    afficherPaire(3.14, true);
    afficherPaire('A', 100);
    afficherPaire(string("nom"), 99.9);

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
