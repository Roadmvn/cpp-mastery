// ============================================================
// Solution : Saisie Utilisateur
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>

int main() {
    // ========================================================
    // PARTIE 1 : Saisie basique avec cin
    // ========================================================

    std::string prenom;
    int age;

    std::cout << "Prenom : ";
    std::cin >> prenom;

    std::cout << "Age : ";
    std::cin >> age;

    std::cout << "Bonjour " << prenom << ", tu as " << age << " ans." << std::endl;

    // ========================================================
    // PARTIE 2 : getline et le piege cin + getline
    // ========================================================

    int code_postal;
    std::cout << "Code postal : ";
    std::cin >> code_postal;

    // cin.ignore() vide le '\n' que cin >> a laisse dans le buffer
    // Sans ca, getline lirait immediatement le '\n' et retournerait ""
    std::cin.ignore();

    std::string adresse;
    std::cout << "Adresse : ";
    std::getline(std::cin, adresse);

    std::cout << "Tu habites au " << adresse << ", " << code_postal << std::endl;

    // ========================================================
    // PARTIE 3 : Validation de saisie
    // ========================================================

    double montant;
    std::cout << "Montant (positif) : ";
    std::cin >> montant;

    // cin.fail() est vrai si l'utilisateur a tape des lettres
    // au lieu d'un nombre
    if (std::cin.fail()) {
        std::cout << "Erreur : saisie invalide" << std::endl;
        return 1;
    }

    if (montant <= 0) {
        std::cout << "Erreur : montant doit etre positif" << std::endl;
        return 1;
    }

    std::cout << "Montant accepte : " << montant << " EUR" << std::endl;

    return 0;
}
