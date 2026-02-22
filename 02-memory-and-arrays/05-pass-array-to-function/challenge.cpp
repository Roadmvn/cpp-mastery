// =============================================================
// Challenge HFT : Fonctions normalize() et scale() sur prix
// =============================================================
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// =============================================================
// Contexte : En HFT, avant d'envoyer des prix a un modele de trading
// ou un algorithme de machine learning, on les normalise souvent.
//
// normalize() : ramene les prix dans [0, 1] avec min-max scaling
//   normalized[i] = (price[i] - min) / (max - min)
//
// scale() : centre les prix autour de la moyenne (z-score)
//   scaled[i] = (price[i] - mean) / stddev
//
// Ces fonctions operent directement sur les arrays (zero-copy).
// =============================================================

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Trouve le minimum d'un array
double findMin(const double arr[], int size) {
    double min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

// Trouve le maximum d'un array
double findMax(const double arr[], int size) {
    double max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// Calcule la moyenne
double mean(const double arr[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

// Calcule l'ecart-type
double stddev(const double arr[], int size) {
    double m = mean(arr, size);
    double sumSquares = 0;
    for (int i = 0; i < size; i++) {
        double diff = arr[i] - m;
        sumSquares += diff * diff;
    }
    return sqrt(sumSquares / size);
}

// Min-max normalization : ramene dans [0, 1]
// Modifie l'array en place
void normalize(double arr[], int size) {
    double min = findMin(arr, size);
    double max = findMax(arr, size);
    double range = max - min;

    if (range == 0) return; // Tous les elements identiques

    for (int i = 0; i < size; i++) {
        arr[i] = (arr[i] - min) / range;
    }
}

// Z-score scaling : centre autour de 0 avec stddev = 1
// Modifie l'array en place
void zscale(double arr[], int size) {
    double m = mean(arr, size);
    double s = stddev(arr, size);

    if (s == 0) return;

    for (int i = 0; i < size; i++) {
        arr[i] = (arr[i] - m) / s;
    }
}

// Copie un array
void copyArray(const double src[], double dst[], int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}

// Affiche un array de doubles
void printArray(const double arr[], int size, int precision = 4) {
    cout << fixed << setprecision(precision);
    for (int i = 0; i < size; i++) {
        cout << setw(8) << arr[i];
        if (i < size - 1) cout << " ";
    }
    cout << endl;
}

// Calcule les rendements (returns) : r[i] = (p[i+1] - p[i]) / p[i]
void computeReturns(const double prices[], double returns[], int size) {
    for (int i = 0; i < size - 1; i++) {
        returns[i] = (prices[i + 1] - prices[i]) / prices[i];
    }
}

int main() {
    // 15 prix de marche
    double prices[] = {
        100.50, 100.55, 100.48, 100.62, 100.58,
        100.70, 100.65, 100.80, 100.75, 100.90,
        100.85, 101.00, 100.95, 101.10, 101.05
    };
    int size = sizeof(prices) / sizeof(prices[0]);

    cout << "=== Pipeline de transformation HFT ===" << endl;

    // --- Donnees originales ---
    cout << "\n--- Prix originaux ---" << endl;
    printArray(prices, size, 2);
    cout << "Min: " << findMin(prices, size) << "  Max: " << findMax(prices, size) << endl;
    cout << "Mean: " << mean(prices, size) << "  Stddev: " << stddev(prices, size) << endl;

    // --- Normalisation min-max [0, 1] ---
    double normalized[15];
    copyArray(prices, normalized, size);
    normalize(normalized, size);

    cout << "\n--- Normalise [0, 1] ---" << endl;
    printArray(normalized, size);
    cout << "Min: " << findMin(normalized, size) << "  Max: " << findMax(normalized, size) << endl;

    // --- Z-score ---
    double zscored[15];
    copyArray(prices, zscored, size);
    zscale(zscored, size);

    cout << "\n--- Z-score (centre, stddev=1) ---" << endl;
    printArray(zscored, size);
    cout << "Mean: " << mean(zscored, size) << "  Stddev: " << stddev(zscored, size) << endl;

    // --- Rendements ---
    double returns[14];
    computeReturns(prices, returns, size);

    cout << "\n--- Rendements (returns) ---" << endl;
    cout << fixed << setprecision(6);
    for (int i = 0; i < size - 1; i++) {
        cout << "  r[" << setw(2) << i << "] = " << setw(10) << returns[i];
        if (returns[i] > 0) cout << "  (+)";
        else if (returns[i] < 0) cout << "  (-)";
        else cout << "  (=)";
        cout << endl;
    }

    // --- Stats des rendements ---
    cout << "\n--- Stats rendements ---" << endl;
    cout << "Mean return : " << mean(returns, size - 1) << endl;
    cout << "Volatilite  : " << stddev(returns, size - 1) << endl;

    // Ratio de Sharpe simplifie (mean / stddev)
    double sharpe = mean(returns, size - 1) / stddev(returns, size - 1);
    cout << "Sharpe ratio: " << setprecision(4) << sharpe << endl;

    if (sharpe > 0.5)
        cout << "-> Signal FORT, strategie potentiellement profitable" << endl;
    else if (sharpe > 0)
        cout << "-> Signal FAIBLE, rendement positif mais risque eleve" << endl;
    else
        cout << "-> Signal NEGATIF, ne pas trader" << endl;

    return 0;
}
