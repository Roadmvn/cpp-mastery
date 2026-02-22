// ============================================================
// Chapitre 13 : Memoire Dynamique - Solutions
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
using namespace std;

// --- PARTIE 1 ---

void partie1() {
    cout << "=== PARTIE 1 : new / delete basiques ===" << endl;

    int* entier = new int(42);
    double* decimal = new double(3.14);

    cout << "entier  : valeur = " << *entier << ", adresse = " << entier << endl;
    cout << "decimal : valeur = " << *decimal << ", adresse = " << decimal << endl;

    delete entier;
    entier = nullptr;

    delete decimal;
    decimal = nullptr;

    cout << "Memoire liberee, pointeurs mis a nullptr" << endl;
    cout << endl;
}

// --- PARTIE 2 ---

void partie2() {
    cout << "=== PARTIE 2 : Tableau dynamique ===" << endl;

    int n = 5;
    int* arr = new int[n];

    // Remplir
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
    }

    // Afficher
    cout << "Tableau : ";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << endl;

    // Somme
    int somme = 0;
    for (int i = 0; i < n; i++) {
        somme += arr[i];
    }
    cout << "Somme : " << somme << endl;

    // Liberation
    delete[] arr;
    arr = nullptr;

    cout << endl;
}

// --- PARTIE 3 ---

void partie3() {
    cout << "=== PARTIE 3 : Copie profonde ===" << endl;

    int* original = new int[4]{10, 20, 30, 40};
    int* copie = new int[4];

    // Copie profonde (element par element)
    for (int i = 0; i < 4; i++) {
        copie[i] = original[i];
    }

    // Modifier la copie
    copie[0] = 999;

    // Afficher original
    cout << "Original : ";
    for (int i = 0; i < 4; i++) {
        cout << original[i] << " ";
    }
    cout << endl;

    // Afficher copie
    cout << "Copie    : ";
    for (int i = 0; i < 4; i++) {
        cout << copie[i] << " ";
    }
    cout << endl;

    cout << "Original intact malgre la modification de la copie !" << endl;

    delete[] original;
    original = nullptr;

    delete[] copie;
    copie = nullptr;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
