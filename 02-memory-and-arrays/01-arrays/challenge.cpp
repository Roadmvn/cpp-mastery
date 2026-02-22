// =============================================================
// Challenge HFT : Analyse de prix avec arrays
// =============================================================
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// =============================================================
// Contexte : Tu travailles sur un systeme de trading haute frequence.
// Tu recois 10 prix de marche (en centimes pour eviter les flottants).
// Tu dois calculer : moyenne, min, max et ecart-type simplifie.
//
// L'ecart-type simplifie = sqrt(moyenne des carres des ecarts a la moyenne)
// En finance, c'est la VOLATILITE : plus elle est haute, plus le marche bouge.
// =============================================================

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // 10 prix de marche successifs (en centimes d'euro)
    // Representent le prix d'un actif sur 10 ticks
    int prices[10] = {10023, 10045, 10012, 10078, 10056,
                      10034, 10089, 10021, 10067, 10043};

    int size = sizeof(prices) / sizeof(prices[0]);

    // --- Calcul de la moyenne ---
    long long somme = 0;
    for (int i = 0; i < size; i++) {
        somme += prices[i];
    }
    double moyenne = static_cast<double>(somme) / size;

    // --- Recherche du min et max ---
    int minPrix = prices[0];
    int maxPrix = prices[0];
    for (int i = 1; i < size; i++) {
        if (prices[i] < minPrix) minPrix = prices[i];
        if (prices[i] > maxPrix) maxPrix = prices[i];
    }

    // --- Calcul de l'ecart-type (volatilite) ---
    // Formule : sigma = sqrt( (1/N) * sum((xi - moyenne)^2) )
    double sommeCarresEcarts = 0.0;
    for (int i = 0; i < size; i++) {
        double ecart = prices[i] - moyenne;
        sommeCarresEcarts += ecart * ecart;
    }
    double ecartType = sqrt(sommeCarresEcarts / size);

    // --- Calcul du spread (max - min) ---
    int spread = maxPrix - minPrix;

    // --- Affichage des resultats ---
    cout << "=== Analyse de marche (10 ticks) ===" << endl;
    cout << "Moyenne    : " << moyenne / 100.0 << " EUR" << endl;
    cout << "Min        : " << minPrix / 100.0 << " EUR" << endl;
    cout << "Max        : " << maxPrix / 100.0 << " EUR" << endl;
    cout << "Spread     : " << spread / 100.0 << " EUR" << endl;
    cout << "Volatilite : " << ecartType / 100.0 << " EUR (ecart-type)" << endl;

    // --- Interpretation rapide ---
    cout << "\n--- Interpretation ---" << endl;
    if (ecartType > 25) {
        cout << "Marche VOLATILE : ecart-type > 0.25 EUR" << endl;
        cout << "-> Opportunites d'arbitrage potentielles" << endl;
    } else {
        cout << "Marche STABLE : ecart-type <= 0.25 EUR" << endl;
        cout << "-> Spread tight, conditions normales" << endl;
    }

    // --- Affichage du graphique ASCII des prix ---
    cout << "\n--- Prix (graphe ASCII) ---" << endl;
    for (int i = 0; i < size; i++) {
        int barLen = (prices[i] - minPrix) / 2;
        cout << "Tick " << i << " [" << prices[i] << "] ";
        for (int j = 0; j < barLen; j++) cout << "#";
        if (prices[i] == minPrix) cout << "|MIN";
        if (prices[i] == maxPrix) cout << "|MAX";
        cout << endl;
    }

    return 0;
}
