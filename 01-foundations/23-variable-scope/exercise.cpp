// ============================================================
// EXERCICE : Portee des Variables
// Fichier : exercise.cpp
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// --------------------------------------------------------
// PARTIE 1 : Comprendre la portee
// --------------------------------------------------------
// TODO : Sans executer le code, predit ce que chaque cout affiche.
// Puis execute pour verifier.

int a = 10;  // Globale

void test_scope() {
    int a = 20;  // Locale (shadow)
    cout << "Dans test_scope : a = " << a << endl;
    {
        int a = 30;  // Encore plus locale
        cout << "Dans bloc interne : a = " << a << endl;
    }
    cout << "Retour dans test_scope : a = " << a << endl;
}

// Ecris tes predictions en commentaire :
// test_scope() affichera :
//   Dans test_scope : a = ???
//   Dans bloc interne : a = ???
//   Retour dans test_scope : a = ???
// Apres test_scope, a global = ???


// --------------------------------------------------------
// PARTIE 2 : Variable static
// --------------------------------------------------------
// TODO : Cree une fonction generate_id() qui retourne un
// identifiant unique a chaque appel (1, 2, 3, 4...).
// Utilise une variable static.
//
// int generate_id();

// Ecris ta fonction ici :



// --------------------------------------------------------
// PARTIE 3 : Scope et boucles
// --------------------------------------------------------
// TODO : Cree une fonction qui calcule la moyenne d'un tableau.
// La variable somme doit etre locale a la fonction.
// Utilise une variable static pour compter combien de fois
// la fonction a ete appelee au total.
//
// double average(int arr[], int size);

// Ecris ta fonction ici :



int main() {
    // PARTIE 1
    cout << "--- Partie 1 ---" << endl;
    cout << "Avant test_scope : a = " << a << endl;
    test_scope();
    cout << "Apres test_scope : a = " << a << endl;

    // PARTIE 2
    // cout << "\n--- Partie 2 ---" << endl;
    // for (int i = 0; i < 5; i++) {
    //     cout << "ID : " << generate_id() << endl;
    // }

    // PARTIE 3
    // cout << "\n--- Partie 3 ---" << endl;
    // int arr1[] = {10, 20, 30};
    // int arr2[] = {5, 15, 25, 35};
    // cout << "Moyenne 1 : " << average(arr1, 3) << endl;
    // cout << "Moyenne 2 : " << average(arr2, 4) << endl;
    // cout << "Moyenne 3 : " << average(arr1, 3) << endl;

    return 0;
}
