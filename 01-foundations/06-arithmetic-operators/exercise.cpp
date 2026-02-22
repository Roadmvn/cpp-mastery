// ============================================================
// Exercice : Operateurs Arithmetiques
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>

int main() {
    // ========================================================
    // PARTIE 1 : Operations de base
    // Effectue les calculs demandes avec les bonnes operations.
    // ========================================================

    int a = 17;
    int b = 5;

    // TODO: Calcule la somme de a et b, stocke dans 'somme'
    // int somme = ...;

    // TODO: Calcule le reste de la division de a par b, stocke dans 'reste'
    // int reste = ...;

    // TODO: Calcule la division entiere de a par b, stocke dans 'div_entiere'
    // int div_entiere = ...;

    // TODO: Calcule la division reelle de a par b, stocke dans 'div_reelle'
    // (indice : il faut forcer la division flottante)
    // double div_reelle = ...;

    // Decommenter pour verifier :
    // std::cout << "Somme       : " << somme << std::endl;       // 22
    // std::cout << "Reste       : " << reste << std::endl;       // 2
    // std::cout << "Div entiere : " << div_entiere << std::endl; // 3
    // std::cout << "Div reelle  : " << div_reelle << std::endl;  // 3.4

    // ========================================================
    // PARTIE 2 : Increment et operateurs composes
    // Utilise ++, --, +=, -=, *= pour modifier la variable.
    // ========================================================

    int compteur = 0;

    // TODO: Incremente compteur de 1 avec l'operateur ++
    // TODO: Ajoute 10 a compteur avec +=
    // TODO: Multiplie compteur par 3 avec *=
    // TODO: Soustrais 8 avec -=

    // Decommenter pour verifier :
    // std::cout << "Compteur : " << compteur << std::endl; // 25

    // ========================================================
    // PARTIE 3 : Calcul de moyenne
    // Calcule la moyenne de 3 notes. Attention a la division !
    // ========================================================

    int note1 = 14;
    int note2 = 17;
    int note3 = 12;

    // TODO: Calcule la moyenne des 3 notes (resultat attendu : 14.3333)
    // Attention : la somme de 3 int divisee par 3 donne un int !
    // double moyenne = ...;

    // Decommenter pour verifier :
    // std::cout << "Moyenne : " << moyenne << std::endl; // 14.3333

    return 0;
}
