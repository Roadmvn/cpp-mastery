// ============================================================
// SOLUTION : Boucles For
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Table de multiplication
    // --------------------------------------------------------
    int n;
    cout << "Entre un nombre : ";
    cin >> n;

    for (int i = 1; i <= 12; i++) {
        cout << n << " x " << i << " = " << (n * i) << endl;
    }

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 2 : FizzBuzz
    // --------------------------------------------------------
    for (int i = 1; i <= 50; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            cout << "FizzBuzz";
        } else if (i % 3 == 0) {
            cout << "Fizz";
        } else if (i % 5 == 0) {
            cout << "Buzz";
        } else {
            cout << i;
        }
        cout << " ";
    }
    cout << endl;

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 3 : Moyenne de prix
    // --------------------------------------------------------
    double prices[] = {152.30, 148.75, 155.20, 149.90, 157.45, 153.60, 150.15};

    double somme = 0;
    double min_price = prices[0];
    double max_price = prices[0];

    for (double p : prices) {
        somme += p;
        if (p < min_price) min_price = p;
        if (p > max_price) max_price = p;
    }

    int count = sizeof(prices) / sizeof(prices[0]);
    double moyenne = somme / count;

    cout << "Nombre de prix : " << count << endl;
    cout << "Moyenne : $" << moyenne << endl;
    cout << "Min     : $" << min_price << endl;
    cout << "Max     : $" << max_price << endl;
    cout << "Range   : $" << (max_price - min_price) << endl;

    return 0;
}
