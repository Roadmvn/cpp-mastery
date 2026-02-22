// ============================================================
// Chapitre 11 : Pointeurs - Solutions
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
using namespace std;

// --- PARTIE 1 ---

void partie1() {
    cout << "=== PARTIE 1 : Pointeurs de base ===" << endl;

    int x = 42;
    int* p = &x;

    cout << "Valeur de x      : " << x << endl;
    cout << "Adresse de x (&x): " << &x << endl;
    cout << "Valeur de p      : " << p << endl;
    cout << "Valeur pointee *p: " << *p << endl;
    cout << "Adresse de p (&p): " << &p << endl;

    cout << endl;
    cout << "Modification via pointeur : *p = 100" << endl;
    *p = 100;
    cout << "x = " << x << " (modifie via le pointeur)" << endl;

    cout << endl;
}

// --- PARTIE 2 ---

void partie2() {
    cout << "=== PARTIE 2 : Arithmetique des pointeurs ===" << endl;

    int arr[6] = {5, 15, 25, 35, 45, 55};
    int* p = arr;

    for (int i = 0; i < 6; i++) {
        cout << "*(p+" << i << ") = " << *(p + i)
             << "\t adresse: " << (p + i) << endl;
    }

    cout << endl;
    cout << "Ecart entre elements : "
         << (char*)(p + 1) - (char*)p << " octets (sizeof(int) = "
         << sizeof(int) << ")" << endl;

    cout << endl;
}

// --- PARTIE 3 ---

void tripler(int* p) {
    *p = *p * 3;
}

void ordonner(int* a, int* b) {
    if (*a > *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

void partie3() {
    cout << "=== PARTIE 3 : Pointeurs en parametres ===" << endl;

    int n = 7;
    cout << "Avant tripler : n = " << n << endl;
    tripler(&n);
    cout << "Apres tripler : n = " << n << endl;

    cout << endl;

    int a = 50, b = 20;
    cout << "Avant ordonner : a = " << a << ", b = " << b << endl;
    ordonner(&a, &b);
    cout << "Apres ordonner : a = " << a << ", b = " << b << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
