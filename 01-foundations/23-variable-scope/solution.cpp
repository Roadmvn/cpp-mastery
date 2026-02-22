// ============================================================
// SOLUTION : Portee des Variables
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// Variable globale
int a = 10;

void test_scope() {
    int a = 20;
    cout << "Dans test_scope : a = " << a << endl;          // 20
    {
        int a = 30;
        cout << "Dans bloc interne : a = " << a << endl;    // 30
    }
    cout << "Retour dans test_scope : a = " << a << endl;   // 20
}

// PARTIE 2 : Variable static
int generate_id() {
    static int id = 0;
    id++;
    return id;
}

// PARTIE 3 : Scope et boucles
double average(int arr[], int size) {
    static int call_count = 0;
    call_count++;

    double somme = 0;  // Locale, reinitialisee a chaque appel
    for (int i = 0; i < size; i++) {
        somme += arr[i];
    }

    cout << "  (appel #" << call_count << " de average())" << endl;
    return somme / size;
}

int main() {
    // PARTIE 1
    cout << "--- Partie 1 ---" << endl;
    cout << "Avant test_scope : a = " << a << endl;  // 10
    test_scope();
    // Dans test_scope : a = 20
    // Dans bloc interne : a = 30
    // Retour dans test_scope : a = 20
    cout << "Apres test_scope : a = " << a << endl;  // 10 (globale inchangee)

    // PARTIE 2
    cout << "\n--- Partie 2 ---" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "ID : " << generate_id() << endl;
    }
    // ID : 1, 2, 3, 4, 5

    // PARTIE 3
    cout << "\n--- Partie 3 ---" << endl;
    int arr1[] = {10, 20, 30};
    int arr2[] = {5, 15, 25, 35};
    cout << "Moyenne 1 : " << average(arr1, 3) << endl;  // 20
    cout << "Moyenne 2 : " << average(arr2, 4) << endl;  // 20
    cout << "Moyenne 3 : " << average(arr1, 3) << endl;  // 20

    return 0;
}
