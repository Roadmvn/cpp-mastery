// =============================================================
// Exercice : Passer un array a une fonction
// =============================================================
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// =============================================================

#include <iostream>
using namespace std;

// ==========================================================
// PARTIE 1 : Fonctions de base sur arrays
// ==========================================================

// TODO 1.1 : Ecris une fonction 'printArray' qui prend un array d'entiers
//            et sa taille, et affiche les elements separes par des espaces
//            Utilise 'const' pour proteger l'array en lecture seule


// TODO 1.2 : Ecris une fonction 'sumArray' qui retourne la somme
//            de tous les elements d'un array d'entiers (const)


// TODO 1.3 : Ecris une fonction 'findMax' qui retourne la valeur maximum
//            d'un array d'entiers (const)


// ==========================================================
// PARTIE 2 : Fonctions qui modifient l'array
// ==========================================================

// TODO 2.1 : Ecris une fonction 'addToAll' qui ajoute une valeur donnee
//            a chaque element de l'array
//            Signature: void addToAll(int arr[], int size, int value)


// TODO 2.2 : Ecris une fonction 'reverseArray' qui inverse l'array en place
//            (le premier element devient le dernier, etc.)
//            Signature: void reverseArray(int arr[], int size)


// TODO 2.3 : Ecris une fonction 'clampArray' qui limite chaque element
//            entre une valeur min et max
//            Signature: void clampArray(int arr[], int size, int minVal, int maxVal)


// ==========================================================
// PARTIE 3 : Fonctions avancees
// ==========================================================

// TODO 3.1 : Ecris une fonction 'copyArray' qui copie les elements d'un array
//            source vers un array destination
//            Signature: void copyArray(const int src[], int dst[], int size)


// TODO 3.2 : Ecris une fonction 'dotProduct' qui calcule le produit scalaire
//            de deux arrays de meme taille : sum(a[i] * b[i])
//            Signature: int dotProduct(const int a[], const int b[], int size)


// TODO 3.3 : Ecris une fonction 'countIf' qui compte les elements
//            superieurs a un seuil donne
//            Signature: int countIf(const int arr[], int size, int threshold)


int main() {
    int data[] = {15, 42, 8, 23, 56, 11, 34, 67, 3, 29};
    int size = sizeof(data) / sizeof(data[0]);

    // Teste tes fonctions ici :

    // 1.1 : printArray(data, size);
    // 1.2 : cout << "Somme: " << sumArray(data, size) << endl;
    // 1.3 : cout << "Max: " << findMax(data, size) << endl;

    // 2.1 : addToAll(data, size, 10); printArray(data, size);
    // 2.2 : reverseArray(data, size); printArray(data, size);
    // 2.3 : clampArray(data, size, 10, 50); printArray(data, size);

    // 3.1 :
    // int copie[10];
    // copyArray(data, copie, size);
    // printArray(copie, size);

    // 3.2 :
    // int a[] = {1, 2, 3};
    // int b[] = {4, 5, 6};
    // cout << "Produit scalaire: " << dotProduct(a, b, 3) << endl; // 32

    // 3.3 : cout << "Nb > 30: " << countIf(data, size, 30) << endl;

    return 0;
}
