// ============================================================
// Chapitre 07 - Exercice : Heritage (Inheritance)
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
// PARTIE 1 : Heritage basique
// - Classe de base Vehicule : marque (string), vitesse_max (int)
//   Methode afficher() const
// - Classe Voiture : herite de Vehicule, ajoute nb_portes (int)
// - Classe Moto : herite de Vehicule, ajoute cylindree (int)
// - Chaque derivee a un constructeur qui appelle celui de Vehicule
// ============================================================

// TODO: Declarer les classes Vehicule, Voiture, Moto

// ============================================================
// PARTIE 2 : Heritage et protected
// - Classe de base Forme : nom (protected string)
//   Methode afficher() const (affiche le nom)
// - Classe Rectangle : herite de Forme, ajoute largeur et hauteur
//   Methode aire() const, perimetre() const
//   Redefinit afficher() pour inclure les dimensions
// - Classe Cercle : herite de Forme, ajoute rayon
//   Methode aire() const, perimetre() const
// ============================================================

// TODO: Declarer les classes Forme, Rectangle, Cercle

// ============================================================
// PARTIE 3 : Chaine d'heritage
// - Classe Employe : nom (string), salaire (double)
// - Classe Manager : herite Employe, ajoute equipe_size (int)
// - Classe Directeur : herite Manager, ajoute budget (double)
// - Chaque classe a afficher() et un constructeur complet
// ============================================================

// TODO: Declarer les classes Employe, Manager, Directeur

int main() {
    std::cout << "=== PARTIE 1 : Vehicules ===" << std::endl;
    // TODO: Creer Voiture et Moto, afficher

    std::cout << "\n=== PARTIE 2 : Formes ===" << std::endl;
    // TODO: Creer Rectangle et Cercle, afficher aires

    std::cout << "\n=== PARTIE 3 : Employes ===" << std::endl;
    // TODO: Creer Employe, Manager, Directeur, afficher

    return 0;
}
