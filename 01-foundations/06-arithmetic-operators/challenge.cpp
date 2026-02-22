// ============================================================
// Challenge HFT : Calculateur de P&L d'un Trade
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
// Contexte : Tu es trader algo. Tu dois calculer le profit ou
// la perte d'un trade en tenant compte des frais de bourse.
//
// Formules :
//   P&L brut  = (prix_sortie - prix_entree) * quantite
//   Frais     = (prix_entree + prix_sortie) * quantite * taux_frais
//   P&L net   = P&L brut - frais
//   Rendement = (P&L net / investissement_initial) * 100
//
// Sortie attendue :
//   === Trade Report ===
//   Instrument  : AAPL
//   Direction   : LONG
//   Entree      : 178.5 x 250
//   Sortie      : 182.3 x 250
//   P&L brut    : 950 USD
//   Frais       : 90.2 USD
//   P&L net     : 859.8 USD
//   Rendement   : 1.92717 %
// ============================================================

#include <iostream>
#include <string>

int main() {
    // Parametres du trade
    std::string instrument = "AAPL";
    std::string direction  = "LONG";
    double entry_price = 178.50;
    double exit_price  = 182.30;
    int    quantity    = 250;
    double fee_rate   = 0.001;  // 0.1% par transaction (achat + vente)

    // Calcul du P&L brut
    double pnl_brut = (exit_price - entry_price) * quantity;

    // Calcul des frais totaux (frais a l'achat + frais a la vente)
    double frais = (entry_price + exit_price) * quantity * fee_rate;

    // P&L net apres frais
    double pnl_net = pnl_brut - frais;

    // Investissement initial (prix d'entree * quantite)
    double investissement = entry_price * quantity;

    // Rendement en pourcentage
    double rendement = (pnl_net / investissement) * 100;

    // Rapport
    std::cout << "=== Trade Report ===" << std::endl;
    std::cout << "Instrument  : " << instrument << std::endl;
    std::cout << "Direction   : " << direction << std::endl;
    std::cout << "Entree      : " << entry_price << " x " << quantity << std::endl;
    std::cout << "Sortie      : " << exit_price << " x " << quantity << std::endl;
    std::cout << "P&L brut    : " << pnl_brut << " USD" << std::endl;
    std::cout << "Frais       : " << frais << " USD" << std::endl;
    std::cout << "P&L net     : " << pnl_net << " USD" << std::endl;
    std::cout << "Rendement   : " << rendement << " %" << std::endl;

    // Bonus : afficher si le trade est gagnant ou perdant
    // On utilise juste le signe du P&L net
    if (pnl_net > 0) {
        std::cout << "Resultat    : GAGNANT" << std::endl;
    } else if (pnl_net < 0) {
        std::cout << "Resultat    : PERDANT" << std::endl;
    } else {
        std::cout << "Resultat    : BREAKEVEN" << std::endl;
    }

    return 0;
}
