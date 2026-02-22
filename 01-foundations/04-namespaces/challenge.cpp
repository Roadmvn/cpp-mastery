// ============================================================
//  Chapitre 04 -- Challenge : Mini Framework de Trading
//  Compile avec : g++ -std=c++11 -o challenge challenge.cpp
// ============================================================
//
//  OBJECTIF :
//  Creer un mini framework de trading organise en namespaces.
//  Le programme simule un flux complet :
//    1. Recevoir un prix de marche
//    2. Creer un ordre d'achat/vente
//    3. Verifier le risque
//    4. Afficher le resultat
//
//  STRUCTURE DES NAMESPACES :
//
//  trading::market  -- Donnees de marche (prix, volume)
//  trading::order   -- Gestion des ordres (buy, sell)
//  trading::risk    -- Verification de risque
//
//  Chaque namespace doit avoir au moins 2 fonctions.
//
//  EXEMPLE DE SORTIE ATTENDUE :
//
//  === TRADING FRAMEWORK ===
//  [MARKET] BTC/USD : 43250.50 USD | Volume : 1500 lots
//  [MARKET] Spread : 0.15 USD
//  [RISK] Verification ordre BUY de 43250.50 USD...
//  [RISK] Montant OK (< 100000 USD)
//  [RISK] Position autorisee (< 10 lots)
//  [ORDER] BUY 2 lots de BTC/USD a 43250.50 USD
//  [ORDER] ID: 100001 | Status: FILLED
//  === FIN DU FLUX ===
//
// ============================================================

#include <iostream>
#include <string>

// -- A TOI DE JOUER --
// Cree les namespaces trading::market, trading::order et trading::risk
// puis utilise-les dans le main()

int main() {
    std::cout << "=== TRADING FRAMEWORK ===" << std::endl;

    // Etape 1 : Recuperer les donnees de marche
    // trading::market::getPrice(...)
    // trading::market::getVolume(...)

    // Etape 2 : Verifier le risque avant de passer l'ordre
    // trading::risk::checkAmount(...)
    // trading::risk::checkPosition(...)

    // Etape 3 : Passer l'ordre
    // trading::order::buy(...)
    // trading::order::getStatus(...)

    std::cout << "=== FIN DU FLUX ===" << std::endl;

    return 0;
}
