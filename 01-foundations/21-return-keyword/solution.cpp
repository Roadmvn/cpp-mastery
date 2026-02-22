// ============================================================
// SOLUTION : Le Mot-Cle Return
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// Prototypes
double apply_discount(double price, double discount_percent);
string grade(int score);
void print_trade(string symbol, int qty, double price);

int main() {
    // PARTIE 1 : Early return
    cout << "--- Discounts ---" << endl;
    cout << "100 - 20% = " << apply_discount(100, 20) << endl;
    cout << "-50 - 10% = " << apply_discount(-50, 10) << endl;
    cout << "100 - 150% = " << apply_discount(100, 150) << endl;
    cout << "250 - 0% = " << apply_discount(250, 0) << endl;

    // PARTIE 2 : Retour conditionnel
    cout << "\n--- Grades ---" << endl;
    int scores[] = {95, 82, 72, 65, 45, -5, 110};
    for (int s : scores) {
        cout << "Score " << s << " -> " << grade(s) << endl;
    }

    // PARTIE 3 : Void avec early return
    cout << "\n--- Trades ---" << endl;
    print_trade("AAPL", 100, 178.50);
    print_trade("", 100, 178.50);
    print_trade("AAPL", -5, 178.50);
    print_trade("TSLA", 50, 0);
    print_trade("GOOG", 200, 142.25);

    return 0;
}

// Definitions

double apply_discount(double price, double discount_percent) {
    if (price <= 0) return 0;
    if (discount_percent < 0 || discount_percent > 100) return price;
    return price * (1.0 - discount_percent / 100.0);
}

string grade(int score) {
    if (score < 0 || score > 100) return "Invalide";
    if (score >= 90) return "A";
    if (score >= 80) return "B";
    if (score >= 70) return "C";
    if (score >= 60) return "D";
    return "F";
}

void print_trade(string symbol, int qty, double price) {
    if (symbol.empty()) {
        cout << "Erreur: symbol manquant" << endl;
        return;
    }
    if (qty <= 0) {
        cout << "Erreur: quantite invalide (" << qty << ")" << endl;
        return;
    }
    if (price <= 0) {
        cout << "Erreur: prix invalide ($" << price << ")" << endl;
        return;
    }
    cout << "TRADE: " << symbol << " x" << qty
         << " @ $" << price << " = $" << (qty * price) << endl;
}
