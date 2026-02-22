// ============================================================
// Challenge HFT : Direction d'Ordre Selon Signaux
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
// Contexte : Ton systeme de trading recoit des signaux de
// plusieurs indicateurs. Tu dois determiner la direction
// (BUY/SELL/HOLD), la taille, et l'urgence en utilisant
// des ternaires pour un code compact et performant.
//
// Signaux :
//   - momentum : positif = haussier, negatif = baissier
//   - rsi      : < 30 = survendu (BUY), > 70 = surachete (SELL)
//   - volume   : > seuil = confirmation, sinon = pas de signal
//
// Sortie attendue :
//   === Order Decision Engine ===
//   Momentum : -1.25 (BEARISH)
//   RSI      : 28.5 (SURVENDU)
//   Volume   : 25000 (CONFIRME)
//
//   Consensus momentum : SELL
//   Consensus RSI      : BUY
//   Conflit de signaux : OUI
//   Decision finale    : HOLD (signaux contradictoires)
//   Taille d'ordre     : 0 lots
// ============================================================

#include <iostream>
#include <string>
#include <cmath>

int main() {
    // Signaux d'entree
    double momentum = -1.25;
    double rsi = 28.5;
    int volume = 25000;
    int volume_seuil = 15000;
    int position_max = 200;

    std::cout << "=== Order Decision Engine ===" << std::endl;

    // Direction du momentum (ternaire simple)
    std::string momentum_dir = (momentum > 0) ? "BULLISH" : "BEARISH";
    std::cout << "Momentum : " << momentum
              << " (" << momentum_dir << ")" << std::endl;

    // Etat du RSI (ternaire imbrique a 1 niveau)
    std::string rsi_state = (rsi < 30) ? "SURVENDU"
                          : (rsi > 70) ? "SURACHETE"
                          :              "NEUTRE";
    std::cout << "RSI      : " << rsi
              << " (" << rsi_state << ")" << std::endl;

    // Confirmation par le volume
    std::string vol_status = (volume > volume_seuil) ? "CONFIRME" : "INSUFFISANT";
    std::cout << "Volume   : " << volume
              << " (" << vol_status << ")" << std::endl;
    std::cout << std::endl;

    // Consensus de chaque indicateur
    std::string sig_momentum = (momentum > 0.5) ? "BUY"
                             : (momentum < -0.5) ? "SELL"
                             :                     "NEUTRAL";

    std::string sig_rsi = (rsi < 30) ? "BUY"
                        : (rsi > 70) ? "SELL"
                        :              "NEUTRAL";

    std::cout << "Consensus momentum : " << sig_momentum << std::endl;
    std::cout << "Consensus RSI      : " << sig_rsi << std::endl;

    // Detection de conflit (un dit BUY, l'autre dit SELL)
    bool conflit = (sig_momentum == "BUY" && sig_rsi == "SELL")
                || (sig_momentum == "SELL" && sig_rsi == "BUY");

    std::cout << "Conflit de signaux : " << (conflit ? "OUI" : "NON") << std::endl;

    // Decision finale
    bool volume_ok = volume > volume_seuil;
    std::string decision;

    if (conflit || !volume_ok) {
        decision = "HOLD";
        std::string raison = conflit ? "signaux contradictoires" : "volume insuffisant";
        std::cout << "Decision finale    : HOLD (" << raison << ")" << std::endl;
    } else {
        // Les deux signaux sont alignes ou un est neutre
        decision = (sig_momentum == "BUY" || sig_rsi == "BUY") ? "BUY"
                 : (sig_momentum == "SELL" || sig_rsi == "SELL") ? "SELL"
                 :                                                 "HOLD";
        std::cout << "Decision finale    : " << decision << std::endl;
    }

    // Taille d'ordre basee sur la force du signal
    double signal_force = fabs(momentum) + fabs(rsi - 50.0) / 50.0;
    int taille = (decision == "HOLD") ? 0
               : (signal_force > 2.0) ? position_max
               : (signal_force > 1.0) ? position_max / 2
               :                         position_max / 4;

    std::cout << "Taille d'ordre     : " << taille << " lots" << std::endl;

    return 0;
}
