// ============================================================
// SOLUTION : Fonctions Surchargees
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// PARTIE 1 : Surcharge par type
void display(int value) {
    cout << "Entier : " << value << endl;
}

void display(double value) {
    cout << "Decimal : " << value << endl;
}

void display(string value) {
    cout << "Texte : " << value << endl;
}

// PARTIE 2 : Surcharge par nombre de parametres
double area(double side) {
    return side * side;
}

double area(double width, double height) {
    return width * height;
}

double area(double base, double height, bool is_triangle) {
    if (is_triangle) {
        return base * height / 2.0;
    }
    return base * height;
}

// PARTIE 3 : Surcharge utile
int clamp(int value, int min_val, int max_val) {
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

double clamp(double value, double min_val, double max_val) {
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

int main() {
    // PARTIE 1
    cout << "--- Display ---" << endl;
    display(42);
    display(3.14);
    display("Hello");

    // PARTIE 2
    cout << "\n--- Area ---" << endl;
    cout << "Carre (5) : " << area(5.0) << endl;
    cout << "Rectangle (4x6) : " << area(4.0, 6.0) << endl;
    cout << "Triangle (10x5) : " << area(10.0, 5.0, true) << endl;
    cout << "Rectangle (10x5) : " << area(10.0, 5.0, false) << endl;

    // PARTIE 3
    cout << "\n--- Clamp ---" << endl;
    cout << "clamp(15, 0, 10) = " << clamp(15, 0, 10) << endl;
    cout << "clamp(-5, 0, 10) = " << clamp(-5, 0, 10) << endl;
    cout << "clamp(5, 0, 10) = " << clamp(5, 0, 10) << endl;
    cout << "clamp(3.7, 0.0, 1.0) = " << clamp(3.7, 0.0, 1.0) << endl;
    cout << "clamp(0.5, 0.0, 1.0) = " << clamp(0.5, 0.0, 1.0) << endl;

    return 0;
}
