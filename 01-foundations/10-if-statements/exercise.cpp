// ============================================================
// Exercice : Conditions if/else
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

int main() {
    // ========================================================
    // PARTIE 1 : if / else basique
    // Determine si un nombre est pair ou impair.
    // ========================================================

    int nombre = 17;

    // TODO: Si nombre est pair, affiche "17 est pair"
    //       Sinon, affiche "17 est impair"
    // (indice : un nombre pair a un reste de 0 quand divise par 2)

    // ========================================================
    // PARTIE 2 : if / else if / else
    // Classe une temperature.
    // ========================================================

    double temperature = 22.5;

    // TODO: Affiche la categorie de temperature :
    //   < 0       -> "Gel"
    //   0 a 15    -> "Froid"
    //   15 a 25   -> "Agreable"
    //   25 a 35   -> "Chaud"
    //   >= 35     -> "Canicule"

    // ========================================================
    // PARTIE 3 : Conditions imbriquees
    // Verifie si un etudiant est admis.
    // Regles :
    //   - Moyenne >= 10 pour etre admis
    //   - Si admis ET moyenne >= 16, mention "Tres Bien"
    //   - Si admis ET moyenne >= 14, mention "Bien"
    //   - Si admis ET moyenne >= 12, mention "Assez Bien"
    //   - Sinon admis sans mention
    //   - Si non admis, afficher "Recale"
    // ========================================================

    double moyenne = 15.5;

    // TODO: Implemente la logique d'admission avec mentions
    // Sortie attendue pour 15.5 : "Admis - Mention Bien"

    return 0;
}
