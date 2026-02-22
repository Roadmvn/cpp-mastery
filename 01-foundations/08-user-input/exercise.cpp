// ============================================================
// Exercice : Saisie Utilisateur
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

int main() {
    // ========================================================
    // PARTIE 1 : Saisie basique avec cin
    // Lis un prenom et un age, puis affiche-les.
    // ========================================================

    // TODO: Declare une variable string 'prenom' et un int 'age'

    // TODO: Demande le prenom avec cout et lis-le avec cin

    // TODO: Demande l'age avec cout et lis-le avec cin

    // Decommenter pour verifier :
    // std::cout << "Bonjour " << prenom << ", tu as " << age << " ans." << std::endl;

    // ========================================================
    // PARTIE 2 : getline et le piege cin + getline
    // Lis un nom complet (avec espaces) apres avoir lu un nombre.
    // ========================================================

    int code_postal;

    // TODO: Demande et lis le code postal avec cin
    // std::cout << "Code postal : ";
    // ...

    // TODO: Utilise cin.ignore() pour vider le buffer
    // ...

    std::string adresse;
    // TODO: Demande et lis l'adresse complete avec getline
    // (l'adresse contient des espaces : "12 rue de la Paix")
    // std::cout << "Adresse : ";
    // ...

    // Decommenter pour verifier :
    // std::cout << "Tu habites au " << adresse << ", " << code_postal << std::endl;

    // ========================================================
    // PARTIE 3 : Validation de saisie
    // Lis un nombre et verifie qu'il est valide et positif.
    // ========================================================

    double montant;
    std::cout << "Montant (positif) : ";
    std::cin >> montant;

    // TODO: Verifie si cin.fail() est vrai (saisie invalide)
    // Si oui, affiche "Erreur : saisie invalide" et retourne 1

    // TODO: Verifie si le montant est negatif ou nul
    // Si oui, affiche "Erreur : montant doit etre positif" et retourne 1

    // Decommenter pour verifier :
    // std::cout << "Montant accepte : " << montant << " EUR" << std::endl;

    return 0;
}
