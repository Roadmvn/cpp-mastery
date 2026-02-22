// ============================================================
// Chapitre 09 : Adresses Memoire - Challenge HFT
// ============================================================
// DEFI : Localite spatiale et disposition memoire
//
// En HFT, comprendre comment les donnees sont disposees en memoire
// est CRUCIAL. Le cache CPU charge des lignes de 64 octets.
// Si tes donnees sont proches, tout est rapide. Sinon, cache miss.
//
// Compile : g++ -std=c++17 -Wall -Wextra -O2 -o challenge challenge.cpp
// ============================================================

#include <iostream>
#include <chrono>
using namespace std;

// Structure "mal disposee" (beaucoup de padding)
struct MarketDataBad {
    char symbol;        // 1 octet + 7 padding
    double price;       // 8 octets
    char exchange;      // 1 octet + 3 padding
    int volume;         // 4 octets
    bool active;        // 1 octet + 7 padding
    double bid;         // 8 octets
    char type;          // 1 octet + 7 padding
    double ask;         // 8 octets
};

// Structure "bien disposee" (minimum de padding)
struct MarketDataGood {
    double price;       // 8 octets
    double bid;         // 8 octets
    double ask;         // 8 octets
    int volume;         // 4 octets
    char symbol;        // 1 octet
    char exchange;      // 1 octet
    char type;          // 1 octet
    bool active;        // 1 octet
};

int main() {
    cout << "=== CHALLENGE HFT : Localite Spatiale ===" << endl << endl;

    // --- Partie 1 : Observer la taille des structs ---
    cout << "--- Taille des structures ---" << endl;
    cout << "sizeof(MarketDataBad)  = " << sizeof(MarketDataBad) << " octets" << endl;
    cout << "sizeof(MarketDataGood) = " << sizeof(MarketDataGood) << " octets" << endl;
    cout << "Difference : " << sizeof(MarketDataBad) - sizeof(MarketDataGood)
         << " octets gaspilles par element !" << endl << endl;

    // --- Partie 2 : Examiner les adresses des champs ---
    cout << "--- Layout MarketDataBad ---" << endl;
    MarketDataBad bad{};
    cout << "symbol   @ offset " << (char*)&bad.symbol - (char*)&bad << endl;
    cout << "price    @ offset " << (char*)&bad.price - (char*)&bad << endl;
    cout << "exchange @ offset " << (char*)&bad.exchange - (char*)&bad << endl;
    cout << "volume   @ offset " << (char*)&bad.volume - (char*)&bad << endl;
    cout << "active   @ offset " << (char*)&bad.active - (char*)&bad << endl;
    cout << "bid      @ offset " << (char*)&bad.bid - (char*)&bad << endl;
    cout << "type     @ offset " << (char*)&bad.type - (char*)&bad << endl;
    cout << "ask      @ offset " << (char*)&bad.ask - (char*)&bad << endl;

    cout << endl;

    cout << "--- Layout MarketDataGood ---" << endl;
    MarketDataGood good{};
    cout << "price    @ offset " << (char*)&good.price - (char*)&good << endl;
    cout << "bid      @ offset " << (char*)&good.bid - (char*)&good << endl;
    cout << "ask      @ offset " << (char*)&good.ask - (char*)&good << endl;
    cout << "volume   @ offset " << (char*)&good.volume - (char*)&good << endl;
    cout << "symbol   @ offset " << (char*)&good.symbol - (char*)&good << endl;
    cout << "exchange @ offset " << (char*)&good.exchange - (char*)&good << endl;
    cout << "type     @ offset " << (char*)&good.type - (char*)&good << endl;
    cout << "active   @ offset " << (char*)&good.active - (char*)&good << endl;

    cout << endl;

    // --- Partie 3 : Benchmark iteration ---
    const int N = 1000000;

    MarketDataBad* bad_array = new MarketDataBad[N];
    MarketDataGood* good_array = new MarketDataGood[N];

    for (int i = 0; i < N; i++) {
        bad_array[i] = {'A', 100.0 + i, 'N', i * 10, true, 99.5 + i, 'L', 100.5 + i};
        good_array[i] = {100.0 + i, 99.5 + i, 100.5 + i, i * 10, 'A', 'N', 'L', true};
    }

    // Benchmark bad layout
    auto start = chrono::high_resolution_clock::now();
    double sum_bad = 0;
    for (int i = 0; i < N; i++) {
        sum_bad += bad_array[i].price + bad_array[i].bid + bad_array[i].ask;
    }
    auto end = chrono::high_resolution_clock::now();
    auto time_bad = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Benchmark good layout
    start = chrono::high_resolution_clock::now();
    double sum_good = 0;
    for (int i = 0; i < N; i++) {
        sum_good += good_array[i].price + good_array[i].bid + good_array[i].ask;
    }
    end = chrono::high_resolution_clock::now();
    auto time_good = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "--- Benchmark : iteration sur " << N << " elements ---" << endl;
    cout << "Bad layout  : " << time_bad << " us (sum = " << sum_bad << ")" << endl;
    cout << "Good layout : " << time_good << " us (sum = " << sum_good << ")" << endl;

    if (time_bad > 0 && time_good > 0) {
        double ratio = (double)time_bad / time_good;
        cout << "Ratio : x" << ratio << endl;
    }

    cout << endl;
    cout << "Lecon HFT : ordonner les champs du plus grand au plus petit" << endl;
    cout << "reduit le padding et ameliore la localite spatiale." << endl;
    cout << "Sur des millions de ticks par seconde, ca fait la difference." << endl;

    delete[] bad_array;
    delete[] good_array;

    return 0;
}
