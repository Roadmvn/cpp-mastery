// ============================================================
// Exercice : Operateur Ternaire
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

int main() {
    // ========================================================
    // PARTIE 1 : Ternaire basique
    // Remplace les if/else par des ternaires.
    // ========================================================

    int age = 20;

    // TODO: Remplace ce if/else par un ternaire
    // std::string statut;
    // if (age >= 18) {
    //     statut = "Majeur";
    // } else {
    //     statut = "Mineur";
    // }
    // Ecris : std::string statut = ... ;

    // std::cout << "Statut : " << statut << std::endl;  // "Majeur"

    int a = 42, b = 17;

    // TODO: Trouve le maximum de a et b avec un ternaire
    // int maximum = ... ;
    // std::cout << "Max : " << maximum << std::endl;  // 42

    // ========================================================
    // PARTIE 2 : Ternaire dans cout
    // Affiche directement avec un ternaire dans cout.
    // ========================================================

    bool connecte = true;

    // TODO: Affiche "En ligne" si connecte, "Hors ligne" sinon
    // Utilise un ternaire directement dans cout
    // std::cout << "Status : " << (...) << std::endl;

    double temperature = -5.0;

    // TODO: Affiche "Positif" ou "Negatif" selon la temperature
    // std::cout << "Temperature : " << (...) << std::endl;

    // ========================================================
    // PARTIE 3 : Ternaire imbrique (1 niveau max)
    // Classe un score en lettre.
    // ========================================================

    int score = 75;

    // TODO: Utilise un ternaire imbrique pour determiner la lettre :
    // >= 90 -> "A", >= 80 -> "B", >= 70 -> "C", < 70 -> "F"
    // std::string lettre = ... ;
    // std::cout << "Score " << score << " = " << lettre << std::endl;  // "C"

    return 0;
}
