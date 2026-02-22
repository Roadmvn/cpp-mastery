// =============================================================
// Challenge HFT : Moving Average sur un array de prix
// =============================================================
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// =============================================================
// Contexte : Le Moving Average (moyenne mobile) est un indicateur
// fondamental en trading. Le SMA (Simple Moving Average) sur une
// fenetre de N periodes est la moyenne des N derniers prix.
//
// Pour chaque prix a l'index i (ou i >= window-1), on calcule :
//   SMA[i] = (prices[i] + prices[i-1] + ... + prices[i-window+1]) / window
//
// En HFT, on utilise des moyennes mobiles courtes (5-20 ticks)
// pour detecter les micro-tendances et generer des signaux de trading.
// =============================================================

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // 20 prix de marche successifs (en centimes)
    double prices[] = {
        100.50, 100.55, 100.48, 100.62, 100.58,
        100.70, 100.65, 100.72, 100.80, 100.75,
        100.68, 100.71, 100.85, 100.90, 100.82,
        100.95, 101.00, 100.92, 101.05, 101.10
    };
    int size = sizeof(prices) / sizeof(prices[0]);
    int window = 5; // Fenetre de 5 periodes

    // --- Calcul du SMA-5 ---
    double sma[20];
    int smaCount = 0;

    for (int i = window - 1; i < size; i++) {
        double somme = 0.0;
        for (int j = i - window + 1; j <= i; j++) {
            somme += prices[j];
        }
        sma[smaCount] = somme / window;
        smaCount++;
    }

    // --- Affichage des resultats ---
    cout << fixed << setprecision(2);
    cout << "=== Moving Average (SMA-" << window << ") ===" << endl;
    cout << endl;
    cout << "Tick | Prix    | SMA-5   | Signal" << endl;
    cout << "-----|---------|---------|--------" << endl;

    for (int i = 0; i < size; i++) {
        cout << setw(4) << i << " | " << setw(7) << prices[i] << " | ";

        if (i >= window - 1) {
            int smaIdx = i - (window - 1);
            cout << setw(7) << sma[smaIdx] << " | ";

            // Signal : prix au dessus ou en dessous de la SMA
            if (prices[i] > sma[smaIdx]) {
                cout << "ABOVE";
            } else if (prices[i] < sma[smaIdx]) {
                cout << "BELOW";
            } else {
                cout << "EQUAL";
            }
        } else {
            cout << "   -    | -";
        }
        cout << endl;
    }

    // --- Detection de croisements (crossovers) ---
    // Un crossover se produit quand le prix passe au dessus ou en dessous de la SMA
    cout << "\n=== Crossovers detectes ===" << endl;
    for (int i = 1; i < smaCount; i++) {
        int priceIdx = i + (window - 1);
        int prevPriceIdx = priceIdx - 1;

        bool prevAbove = prices[prevPriceIdx] > sma[i - 1];
        bool currAbove = prices[priceIdx] > sma[i];

        if (!prevAbove && currAbove) {
            cout << "Tick " << priceIdx << " : Crossover HAUSSIER (prix passe au dessus de SMA)" << endl;
        } else if (prevAbove && !currAbove) {
            cout << "Tick " << priceIdx << " : Crossover BAISSIER (prix passe en dessous de SMA)" << endl;
        }
    }

    // --- Statistiques de la SMA ---
    double smaMin = sma[0], smaMax = sma[0];
    for (int i = 1; i < smaCount; i++) {
        if (sma[i] < smaMin) smaMin = sma[i];
        if (sma[i] > smaMax) smaMax = sma[i];
    }

    cout << "\n=== Statistiques SMA ===" << endl;
    cout << "SMA min : " << smaMin << endl;
    cout << "SMA max : " << smaMax << endl;
    cout << "Range   : " << smaMax - smaMin << endl;

    // --- Graphe ASCII ---
    cout << "\n=== Graphe prix vs SMA ===" << endl;
    double globalMin = prices[0];
    double globalMax = prices[0];
    for (int i = 0; i < size; i++) {
        if (prices[i] < globalMin) globalMin = prices[i];
        if (prices[i] > globalMax) globalMax = prices[i];
    }

    for (int i = window - 1; i < size; i++) {
        int smaIdx = i - (window - 1);
        int pricePosRaw = static_cast<int>((prices[i] - globalMin) / (globalMax - globalMin) * 40);
        int smaPosRaw = static_cast<int>((sma[smaIdx] - globalMin) / (globalMax - globalMin) * 40);
        int pricePos = (pricePosRaw < 0) ? 0 : (pricePosRaw > 40) ? 40 : pricePosRaw;
        int smaPos = (smaPosRaw < 0) ? 0 : (smaPosRaw > 40) ? 40 : smaPosRaw;

        cout << setw(2) << i << " ";
        for (int c = 0; c <= 40; c++) {
            if (c == pricePos && c == smaPos) cout << "X";
            else if (c == pricePos) cout << "*";
            else if (c == smaPos) cout << "o";
            else cout << ".";
        }
        cout << endl;
    }
    cout << "   * = prix, o = SMA, X = croisement" << endl;

    return 0;
}
