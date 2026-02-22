// ============================================================
// Chapitre 08 - Exercice : Polymorphisme et virtual
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ============================================================
// PARTIE 1 : Polymorphisme basique
// - Classe de base Forme avec :
//   - virtual double aire() const = retourne 0
//   - virtual string type() const = retourne "Forme"
//   - virtual void afficher() const
//   - Destructeur virtuel
// - Derivees : Carre(cote), Cercle(rayon), Triangle(base, hauteur)
//   Chaque derivee surcharge aire(), type() avec override
// ============================================================

// TODO: Declarer les classes Forme, Carre, Cercle, Triangle

// ============================================================
// PARTIE 2 : Polymorphisme avec vector
// - Creer un vector<Forme*> contenant differentes formes
// - Iterer et appeler afficher() sur chaque forme
// - Verifier que la bonne methode est appelee (late binding)
// - Liberer la memoire
// ============================================================

// (Utilise les classes de la PARTIE 1)

// ============================================================
// PARTIE 3 : override et final
// - Classe Vehicule avec virtual void demarrer() et virtual void arreter()
// - Classe VoitureElectrique : override demarrer() (silencieux)
// - Classe Tesla final : herite VoitureElectrique, override arreter()
// - Tester le polymorphisme via pointeur Vehicule*
// ============================================================

// TODO: Declarer les classes Vehicule, VoitureElectrique, Tesla

int main() {
    std::cout << "=== PARTIE 1 : Formes ===" << std::endl;
    // TODO: Creer des formes et afficher leurs aires

    std::cout << "\n=== PARTIE 2 : Vector polymorphe ===" << std::endl;
    // TODO: Vector de Forme*, iterer et afficher

    std::cout << "\n=== PARTIE 3 : Override et final ===" << std::endl;
    // TODO: Tester la hierarchie Vehicule

    return 0;
}
