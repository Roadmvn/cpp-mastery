// =============================================================
// Exercice : Parcourir les Arrays
// =============================================================
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// =============================================================

#include <iostream>
using namespace std;

int main() {
    int data[] = {15, 42, 8, 23, 56, 11, 34, 67, 3, 29};
    int size = sizeof(data) / sizeof(data[0]);

    // ==========================================================
    // PARTIE 1 : Boucle for classique
    // ==========================================================

    // TODO 1.1 : Affiche tous les elements de 'data' sur une seule ligne
    //            separes par des espaces, avec un saut de ligne a la fin
    //            Format: "15 42 8 23 56 11 34 67 3 29"


    // TODO 1.2 : Affiche les elements a index PAIR (0, 2, 4, ...)
    //            Format: "Index pairs: 15 8 56 34 3"


    // TODO 1.3 : Affiche les elements en sens inverse
    //            Format: "Inverse: 29 3 67 34 11 56 23 8 42 15"


    // ==========================================================
    // PARTIE 2 : Boucle while
    // ==========================================================

    // TODO 2.1 : Utilise une boucle while pour trouver le premier element
    //            superieur a 50. Affiche sa valeur et son index.
    //            Format: "Premier > 50 : data[X] = Y"


    // TODO 2.2 : Utilise une boucle while pour compter combien d'elements
    //            sont inferieurs a 20
    //            Format: "Elements < 20 : X"


    // TODO 2.3 : Utilise une boucle while pour calculer la somme des elements
    //            jusqu'a ce qu'on depasse 100 (somme cumulative)
    //            Affiche le nombre d'elements necessaires
    //            Format: "Il faut X elements pour depasser 100 (somme: Y)"


    // ==========================================================
    // PARTIE 3 : Parcours avec transformation
    // ==========================================================

    // TODO 3.1 : Cree un nouveau array 'doubled' de meme taille que 'data'
    //            Remplis-le avec chaque element de data multiplie par 2
    //            Affiche 'doubled'


    // TODO 3.2 : Parcours 'data' et affiche uniquement les elements qui sont
    //            a la fois pairs ET superieurs a 10
    //            Format: "Pairs > 10 : X Y Z"


    // TODO 3.3 : Calcule et affiche la difference entre chaque element consecutif
    //            (data[i+1] - data[i]) pour i de 0 a size-2
    //            Format: "Differences: 27 -34 15 ..."


    return 0;
}
