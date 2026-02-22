// ============================================================
// Solution : Operateur Ternaire
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>

int main() {
    // ========================================================
    // PARTIE 1 : Ternaire basique
    // ========================================================

    int age = 20;

    // Le ternaire remplace le if/else en une seule ligne
    std::string statut = (age >= 18) ? "Majeur" : "Mineur";
    std::cout << "Statut : " << statut << std::endl;  // "Majeur"

    int a = 42, b = 17;

    // Le max de deux nombres en une ligne
    int maximum = (a > b) ? a : b;
    std::cout << "Max : " << maximum << std::endl;  // 42

    // ========================================================
    // PARTIE 2 : Ternaire dans cout
    // ========================================================

    bool connecte = true;

    // Les parentheses sont essentielles dans cout pour eviter
    // les conflits avec l'operateur <<
    std::cout << "Status : " << (connecte ? "En ligne" : "Hors ligne") << std::endl;

    double temperature = -5.0;
    std::cout << "Temperature : " << ((temperature >= 0) ? "Positif" : "Negatif") << std::endl;

    // ========================================================
    // PARTIE 3 : Ternaire imbrique
    // ========================================================

    int score = 75;

    // Ternaire imbrique sur plusieurs lignes pour la lisibilite
    // On lit : si >= 90 -> A, sinon si >= 80 -> B, sinon si >= 70 -> C, sinon F
    std::string lettre = (score >= 90) ? "A"
                       : (score >= 80) ? "B"
                       : (score >= 70) ? "C"
                       :                 "F";

    std::cout << "Score " << score << " = " << lettre << std::endl;  // "C"

    return 0;
}
