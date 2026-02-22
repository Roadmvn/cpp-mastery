// ============================================================
// Chapitre 09 : Adresses Memoire - Solutions
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
using namespace std;

void partie1() {
    cout << "=== PARTIE 1 : Adresses de variables ===" << endl;

    int age = 25;
    double salaire = 72000.50;
    char grade = 'A';
    bool actif = true;

    cout << "Valeur de age     : " << age << endl;
    cout << "Adresse de age    : " << &age << endl;

    cout << "Valeur de salaire : " << salaire << endl;
    cout << "Adresse de salaire: " << &salaire << endl;

    cout << "Valeur de grade   : " << grade << endl;
    cout << "Adresse de grade  : " << (void*)&grade << endl;

    cout << "Valeur de actif   : " << actif << endl;
    cout << "Adresse de actif  : " << (void*)&actif << endl;

    cout << endl;
    cout << "sizeof(int)    = " << sizeof(int) << " octets" << endl;
    cout << "sizeof(double) = " << sizeof(double) << " octets" << endl;
    cout << "sizeof(char)   = " << sizeof(char) << " octet" << endl;
    cout << "sizeof(bool)   = " << sizeof(bool) << " octet" << endl;

    cout << endl;
}

void partie2() {
    cout << "=== PARTIE 2 : Adresses d'un array ===" << endl;

    int scores[6] = {95, 87, 73, 100, 64, 88};

    for (int i = 0; i < 6; i++) {
        cout << "scores[" << i << "] = " << scores[i]
             << "\t adresse: " << &scores[i] << endl;
    }

    cout << endl;
    for (int i = 0; i < 5; i++) {
        long ecart = (char*)&scores[i + 1] - (char*)&scores[i];
        cout << "Ecart entre [" << i << "] et [" << i + 1 << "] : "
             << ecart << " octets" << endl;
    }
    cout << "Chaque int fait " << sizeof(int) << " octets  elements contigus !" << endl;

    cout << endl;
}

void partie3() {
    cout << "=== PARTIE 3 : Disposition sur la stack ===" << endl;

    int a = 10;
    double b = 3.14;
    char c = 'X';
    int d = 42;
    bool e = false;

    cout << "a (int)    : adresse = " << &a
         << "  sizeof = " << sizeof(a) << endl;
    cout << "b (double) : adresse = " << &b
         << "  sizeof = " << sizeof(b) << endl;
    cout << "c (char)   : adresse = " << (void*)&c
         << "  sizeof = " << sizeof(c) << endl;
    cout << "d (int)    : adresse = " << &d
         << "  sizeof = " << sizeof(d) << endl;
    cout << "e (bool)   : adresse = " << (void*)&e
         << "  sizeof = " << sizeof(e) << endl;

    cout << endl;
    cout << "Note : le compilateur peut reordonner les variables" << endl;
    cout << "et ajouter du padding pour l'alignement memoire." << endl;
    cout << "Les adresses ne sont pas forcement dans l'ordre de declaration !" << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
