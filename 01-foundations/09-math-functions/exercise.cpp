// ============================================================
// Exercice : Fonctions Mathematiques
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int main() {
    // ========================================================
    // PARTIE 1 : Fonctions de base (pow, sqrt, abs)
    // ========================================================

    // TODO: Calcule 2 puissance 16 avec pow(), stocke dans 'resultat'
    // double resultat = ...;
    // std::cout << "2^16 = " << resultat << std::endl;  // 65536

    // TODO: Calcule la racine carree de 256, stocke dans 'racine'
    // double racine = ...;
    // std::cout << "sqrt(256) = " << racine << std::endl;  // 16

    // TODO: Calcule la valeur absolue de -42.5 avec fabs()
    // double absolu = ...;
    // std::cout << "|-42.5| = " << absolu << std::endl;  // 42.5

    // ========================================================
    // PARTIE 2 : Arrondis
    // Pour un prix de 99.674, calcule les 3 types d'arrondi.
    // ========================================================

    double prix = 99.674;

    // TODO: Arrondi au plus proche
    // double arrondi = ...;
    // std::cout << "round(99.674) = " << arrondi << std::endl;  // 100

    // TODO: Arrondi superieur
    // double superieur = ...;
    // std::cout << "ceil(99.674)  = " << superieur << std::endl;  // 100

    // TODO: Arrondi inferieur
    // double inferieur = ...;
    // std::cout << "floor(99.674) = " << inferieur << std::endl;  // 99

    // ========================================================
    // PARTIE 3 : Application -- Interet compose
    // Calcule la valeur future d'un investissement.
    // Formule : V = C * (1 + r)^n
    //   C = capital initial
    //   r = taux annuel
    //   n = nombre d'annees
    // ========================================================

    double capital = 5000.0;
    double taux = 0.05;  // 5%
    int annees = 20;

    // TODO: Calcule la valeur future avec pow()
    // double valeur_future = ...;
    // std::cout << "Valeur dans " << annees << " ans : " << valeur_future << std::endl;
    // Attendu : ~13266.5

    // TODO: Calcule le gain (valeur future - capital)
    // double gain = ...;
    // std::cout << "Gain : " << gain << std::endl;

    return 0;
}
