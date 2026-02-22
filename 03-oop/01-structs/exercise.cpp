// ============================================================
// Chapitre 01 - Exercice : Les Structures (struct)
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>

// ============================================================
// PARTIE 1 : Declarer une struct Etudiant
// - nom (string), age (int), moyenne (double)
// - Creer une fonction afficher_etudiant(const Etudiant&)
// ============================================================

// TODO: Declarer la struct Etudiant ici

// TODO: Ecrire la fonction afficher_etudiant ici

// ============================================================
// PARTIE 2 : Struct avec methode
// - Declarer une struct Cercle avec rayon (double)
// - Ajouter une methode aire() const
// - Ajouter une methode perimetre() const
// (utiliser 3.14159265 pour PI)
// ============================================================

// TODO: Declarer la struct Cercle avec ses methodes ici

// ============================================================
// PARTIE 3 : Struct imbriquee + vector
// - Declarer une struct Coordonnee { double lat, lon; }
// - Declarer une struct Ville { string nom; int population; Coordonnee pos; }
// - Creer un vector<Ville>, y ajouter 3 villes
// - Ecrire une fonction qui trouve la ville la plus peuplee
// ============================================================

// TODO: Declarer les structs et la fonction ici

int main() {
    std::cout << "=== PARTIE 1 : Struct Etudiant ===" << std::endl;
    // TODO: Creer un Etudiant et l'afficher

    std::cout << "\n=== PARTIE 2 : Struct Cercle ===" << std::endl;
    // TODO: Creer un Cercle de rayon 5.0, afficher aire et perimetre

    std::cout << "\n=== PARTIE 3 : Villes ===" << std::endl;
    // TODO: Creer un vector de villes et trouver la plus peuplee

    return 0;
}
