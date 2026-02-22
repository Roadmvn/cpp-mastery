// ============================================================
// Solution : Conditions if/else
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>

int main() {
    // ========================================================
    // PARTIE 1 : if / else basique
    // ========================================================

    int nombre = 17;

    // Le modulo % 2 donne 0 pour les pairs, 1 pour les impairs
    if (nombre % 2 == 0) {
        std::cout << nombre << " est pair" << std::endl;
    } else {
        std::cout << nombre << " est impair" << std::endl;
    }

    // ========================================================
    // PARTIE 2 : if / else if / else
    // ========================================================

    double temperature = 22.5;

    // Les conditions sont testees dans l'ordre, du plus extreme au plus doux
    if (temperature < 0) {
        std::cout << "Gel" << std::endl;
    } else if (temperature < 15) {
        std::cout << "Froid" << std::endl;
    } else if (temperature < 25) {
        std::cout << "Agreable" << std::endl;
    } else if (temperature < 35) {
        std::cout << "Chaud" << std::endl;
    } else {
        std::cout << "Canicule" << std::endl;
    }

    // ========================================================
    // PARTIE 3 : Conditions imbriquees
    // ========================================================

    double moyenne = 15.5;

    if (moyenne >= 10) {
        // Admis : on determine la mention
        std::cout << "Admis";

        if (moyenne >= 16) {
            std::cout << " - Mention Tres Bien";
        } else if (moyenne >= 14) {
            std::cout << " - Mention Bien";
        } else if (moyenne >= 12) {
            std::cout << " - Mention Assez Bien";
        }
        // Pas de else : si < 12, pas de mention (juste "Admis")

        std::cout << std::endl;
    } else {
        std::cout << "Recale" << std::endl;
    }

    return 0;
}
