// ============================================================
// Solution : Conversion de Types
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>

int main() {
    // ========================================================
    // PARTIE 1 : Identifier les conversions implicites
    // ========================================================

    int a = 5;
    double b = 2.0;

    // a est promu en double automatiquement -> 5.0 + 2.0 = 7.0
    double result1 = a + b;
    std::cout << "a + b = " << result1 << std::endl;  // 7

    // Division entre deux int -> resultat int (tronque)
    int result2 = a / 2;
    std::cout << "a / 2 = " << result2 << std::endl;  // 2

    // b est double, donc a est promu -> 5.0 / 2.0 = 2.5
    double result3 = a / b;
    std::cout << "a / b = " << result3 << std::endl;  // 2.5

    // ========================================================
    // PARTIE 2 : Utiliser static_cast
    // ========================================================

    int total_points = 87;
    int nb_joueurs = 4;

    // Sans cast : 87 / 4 = 21 (division entiere)
    // Avec cast : 87.0 / 4 = 21.75
    double moyenne = static_cast<double>(total_points) / nb_joueurs;
    std::cout << "Moyenne : " << moyenne << std::endl;  // 21.75

    // Conversion char -> int pour obtenir le code ASCII
    char lettre = 'a';
    int code = static_cast<int>(lettre);
    std::cout << "'a' = " << code << std::endl;  // 97

    // Conversion int -> char pour obtenir le caractere
    int ascii_code = 72;
    char caractere = static_cast<char>(ascii_code);
    std::cout << "72 = '" << caractere << "'" << std::endl;  // 'H'

    // ========================================================
    // PARTIE 3 : Detecter le narrowing
    // ========================================================

    double prix_exact = 156.789;

    // Conversion explicite : on montre qu'on accepte la perte
    int prix_tronque = static_cast<int>(prix_exact);
    std::cout << "Prix tronque : " << prix_tronque << std::endl;  // 156

    // La perte est la difference entre l'original et le tronque
    double perte = prix_exact - prix_tronque;
    std::cout << "Perte : " << perte << std::endl;  // 0.789

    return 0;
}
