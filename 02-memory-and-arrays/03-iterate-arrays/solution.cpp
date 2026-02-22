// =============================================================
// Solution : Parcourir les Arrays
// =============================================================
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// =============================================================

#include <iostream>
using namespace std;

int main() {
    int data[] = {15, 42, 8, 23, 56, 11, 34, 67, 3, 29};
    int size = sizeof(data) / sizeof(data[0]);

    // ==========================================================
    // PARTIE 1 : Boucle for classique
    // ==========================================================

    // 1.1
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << " ";
    }
    cout << endl;

    // 1.2
    cout << "Index pairs: ";
    for (int i = 0; i < size; i += 2) {
        cout << data[i];
        if (i + 2 < size) cout << " ";
    }
    cout << endl;

    // 1.3
    cout << "Inverse: ";
    for (int i = size - 1; i >= 0; i--) {
        cout << data[i];
        if (i > 0) cout << " ";
    }
    cout << endl;

    // ==========================================================
    // PARTIE 2 : Boucle while
    // ==========================================================

    // 2.1
    int idx = 0;
    while (idx < size && data[idx] <= 50) {
        idx++;
    }
    if (idx < size) {
        cout << "Premier > 50 : data[" << idx << "] = " << data[idx] << endl;
    }

    // 2.2
    int count = 0;
    int j = 0;
    while (j < size) {
        if (data[j] < 20) count++;
        j++;
    }
    cout << "Elements < 20 : " << count << endl;

    // 2.3
    int somme = 0;
    int k = 0;
    while (k < size && somme <= 100) {
        somme += data[k];
        k++;
    }
    cout << "Il faut " << k << " elements pour depasser 100 (somme: " << somme << ")" << endl;

    // ==========================================================
    // PARTIE 3 : Parcours avec transformation
    // ==========================================================

    // 3.1
    int doubled[10];
    for (int i = 0; i < size; i++) {
        doubled[i] = data[i] * 2;
    }
    cout << "Doubled: ";
    for (int i = 0; i < size; i++) {
        cout << doubled[i];
        if (i < size - 1) cout << " ";
    }
    cout << endl;

    // 3.2
    cout << "Pairs > 10 : ";
    for (int i = 0; i < size; i++) {
        if (data[i] % 2 == 0 && data[i] > 10) {
            cout << data[i] << " ";
        }
    }
    cout << endl;

    // 3.3
    cout << "Differences: ";
    for (int i = 0; i < size - 1; i++) {
        cout << (data[i + 1] - data[i]);
        if (i < size - 2) cout << " ";
    }
    cout << endl;

    return 0;
}
