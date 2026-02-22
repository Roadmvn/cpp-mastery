// ============================================================
// SOLUTION : Hello World & Premiers Pas
// Fichier : solution.cpp
// Compile : g++ -o solution solution.cpp
// ============================================================

#include <iostream>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Modifier le message
    // --------------------------------------------------------
    cout << "Salut, je suis Alex !" << endl;

    // --------------------------------------------------------
    // PARTIE 2 : Afficher plusieurs lignes
    // --------------------------------------------------------
    cout << "J'ai 25 ans" << endl;
    cout << "Je vis a Paris" << endl;
    cout << "Mon langage prefere : C++" << endl;

    // --------------------------------------------------------
    // PARTIE 3 : Retours a la ligne
    // --------------------------------------------------------

    // Methode 1 : avec \n (plus rapide, pas de flush du buffer)
    cout << "Ligne 1\nLigne 2\nLigne 3\n";

    // Methode 2 : avec endl (flush le buffer a chaque fois)
    cout << "Ligne 1" << endl << "Ligne 2" << endl << "Ligne 3" << endl;

    // Note : \n est generalement prefere en HFT car endl force
    // un flush du buffer, ce qui est plus lent. Pour du debug
    // ou des logs critiques, endl garantit que tout s'affiche
    // immediatement.

    return 0;
}
