// ============================================================
// EXERCICE : Methodes de Strings
// Fichier : exercise.cpp
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Extraction et recherche
    // --------------------------------------------------------
    // Tu recois un ticker sous ce format : "EXCHANGE:SYMBOL"
    // Exemple : "NASDAQ:AAPL"
    //
    // TODO : Extrais et affiche separement l'exchange et le symbol
    // Utilise find() et substr()

    string ticker = "NASDAQ:AAPL";

    // Ecris ton code ici :



    // --------------------------------------------------------
    // PARTIE 2 : Manipulation de chaine
    // --------------------------------------------------------
    // Tu as un message d'erreur brut. Tu dois :
    // 1. Remplacer "ERROR" par "WARNING"
    // 2. Ajouter " [LOGGED]" a la fin
    // 3. Inserer "2024-01-15 " au debut (position 0)
    // 4. Afficher le resultat final et sa longueur

    string log_msg = "ERROR: Connection timeout on port 443";

    // Ecris ton code ici :



    // --------------------------------------------------------
    // PARTIE 3 : Nettoyage de donnees
    // --------------------------------------------------------
    // Tu as une chaine avec des espaces en trop.
    // Utilise find(), erase(), et une boucle pour :
    // 1. Supprimer tous les espaces doubles (les remplacer par un seul espace)
    // 2. Afficher le resultat propre
    //
    // Hint : cherche "  " (double espace) avec find() dans une boucle

    string dirty = "Prix :   150.25   USD    par   action";

    // Ecris ton code ici :



    return 0;
}
