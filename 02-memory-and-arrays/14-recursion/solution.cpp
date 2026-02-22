// ============================================================
// Chapitre 14 : Recursion - Solutions
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
using namespace std;

// --- PARTIE 1 ---

int factorielle(int n) {
    if (n <= 1) return 1;
    return n * factorielle(n - 1);
}

int somme(int n) {
    if (n <= 0) return 0;
    return n + somme(n - 1);
}

void partie1() {
    cout << "=== PARTIE 1 : Factorielle et somme ===" << endl;

    cout << "factorielle(0)  = " << factorielle(0) << endl;
    cout << "factorielle(5)  = " << factorielle(5) << endl;
    cout << "factorielle(10) = " << factorielle(10) << endl;

    cout << "somme(0)   = " << somme(0) << endl;
    cout << "somme(5)   = " << somme(5) << endl;
    cout << "somme(100) = " << somme(100) << endl;

    cout << endl;
}

// --- PARTIE 2 ---

int sommeArray(const int arr[], int size) {
    if (size == 0) return 0;
    return arr[size - 1] + sommeArray(arr, size - 1);
}

int maxArray(const int arr[], int size) {
    if (size == 1) return arr[0];
    int maxReste = maxArray(arr, size - 1);
    return (arr[size - 1] > maxReste) ? arr[size - 1] : maxReste;
}

void partie2() {
    cout << "=== PARTIE 2 : Recursion sur array ===" << endl;

    int arr[] = {3, 7, 2, 9, 4, 1};
    int size = 6;

    cout << "Array : ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "sommeArray = " << sommeArray(arr, size) << endl;
    cout << "maxArray   = " << maxArray(arr, size) << endl;

    cout << endl;
}

// --- PARTIE 3 ---

void countdown(int n) {
    if (n <= 0) return;
    cout << n << " ";           // Affiche AVANT l'appel
    countdown(n - 1);
}

void countup(int n) {
    if (n <= 0) return;
    countup(n - 1);             // Appel recursif D'ABORD
    cout << n << " ";           // Affiche APRES le retour
}

void partie3() {
    cout << "=== PARTIE 3 : Affichage recursif ===" << endl;

    cout << "countdown(5) : ";
    countdown(5);
    cout << endl;

    cout << "countup(5)   : ";
    countup(5);
    cout << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
