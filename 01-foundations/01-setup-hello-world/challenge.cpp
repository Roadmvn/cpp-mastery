// ============================================================
// CHALLENGE : Fausse banniere de login (Social Engineering 101)
// Fichier : challenge.cpp
// Compile : g++ -o challenge challenge.cpp
// ============================================================
//
// OBJECTIF :
// Creer un programme qui imite un ecran de connexion systeme.
// C'est un exercice PEDAGOGIQUE pour comprendre cout et cin.
//
// Le programme doit :
// 1. Afficher une banniere "officielle" avec des separateurs
// 2. Demander un identifiant
// 3. Demander un mot de passe
// 4. Afficher "Acces refuse" peu importe ce qu'on tape
//
// Ca te montre comment fonctionne le phishing de terminal
// et pourquoi il faut TOUJOURS verifier ce qu'on execute.
//
// ⚠️  Usage educatif uniquement.
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    string identifiant;
    string mot_de_passe;

    // Affiche la fausse banniere
    cout << "========================================" << endl;
    cout << "   SYSTEME DE SECURITE v3.1.4          " << endl;
    cout << "   Authentification requise             " << endl;
    cout << "========================================" << endl;
    cout << endl;

    // Demande l'identifiant
    cout << "Identifiant : ";
    getline(cin, identifiant);

    // Demande le mot de passe
    cout << "Mot de passe : ";
    getline(cin, mot_de_passe);

    // Refus systematique
    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "  [ERREUR] Acces refuse.                " << endl;
    cout << "  Tentative enregistree.                " << endl;
    cout << "  IP : 192.168.1.42                     " << endl;
    cout << "----------------------------------------" << endl;

    // En vrai, un vrai programme malveillant enverrait
    // les credentials quelque part. Ici on fait rien
    // avec, c'est juste pour comprendre cout/cin.

    return 0;
}
