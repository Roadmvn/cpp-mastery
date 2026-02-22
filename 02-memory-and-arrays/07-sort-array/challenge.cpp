// =============================================================
// Challenge HFT : Trier un Order Book
// =============================================================
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// =============================================================
// Contexte : Un order book contient les ordres d'achat (bids) et
// de vente (asks) pour un actif financier.
//
// Regles de tri :
// - Bids (achats) : tries par prix DECROISSANT (meilleur prix en haut)
// - Asks (ventes) : tries par prix CROISSANT (meilleur prix en haut)
// - A prix egal, l'ordre arrive EN PREMIER a priorite (FIFO)
//
// Le "spread" = meilleur ask - meilleur bid (ecart de marche)
// =============================================================

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Order {
    int id;
    double price;
    int quantity;
    int timestamp; // Plus petit = arrive plus tot
};

void printOrders(const Order orders[], int size, const char* label) {
    cout << label << endl;
    cout << "  ID   | Prix     | Qty  | Time" << endl;
    cout << "  -----|----------|------|-----" << endl;
    for (int i = 0; i < size; i++) {
        cout << "  " << setw(4) << orders[i].id << " | "
             << fixed << setprecision(2) << setw(8) << orders[i].price << " | "
             << setw(4) << orders[i].quantity << " | "
             << setw(4) << orders[i].timestamp << endl;
    }
}

int main() {
    // Ordres d'achat (bids) - arrives dans le desordre
    Order bids[] = {
        {101, 100.50, 200, 3},
        {102, 100.55, 150, 1},
        {103, 100.50, 300, 1},
        {104, 100.60, 100, 5},
        {105, 100.55, 250, 4},
        {106, 100.45, 500, 2},
        {107, 100.60, 175, 2},
        {108, 100.50, 125, 7}
    };
    int nbBids = sizeof(bids) / sizeof(bids[0]);

    // Ordres de vente (asks) - arrives dans le desordre
    Order asks[] = {
        {201, 100.70, 180, 2},
        {202, 100.65, 220, 3},
        {203, 100.75, 300, 1},
        {204, 100.65, 150, 1},
        {205, 100.80, 400, 4},
        {206, 100.70, 100, 5},
        {207, 100.65, 175, 6}
    };
    int nbAsks = sizeof(asks) / sizeof(asks[0]);

    cout << "=== Order Book avant tri ===" << endl;
    printOrders(bids, nbBids, "\n--- BIDS (achats) ---");
    printOrders(asks, nbAsks, "\n--- ASKS (ventes) ---");

    // --- Tri des bids : prix decroissant, puis timestamp croissant (FIFO) ---
    sort(bids, bids + nbBids, [](const Order& a, const Order& b) {
        if (a.price != b.price) return a.price > b.price; // Prix decroissant
        return a.timestamp < b.timestamp; // FIFO a prix egal
    });

    // --- Tri des asks : prix croissant, puis timestamp croissant (FIFO) ---
    sort(asks, asks + nbAsks, [](const Order& a, const Order& b) {
        if (a.price != b.price) return a.price < b.price; // Prix croissant
        return a.timestamp < b.timestamp; // FIFO a prix egal
    });

    cout << "\n\n=== Order Book apres tri ===" << endl;
    printOrders(bids, nbBids, "\n--- BIDS (meilleur prix en haut) ---");
    printOrders(asks, nbAsks, "\n--- ASKS (meilleur prix en haut) ---");

    // --- Calcul du spread ---
    double bestBid = bids[0].price;
    double bestAsk = asks[0].price;
    double spread = bestAsk - bestBid;

    cout << "\n=== Metriques de marche ===" << endl;
    cout << "Meilleur bid : " << fixed << setprecision(2) << bestBid << endl;
    cout << "Meilleur ask : " << bestAsk << endl;
    cout << "Spread       : " << spread << " ("
         << setprecision(4) << (spread / bestBid * 100) << "%)" << endl;

    // --- Profondeur du marche (depth) ---
    cout << "\n=== Profondeur du marche ===" << endl;

    // Agreger les quantites par niveau de prix pour les bids
    cout << "\nBID depth:" << endl;
    double currentPrice = bids[0].price;
    int totalQty = 0;
    int cumulativeQty = 0;

    for (int i = 0; i < nbBids; i++) {
        if (bids[i].price != currentPrice) {
            cumulativeQty += totalQty;
            cout << "  " << fixed << setprecision(2) << currentPrice
                 << " | qty=" << setw(4) << totalQty
                 << " | cumul=" << setw(5) << cumulativeQty << " ";
            int barLen = totalQty / 25;
            for (int b = 0; b < barLen; b++) cout << "#";
            cout << endl;
            currentPrice = bids[i].price;
            totalQty = 0;
        }
        totalQty += bids[i].quantity;
    }
    cumulativeQty += totalQty;
    cout << "  " << fixed << setprecision(2) << currentPrice
         << " | qty=" << setw(4) << totalQty
         << " | cumul=" << setw(5) << cumulativeQty << " ";
    int barLen = totalQty / 25;
    for (int b = 0; b < barLen; b++) cout << "#";
    cout << endl;

    // Agreger pour les asks
    cout << "\nASK depth:" << endl;
    currentPrice = asks[0].price;
    totalQty = 0;
    cumulativeQty = 0;

    for (int i = 0; i < nbAsks; i++) {
        if (asks[i].price != currentPrice) {
            cumulativeQty += totalQty;
            cout << "  " << fixed << setprecision(2) << currentPrice
                 << " | qty=" << setw(4) << totalQty
                 << " | cumul=" << setw(5) << cumulativeQty << " ";
            int bLen = totalQty / 25;
            for (int b = 0; b < bLen; b++) cout << "=";
            cout << endl;
            currentPrice = asks[i].price;
            totalQty = 0;
        }
        totalQty += asks[i].quantity;
    }
    cumulativeQty += totalQty;
    cout << "  " << fixed << setprecision(2) << currentPrice
         << " | qty=" << setw(4) << totalQty
         << " | cumul=" << setw(5) << cumulativeQty << " ";
    barLen = totalQty / 25;
    for (int b = 0; b < barLen; b++) cout << "=";
    cout << endl;

    // --- Simulation de match ---
    cout << "\n=== Simulation de matching ===" << endl;
    if (bestBid >= bestAsk) {
        cout << "MATCH possible : bid " << bestBid << " >= ask " << bestAsk << endl;
        int matchQty = min(bids[0].quantity, asks[0].quantity);
        cout << "Quantite matchee : " << matchQty << " a " << bestAsk << endl;
    } else {
        cout << "Pas de match : spread ouvert de " << spread << endl;
        cout << "Le marche attend un rapprochement des prix" << endl;
    }

    return 0;
}
