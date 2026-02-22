// =============================================================
// Exercice : Trier un array
// =============================================================
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// =============================================================

#include <iostream>
#include <algorithm>
using namespace std;

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << " ";
    }
    cout << endl;
}

// ==========================================================
// PARTIE 1 : Algorithmes de tri manuels
// ==========================================================

// TODO 1.1 : Implemente bubbleSort en ordre croissant
//            Signature: void bubbleSort(int arr[], int size)


// TODO 1.2 : Implemente selectionSort en ordre croissant
//            Signature: void selectionSort(int arr[], int size)


// TODO 1.3 : Implemente une version optimisee de bubbleSort qui s'arrete
//            si aucun echange n'a ete fait pendant une passe (deja trie)
//            Signature: void bubbleSortOptimized(int arr[], int size)


// ==========================================================
// PARTIE 2 : std::sort avec comparateurs
// ==========================================================

// TODO 2.1 : Utilise std::sort pour trier un array en ordre croissant
//            (utilise la version par defaut)


// TODO 2.2 : Utilise std::sort pour trier un array en ordre decroissant
//            (utilise un comparateur lambda)


// TODO 2.3 : Utilise std::sort pour trier un array de valeurs absolues
//            croissantes : [-5, 3, -1, 4, -2] -> [-1, -2, 3, 4, -5]
//            (trie par valeur absolue croissante)


// ==========================================================
// PARTIE 3 : Applications
// ==========================================================

// TODO 3.1 : Ecris une fonction 'isSorted' qui retourne true si l'array
//            est trie en ordre croissant
//            Signature: bool isSorted(const int arr[], int size)


// TODO 3.2 : Ecris une fonction 'sortedMedian' qui trie une copie de l'array
//            et retourne la mediane (element du milieu)
//            Signature: double sortedMedian(int arr[], int size)
//            Note: pour un nombre pair d'elements, moyenne des 2 du milieu


// TODO 3.3 : Ecris une fonction 'removeDuplicates' qui trie l'array puis
//            retourne le nombre d'elements uniques (deplace les uniques au debut)
//            Signature: int removeDuplicates(int arr[], int size)


int main() {
    int data1[] = {64, 25, 12, 22, 11, 90, 45, 33};
    int size1 = 8;

    // Decommente et teste :

    // cout << "Original: "; printArray(data1, size1);
    // bubbleSort(data1, size1);
    // cout << "Bubble:   "; printArray(data1, size1);

    // int data2[] = {64, 25, 12, 22, 11, 90, 45, 33};
    // selectionSort(data2, size1);
    // cout << "Selection: "; printArray(data2, size1);

    // int data3[] = {1, 2, 3, 4, 5};
    // bubbleSortOptimized(data3, 5); // Doit s'arreter vite

    // 2.1, 2.2, 2.3 : utilise directement std::sort

    // cout << "isSorted: " << isSorted(data1, size1) << endl;

    // int medData[] = {7, 3, 1, 9, 5};
    // cout << "Mediane: " << sortedMedian(medData, 5) << endl;

    // int dupData[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    // int uniques = removeDuplicates(dupData, 10);
    // cout << "Uniques: " << uniques << " -> ";
    // printArray(dupData, uniques);

    return 0;
}
