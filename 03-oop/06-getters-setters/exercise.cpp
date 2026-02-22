// ============================================================
// Chapitre 06 - Exercice : Getters, Setters et Encapsulation
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
// PARTIE 1 : Getters et setters basiques avec validation
// - Creer une classe Temperature avec :
//   - double celsius (private)
//   - Getter : get_celsius(), get_fahrenheit(), get_kelvin()
//   - Setter : set_celsius(double) avec validation (>= -273.15)
//   - Setter : set_fahrenheit(double) (convertit et stocke en celsius)
// ============================================================

// TODO: Declarer la classe Temperature

// ============================================================
// PARTIE 2 : Encapsulation avec invariant
// - Creer une classe CompteBancaire avec :
//   - double solde (private, commence a 0)
//   - string titulaire (private)
//   - Getter const pour solde et titulaire
//   - Methode deposer(double) : refuse les montants <= 0
//   - Methode retirer(double) : refuse si solde insuffisant
//   - Methode afficher() const
// ============================================================

// TODO: Declarer la classe CompteBancaire

// ============================================================
// PARTIE 3 : Fluent interface
// - Creer une classe Requete avec :
//   - string url, string methode, int timeout, bool ssl
// - Tous les setters retournent *this pour le chainage
// - Methode afficher() const
// ============================================================

// TODO: Declarer la classe Requete

int main() {
    std::cout << "=== PARTIE 1 : Temperature ===" << std::endl;
    // TODO: Tester les conversions et la validation

    std::cout << "\n=== PARTIE 2 : Compte Bancaire ===" << std::endl;
    // TODO: Tester depot, retrait, cas invalides

    std::cout << "\n=== PARTIE 3 : Requete (fluent) ===" << std::endl;
    // TODO: Construire une requete avec chainage

    return 0;
}
