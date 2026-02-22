// ============================================================
// Solution : Operateurs Arithmetiques
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>

int main() {
    // ========================================================
    // PARTIE 1 : Operations de base
    // ========================================================

    int a = 17;
    int b = 5;

    // Somme classique
    int somme = a + b;

    // Modulo : retourne le reste de la division euclidienne
    int reste = a % b;

    // Division entiere : 17/5 = 3 (tronque, pas arrondi)
    int div_entiere = a / b;

    // Division reelle : on caste un des operandes en double
    // pour forcer la division flottante
    double div_reelle = static_cast<double>(a) / b;

    std::cout << "Somme       : " << somme << std::endl;       // 22
    std::cout << "Reste       : " << reste << std::endl;       // 2
    std::cout << "Div entiere : " << div_entiere << std::endl; // 3
    std::cout << "Div reelle  : " << div_reelle << std::endl;  // 3.4

    // ========================================================
    // PARTIE 2 : Increment et operateurs composes
    // ========================================================

    int compteur = 0;

    ++compteur;    // compteur = 1
    compteur += 10; // compteur = 11
    compteur *= 3;  // compteur = 33
    compteur -= 8;  // compteur = 25

    std::cout << "Compteur : " << compteur << std::endl; // 25

    // ========================================================
    // PARTIE 3 : Calcul de moyenne
    // ========================================================

    int note1 = 14;
    int note2 = 17;
    int note3 = 12;

    // On force la division flottante avec 3.0 au lieu de 3
    double moyenne = (note1 + note2 + note3) / 3.0;

    std::cout << "Moyenne : " << moyenne << std::endl; // 14.3333

    return 0;
}
