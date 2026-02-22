// ============================================================
// SOLUTION : Methodes de Strings
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Extraction et recherche
    // --------------------------------------------------------
    string ticker = "NASDAQ:AAPL";

    size_t sep = ticker.find(":");
    string exchange = ticker.substr(0, sep);
    string symbol = ticker.substr(sep + 1);

    cout << "Exchange : " << exchange << endl;  // NASDAQ
    cout << "Symbol   : " << symbol << endl;    // AAPL

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 2 : Manipulation de chaine
    // --------------------------------------------------------
    string log_msg = "ERROR: Connection timeout on port 443";

    // 1. Remplacer ERROR par WARNING
    size_t pos = log_msg.find("ERROR");
    if (pos != string::npos) {
        log_msg.replace(pos, 5, "WARNING");
    }

    // 2. Ajouter [LOGGED] a la fin
    log_msg.append(" [LOGGED]");

    // 3. Inserer la date au debut
    log_msg.insert(0, "2024-01-15 ");

    // 4. Afficher
    cout << log_msg << endl;
    cout << "Longueur : " << log_msg.length() << endl;

    cout << "---" << endl;

    // --------------------------------------------------------
    // PARTIE 3 : Nettoyage de donnees
    // --------------------------------------------------------
    string dirty = "Prix :   150.25   USD    par   action";

    size_t found = dirty.find("  ");
    while (found != string::npos) {
        dirty.erase(found, 1);  // Supprime un espace
        found = dirty.find("  ");
    }

    cout << "Propre : \"" << dirty << "\"" << endl;
    // "Prix : 150.25 USD par action"

    return 0;
}
