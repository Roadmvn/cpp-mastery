// ============================================================
// Chapitre 10 : Passage par Valeur vs Reference - Challenge HFT
// ============================================================
// DEFI : Benchmark pass-by-value vs pass-by-reference
//
// En HFT, chaque nanoseconde compte. Copier un gros struct
// a chaque appel de fonction peut couter tres cher quand tu
// traites des millions de ticks par seconde.
//
// Compile : g++ -std=c++17 -Wall -Wextra -O2 -o challenge challenge.cpp
// ============================================================

#include <iostream>
#include <chrono>
#include <cstring>
using namespace std;

// Struct realiste de donnees de marche (environ 256 octets)
struct OrderBookLevel {
    double bid_prices[8];
    double ask_prices[8];
    int bid_sizes[8];
    int ask_sizes[8];
    long long timestamp;
    int symbol_id;
    char exchange[4];
};

// PASSAGE PAR VALEUR : copie 256 octets a chaque appel
double processOrderByValue(OrderBookLevel book) {
    double spread = book.ask_prices[0] - book.bid_prices[0];
    double mid = (book.ask_prices[0] + book.bid_prices[0]) / 2.0;
    return spread / mid;
}

// PASSAGE PAR CONST REF : zero copie, juste une adresse (8 octets)
double processOrderByRef(const OrderBookLevel& book) {
    double spread = book.ask_prices[0] - book.bid_prices[0];
    double mid = (book.ask_prices[0] + book.bid_prices[0]) / 2.0;
    return spread / mid;
}

// PASSAGE PAR VALEUR pour un type primitif (baseline)
double processPrice(double price) {
    return price * 1.001;
}

// PASSAGE PAR CONST REF pour un type primitif
double processPriceRef(const double& price) {
    return price * 1.001;
}

int main() {
    cout << "=== CHALLENGE HFT : Value vs Reference Benchmark ===" << endl << endl;

    cout << "sizeof(OrderBookLevel) = " << sizeof(OrderBookLevel)
         << " octets" << endl;
    cout << "sizeof(double)         = " << sizeof(double)
         << " octets" << endl << endl;

    // Initialiser les donnees
    OrderBookLevel book{};
    for (int i = 0; i < 8; i++) {
        book.bid_prices[i] = 100.0 - i * 0.01;
        book.ask_prices[i] = 100.0 + (i + 1) * 0.01;
        book.bid_sizes[i] = 100 * (i + 1);
        book.ask_sizes[i] = 150 * (i + 1);
    }
    book.timestamp = 1234567890;
    book.symbol_id = 42;
    memcpy(book.exchange, "NYS", 4);

    const int ITERATIONS = 10000000;
    double result = 0;

    // --- Benchmark 1 : Gros struct par valeur ---
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; i++) {
        result += processOrderByValue(book);
    }
    auto end = chrono::high_resolution_clock::now();
    auto time_value = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // --- Benchmark 2 : Gros struct par const ref ---
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; i++) {
        result += processOrderByRef(book);
    }
    end = chrono::high_resolution_clock::now();
    auto time_ref = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "--- Gros struct (" << sizeof(OrderBookLevel) << " octets) x "
         << ITERATIONS << " appels ---" << endl;
    cout << "Par valeur   : " << time_value << " us" << endl;
    cout << "Par const&   : " << time_ref << " us" << endl;
    if (time_ref > 0) {
        cout << "Speedup      : x" << (double)time_value / time_ref << endl;
    }
    cout << endl;

    // --- Benchmark 3 : Type primitif par valeur ---
    double price = 150.25;
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; i++) {
        result += processPrice(price);
    }
    end = chrono::high_resolution_clock::now();
    auto time_prim_val = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // --- Benchmark 4 : Type primitif par const ref ---
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; i++) {
        result += processPriceRef(price);
    }
    end = chrono::high_resolution_clock::now();
    auto time_prim_ref = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "--- Type primitif (double, " << sizeof(double) << " octets) x "
         << ITERATIONS << " appels ---" << endl;
    cout << "Par valeur   : " << time_prim_val << " us" << endl;
    cout << "Par const&   : " << time_prim_ref << " us" << endl;
    cout << "(Difference negligeable pour les types primitifs)" << endl;

    cout << endl;
    cout << "--- Conclusions HFT ---" << endl;
    cout << "1. Gros struct  TOUJOURS const& (economise des copies couteuses)" << endl;
    cout << "2. Type primitif  par valeur (la ref ajoute une indirection inutile)" << endl;
    cout << "3. Seuil : au-dela de ~16 octets, const& devient avantageux" << endl;
    cout << "(result checksum: " << result << ")" << endl;

    return 0;
}
