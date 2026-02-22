// ============================================================
// Chapitre 04 - Exercice : Constructeurs et Destructeurs
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
// PARTIE 1 : Constructeur par defaut + parametre
// - Creer une classe Rectangle avec largeur et hauteur (double)
// - Constructeur par defaut : 1.0 x 1.0
// - Constructeur parametre avec liste d'initialisation
// - Methodes const : aire(), perimetre(), afficher()
// ============================================================

// TODO: Declarer la classe Rectangle

// ============================================================
// PARTIE 2 : Destructeur avec trace
// - Creer une classe Trace avec un attribut string nom
// - Le constructeur affiche "Trace [nom] : cree"
// - Le destructeur affiche "Trace [nom] : detruit"
// - Creer des objets dans differents scopes pour observer
//   l'ordre de construction/destruction
// ============================================================

// TODO: Declarer la classe Trace

// ============================================================
// PARTIE 3 : Classe avec membre const
// - Creer une classe Etudiant avec :
//   - const int matricule (ne change jamais)
//   - string nom
//   - double moyenne (defaut 0.0)
// - Le constructeur DOIT utiliser la liste d'initialisation
// - Methode modifier_note(double) et afficher() const
// ============================================================

// TODO: Declarer la classe Etudiant

int main() {
    std::cout << "=== PARTIE 1 : Rectangle ===" << std::endl;
    // TODO: Creer des rectangles et afficher aire/perimetre

    std::cout << "\n=== PARTIE 2 : Destructeur ===" << std::endl;
    // TODO: Creer des objets Trace dans differents scopes

    std::cout << "\n=== PARTIE 3 : Etudiant ===" << std::endl;
    // TODO: Creer des etudiants avec matricule const

    return 0;
}
