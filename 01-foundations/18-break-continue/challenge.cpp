// ============================================================
// CHALLENGE HFT : Filtre de trades
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// Tu recois un flux de trades. Tu dois les filtrer selon des regles :
// - Skip les trades avec un volume < 100 (bruit de marche)
// - Arrete le traitement si un prix depasse $200 (circuit breaker)
// - Calcule le VWAP (Volume Weighted Average Price) des trades valides
//
// VWAP = somme(prix * volume) / somme(volumes)
//
// ============================================================

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Donnees simulees : {prix, volume}
    double trades[][2] = {
        {150.25, 500},
        {150.30, 50},     // Volume trop faible -> skip
        {150.50, 1200},
        {150.45, 30},     // Volume trop faible -> skip
        {151.00, 800},
        {150.90, 2000},
        {151.25, 150},
        {150.80, 75},     // Volume trop faible -> skip
        {155.00, 3000},
        {160.50, 1500},
        {175.00, 500},
        {201.00, 100},    // Prix > 200 -> circuit breaker !
        {180.00, 2000},   // Jamais traite
        {185.00, 1000},   // Jamais traite
    };
    int nb_trades = 14;
    int min_volume = 100;
    double price_limit = 200.0;

    cout << "========================================" << endl;
    cout << "  Trade Filter & VWAP Calculator" << endl;
    cout << "========================================" << endl;
    cout << "Min volume   : " << min_volume << endl;
    cout << "Price limit  : $" << price_limit << " (circuit breaker)" << endl;
    cout << "----------------------------------------" << endl;

    double sum_pv = 0;      // Somme des (prix * volume)
    double sum_vol = 0;     // Somme des volumes
    int trades_traites = 0;
    int trades_skip = 0;
    bool circuit_break = false;

    cout << fixed << setprecision(2);

    for (int i = 0; i < nb_trades; i++) {
        double price = trades[i][0];
        double volume = trades[i][1];

        // Circuit breaker : prix depasse le seuil
        if (price > price_limit) {
            cout << "[!] CIRCUIT BREAKER @ $" << price
                 << " (limite: $" << price_limit << ")" << endl;
            circuit_break = true;
            break;
        }

        // Skip les petits volumes
        if (volume < min_volume) {
            trades_skip++;
            continue;
        }

        // Trade valide
        sum_pv += price * volume;
        sum_vol += volume;
        trades_traites++;

        cout << "  [TRADE] $" << price << " x " << (int)volume
             << " = $" << (price * volume) << endl;
    }

    cout << "----------------------------------------" << endl;

    if (sum_vol > 0) {
        double vwap = sum_pv / sum_vol;
        cout << "  VWAP            : $" << vwap << endl;
    }

    cout << "  Trades valides  : " << trades_traites << endl;
    cout << "  Trades skip     : " << trades_skip << endl;
    cout << "  Volume total    : " << (int)sum_vol << endl;
    cout << "  Valeur totale   : $" << sum_pv << endl;

    if (circuit_break) {
        cout << "\n  [!] Trading suspendu -- prix anormal detecte" << endl;
    }

    cout << "========================================" << endl;

    return 0;
}
