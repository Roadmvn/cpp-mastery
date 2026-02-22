// ============================================================
// CHALLENGE HFT : Bibliotheque de calculs financiers
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// Fonctions essentielles pour un systeme de trading :
// - Spread : difference entre le meilleur ask et le meilleur bid
// - Mid-price : point milieu entre bid et ask
// - VWAP : Volume Weighted Average Price
//
// Ces calculs sont la base de tout algo de market making.
//
// ============================================================

#include <iostream>
#include <iomanip>
using namespace std;

// --- Prototypes ---
double spread(double bid, double ask);
double mid_price(double bid, double ask);
double spread_bps(double bid, double ask);
double vwap(double prices[], double volumes[], int size);
void print_market_data(string symbol, double bid, double ask);

int main() {
    cout << fixed << setprecision(4);

    cout << "========================================" << endl;
    cout << "  HFT Trading Calculations Library" << endl;
    cout << "========================================" << endl;

    // --- Test avec AAPL ---
    double aapl_bid = 178.4500;
    double aapl_ask = 178.4800;
    print_market_data("AAPL", aapl_bid, aapl_ask);

    // --- Test avec TSLA (spread plus large) ---
    double tsla_bid = 245.1000;
    double tsla_ask = 245.3500;
    print_market_data("TSLA", tsla_bid, tsla_ask);

    cout << "\n--- VWAP Calculation ---" << endl;

    // Trades recents
    double prices[]  = {178.45, 178.48, 178.42, 178.50, 178.47, 178.44, 178.49};
    double volumes[] = {500,    1200,   300,    2000,   800,    150,    1500};
    int nb_trades = 7;

    double calculated_vwap = vwap(prices, volumes, nb_trades);
    cout << "VWAP (" << nb_trades << " trades) : $" << calculated_vwap << endl;

    // Comparer le dernier prix au VWAP
    double last_price = prices[nb_trades - 1];
    cout << "Last price           : $" << last_price << endl;
    if (last_price > calculated_vwap) {
        cout << "Signal : Prix AU-DESSUS du VWAP (momentum haussier)" << endl;
    } else {
        cout << "Signal : Prix EN-DESSOUS du VWAP (momentum baissier)" << endl;
    }

    cout << "========================================" << endl;

    return 0;
}

// --- Definitions ---

double spread(double bid, double ask) {
    return ask - bid;
}

double mid_price(double bid, double ask) {
    return (bid + ask) / 2.0;
}

double spread_bps(double bid, double ask) {
    // Spread en basis points (1 bps = 0.01%)
    double mid = mid_price(bid, ask);
    return (spread(bid, ask) / mid) * 10000.0;
}

double vwap(double prices[], double volumes[], int size) {
    double sum_pv = 0.0;
    double sum_v = 0.0;

    for (int i = 0; i < size; i++) {
        sum_pv += prices[i] * volumes[i];
        sum_v += volumes[i];
    }

    if (sum_v == 0) return 0.0;
    return sum_pv / sum_v;
}

void print_market_data(string symbol, double bid, double ask) {
    cout << "\n--- " << symbol << " ---" << endl;
    cout << "  Bid       : $" << bid << endl;
    cout << "  Ask       : $" << ask << endl;
    cout << "  Spread    : $" << spread(bid, ask) << endl;
    cout << "  Spread    : " << spread_bps(bid, ask) << " bps" << endl;
    cout << "  Mid-price : $" << mid_price(bid, ask) << endl;
}
