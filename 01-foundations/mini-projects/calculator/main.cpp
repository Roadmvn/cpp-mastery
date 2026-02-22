// ============================================================
// MINI-PROJET : Calculatrice CLI
// Compile : g++ -std=c++17 -o calculator main.cpp
// ============================================================

#include <iostream>
#include <cmath>
using namespace std;

// Prototypes
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b, bool& success);
int modulo(int a, int b, bool& success);
double power(double base, double exponent);
void print_result(double result);

int main() {
    int choix;

    cout << "========================================" << endl;
    cout << "  Calculatrice CLI" << endl;
    cout << "========================================" << endl;

    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Addition (+)" << endl;
        cout << "2. Soustraction (-)" << endl;
        cout << "3. Multiplication (*)" << endl;
        cout << "4. Division (/)" << endl;
        cout << "5. Modulo (%)" << endl;
        cout << "6. Puissance (x^n)" << endl;
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

        double a, b;
        cout << "Premier nombre  : ";
        cin >> a;
        cout << "Deuxieme nombre : ";
        cin >> b;

        bool success = true;

        switch (choix) {
            case 1:
                cout << a << " + " << b << " = ";
                print_result(add(a, b));
                break;
            case 2:
                cout << a << " - " << b << " = ";
                print_result(subtract(a, b));
                break;
            case 3:
                cout << a << " * " << b << " = ";
                print_result(multiply(a, b));
                break;
            case 4: {
                double result = divide(a, b, success);
                if (success) {
                    cout << a << " / " << b << " = ";
                    print_result(result);
                } else {
                    cout << "Erreur : division par zero !" << endl;
                }
                break;
            }
            case 5: {
                int result = modulo((int)a, (int)b, success);
                if (success) {
                    cout << (int)a << " % " << (int)b << " = " << result << endl;
                } else {
                    cout << "Erreur : modulo par zero !" << endl;
                }
                break;
            }
            case 6:
                cout << a << " ^ " << b << " = ";
                print_result(power(a, b));
                break;
        }

    } while (true);

    return 0;
}

// --- Definitions ---

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b, bool& success) {
    if (b == 0) {
        success = false;
        return 0;
    }
    success = true;
    return a / b;
}

int modulo(int a, int b, bool& success) {
    if (b == 0) {
        success = false;
        return 0;
    }
    success = true;
    return a % b;
}

double power(double base, double exponent) {
    return pow(base, exponent);
}

void print_result(double result) {
    if (result == (int)result) {
        cout << (int)result << endl;
    } else {
        cout << result << endl;
    }
}
