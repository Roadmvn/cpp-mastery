// ============================================================
// Challenge HFT : Signal d'Achat/Vente Base sur Prix et Volume
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
// Contexte : Tu codes un systeme de signaux de trading simple.
// Le systeme analyse le prix actuel par rapport a la moyenne
// mobile et le volume par rapport au volume moyen pour generer
// des signaux d'achat ou de vente.
//
// Regles du systeme :
//   1. Volume doit etre > volume_moyen * 1.5 (volume eleve)
//   2. Si prix < moyenne_mobile * 0.98 -> STRONG BUY
//   3. Si prix < moyenne_mobile        -> WEAK BUY
//   4. Si prix > moyenne_mobile * 1.02 -> STRONG SELL
//   5. Si prix > moyenne_mobile        -> WEAK SELL
//   6. Sinon -> HOLD
//   7. Si volume insuffisant -> NO SIGNAL (peu importe le prix)
//
// Sortie attendue :
//   === Trading Signal Engine ===
//   Instrument : NVDA
//   Prix       : 875.4 | MA(20) : 892.0
//   Volume     : 18500000 | Avg Vol : 12000000
//   Ecart prix : -1.86 %
//   Volume     : ELEVE (x1.54)
//   Signal     : STRONG BUY
//   Action     : Acheter 112 actions (budget: 100000 USD)
// ============================================================

#include <iostream>
#include <string>
#include <cmath>

int main() {
    // Donnees de marche (normalement recues en temps reel)
    std::string instrument = "NVDA";
    double prix_actuel    = 875.40;
    double moyenne_mobile = 892.00;   // MA(20)
    long volume_actuel    = 18500000;
    long volume_moyen     = 12000000;
    double budget         = 100000.0;

    std::cout << "=== Trading Signal Engine ===" << std::endl;
    std::cout << "Instrument : " << instrument << std::endl;
    std::cout << "Prix       : " << prix_actuel
              << " | MA(20) : " << moyenne_mobile << std::endl;
    std::cout << "Volume     : " << volume_actuel
              << " | Avg Vol : " << volume_moyen << std::endl;

    // Calcul de l'ecart en pourcentage
    double ecart_pct = ((prix_actuel - moyenne_mobile) / moyenne_mobile) * 100;
    std::cout << "Ecart prix : " << ecart_pct << " %" << std::endl;

    // Ratio de volume
    double volume_ratio = static_cast<double>(volume_actuel) / volume_moyen;

    // Analyse du volume
    bool volume_eleve = volume_ratio > 1.5;
    if (volume_eleve) {
        std::cout << "Volume     : ELEVE (x"
                  << round(volume_ratio * 100) / 100 << ")" << std::endl;
    } else {
        std::cout << "Volume     : FAIBLE (x"
                  << round(volume_ratio * 100) / 100 << ")" << std::endl;
    }

    // Generation du signal
    std::string signal;
    std::string action;

    if (!volume_eleve) {
        signal = "NO SIGNAL";
        action = "Attendre un volume suffisant";
    } else {
        if (prix_actuel < moyenne_mobile * 0.98) {
            signal = "STRONG BUY";
            int qty = static_cast<int>(budget / prix_actuel);
            action = "Acheter " + std::to_string(qty) + " actions (budget: "
                   + std::to_string(static_cast<int>(budget)) + " USD)";
        } else if (prix_actuel < moyenne_mobile) {
            signal = "WEAK BUY";
            int qty = static_cast<int>((budget * 0.5) / prix_actuel);
            action = "Acheter " + std::to_string(qty) + " actions (demi-position)";
        } else if (prix_actuel > moyenne_mobile * 1.02) {
            signal = "STRONG SELL";
            action = "Vendre toute la position";
        } else if (prix_actuel > moyenne_mobile) {
            signal = "WEAK SELL";
            action = "Reduire la position de 50%";
        } else {
            signal = "HOLD";
            action = "Maintenir la position actuelle";
        }
    }

    std::cout << "Signal     : " << signal << std::endl;
    std::cout << "Action     : " << action << std::endl;

    return 0;
}
