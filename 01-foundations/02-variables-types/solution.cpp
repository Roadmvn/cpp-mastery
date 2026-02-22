// ============================================================
// SOLUTION : Variables & Types de donnees
// Fichier : solution.cpp
// Compile : g++ -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Declarer et afficher chaque type
    // --------------------------------------------------------
    int age = 25;
    double solde = 1337.42;
    float ratio = 3.14f;
    char initiale = 'T';
    bool est_connecte = true;
    string pseudo = "root";

    cout << "=== PARTIE 1 : Types de base ===" << endl;
    cout << "int    : " << age << endl;
    cout << "double : " << solde << endl;
    cout << "float  : " << ratio << endl;
    cout << "char   : " << initiale << endl;
    cout << "bool   : " << est_connecte << endl;
    cout << "string : " << pseudo << endl;
    cout << endl;

    // --------------------------------------------------------
    // PARTIE 2 : Tailles en memoire
    // --------------------------------------------------------
    cout << "=== PARTIE 2 : sizeof() ===" << endl;
    cout << "int    : " << sizeof(int)    << " bytes" << endl;
    cout << "double : " << sizeof(double) << " bytes" << endl;
    cout << "float  : " << sizeof(float)  << " bytes" << endl;
    cout << "char   : " << sizeof(char)   << " bytes" << endl;
    cout << "bool   : " << sizeof(bool)   << " bytes" << endl;
    cout << "long   : " << sizeof(long)   << " bytes" << endl;
    cout << "short  : " << sizeof(short)  << " bytes" << endl;
    cout << "string : " << sizeof(string) << " bytes" << endl;
    // Note : sizeof(string) donne la taille de l'OBJET string,
    // pas la taille du texte qu'il contient. C'est different.
    cout << endl;

    // --------------------------------------------------------
    // PARTIE 3 : Mini profil
    // --------------------------------------------------------
    string nom = "Alex Dupont";
    int user_age = 22;
    double taille = 1.78;
    bool est_etudiant = true;

    cout << "========================" << endl;
    cout << "  PROFIL UTILISATEUR    " << endl;
    cout << "========================" << endl;
    cout << "Nom       : " << nom << endl;
    cout << "Age       : " << user_age << " ans" << endl;
    cout << "Taille    : " << taille << " m" << endl;
    cout << "Etudiant  : " << (est_etudiant ? "Oui" : "Non") << endl;
    cout << "========================" << endl;

    return 0;
}
