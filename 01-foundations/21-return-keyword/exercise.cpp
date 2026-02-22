// ============================================================
// EXERCICE : Le Mot-Cle Return
// Fichier : exercise.cpp
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// --------------------------------------------------------
// PARTIE 1 : Early return
// --------------------------------------------------------
// TODO : Ecris une fonction qui calcule la reduction sur un prix.
//
// double apply_discount(double price, double discount_percent)
//
// Regles :
// - Si price <= 0, retourne 0 (early return)
// - Si discount_percent < 0 ou > 100, retourne price inchange
// - Sinon, retourne le prix apres reduction

// Ecris ton prototype et ta definition ici :



// --------------------------------------------------------
// PARTIE 2 : Retour conditionnel
// --------------------------------------------------------
// TODO : Ecris une fonction qui classifie un score d'examen.
//
// string grade(int score)
//
// - 90-100 : "A"
// - 80-89  : "B"
// - 70-79  : "C"
// - 60-69  : "D"
// - < 60   : "F"
// - < 0 ou > 100 : "Invalide"

// Ecris ton prototype et ta definition ici :



// --------------------------------------------------------
// PARTIE 3 : Fonction void avec early return
// --------------------------------------------------------
// TODO : Ecris une fonction void qui affiche les details d'un trade.
//
// void print_trade(string symbol, int qty, double price)
//
// - Si symbol est vide, affiche "Erreur: symbol manquant" et return
// - Si qty <= 0, affiche "Erreur: quantite invalide" et return
// - Si price <= 0, affiche "Erreur: prix invalide" et return
// - Sinon affiche : "TRADE: [symbol] x[qty] @ $[price] = $[total]"

// Ecris ton prototype et ta definition ici :



int main() {
    // Decommente pour tester :

    // PARTIE 1
    // cout << apply_discount(100, 20) << endl;    // 80
    // cout << apply_discount(-50, 10) << endl;    // 0
    // cout << apply_discount(100, 150) << endl;   // 100

    // PARTIE 2
    // cout << grade(95) << endl;    // A
    // cout << grade(72) << endl;    // C
    // cout << grade(-5) << endl;    // Invalide

    // PARTIE 3
    // print_trade("AAPL", 100, 178.50);
    // print_trade("", 100, 178.50);
    // print_trade("AAPL", -5, 178.50);

    return 0;
}
