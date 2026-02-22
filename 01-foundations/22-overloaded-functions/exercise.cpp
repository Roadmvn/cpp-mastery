// ============================================================
// EXERCICE : Fonctions Surchargees
// Fichier : exercise.cpp
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// --------------------------------------------------------
// PARTIE 1 : Surcharge par type
// --------------------------------------------------------
// TODO : Cree 3 versions surchargees de la fonction display() :
//
// void display(int value)       -> "Entier : [value]"
// void display(double value)    -> "Decimal : [value]"
// void display(string value)    -> "Texte : [value]"

// Ecris tes fonctions ici :



// --------------------------------------------------------
// PARTIE 2 : Surcharge par nombre de parametres
// --------------------------------------------------------
// TODO : Cree des versions surchargees de area() :
//
// double area(double side)                    -> carre (side * side)
// double area(double width, double height)    -> rectangle (width * height)
// double area(double base, double height, bool is_triangle)
//    -> si is_triangle : triangle (base * height / 2)
//    -> sinon : rectangle (base * height)

// Ecris tes fonctions ici :



// --------------------------------------------------------
// PARTIE 3 : Surcharge utile
// --------------------------------------------------------
// TODO : Cree des versions surchargees de clamp() qui
// limite une valeur entre un min et un max :
//
// int clamp(int value, int min_val, int max_val)
// double clamp(double value, double min_val, double max_val)
//
// Si value < min_val, retourne min_val
// Si value > max_val, retourne max_val
// Sinon retourne value

// Ecris tes fonctions ici :



int main() {
    // Decommente pour tester :

    // PARTIE 1
    // display(42);
    // display(3.14);
    // display("Hello");

    // PARTIE 2
    // cout << "Carre (5) : " << area(5.0) << endl;
    // cout << "Rectangle (4x6) : " << area(4.0, 6.0) << endl;
    // cout << "Triangle (10x5) : " << area(10.0, 5.0, true) << endl;

    // PARTIE 3
    // cout << "clamp(15, 0, 10) = " << clamp(15, 0, 10) << endl;
    // cout << "clamp(-5, 0, 10) = " << clamp(-5, 0, 10) << endl;
    // cout << "clamp(5, 0, 10) = " << clamp(5, 0, 10) << endl;
    // cout << "clamp(3.7, 0.0, 1.0) = " << clamp(3.7, 0.0, 1.0) << endl;

    return 0;
}
