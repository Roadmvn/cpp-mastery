// ============================================================
// Chapitre 12 : Null Pointers - Challenge HFT
// ============================================================
// DEFI : Gestion robuste de pointeurs pour donnees de marche
// optionnelles.
//
// En HFT, toutes les donnees ne sont pas toujours disponibles.
// Le bid/ask peut etre absent, le dernier trade peut ne pas
// exister. Il faut gerer ca sans crasher a 3 millions de
// messages par seconde.
//
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================

#include <iostream>
#include <cstring>
using namespace std;

struct MarketTick {
    char symbol[8];
    double* bid;           // Peut etre null (pas de bid)
    double* ask;           // Peut etre null (pas de ask)
    double* lastTrade;     // Peut etre null (pas de trade recent)
    int* volume;           // Peut etre null (volume inconnu)
    long long timestamp;
};

// Cree un tick avec toutes les donnees
MarketTick createFullTick(const char* sym, double bidVal, double askVal,
                          double tradeVal, int vol, long long ts) {
    MarketTick tick{};
    strncpy(tick.symbol, sym, 7);
    tick.bid = new double(bidVal);
    tick.ask = new double(askVal);
    tick.lastTrade = new double(tradeVal);
    tick.volume = new int(vol);
    tick.timestamp = ts;
    return tick;
}

// Cree un tick partiel (seulement bid/ask, pas de trade ni volume)
MarketTick createPartialTick(const char* sym, double bidVal, double askVal,
                             long long ts) {
    MarketTick tick{};
    strncpy(tick.symbol, sym, 7);
    tick.bid = new double(bidVal);
    tick.ask = new double(askVal);
    tick.lastTrade = nullptr;
    tick.volume = nullptr;
    tick.timestamp = ts;
    return tick;
}

// Cree un tick vide (aucune donnee de prix)
MarketTick createEmptyTick(const char* sym, long long ts) {
    MarketTick tick{};
    strncpy(tick.symbol, sym, 7);
    tick.bid = nullptr;
    tick.ask = nullptr;
    tick.lastTrade = nullptr;
    tick.volume = nullptr;
    tick.timestamp = ts;
    return tick;
}

// Calcul du spread avec gestion null robuste
double safeSpread(const MarketTick& tick) {
    if (tick.bid && tick.ask) {
        return *tick.ask - *tick.bid;
    }
    return -1.0;  // Spread indisponible
}

// Calcul du mid-price avec gestion null robuste
double safeMidPrice(const MarketTick& tick) {
    if (tick.bid && tick.ask) {
        return (*tick.bid + *tick.ask) / 2.0;
    }
    if (tick.bid) return *tick.bid;
    if (tick.ask) return *tick.ask;
    if (tick.lastTrade) return *tick.lastTrade;
    return 0.0;  // Aucune donnee de prix
}

// Affichage safe d'un tick
void printTick(const MarketTick& tick) {
    cout << "[" << tick.symbol << " @ " << tick.timestamp << "]" << endl;

    cout << "  Bid       : ";
    if (tick.bid) cout << *tick.bid; else cout << "N/A";
    cout << endl;

    cout << "  Ask       : ";
    if (tick.ask) cout << *tick.ask; else cout << "N/A";
    cout << endl;

    cout << "  Last Trade: ";
    if (tick.lastTrade) cout << *tick.lastTrade; else cout << "N/A";
    cout << endl;

    cout << "  Volume    : ";
    if (tick.volume) cout << *tick.volume; else cout << "N/A";
    cout << endl;

    double spread = safeSpread(tick);
    cout << "  Spread    : ";
    if (spread >= 0) cout << spread; else cout << "indisponible";
    cout << endl;

    cout << "  Mid Price : " << safeMidPrice(tick) << endl;
}

// Liberation propre de la memoire
void freeTick(MarketTick& tick) {
    delete tick.bid;       tick.bid = nullptr;
    delete tick.ask;       tick.ask = nullptr;
    delete tick.lastTrade; tick.lastTrade = nullptr;
    delete tick.volume;    tick.volume = nullptr;
}

int main() {
    cout << "=== CHALLENGE HFT : Donnees de marche optionnelles ===" << endl << endl;

    // Simuler un flux de donnees de marche avec des donnees partielles
    const int NUM_TICKS = 5;
    MarketTick ticks[NUM_TICKS];

    ticks[0] = createFullTick("AAPL", 185.50, 185.52, 185.51, 1500, 1000001);
    ticks[1] = createPartialTick("GOOGL", 141.20, 141.25, 1000002);
    ticks[2] = createEmptyTick("TSLA", 1000003);
    ticks[3] = createFullTick("MSFT", 420.10, 420.15, 420.12, 3200, 1000004);
    ticks[4] = createPartialTick("AMZN", 178.80, 178.90, 1000005);

    cout << "--- Flux de " << NUM_TICKS << " ticks ---" << endl << endl;

    for (int i = 0; i < NUM_TICKS; i++) {
        printTick(ticks[i]);
        cout << endl;
    }

    // Statistiques : combien de ticks ont chaque donnee ?
    cout << "--- Statistiques de disponibilite ---" << endl;
    int hasBid = 0, hasAsk = 0, hasTrade = 0, hasVol = 0;
    for (int i = 0; i < NUM_TICKS; i++) {
        if (ticks[i].bid) hasBid++;
        if (ticks[i].ask) hasAsk++;
        if (ticks[i].lastTrade) hasTrade++;
        if (ticks[i].volume) hasVol++;
    }
    cout << "Bid disponible       : " << hasBid << "/" << NUM_TICKS << endl;
    cout << "Ask disponible       : " << hasAsk << "/" << NUM_TICKS << endl;
    cout << "Last trade disponible: " << hasTrade << "/" << NUM_TICKS << endl;
    cout << "Volume disponible    : " << hasVol << "/" << NUM_TICKS << endl;
    cout << endl;

    // Nettoyage propre
    for (int i = 0; i < NUM_TICKS; i++) {
        freeTick(ticks[i]);
    }

    // Verification post-cleanup
    cout << "--- Verification post-cleanup ---" << endl;
    for (int i = 0; i < NUM_TICKS; i++) {
        bool clean = (!ticks[i].bid && !ticks[i].ask &&
                      !ticks[i].lastTrade && !ticks[i].volume);
        cout << ticks[i].symbol << " : "
             << (clean ? "propre (tous nullptr)" : "FUITE MEMOIRE !") << endl;
    }

    cout << endl;
    cout << "Lecon HFT : en production, on utilise std::optional<double>" << endl;
    cout << "ou des valeurs sentinelles (NaN). Mais comprendre les pointeurs" << endl;
    cout << "null est la base pour gerer les donnees partielles." << endl;

    return 0;
}
