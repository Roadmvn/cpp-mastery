// =============================================================
// Solution : Recherche dans un array
// =============================================================
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// =============================================================

#include <iostream>
#include <cmath>
using namespace std;

// ==========================================================
// PARTIE 1 : Recherche lineaire
// ==========================================================

// 1.1
int linearSearch(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// 1.2
int countOccurrences(const int arr[], int size, int target) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) count++;
    }
    return count;
}

// 1.3
int findLastIndex(const int arr[], int size, int target) {
    int lastIdx = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) lastIdx = i;
    }
    return lastIdx;
}

// ==========================================================
// PARTIE 2 : Recherche binaire
// ==========================================================

// 2.1
int binarySearch(const int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// 2.2
int lowerBound(const int arr[], int size, int target) {
    int low = 0, high = size;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target) low = mid + 1;
        else high = mid;
    }
    return low;
}

// 2.3
int binarySearchCount(const int arr[], int size, int target) {
    int low = 0, high = size - 1;
    int comparisons = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        comparisons++;
        if (arr[mid] == target) return comparisons;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return comparisons;
}

// ==========================================================
// PARTIE 3 : Comparaison et application
// ==========================================================

// 3.1
void findMinMax(const int arr[], int size, int& minVal, int& maxVal) {
    minVal = arr[0];
    maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}

// 3.2
int findClosest(const int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return arr[mid];
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    // low est l'index du premier element > target
    // high est l'index du dernier element < target
    if (low >= size) return arr[high];
    if (high < 0) return arr[low];
    return (abs(arr[low] - target) <= abs(arr[high] - target)) ? arr[low] : arr[high];
}

// 3.3
bool isPresent(const int arr[], int size, int target) {
    return binarySearch(arr, size, target) != -1;
}

int main() {
    int data[] = {15, 42, 8, 23, 42, 11, 34, 42, 3, 29};
    int dataSize = 10;

    int sorted[] = {3, 8, 11, 15, 23, 29, 34, 42, 56, 78};
    int sortedSize = 10;

    // Tests partie 1
    cout << "=== Recherche lineaire ===" << endl;
    cout << "linearSearch(42): " << linearSearch(data, dataSize, 42) << endl;
    cout << "countOccurrences(42): " << countOccurrences(data, dataSize, 42) << endl;
    cout << "findLastIndex(42): " << findLastIndex(data, dataSize, 42) << endl;
    cout << "linearSearch(99): " << linearSearch(data, dataSize, 99) << endl;

    // Tests partie 2
    cout << "\n=== Recherche binaire ===" << endl;
    cout << "binarySearch(23): " << binarySearch(sorted, sortedSize, 23) << endl;
    cout << "binarySearch(99): " << binarySearch(sorted, sortedSize, 99) << endl;
    cout << "lowerBound(20): " << lowerBound(sorted, sortedSize, 20) << endl;
    cout << "lowerBound(42): " << lowerBound(sorted, sortedSize, 42) << endl;
    cout << "binarySearchCount(42): " << binarySearchCount(sorted, sortedSize, 42)
         << " comparaisons" << endl;
    cout << "binarySearchCount(99): " << binarySearchCount(sorted, sortedSize, 99)
         << " comparaisons" << endl;

    // Tests partie 3
    cout << "\n=== Applications ===" << endl;
    int minVal, maxVal;
    findMinMax(data, dataSize, minVal, maxVal);
    cout << "Min: " << minVal << " Max: " << maxVal << endl;

    cout << "findClosest(40): " << findClosest(sorted, sortedSize, 40) << endl;
    cout << "findClosest(50): " << findClosest(sorted, sortedSize, 50) << endl;
    cout << "isPresent(23): " << (isPresent(sorted, sortedSize, 23) ? "true" : "false") << endl;
    cout << "isPresent(99): " << (isPresent(sorted, sortedSize, 99) ? "true" : "false") << endl;

    return 0;
}
