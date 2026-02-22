// ============================================================
// EXERCICE : Break & Continue
// Fichier : exercise.cpp
// Compile : g++ -std=c++17 -o exercise exercise.cpp
// ============================================================

#include <iostream>
using namespace std;

int main() {

    // --------------------------------------------------------
    // PARTIE 1 : Trouver un element
    // --------------------------------------------------------
    // TODO : Parcours le tableau ci-dessous avec un for.
    // Quand tu trouves la valeur 42, affiche sa position
    // et arrete la boucle avec break.
    // Si non trouve, affiche "Non trouve".

    int data[] = {10, 25, 33, 7, 42, 88, 99, 42, 15};
    int data_size = 9;

    // Ecris ton code ici :



    // --------------------------------------------------------
    // PARTIE 2 : Filtrer les negatifs
    // --------------------------------------------------------
    // TODO : Parcours le tableau et affiche UNIQUEMENT
    // les nombres positifs. Utilise continue pour sauter les negatifs.
    // Calcule aussi la somme des nombres positifs.

    int values[] = {15, -3, 22, -7, 8, -1, 30, -12, 5, -4};
    int values_size = 10;

    // Ecris ton code ici :



    // --------------------------------------------------------
    // PARTIE 3 : Premier nombre premier
    // --------------------------------------------------------
    // TODO : Affiche les 20 premiers nombres premiers.
    // Utilise une boucle for avec un compteur de premiers trouves.
    // Pour tester si un nombre est premier, utilise une boucle
    // interne avec break quand tu trouves un diviseur.
    //
    // Rappel : un nombre premier n'est divisible que par 1 et lui-meme.
    // 2, 3, 5, 7, 11, 13, 17, 19, 23, 29...

    // Ecris ton code ici :



    return 0;
}
