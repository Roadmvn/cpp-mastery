// ============================================================
// Chapitre 05 - Exercice : Surcharge de Constructeurs
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
// PARTIE 1 : Multiples constructeurs
// - Creer une classe Date avec jour, mois, annee (int)
// - Constructeur() : date d'aujourd'hui (01/01/2026 par defaut)
// - Constructeur(int annee) : 01/01/annee
// - Constructeur(int jour, int mois, int annee)
// - Methode afficher() const
// ============================================================

// TODO: Declarer la classe Date

// ============================================================
// PARTIE 2 : Delegation de constructeurs
// - Creer une classe Email avec :
//   - destinataire (string), sujet (string), corps (string),
//     priorite (int, defaut 0)
// - Un constructeur principal (4 parametres)
// - Les autres deleguent au principal
// - Methode afficher() const
// ============================================================

// TODO: Declarer la classe Email avec delegation

// ============================================================
// PARTIE 3 : explicit et = delete
// - Creer une classe Identifiant avec :
//   - id (int), label (string)
// - Constructeur explicit (int id, string label)
// - Constructeur explicit (int id) avec label = "sans-nom"
// - Interdire la copie (= delete)
// - Methode afficher() const
// ============================================================

// TODO: Declarer la classe Identifiant

int main() {
    std::cout << "=== PARTIE 1 : Date ===" << std::endl;
    // TODO: Creer des dates avec les differents constructeurs

    std::cout << "\n=== PARTIE 2 : Email ===" << std::endl;
    // TODO: Creer des emails avec differents constructeurs

    std::cout << "\n=== PARTIE 3 : Identifiant ===" << std::endl;
    // TODO: Creer des identifiants, verifier que la copie echoue

    return 0;
}
