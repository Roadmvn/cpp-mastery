// ============================================================
// SOLUTION : Fonctions
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// Prototypes
int max_of_three(int a, int b, int c);
bool is_even(int n);
void print_separator(int length, char c);
void greet(string name, string greeting = "Bonjour");
double celsius_to_fahrenheit(double celsius);
double fahrenheit_to_celsius(double fahrenheit);

int main() {
    // PARTIE 1
    cout << "Max de 10, 25, 17 : " << max_of_three(10, 25, 17) << endl;
    cout << "Max de -5, -2, -8 : " << max_of_three(-5, -2, -8) << endl;
    cout << "42 est pair ? " << (is_even(42) ? "oui" : "non") << endl;
    cout << "7 est pair ? " << (is_even(7) ? "oui" : "non") << endl;
    print_separator(30, '-');

    // PARTIE 2
    greet("Alex");
    greet("Alex", "Salut");

    print_separator(30, '=');

    // PARTIE 3
    cout << "0C   = " << celsius_to_fahrenheit(0) << "F" << endl;
    cout << "100C = " << celsius_to_fahrenheit(100) << "F" << endl;
    cout << "32F  = " << fahrenheit_to_celsius(32) << "C" << endl;
    cout << "72F  = " << fahrenheit_to_celsius(72) << "C" << endl;

    return 0;
}

// Definitions

int max_of_three(int a, int b, int c) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

bool is_even(int n) {
    return n % 2 == 0;
}

void print_separator(int length, char c) {
    for (int i = 0; i < length; i++) {
        cout << c;
    }
    cout << endl;
}

void greet(string name, string greeting) {
    cout << greeting << ", " << name << " !" << endl;
}

double celsius_to_fahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

double fahrenheit_to_celsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}
