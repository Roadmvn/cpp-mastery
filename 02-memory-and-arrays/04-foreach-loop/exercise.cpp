// =============================================================
// Exercice : Range-based for (foreach)
// =============================================================
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// =============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    // ==========================================================
    // PARTIE 1 : Lecture avec range-based for
    // ==========================================================

    int values[] = {12, 45, 7, 89, 23, 56, 34, 78, 1, 90};

    // TODO 1.1 : Utilise un range-based for avec const auto& pour afficher
    //            tous les elements sur une seule ligne, separes par des espaces


    // TODO 1.2 : Utilise un range-based for pour compter combien d'elements
    //            sont superieurs a 50
    //            Format: "Elements > 50 : X"


    // TODO 1.3 : Utilise un range-based for pour trouver le maximum
    //            Format: "Maximum : X"


    // ==========================================================
    // PARTIE 2 : Modification avec range-based for
    // ==========================================================

    double prices[] = {10.5, 20.3, 15.7, 8.9, 25.0};

    // TODO 2.1 : Utilise un range-based for avec auto& pour multiplier
    //            chaque prix par 1.10 (augmentation de 10%)


    // TODO 2.2 : Affiche les prix modifies avec const auto&
    //            Format: "Prix: 11.55 22.33 ..."


    // TODO 2.3 : Utilise un range-based for avec auto& pour plafonner
    //            chaque prix a 25.0 maximum (si prix > 25, prix = 25)
    //            Puis affiche le resultat


    // ==========================================================
    // PARTIE 3 : Strings et range-based for
    // ==========================================================

    string mots[] = {"hello", "world", "foo", "bar", "cpp", "is", "fast"};

    // TODO 3.1 : Affiche chaque mot et sa longueur
    //            Format: "hello (5)"


    // TODO 3.2 : Compte le nombre total de caracteres dans tous les mots
    //            Format: "Total caracteres: X"


    // TODO 3.3 : Affiche uniquement les mots de 3 lettres ou moins
    //            Format: "Mots courts: foo bar cpp is"


    return 0;
}
