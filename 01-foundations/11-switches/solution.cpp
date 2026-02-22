// ============================================================
// Solution : Switch / Case
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>

int main() {
    // ========================================================
    // PARTIE 1 : Switch basique
    // ========================================================

    int jour = 3;

    switch (jour) {
        case 1: std::cout << "Lundi" << std::endl; break;
        case 2: std::cout << "Mardi" << std::endl; break;
        case 3: std::cout << "Mercredi" << std::endl; break;
        case 4: std::cout << "Jeudi" << std::endl; break;
        case 5: std::cout << "Vendredi" << std::endl; break;
        case 6: std::cout << "Samedi" << std::endl; break;
        case 7: std::cout << "Dimanche" << std::endl; break;
        default: std::cout << "Jour invalide" << std::endl; break;
    }

    // ========================================================
    // PARTIE 2 : Grouper des cases
    // ========================================================

    int jour2 = 6;

    // Les cases 1 a 5 tombent les uns dans les autres (fall-through voulu)
    // jusqu'au premier break. Meme chose pour 6 et 7.
    switch (jour2) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            std::cout << "Jour de semaine" << std::endl;
            break;
        case 6:
        case 7:
            std::cout << "Weekend" << std::endl;
            break;
        default:
            std::cout << "Invalide" << std::endl;
            break;
    }

    // ========================================================
    // PARTIE 3 : Switch sur un char
    // ========================================================

    double x = 10.0;
    double y = 3.0;
    char operateur = '/';

    switch (operateur) {
        case '+':
            std::cout << x << " + " << y << " = " << (x + y) << std::endl;
            break;
        case '-':
            std::cout << x << " - " << y << " = " << (x - y) << std::endl;
            break;
        case '*':
            std::cout << x << " * " << y << " = " << (x * y) << std::endl;
            break;
        case '/':
            if (y != 0) {
                std::cout << x << " / " << y << " = " << (x / y) << std::endl;
            } else {
                std::cout << "Erreur : division par zero" << std::endl;
            }
            break;
        default:
            std::cout << "Operateur inconnu" << std::endl;
            break;
    }

    return 0;
}
