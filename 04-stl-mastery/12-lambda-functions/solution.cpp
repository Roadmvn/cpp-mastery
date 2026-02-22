// ============================================================
// Lambdas — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

// ============================================================
// PARTIE 1 : Syntaxe de base et captures
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Syntaxe et captures ===" << endl;

    // 1. Lambda simple sans capture
    auto doubler = [](int x) { return x * 2; };
    cout << "doubler(5) = " << doubler(5) << endl;   // 10
    cout << "doubler(10) = " << doubler(10) << endl; // 20

    // 2. Capture par valeur
    int threshold = 5;
    auto isAbove = [threshold](int x) { return x > threshold; };
    cout << "3 > threshold(5) ? " << (isAbove(3) ? "oui" : "non") << endl;  // non
    cout << "7 > threshold(5) ? " << (isAbove(7) ? "oui" : "non") << endl;  // oui
    cout << "5 > threshold(5) ? " << (isAbove(5) ? "oui" : "non") << endl;  // non (strictement)

    // 3. Capture par reference
    int count = 0;
    auto increment = [&count]() { count++; };
    increment(); increment(); increment(); increment(); increment();
    cout << "count apres 5 appels : " << count << endl;  // 5

    // 4. mutable : modifier la copie locale sans toucher l'original
    int n = 10;
    auto addToLocalCopy = [n]() mutable {
        n++;  // modifie la COPIE locale, pas l'original
        return n;
    };
    cout << "addToLocalCopy() : " << addToLocalCopy() << endl;  // 11
    cout << "addToLocalCopy() : " << addToLocalCopy() << endl;  // 11 (chaque appel repart de la copie initiale? non, mutable preserve l'etat)
    // Note : en realite la copie est preservee entre appels
    // (la lambda a son propre etat)
    cout << "n original : " << n << endl;  // 10, inchange

    cout << endl;
}

// ============================================================
// PARTIE 2 : Lambdas avec algorithmes STL
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : Lambdas + algorithmes STL ===" << endl;

    vector<int> v = {3, 7, 1, 8, 2, 9, 4, 6, 5, 10};

    // 2. Trier en decroissant
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    cout << "Tri decroissant : ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 3. Premier element > 6
    auto it = find_if(v.begin(), v.end(), [](int x) { return x > 6; });
    if (it != v.end()) {
        cout << "Premier element > 6 : " << *it << endl;  // 10 (apres tri decroissant)
    }

    // 4. Compter les impairs
    int impairs = count_if(v.begin(), v.end(), [](int x) { return x % 2 != 0; });
    cout << "Nombre d'impairs : " << impairs << endl;  // 5

    // 5. Somme des carres
    long long sumSq = accumulate(v.begin(), v.end(), 0LL,
        [](long long acc, int x) { return acc + (long long)x * x; });
    cout << "Somme des carres : " << sumSq << endl;  // 1+4+9+16+25+36+49+64+81+100 = 385

    // 6. Supprimer les elements dans [4, 7]
    vector<int> v2 = {3, 7, 1, 8, 2, 9, 4, 6, 5, 10};
    v2.erase(
        remove_if(v2.begin(), v2.end(), [](int x) { return x >= 4 && x <= 7; }),
        v2.end()
    );
    cout << "Sans [4,7] : ";
    for (int x : v2) cout << x << " ";
    cout << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : std::function et lambdas avancees
// ============================================================

vector<int> applyAll(int x, vector<function<int(int)>>& ops) {
    vector<int> results;
    transform(ops.begin(), ops.end(), back_inserter(results),
              [x](const function<int(int)>& op) { return op(x); });
    return results;
}

void partie3() {
    cout << "=== PARTIE 3 : std::function et lambdas avancees ===" << endl;

    // 1. Vecteur d'operations
    vector<function<int(int)>> ops = {
        [](int x) { return x + 10; },
        [](int x) { return x * 3; },
        [](int x) { return x * x; }
    };

    cout << "Operations sur 4 : ";
    for (auto& op : ops) cout << op(4) << " ";  // 14 12 16
    cout << endl;

    // 2. applyAll
    auto results = applyAll(7, ops);
    cout << "applyAll(7) : ";
    for (int r : results) cout << r << " ";  // 17 21 49
    cout << endl;

    // 3. Lambda recursive pour factorielle
    function<long long(int)> factorial = [&](int n) -> long long {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    };

    cout << "0! = " << factorial(0) << endl;   // 1
    cout << "1! = " << factorial(1) << endl;   // 1
    cout << "5! = " << factorial(5) << endl;   // 120
    cout << "10! = " << factorial(10) << endl; // 3628800

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
