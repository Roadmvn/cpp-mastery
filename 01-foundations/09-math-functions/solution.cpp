// ============================================================
// Solution : Fonctions Mathematiques
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int main() {
    // ========================================================
    // PARTIE 1 : Fonctions de base
    // ========================================================

    // pow(base, exposant) retourne base^exposant
    double resultat = pow(2, 16);
    std::cout << "2^16 = " << resultat << std::endl;  // 65536

    // sqrt retourne la racine carree
    double racine = sqrt(256);
    std::cout << "sqrt(256) = " << racine << std::endl;  // 16

    // fabs pour la valeur absolue d'un double
    // (abs() marche pour les int, fabs() pour les flottants)
    double absolu = fabs(-42.5);
    std::cout << "|-42.5| = " << absolu << std::endl;  // 42.5

    // ========================================================
    // PARTIE 2 : Arrondis
    // ========================================================

    double prix = 99.674;

    // round : au plus proche (0.674 > 0.5 donc arrondi vers le haut)
    double arrondi = round(prix);
    std::cout << "round(99.674) = " << arrondi << std::endl;  // 100

    // ceil : toujours vers le haut (ceiling = plafond)
    double superieur = ceil(prix);
    std::cout << "ceil(99.674)  = " << superieur << std::endl;  // 100

    // floor : toujours vers le bas (floor = plancher)
    double inferieur = floor(prix);
    std::cout << "floor(99.674) = " << inferieur << std::endl;  // 99

    // ========================================================
    // PARTIE 3 : Interet compose
    // ========================================================

    double capital = 5000.0;
    double taux = 0.05;
    int annees = 20;

    // V = C * (1 + r)^n
    double valeur_future = capital * pow(1 + taux, annees);
    std::cout << "Valeur dans " << annees << " ans : " << valeur_future << std::endl;

    double gain = valeur_future - capital;
    std::cout << "Gain : " << gain << std::endl;

    return 0;
}
