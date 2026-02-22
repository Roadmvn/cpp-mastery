// ============================================================
// Chapitre 14 : Recursion - Challenge HFT
// ============================================================
// DEFI : Binary Search recursif + Fibonacci avec memoization
//
// Binary search est l'algo le plus utilise en finance pour
// chercher dans des donnees triees (prix, timestamps...).
// La memoization transforme un algo O(2^n) en O(n).
//
// Compile : g++ -std=c++17 -Wall -Wextra -O2 -o challenge challenge.cpp
// ============================================================

#include <iostream>
#include <chrono>
using namespace std;

// ============================================================
// PARTIE 1 : Binary Search recursif
// ============================================================

int binarySearch(const int arr[], int left, int right, int target) {
    if (left > right) return -1;  // Pas trouve

    int mid = left + (right - left) / 2;  // Evite overflow

    if (arr[mid] == target) return mid;
    if (arr[mid] > target) return binarySearch(arr, left, mid - 1, target);
    return binarySearch(arr, mid + 1, right, target);
}

/*
    Binary Search recursif sur [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    Cherche 70 :

    Etape 1 : left=0, right=9, mid=4  arr[4]=50 < 70  cherche a droite
    ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
    │ 10 │ 20 │ 30 │ 40 │ 50 │ 60 │ 70 │ 80 │ 90 │100│
    └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
                          mid      ─── cherche ici ──

    Etape 2 : left=5, right=9, mid=7  arr[7]=80 > 70  cherche a gauche
    ┌────┬────┬────┬────┬────┐
    │ 60 │ 70 │ 80 │ 90 │100│
    └────┴────┴────┴────┴────┘
              mid 
         ici

    Etape 3 : left=5, right=6, mid=5  arr[5]=60 < 70  cherche a droite

    Etape 4 : left=6, right=6, mid=6  arr[6]=70 == 70  TROUVE !
*/

// ============================================================
// PARTIE 2 : Fibonacci naif (lent) vs memoization (rapide)
// ============================================================

// Fibonacci naif : O(2^n) — exponentiellement lent
long long fibNaif(int n) {
    if (n <= 1) return n;
    return fibNaif(n - 1) + fibNaif(n - 2);
}

/*
    Arbre d'appels de fibNaif(5) — enorme redondance :

                        fib(5)
                       /      \
                    fib(4)    fib(3)
                   /    \     /    \
                fib(3) fib(2) fib(2) fib(1)
               /    \   / \    / \
            fib(2) fib(1) ... ...
            / \
         fib(1) fib(0)

    fib(3) calcule 2 fois, fib(2) calcule 3 fois !
*/

// Fibonacci avec memoization : O(n)
long long memo[100] = {};
bool computed[100] = {};

long long fibMemo(int n) {
    if (n <= 1) return n;
    if (computed[n]) return memo[n];  // Deja calcule ? Retourne le cache

    memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
    computed[n] = true;
    return memo[n];
}

/*
    Avec memoization, chaque fib(k) est calcule UNE SEULE FOIS :

    fib(5)  calcule fib(4), fib(3)
    fib(4)  calcule fib(3), fib(2)
    fib(3)  CACHE ! (deja calcule par fib(4))
    fib(2)  CACHE !

    Total : 5 calculs au lieu de 15
*/

int main() {
    cout << "=== CHALLENGE HFT : Binary Search + Memoization ===" << endl << endl;

    // --- Binary Search ---
    cout << "--- Binary Search recursif ---" << endl;
    int prices[] = {100, 105, 110, 115, 120, 125, 130, 135, 140, 145,
                    150, 155, 160, 165, 170, 175, 180, 185, 190, 195};
    int size = 20;

    cout << "Prix tries : ";
    for (int i = 0; i < size; i++) cout << prices[i] << " ";
    cout << endl;

    int targets[] = {130, 100, 195, 142, 170};
    for (int t : targets) {
        int idx = binarySearch(prices, 0, size - 1, t);
        if (idx >= 0)
            cout << "Prix " << t << " trouve a l'index " << idx << endl;
        else
            cout << "Prix " << t << " non trouve" << endl;
    }
    cout << endl;

    // Benchmark : binary search sur gros tableau
    const int BIG = 100000;
    int* bigArr = new int[BIG];
    for (int i = 0; i < BIG; i++) bigArr[i] = i * 2;

    auto start = chrono::high_resolution_clock::now();
    int found = 0;
    for (int i = 0; i < 100000; i++) {
        if (binarySearch(bigArr, 0, BIG - 1, i * 2) >= 0) found++;
    }
    auto end = chrono::high_resolution_clock::now();
    auto timeBS = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Binary search x100000 sur tableau de " << BIG << " : "
         << timeBS << " us (" << found << " trouves)" << endl << endl;

    delete[] bigArr;

    // --- Fibonacci ---
    cout << "--- Fibonacci : naif vs memoization ---" << endl;

    // Fibonacci naif (petit n seulement, sinon trop lent)
    cout << "Fibonacci naif :" << endl;
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i <= 10; i++) {
        cout << "  fib(" << i << ") = " << fibNaif(i) << endl;
    }
    end = chrono::high_resolution_clock::now();

    // Benchmark naif sur n=35
    start = chrono::high_resolution_clock::now();
    long long result35 = fibNaif(35);
    end = chrono::high_resolution_clock::now();
    auto timeNaif = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "  fib(35) = " << result35 << " en " << timeNaif << " us" << endl;

    cout << endl;

    // Fibonacci memoization
    cout << "Fibonacci memoization :" << endl;
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i <= 10; i++) {
        cout << "  fib(" << i << ") = " << fibMemo(i) << endl;
    }

    long long result90 = fibMemo(90);
    end = chrono::high_resolution_clock::now();
    auto timeMemo = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "  fib(90) = " << result90 << " en " << timeMemo << " us" << endl;

    cout << endl;
    cout << "--- Comparaison ---" << endl;
    cout << "Naif   fib(35)  : " << timeNaif << " us" << endl;
    cout << "Memo   fib(90)  : " << timeMemo << " us" << endl;
    if (timeMemo > 0) {
        cout << "Speedup : x" << (double)timeNaif / timeMemo
             << " (et memo va jusqu'a fib(90) !)" << endl;
    }

    cout << endl;
    cout << "--- Lecons HFT ---" << endl;
    cout << "1. Binary search O(log n) : essentiel pour chercher dans les order books" << endl;
    cout << "2. Memoization : cache les resultats pour eviter les calculs redondants" << endl;
    cout << "3. En production : utilise iteratif + lookup table pour zero overhead" << endl;

    return 0;
}
