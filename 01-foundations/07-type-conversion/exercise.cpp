// ============================================================
// Exercice : Conversion de Types
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>

int main() {
    // ========================================================
    // PARTIE 1 : Identifier les conversions implicites
    // Pour chaque ligne, determine la valeur et le type du resultat.
    // ========================================================

    int a = 5;
    double b = 2.0;

    // TODO: Stocke le resultat de a + b dans une variable du bon type
    // ... result1 = a + b;
    // std::cout << "a + b = " << result1 << std::endl;  // 7

    // TODO: Stocke le resultat de a / 2 (division entiere)
    // ... result2 = a / 2;
    // std::cout << "a / 2 = " << result2 << std::endl;  // 2

    // TODO: Stocke le resultat de a / b (division reelle)
    // ... result3 = a / b;
    // std::cout << "a / b = " << result3 << std::endl;  // 2.5

    // ========================================================
    // PARTIE 2 : Utiliser static_cast
    // Corrige les divisions pour obtenir les bons resultats.
    // ========================================================

    int total_points = 87;
    int nb_joueurs = 4;

    // TODO: Calcule la moyenne REELLE des points (pas tronquee)
    // Utilise static_cast pour obtenir 21.75
    // double moyenne = ...;
    // std::cout << "Moyenne : " << moyenne << std::endl;  // 21.75

    // TODO: Convertis le caractere 'a' en son code ASCII avec static_cast
    char lettre = 'a';
    // int code = ...;
    // std::cout << "'a' = " << code << std::endl;  // 97

    // TODO: Convertis le code ASCII 72 en caractere avec static_cast
    int ascii_code = 72;
    // char caractere = ...;
    // std::cout << "72 = '" << caractere << "'" << std::endl;  // 'H'

    // ========================================================
    // PARTIE 3 : Detecter le narrowing
    // Identifie et corrige les problemes de perte de precision.
    // ========================================================

    double prix_exact = 156.789;

    // Cette ligne perd de la precision (narrowing) :
    // int prix_arrondi = prix_exact;

    // TODO: Fais la meme conversion mais de maniere EXPLICITE avec static_cast
    // pour montrer que c'est intentionnel
    // int prix_tronque = ...;
    // std::cout << "Prix tronque : " << prix_tronque << std::endl;  // 156

    // TODO: Calcule le montant perdu par la troncation
    // double perte = ...;
    // std::cout << "Perte : " << perte << std::endl;  // 0.789

    return 0;
}
