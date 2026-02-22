// ============================================================
// SOLUTION : Const & Constantes
// Fichier : solution.cpp
// Compile : g++ -std=c++17 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Declarer des constantes
    // --------------------------------------------------------
    const double PI = 3.14159265358979;
    const double TAUX_TVA = 0.20;
    const string NOM_SERVEUR = "srv-prod-01";

    cout << "=== PARTIE 1 : Constantes ===" << endl;
    cout << "PI          : " << PI << endl;
    cout << "TAUX_TVA    : " << TAUX_TVA << " (" << TAUX_TVA * 100 << "%)" << endl;
    cout << "NOM_SERVEUR : " << NOM_SERVEUR << endl;
    cout << endl;

    // --------------------------------------------------------
    // PARTIE 2 : Tenter de modifier une constante
    // --------------------------------------------------------
    // Si on decommente les lignes suivantes :
    //   const int MAX_USERS = 100;
    //   MAX_USERS = 200;
    //
    // Le compilateur affiche une erreur du type :
    //   error: assignment of read-only variable 'MAX_USERS'
    //
    // Explication : const interdit toute modification apres
    // l'initialisation. C'est le compilateur qui enforce cette
    // regle, pas le runtime. Ca veut dire que la protection
    // existe AVANT meme que le programme s'execute.

    cout << "=== PARTIE 2 : Erreur de compilation ===" << endl;
    cout << "Modifier une constante = erreur du compilateur" << endl;
    cout << "Message : 'assignment of read-only variable'" << endl;
    cout << endl;

    // --------------------------------------------------------
    // PARTIE 3 : constexpr
    // --------------------------------------------------------
    constexpr int OCTETS_PAR_KO = 1024;
    constexpr int OCTETS_PAR_MO = OCTETS_PAR_KO * 1024;
    constexpr long OCTETS_PAR_GO = OCTETS_PAR_MO * 1024L;

    cout << "=== PARTIE 3 : constexpr ===" << endl;
    cout << "1 Ko = " << OCTETS_PAR_KO << " octets" << endl;
    cout << "1 Mo = " << OCTETS_PAR_MO << " octets" << endl;
    cout << "1 Go = " << OCTETS_PAR_GO << " octets" << endl;
    cout << endl;

    // Pourquoi constexpr int y = x ne marche pas :
    //
    //   int x = 42;
    //   constexpr int y = x;  // ERREUR !
    //
    // constexpr exige que la valeur soit connue a la COMPILATION.
    // Or, x est une variable runtime : meme si on sait qu'elle
    // vaut 42, le compilateur ne fait pas cette deduction.
    // Solution : utiliser const int y = x; (accepte le runtime)
    //       ou : constexpr int x = 42; (rendre x aussi constexpr)

    cout << "constexpr int y = x; ne compile pas car :" << endl;
    cout << "  -> x est une variable runtime" << endl;
    cout << "  -> constexpr exige une valeur connue a la compilation" << endl;

    return 0;
}
