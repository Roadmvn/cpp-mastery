// =============================================================
// Solution : Trier un array
// =============================================================
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// =============================================================

#include <iostream>
#include <algorithm>
#include <cmath>
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

// 1.1
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 1.2
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }
}

// 1.3
void bubbleSortOptimized(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            cout << "(Optimise: arrete a la passe " << i + 1 << ")" << endl;
            break;
        }
    }
}

// ==========================================================
// PARTIE 3 : Applications
// ==========================================================

// 3.1
bool isSorted(const int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

// 3.2
double sortedMedian(int arr[], int size) {
    // Copie pour ne pas modifier l'original
    int copy[100];
    for (int i = 0; i < size; i++) copy[i] = arr[i];
    sort(copy, copy + size);

    if (size % 2 == 1) {
        return copy[size / 2];
    } else {
        return (copy[size / 2 - 1] + copy[size / 2]) / 2.0;
    }
}

// 3.3
int removeDuplicates(int arr[], int size) {
    sort(arr, arr + size);
    int unique = 1;
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[i - 1]) {
            arr[unique] = arr[i];
            unique++;
        }
    }
    return unique;
}

int main() {
    // Tests partie 1
    cout << "=== Bubble Sort ===" << endl;
    int data1[] = {64, 25, 12, 22, 11, 90, 45, 33};
    int size1 = 8;
    cout << "Original:  "; printArray(data1, size1);
    bubbleSort(data1, size1);
    cout << "Bubble:    "; printArray(data1, size1);

    int data2[] = {64, 25, 12, 22, 11, 90, 45, 33};
    cout << "\n=== Selection Sort ===" << endl;
    cout << "Original:  "; printArray(data2, size1);
    selectionSort(data2, size1);
    cout << "Selection: "; printArray(data2, size1);

    int data3[] = {1, 2, 3, 4, 5};
    cout << "\n=== Bubble Sort Optimise ===" << endl;
    cout << "Deja trie: "; printArray(data3, 5);
    bubbleSortOptimized(data3, 5);
    cout << "Resultat:  "; printArray(data3, 5);

    // Tests partie 2
    cout << "\n=== std::sort ===" << endl;

    // 2.1 : Croissant
    int data4[] = {64, 25, 12, 22, 11};
    sort(data4, data4 + 5);
    cout << "Croissant:  "; printArray(data4, 5);

    // 2.2 : Decroissant
    sort(data4, data4 + 5, [](int a, int b) { return a > b; });
    cout << "Decroissant: "; printArray(data4, 5);

    // 2.3 : Valeur absolue
    int data5[] = {-5, 3, -1, 4, -2};
    sort(data5, data5 + 5, [](int a, int b) { return abs(a) < abs(b); });
    cout << "Abs croiss:  "; printArray(data5, 5);

    // Tests partie 3
    cout << "\n=== Applications ===" << endl;
    int sorted[] = {1, 2, 3, 4, 5};
    int unsorted[] = {5, 3, 1, 4, 2};
    cout << "isSorted(sorted): " << (isSorted(sorted, 5) ? "true" : "false") << endl;
    cout << "isSorted(unsorted): " << (isSorted(unsorted, 5) ? "true" : "false") << endl;

    int medData[] = {7, 3, 1, 9, 5};
    cout << "Mediane (impair): " << sortedMedian(medData, 5) << endl;
    int medData2[] = {7, 3, 1, 9, 5, 2};
    cout << "Mediane (pair): " << sortedMedian(medData2, 6) << endl;

    int dupData[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int uniques = removeDuplicates(dupData, 10);
    cout << "Uniques: " << uniques << " -> ";
    printArray(dupData, uniques);

    return 0;
}
