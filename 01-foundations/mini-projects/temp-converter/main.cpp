// ============================================================
// MINI-PROJET : Convertisseur de Temperature
// Compile : g++ -std=c++17 -o temp-converter main.cpp
// ============================================================

#include <iostream>
#include <iomanip>
using namespace std;

// Prototypes
double celsius_to_fahrenheit(double c);
double fahrenheit_to_celsius(double f);
double celsius_to_kelvin(double c);
double kelvin_to_celsius(double k);
double fahrenheit_to_kelvin(double f);
double kelvin_to_fahrenheit(double k);

int main() {
    int choix;

    cout << "========================================" << endl;
    cout << "  Convertisseur de Temperature" << endl;
    cout << "========================================" << endl;

    cout << fixed << setprecision(2);

    do {
        cout << "\n--- CONVERSIONS ---" << endl;
        cout << "1. Celsius    -> Fahrenheit" << endl;
        cout << "2. Fahrenheit -> Celsius" << endl;
        cout << "3. Celsius    -> Kelvin" << endl;
        cout << "4. Kelvin     -> Celsius" << endl;
        cout << "5. Fahrenheit -> Kelvin" << endl;
        cout << "6. Kelvin     -> Fahrenheit" << endl;
        cout << "7. Quitter" << endl;
        cout << "Choix : ";
        cin >> choix;

        if (choix == 7) {
            cout << "\nAu revoir !" << endl;
            break;
        }

        if (choix < 1 || choix > 7) {
            cout << "Choix invalide." << endl;
            continue;
        }

        double temp;
        cout << "Temperature : ";
        cin >> temp;

        switch (choix) {
            case 1:
                cout << temp << " C = " << celsius_to_fahrenheit(temp) << " F" << endl;
                break;
            case 2:
                cout << temp << " F = " << fahrenheit_to_celsius(temp) << " C" << endl;
                break;
            case 3:
                cout << temp << " C = " << celsius_to_kelvin(temp) << " K" << endl;
                break;
            case 4:
                if (temp < 0) {
                    cout << "Erreur : le Kelvin ne peut pas etre negatif." << endl;
                } else {
                    cout << temp << " K = " << kelvin_to_celsius(temp) << " C" << endl;
                }
                break;
            case 5:
                cout << temp << " F = " << fahrenheit_to_kelvin(temp) << " K" << endl;
                break;
            case 6:
                if (temp < 0) {
                    cout << "Erreur : le Kelvin ne peut pas etre negatif." << endl;
                } else {
                    cout << temp << " K = " << kelvin_to_fahrenheit(temp) << " F" << endl;
                }
                break;
        }

    } while (true);

    return 0;
}

// --- Definitions ---

double celsius_to_fahrenheit(double c) {
    return c * 9.0 / 5.0 + 32.0;
}

double fahrenheit_to_celsius(double f) {
    return (f - 32.0) * 5.0 / 9.0;
}

double celsius_to_kelvin(double c) {
    return c + 273.15;
}

double kelvin_to_celsius(double k) {
    return k - 273.15;
}

double fahrenheit_to_kelvin(double f) {
    return fahrenheit_to_celsius(f) + 273.15;
}

double kelvin_to_fahrenheit(double k) {
    return celsius_to_fahrenheit(kelvin_to_celsius(k));
}
