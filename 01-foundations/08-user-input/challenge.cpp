// ============================================================
// Challenge HFT : Interface de Saisie d'Ordres Boursiers
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
// Contexte : Tu developpes l'interface manuelle d'un systeme de
// trading. Le trader doit pouvoir saisir des ordres avec
// validation stricte. Un champ invalide = ordre rejete.
//
// Sortie attendue (exemple) :
//   === Saisie d'Ordre ===
//   Symbole (ex: AAPL) : TSLA
//   Direction (BUY/SELL) : BUY
//   Prix limite : 245.50
//   Quantite : 100
//   Commentaire : Achat sur support technique
//
//   === Confirmation ===
//   BUY 100 TSLA @ 245.50 USD
//   Montant total : 24550 USD
//   Note : Achat sur support technique
//   Statut : ORDRE ACCEPTE
// ============================================================

#include <iostream>
#include <string>

int main() {
    std::cout << "=== Saisie d'Ordre ===" << std::endl;

    // Saisie du symbole
    std::string symbole;
    std::cout << "Symbole (ex: AAPL) : ";
    std::cin >> symbole;

    // Validation : symbole non vide
    if (symbole.empty()) {
        std::cout << "REJETE : symbole vide" << std::endl;
        return 1;
    }

    // Saisie de la direction
    std::string direction;
    std::cout << "Direction (BUY/SELL) : ";
    std::cin >> direction;

    // Validation : doit etre BUY ou SELL
    if (direction != "BUY" && direction != "SELL") {
        std::cout << "REJETE : direction invalide (BUY ou SELL uniquement)" << std::endl;
        return 1;
    }

    // Saisie du prix
    double prix;
    std::cout << "Prix limite : ";
    std::cin >> prix;

    if (std::cin.fail() || prix <= 0) {
        std::cout << "REJETE : prix invalide" << std::endl;
        return 1;
    }

    // Saisie de la quantite
    int quantite;
    std::cout << "Quantite : ";
    std::cin >> quantite;

    if (std::cin.fail() || quantite <= 0) {
        std::cout << "REJETE : quantite invalide" << std::endl;
        return 1;
    }

    // Vider le buffer avant getline
    std::cin.ignore();

    // Saisie du commentaire (peut contenir des espaces)
    std::string commentaire;
    std::cout << "Commentaire : ";
    std::getline(std::cin, commentaire);

    // Calcul du montant total
    double montant_total = prix * quantite;

    // Confirmation
    std::cout << "\n=== Confirmation ===" << std::endl;
    std::cout << direction << " " << quantite << " " << symbole
              << " @ " << prix << " USD" << std::endl;
    std::cout << "Montant total : " << montant_total << " USD" << std::endl;

    if (!commentaire.empty()) {
        std::cout << "Note : " << commentaire << std::endl;
    }

    // Controle de risque basique : montant max 1 million
    if (montant_total > 1000000) {
        std::cout << "Statut : REJETE (montant > 1M USD)" << std::endl;
        return 1;
    }

    std::cout << "Statut : ORDRE ACCEPTE" << std::endl;

    return 0;
}
