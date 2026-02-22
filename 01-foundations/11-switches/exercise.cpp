// ============================================================
// Exercice : Switch / Case
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>

int main() {
    // ========================================================
    // PARTIE 1 : Switch basique
    // Affiche le jour de la semaine selon un numero (1-7).
    // ========================================================

    int jour = 3;

    // TODO: Ecris un switch qui affiche le jour correspondant :
    // 1 = Lundi, 2 = Mardi, 3 = Mercredi, 4 = Jeudi,
    // 5 = Vendredi, 6 = Samedi, 7 = Dimanche
    // default = "Jour invalide"
    // Sortie attendue : "Mercredi"

    // ========================================================
    // PARTIE 2 : Grouper des cases (fall-through volontaire)
    // Determine si un jour est en semaine ou le weekend.
    // ========================================================

    int jour2 = 6;

    // TODO: Ecris un switch ou :
    // - 1 a 5 affiche "Jour de semaine"
    // - 6 et 7 affiche "Weekend"
    // - default affiche "Invalide"
    // (indice : groupe les cases sans break entre eux)

    // ========================================================
    // PARTIE 3 : Switch sur un char
    // Calcule le resultat d'une operation simple.
    // ========================================================

    double x = 10.0;
    double y = 3.0;
    char operateur = '/';

    // TODO: Ecris un switch sur 'operateur' qui :
    // '+' -> affiche x + y
    // '-' -> affiche x - y
    // '*' -> affiche x * y
    // '/' -> affiche x / y (verifie que y != 0)
    // default -> "Operateur inconnu"
    // Sortie attendue : "10 / 3 = 3.33333"

    return 0;
}
