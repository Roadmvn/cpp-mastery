// ============================================================
// CHALLENGE HFT : Parser un message FIX simplifie
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// Le protocole FIX (Financial Information eXchange) est LE standard
// de communication en finance electronique. Les messages FIX
// sont des paires tag=valeur separees par un delimiteur (ici '|').
//
// Format : "tag=valeur|tag=valeur|tag=valeur|"
//
// Tags courants :
//   8  = Version du protocole (BeginString)
//   35 = Type de message (MsgType) -- D = New Order Single
//   55 = Symbol (ticker de l'instrument)
//   44 = Price (prix)
//   38 = OrderQty (quantite)
//   54 = Side (1 = Buy, 2 = Sell)
//
// OBJECTIF :
// Parser le message FIX ci-dessous et extraire chaque champ.
// Afficher un resume lisible de l'ordre.
//
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    string fix_message = "8=FIX.4.2|35=D|49=TRADER1|55=AAPL|54=1|44=150.25|38=1000|";

    cout << "========================================" << endl;
    cout << "  FIX Message Parser" << endl;
    cout << "========================================" << endl;
    cout << "Raw : " << fix_message << endl;
    cout << "----------------------------------------" << endl;

    // Parse chaque paire tag=valeur
    string msg = fix_message;
    size_t pos = 0;
    string delimiter = "|";

    string version, msg_type, sender, symbol, side, price, qty;

    while ((pos = msg.find(delimiter)) != string::npos) {
        string field = msg.substr(0, pos);

        // Trouver le '=' dans le champ
        size_t eq = field.find("=");
        if (eq != string::npos) {
            string tag = field.substr(0, eq);
            string value = field.substr(eq + 1);

            if (tag == "8")  version = value;
            else if (tag == "35") msg_type = value;
            else if (tag == "49") sender = value;
            else if (tag == "55") symbol = value;
            else if (tag == "54") side = value;
            else if (tag == "44") price = value;
            else if (tag == "38") qty = value;
        }

        msg.erase(0, pos + delimiter.length());
    }

    // Affichage structure
    cout << "  Protocol  : " << version << endl;
    cout << "  Msg Type  : " << msg_type;
    if (msg_type == "D") cout << " (New Order Single)";
    cout << endl;
    cout << "  Sender    : " << sender << endl;
    cout << "  Symbol    : " << symbol << endl;
    cout << "  Side      : " << (side == "1" ? "BUY" : "SELL") << endl;
    cout << "  Price     : $" << price << endl;
    cout << "  Quantity  : " << qty << endl;
    cout << "----------------------------------------" << endl;

    // Resume de l'ordre
    cout << "\n>> ORDRE : " << (side == "1" ? "ACHETER" : "VENDRE")
         << " " << qty << " x " << symbol
         << " @ $" << price << endl;

    return 0;
}
