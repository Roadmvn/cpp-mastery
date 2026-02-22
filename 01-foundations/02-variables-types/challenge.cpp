// ============================================================
// CHALLENGE : Simulateur de Ticker Boursier (HFT)
// Fichier : challenge.cpp
// Compile : g++ -o challenge challenge.cpp
// ============================================================
//
// OBJECTIF :
// Creer un programme qui simule l'affichage d'un ticker
// boursier simplifie, comme on en voit sur les terminaux
// de trading haute frequence.
//
// Le programme doit :
// 1. Stocker les infos d'un actif (symbole, prix, volume, statut)
// 2. Afficher un resume formate du ticker
// 3. Calculer la valeur totale (prix * volume)
// 4. Afficher les tailles memoire de chaque variable
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Donnees du ticker
    string symbole = "AAPL";
    double prix = 178.72;
    int volume = 1500000;
    bool est_actif = true;
    double variation = -2.34;     // Variation en pourcentage

    // Calcul de la valeur totale echangee
    double valeur_totale = prix * volume;

    // Affichage du ticker
    cout << "╔══════════════════════════════════════╗" << endl;
    cout << "║        TERMINAL DE TRADING           ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║  Symbole    : " << symbole << "                    ║" << endl;
    cout << "║  Prix       : $" << prix << "                ║" << endl;
    cout << "║  Volume     : " << volume << "             ║" << endl;
    cout << "║  Variation  : " << variation << "%               ║" << endl;
    cout << "║  Statut     : " << (est_actif ? "ACTIF" : "INACTIF") << "                  ║" << endl;
    cout << "╠══════════════════════════════════════╣" << endl;
    cout << "║  Valeur totale : $" << valeur_totale << "      ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;

    cout << endl;

    // Empreinte memoire -- important en HFT ou chaque byte compte
    cout << "--- Empreinte memoire ---" << endl;
    cout << "symbole (string) : " << sizeof(symbole) << " bytes (objet)" << endl;
    cout << "prix    (double) : " << sizeof(prix) << " bytes" << endl;
    cout << "volume  (int)    : " << sizeof(volume) << " bytes" << endl;
    cout << "est_actif (bool) : " << sizeof(est_actif) << " byte" << endl;
    cout << "variation(double): " << sizeof(variation) << " bytes" << endl;
    cout << "TOTAL (approx)   : "
         << sizeof(symbole) + sizeof(prix) + sizeof(volume)
            + sizeof(est_actif) + sizeof(variation)
         << " bytes" << endl;

    return 0;
}
