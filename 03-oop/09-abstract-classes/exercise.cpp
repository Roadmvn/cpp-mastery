// ============================================================
// Chapitre 09 - Exercice : Classes Abstraites et Interfaces
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ============================================================
// PARTIE 1 : Classe abstraite basique
// - Creer une classe abstraite Forme avec :
//   - virtual double aire() const = 0
//   - virtual string description() const = 0
//   - Methode concrete afficher() qui utilise les deux
// - Implementer : Rectangle(l,h), Cercle(r), Triangle(b,h)
// - Creer un vector<unique_ptr<Forme>> et afficher toutes les formes
// ============================================================

// TODO: Declarer Forme (abstraite) et ses implementations

// ============================================================
// PARTIE 2 : Interface pattern
// - Creer une interface IPrintable avec :
//   - virtual string to_string() const = 0
// - Creer une interface IComparable avec :
//   - virtual bool est_superieur(const IComparable&) const = 0
// - Creer une classe Note qui implemente les DEUX interfaces :
//   - valeur (double, 0-20)
//   - to_string() retourne "Note: XX/20"
//   - est_superieur() compare les valeurs
// ============================================================

// TODO: Declarer les interfaces et la classe Note

// ============================================================
// PARTIE 3 : Classe abstraite avec logique partagee
// - Creer une classe abstraite Notification avec :
//   - virtual void envoyer(string message) = 0 (pure virtual)
//   - void envoyer_urgente(string msg) (concrete, ajoute "[URGENT]")
//   - void envoyer_info(string msg) (concrete, ajoute "[INFO]")
// - Implementer : EmailNotif, SmsNotif, SlackNotif
// ============================================================

// TODO: Declarer les classes

int main() {
    std::cout << "=== PARTIE 1 : Formes abstraites ===" << std::endl;
    // TODO: Creer des formes et les afficher via pointeur Forme*

    std::cout << "\n=== PARTIE 2 : Interfaces ===" << std::endl;
    // TODO: Creer des Notes, les comparer et les afficher

    std::cout << "\n=== PARTIE 3 : Notifications ===" << std::endl;
    // TODO: Envoyer des notifications via differents canaux

    return 0;
}
