// ============================================================
// Chapitre 03 - Exercice : Classes et Objets
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>

// ============================================================
// PARTIE 1 : Classe basique
// - Creer une classe Compteur avec :
//   - Un attribut private int valeur (initialise a 0)
//   - Methodes public : incrementer(), decrementer(), reset()
//   - Methode const : get_valeur()
// ============================================================

// TODO: Declarer la classe Compteur

// ============================================================
// PARTIE 2 : Classe avec methode const et this
// - Creer une classe Vecteur2D avec :
//   - Attributs private : double x, y
//   - Methodes const : norme(), afficher()
//   - Methode non-const : Vecteur2D& ajouter(double dx, double dy)
//     qui retourne *this pour le chainage
// ============================================================

// TODO: Declarer la classe Vecteur2D

// ============================================================
// PARTIE 3 : Classe avec vector interne
// - Creer une classe ListeNoms avec :
//   - Attribut private : vector<string> noms
//   - Methodes : ajouter(string), supprimer(string),
//                contient(string) const, taille() const
//   - Methode const : afficher()
// ============================================================

// TODO: Declarer la classe ListeNoms

int main() {
    std::cout << "=== PARTIE 1 : Compteur ===" << std::endl;
    // TODO: Creer un Compteur, incrementer 5 fois, decrementer 2 fois, afficher

    std::cout << "\n=== PARTIE 2 : Vecteur2D ===" << std::endl;
    // TODO: Creer un Vecteur2D, tester le chainage avec ajouter()

    std::cout << "\n=== PARTIE 3 : ListeNoms ===" << std::endl;
    // TODO: Creer une ListeNoms, ajouter/supprimer des noms, afficher

    return 0;
}
