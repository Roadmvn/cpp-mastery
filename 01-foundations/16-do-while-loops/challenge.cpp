// ============================================================
// CHALLENGE HFT : Menu de trading interactif
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// Interface CLI simplifiee d'un terminal de trading.
// L'utilisateur peut acheter, vendre, consulter son portfolio
// et quitter. Le programme maintient un solde cash et des
// positions en actions.
//
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Etat du compte
    double cash = 100000.00;      // 100k de capital initial
    int shares_aapl = 0;
    int shares_tsla = 0;
    double price_aapl = 178.50;   // Prix simule
    double price_tsla = 245.30;

    int choix;

    cout << "========================================" << endl;
    cout << "  Terminal de Trading v1.0" << endl;
    cout << "  Capital initial : $" << cash << endl;
    cout << "========================================" << endl;

    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Acheter (Buy)" << endl;
        cout << "2. Vendre (Sell)" << endl;
        cout << "3. Portfolio" << endl;
        cout << "4. Quitter" << endl;
        cout << "Choix : ";
        cin >> choix;

        if (choix == 1) {
            // --- ACHAT ---
            int ticker;
            int qty;
            cout << "\n  Quel ticker ? (1=AAPL $" << price_aapl
                 << " | 2=TSLA $" << price_tsla << ") : ";
            cin >> ticker;
            cout << "  Quantite : ";
            cin >> qty;

            double cost = 0;
            if (ticker == 1) cost = qty * price_aapl;
            else if (ticker == 2) cost = qty * price_tsla;
            else { cout << "  Ticker invalide." << endl; continue; }

            if (qty <= 0) {
                cout << "  Quantite invalide." << endl;
            } else if (cost > cash) {
                cout << "  Fonds insuffisants. Cout : $" << cost
                     << " | Cash : $" << cash << endl;
            } else {
                cash -= cost;
                if (ticker == 1) shares_aapl += qty;
                else shares_tsla += qty;
                cout << "  [FILL] Achat de " << qty << " actions a $"
                     << (ticker == 1 ? price_aapl : price_tsla)
                     << " | Total : $" << cost << endl;
            }

        } else if (choix == 2) {
            // --- VENTE ---
            int ticker;
            int qty;
            cout << "\n  Quel ticker ? (1=AAPL [" << shares_aapl
                 << "] | 2=TSLA [" << shares_tsla << "]) : ";
            cin >> ticker;
            cout << "  Quantite : ";
            cin >> qty;

            if (qty <= 0) {
                cout << "  Quantite invalide." << endl;
            } else if (ticker == 1 && qty > shares_aapl) {
                cout << "  Position insuffisante (AAPL : " << shares_aapl << ")" << endl;
            } else if (ticker == 2 && qty > shares_tsla) {
                cout << "  Position insuffisante (TSLA : " << shares_tsla << ")" << endl;
            } else if (ticker == 1) {
                double revenue = qty * price_aapl;
                shares_aapl -= qty;
                cash += revenue;
                cout << "  [FILL] Vente de " << qty << " AAPL | Revenue : $" << revenue << endl;
            } else if (ticker == 2) {
                double revenue = qty * price_tsla;
                shares_tsla -= qty;
                cash += revenue;
                cout << "  [FILL] Vente de " << qty << " TSLA | Revenue : $" << revenue << endl;
            } else {
                cout << "  Ticker invalide." << endl;
            }

        } else if (choix == 3) {
            // --- PORTFOLIO ---
            double value_aapl = shares_aapl * price_aapl;
            double value_tsla = shares_tsla * price_tsla;
            double total = cash + value_aapl + value_tsla;

            cout << "\n  ======== PORTFOLIO ========" << endl;
            cout << "  Cash       : $" << cash << endl;
            cout << "  AAPL       : " << shares_aapl << " x $"
                 << price_aapl << " = $" << value_aapl << endl;
            cout << "  TSLA       : " << shares_tsla << " x $"
                 << price_tsla << " = $" << value_tsla << endl;
            cout << "  ----------------------------" << endl;
            cout << "  Total      : $" << total << endl;
            cout << "  P&L        : $" << (total - 100000.0)
                 << " (" << ((total - 100000.0) / 100000.0 * 100) << "%)" << endl;
            cout << "  ============================" << endl;

        } else if (choix == 4) {
            double total = cash + shares_aapl * price_aapl + shares_tsla * price_tsla;
            cout << "\n  Session terminee." << endl;
            cout << "  P&L final : $" << (total - 100000.0) << endl;
            cout << "  Au revoir, trader." << endl;

        } else {
            cout << "  Choix invalide." << endl;
        }

    } while (choix != 4);

    return 0;
}
