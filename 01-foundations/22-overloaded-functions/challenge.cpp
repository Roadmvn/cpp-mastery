// ============================================================
// CHALLENGE HFT : Fonction format() pour market data
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// En HFT, tu affiches des donnees de marche dans differents formats.
// Une seule fonction format() doit gerer : prix, volumes, timestamps,
// pourcentages, et ordres complets.
//
// La surcharge permet une API propre et uniforme.
//
// ============================================================

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// --- Format un prix (4 decimales, prefixe $) ---
string format(double price) {
    ostringstream oss;
    oss << "$" << fixed << setprecision(4) << price;
    return oss.str();
}

// --- Format un volume (separateur de milliers) ---
string format(int volume) {
    string s = to_string(volume);
    string result = "";
    int count = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (count > 0 && count % 3 == 0) {
            result = "," + result;
        }
        result = s[i] + result;
        count++;
    }
    return result;
}

// --- Format un pourcentage ---
string format(double value, string suffix) {
    ostringstream oss;
    oss << fixed << setprecision(2) << value << suffix;
    return oss.str();
}

// --- Format un ordre complet ---
string format(string symbol, string side, int qty, double price) {
    ostringstream oss;
    oss << "[" << side << "] " << symbol << " x" << format(qty)
        << " @ " << format(price);
    return oss.str();
}

// --- Format un spread (bid/ask) ---
string format(double bid, double ask) {
    ostringstream oss;
    double sp = ask - bid;
    double mid = (bid + ask) / 2.0;
    double bps = (sp / mid) * 10000.0;
    oss << format(bid) << " / " << format(ask)
        << " (spread: " << format(bps, " bps") << ")";
    return oss.str();
}

int main() {
    cout << "========================================" << endl;
    cout << "  Market Data Formatter" << endl;
    cout << "========================================" << endl;

    // Prix
    cout << "\n--- Prix ---" << endl;
    cout << "AAPL : " << format(178.4523) << endl;
    cout << "TSLA : " << format(245.1000) << endl;
    cout << "BTC  : " << format(67542.8750) << endl;

    // Volumes
    cout << "\n--- Volumes ---" << endl;
    cout << "AAPL : " << format(1500000) << " shares" << endl;
    cout << "TSLA : " << format(850000) << " shares" << endl;
    cout << "SPY  : " << format(95000000) << " shares" << endl;

    // Pourcentages
    cout << "\n--- Variations ---" << endl;
    cout << "AAPL : " << format(2.45, "%") << endl;
    cout << "TSLA : " << format(-1.82, "%") << endl;
    cout << "GOOG : " << format(0.15, "%") << endl;

    // Ordres
    cout << "\n--- Ordres ---" << endl;
    cout << format("AAPL", "BUY", 1000, 178.45) << endl;
    cout << format("TSLA", "SELL", 500, 245.10) << endl;
    cout << format("GOOG", "BUY", 2500, 142.30) << endl;

    // Spreads
    cout << "\n--- Spreads ---" << endl;
    cout << "AAPL : " << format(178.4500, 178.4800) << endl;
    cout << "TSLA : " << format(245.1000, 245.3500) << endl;
    cout << "SPY  : " << format(450.2000, 450.2100) << endl;

    cout << "\n========================================" << endl;
    cout << "Meme nom 'format()', 5 comportements." << endl;
    cout << "C'est la puissance de l'overloading." << endl;
    cout << "========================================" << endl;

    return 0;
}
