// ============================================================
// Chapitre 02 - Exercice : Les Enumerations (enum)
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
// PARTIE 1 : Enum class basique
// - Declarer un enum class Saison { PRINTEMPS, ETE, AUTOMNE, HIVER }
// - Ecrire une fonction to_string(Saison) qui retourne le nom
// - Ecrire une fonction temperature_moyenne(Saison) qui retourne
//   un int approximatif (15, 28, 12, 3)
// ============================================================

// TODO: Declarer l'enum class Saison et les fonctions

// ============================================================
// PARTIE 2 : Enum class avec valeurs et underlying type
// - Declarer un enum class Priorite : uint8_t
//   { BASSE = 1, NORMALE = 5, HAUTE = 8, CRITIQUE = 10 }
// - Ecrire une fonction to_string(Priorite)
// - Ecrire une fonction comparer(Priorite a, Priorite b) qui
//   affiche laquelle est la plus haute
// ============================================================

// TODO: Declarer l'enum class Priorite et les fonctions

// ============================================================
// PARTIE 3 : Enum dans une struct
// - Declarer un enum class Statut { EN_ATTENTE, EN_COURS, TERMINE, ECHEC }
// - Declarer une struct Tache { string nom; Statut statut; int progression; }
// - Ecrire une fonction afficher_tache(const Tache&)
// - Creer 3 taches avec differents statuts et les afficher
// ============================================================

// TODO: Declarer les types et fonctions

int main() {
    std::cout << "=== PARTIE 1 : Saisons ===" << std::endl;
    // TODO: Tester chaque saison avec to_string et temperature_moyenne

    std::cout << "\n=== PARTIE 2 : Priorites ===" << std::endl;
    // TODO: Tester les priorites, afficher leur taille en bytes

    std::cout << "\n=== PARTIE 3 : Taches ===" << std::endl;
    // TODO: Creer et afficher les taches

    return 0;
}
