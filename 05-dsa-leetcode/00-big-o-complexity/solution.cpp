// ============================================
// Big O Complexity - Solutions et Explications
// ============================================
// Compile : g++ -std=c++17 solution.cpp -o solution

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// -----------------------------------------------
// EXERCICE 1 : O(1) - Constant
// Explication : On accede a 2 elements par index.
// Peu importe la taille du tableau, c'est 2 operations.
// -----------------------------------------------
int exercise1(vector<int>& arr) {
    return arr[0] + arr[arr.size() - 1];
}

// -----------------------------------------------
// EXERCICE 2 : O(n) - Lineaire
// Explication : Dans le pire cas, on parcourt TOUT
// le tableau (element pas trouve ou en derniere position).
// -----------------------------------------------
int exercise2(vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// -----------------------------------------------
// EXERCICE 3 : O(n²) - Quadratique
// Explication : Deux boucles imbriquees sur le meme
// tableau. Pour chaque element, on compare avec tous
// les suivants. n*(n-1)/2 comparaisons = O(n²).
// -----------------------------------------------
bool exercise3(vector<int>& arr) {
    for (int i = 0; i < (int)arr.size(); i++) {
        for (int j = i + 1; j < (int)arr.size(); j++) {
            if (arr[i] == arr[j]) return true;
        }
    }
    return false;
}

// -----------------------------------------------
// EXERCICE 4 : O(log n) - Logarithmique
// Explication : On divise n par 2 a chaque iteration.
// Pour n=1024, on fait 10 iterations (2^10 = 1024).
// -----------------------------------------------
int exercise4(int n) {
    int count = 0;
    while (n > 1) {
        n /= 2;
        count++;
    }
    return count;
}

// -----------------------------------------------
// EXERCICE 5 : O(n log n) - Linearithmique
// Explication : std::sort utilise IntroSort (hybride
// quicksort/heapsort) qui garantit O(n log n).
// -----------------------------------------------
void exercise5(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}

// -----------------------------------------------
// EXERCICE 6 : O(2^n) - Exponentielle
// Explication : Chaque appel genere 2 appels recursifs.
// L'arbre d'appels double a chaque niveau.
//
//                 fib(5)
//               /        \
//          fib(4)        fib(3)
//         /     \        /    \
//      fib(3)  fib(2) fib(2) fib(1)
//      /   \
//   fib(2) fib(1)
//
// Beaucoup de calculs redondants !
// -----------------------------------------------
int exercise6(int n) {
    if (n <= 1) return n;
    return exercise6(n - 1) + exercise6(n - 2);
}

// -----------------------------------------------
// EXERCICE 7 : O(n³) - Cubique
// Explication : TROIS boucles imbriquees, chacune
// parcourant n elements. n * n * n = n³ operations.
// -----------------------------------------------
void exercise7(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                // operation O(1)
            }
        }
    }
}

// -----------------------------------------------
// EXERCICE 8 : O(log n) - Logarithmique
// Explication : C'est un binary search classique.
// On divise l'espace de recherche par 2 a chaque
// iteration. Pour n=1000000, ~20 iterations max.
// -----------------------------------------------
bool exercise8(vector<int>& sortedArr, int target) {
    int lo = 0, hi = sortedArr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (sortedArr[mid] == target) return true;
        else if (sortedArr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}

// -----------------------------------------------
// EXERCICE 9 : O(n) - Lineaire
// Explication : Deux boucles SEPAREES (pas imbriquees).
// O(n) + O(n) = O(2n) = O(n).
// On ignore les constantes en Big O !
// -----------------------------------------------
int exercise9(vector<int>& arr) {
    int sum = 0;
    for (int x : arr) sum += x;       // O(n)

    int maxVal = arr[0];
    for (int x : arr) maxVal = max(maxVal, x);  // O(n)

    return sum + maxVal;               // O(n) + O(n) = O(n)
}

// -----------------------------------------------
// EXERCICE 10 : O(n) - Lineaire
// Explication : Une boucle pour construire la hash map
// (chaque insertion est O(1) en moyenne), puis une
// boucle pour parcourir la map.
// O(n) + O(n) = O(n).
// -----------------------------------------------
bool exercise10(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;      // O(n) * O(1) = O(n)

    for (auto& [key, val] : freq) {   // O(n) max
        if (val > 1) return true;
    }
    return false;
}

int main() {
    cout << "========================================" << endl;
    cout << "  Big O - Solutions et Explications" << endl;
    cout << "========================================" << endl;
    cout << endl;

    cout << "Exercice 1  : O(1)       - Acces par index (constant)" << endl;
    cout << "Exercice 2  : O(n)       - Recherche lineaire" << endl;
    cout << "Exercice 3  : O(n^2)     - Double boucle imbriquee" << endl;
    cout << "Exercice 4  : O(log n)   - Division par 2 repetee" << endl;
    cout << "Exercice 5  : O(n log n) - std::sort (IntroSort)" << endl;
    cout << "Exercice 6  : O(2^n)     - Fibonacci recursif naif" << endl;
    cout << "Exercice 7  : O(n^3)     - Triple boucle imbriquee" << endl;
    cout << "Exercice 8  : O(log n)   - Binary search" << endl;
    cout << "Exercice 9  : O(n)       - Deux boucles separees (pas imbriquees)" << endl;
    cout << "Exercice 10 : O(n)       - Hash map + parcours" << endl;

    cout << endl;
    cout << "========================================" << endl;
    cout << "  Resume des regles" << endl;
    cout << "========================================" << endl;
    cout << "- Boucle simple sur n       -> O(n)" << endl;
    cout << "- Deux boucles imbriquees   -> O(n^2)" << endl;
    cout << "- Trois boucles imbriquees  -> O(n^3)" << endl;
    cout << "- Diviser par 2 a chaque pas -> O(log n)" << endl;
    cout << "- Tri standard              -> O(n log n)" << endl;
    cout << "- 2 appels recursifs        -> O(2^n)" << endl;
    cout << "- Boucles separees          -> O(max des deux)" << endl;
    cout << "- On ignore les constantes  -> O(2n) = O(n)" << endl;

    return 0;
}
