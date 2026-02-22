// ============================================================
// EXERCICE : Const & Constantes
// Fichier : exercise.cpp
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Declarer des constantes
    // --------------------------------------------------------
    // Declare les constantes suivantes avec const :
    //   - PI           (double, valeur : 3.14159265358979)
    //   - TAUX_TVA     (double, valeur : 0.20)
    //   - NOM_SERVEUR  (string, valeur : "srv-prod-01")
    //
    // Affiche chacune d'elles.
    //
    // Ecris ton code ici :



    // --------------------------------------------------------
    // PARTIE 2 : Tenter de modifier une constante
    // --------------------------------------------------------
    // Decommente la ligne ci-dessous, compile, et observe
    // l'erreur du compilateur. Puis re-commente-la.
    //
    // const int MAX_USERS = 100;
    // MAX_USERS = 200;  // Que se passe-t-il ?
    //
    // Ecris un commentaire expliquant l'erreur :
    // Ton explication :



    // --------------------------------------------------------
    // PARTIE 3 : constexpr
    // --------------------------------------------------------
    // Declare les constantes suivantes avec constexpr :
    //   - OCTETS_PAR_KO   (int, valeur : 1024)
    //   - OCTETS_PAR_MO   (int, valeur : OCTETS_PAR_KO * 1024)
    //   - OCTETS_PAR_GO   (long, valeur : OCTETS_PAR_MO * 1024L)
    //
    // Affiche les trois valeurs.
    //
    // Ensuite, essaie de faire :
    //   int x = 42;
    //   constexpr int y = x;  // Ca marche ? Pourquoi ?
    //
    // Ecris ton code ici :



    return 0;
}
