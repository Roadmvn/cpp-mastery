// =============================================================
// Exercice : Recherche dans un array
// =============================================================
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// =============================================================

#include <iostream>
using namespace std;

// ==========================================================
// PARTIE 1 : Recherche lineaire
// ==========================================================

// TODO 1.1 : Implemente linearSearch qui retourne l'index de 'target'
//            dans l'array, ou -1 si non trouve
//            Signature: int linearSearch(const int arr[], int size, int target)


// TODO 1.2 : Implemente countOccurrences qui retourne le nombre de fois
//            que 'target' apparait dans l'array
//            Signature: int countOccurrences(const int arr[], int size, int target)


// TODO 1.3 : Implemente findLastIndex qui retourne l'index de la DERNIERE
//            occurrence de 'target', ou -1 si non trouve
//            Signature: int findLastIndex(const int arr[], int size, int target)


// ==========================================================
// PARTIE 2 : Recherche binaire
// ==========================================================

// TODO 2.1 : Implemente binarySearch sur un array TRIE
//            Retourne l'index de 'target' ou -1 si non trouve
//            Signature: int binarySearch(const int arr[], int size, int target)


// TODO 2.2 : Implemente lowerBound qui retourne l'index du premier element
//            >= target dans un array trie (ou size si tous sont < target)
//            Signature: int lowerBound(const int arr[], int size, int target)


// TODO 2.3 : Implemente binarySearchCount qui retourne le nombre de
//            comparaisons effectuees pour trouver (ou ne pas trouver) target
//            Signature: int binarySearchCount(const int arr[], int size, int target)


// ==========================================================
// PARTIE 3 : Comparaison et application
// ==========================================================

// TODO 3.1 : Implemente findMinMax qui trouve a la fois le minimum et le
//            maximum en un seul parcours. Utilise des references pour retourner
//            les deux valeurs.
//            Signature: void findMinMax(const int arr[], int size, int& min, int& max)


// TODO 3.2 : Implemente findClosest qui retourne l'element de l'array trie
//            le plus proche de 'target' (pas forcement egal)
//            Signature: int findClosest(const int arr[], int size, int target)


// TODO 3.3 : Implemente isPresent qui retourne true si 'target' est dans l'array
//            Utilise binarySearch en interne
//            Signature: bool isPresent(const int arr[], int size, int target)


int main() {
    // Array non trie pour recherche lineaire
    int data[] = {15, 42, 8, 23, 42, 11, 34, 42, 3, 29};
    int dataSize = 10;

    // Array trie pour recherche binaire
    int sorted[] = {3, 8, 11, 15, 23, 29, 34, 42, 56, 78};
    int sortedSize = 10;

    // Decommente et teste :

    // cout << "linearSearch(42): " << linearSearch(data, dataSize, 42) << endl;
    // cout << "countOccurrences(42): " << countOccurrences(data, dataSize, 42) << endl;
    // cout << "findLastIndex(42): " << findLastIndex(data, dataSize, 42) << endl;

    // cout << "binarySearch(23): " << binarySearch(sorted, sortedSize, 23) << endl;
    // cout << "lowerBound(20): " << lowerBound(sorted, sortedSize, 20) << endl;
    // cout << "binarySearchCount(42): " << binarySearchCount(sorted, sortedSize, 42) << endl;

    // int min, max;
    // findMinMax(data, dataSize, min, max);
    // cout << "Min: " << min << " Max: " << max << endl;

    // cout << "findClosest(40): " << findClosest(sorted, sortedSize, 40) << endl;
    // cout << "isPresent(23): " << isPresent(sorted, sortedSize, 23) << endl;

    return 0;
}
