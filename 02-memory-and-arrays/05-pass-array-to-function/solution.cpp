// =============================================================
// Solution : Passer un array a une fonction
// =============================================================
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// =============================================================

#include <iostream>
using namespace std;

// ==========================================================
// PARTIE 1 : Fonctions de base sur arrays
// ==========================================================

// 1.1
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << " ";
    }
    cout << endl;
}

// 1.2
int sumArray(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 1.3
int findMax(const int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// ==========================================================
// PARTIE 2 : Fonctions qui modifient l'array
// ==========================================================

// 2.1
void addToAll(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] += value;
    }
}

// 2.2
void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

// 2.3
void clampArray(int arr[], int size, int minVal, int maxVal) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < minVal) arr[i] = minVal;
        if (arr[i] > maxVal) arr[i] = maxVal;
    }
}

// ==========================================================
// PARTIE 3 : Fonctions avancees
// ==========================================================

// 3.1
void copyArray(const int src[], int dst[], int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}

// 3.2
int dotProduct(const int a[], const int b[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += a[i] * b[i];
    }
    return result;
}

// 3.3
int countIf(const int arr[], int size, int threshold) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > threshold) count++;
    }
    return count;
}

int main() {
    int data[] = {15, 42, 8, 23, 56, 11, 34, 67, 3, 29};
    int size = sizeof(data) / sizeof(data[0]);

    // Tests partie 1
    cout << "=== Partie 1 ===" << endl;
    cout << "Array: ";
    printArray(data, size);
    cout << "Somme: " << sumArray(data, size) << endl;
    cout << "Max: " << findMax(data, size) << endl;

    // Tests partie 2
    cout << "\n=== Partie 2 ===" << endl;
    addToAll(data, size, 10);
    cout << "Apres +10: ";
    printArray(data, size);

    reverseArray(data, size);
    cout << "Inverse: ";
    printArray(data, size);

    clampArray(data, size, 20, 60);
    cout << "Clampe [20,60]: ";
    printArray(data, size);

    // Tests partie 3
    cout << "\n=== Partie 3 ===" << endl;
    int copie[10];
    copyArray(data, copie, size);
    cout << "Copie: ";
    printArray(copie, size);

    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    cout << "Produit scalaire: " << dotProduct(a, b, 3) << endl;

    cout << "Nb > 30: " << countIf(data, size, 30) << endl;

    return 0;
}
