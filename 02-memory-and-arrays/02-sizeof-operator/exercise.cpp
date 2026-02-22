// =============================================================
// Exercice : L'operateur sizeof
// =============================================================
// Compile : g++ -std=c++17 -o exercise exercise.cpp && ./exercise
// =============================================================

#include <iostream>
using namespace std;

int main() {
    // ==========================================================
    // PARTIE 1 : sizeof sur les types fondamentaux
    // ==========================================================

    // TODO 1.1 : Affiche la taille en octets de : char, short, int, long,
    //            float, double, bool
    //            Format: "char   : X octet(s)"


    // TODO 1.2 : Affiche la taille d'un pointeur (int*)
    //            Format: "int*   : X octet(s)"


    // TODO 1.3 : Affiche la taille de 'long long' et 'long double'
    //            Format: "long long   : X octet(s)"


    // ==========================================================
    // PARTIE 2 : sizeof sur les arrays
    // ==========================================================

    int numbers[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    double values[5] = {1.1, 2.2, 3.3, 4.4, 5.5};

    // TODO 2.1 : Affiche la taille totale en octets de 'numbers' et 'values'


    // TODO 2.2 : Calcule et affiche le nombre d'elements de chaque array
    //            en utilisant sizeof
    //            Format: "numbers : X elements"


    // TODO 2.3 : Declare un array de 100 chars et affiche sa taille totale


    // ==========================================================
    // PARTIE 3 : sizeof sur les structs
    // ==========================================================

    // TODO 3.1 : Declare une struct 'Packet' avec : char type, int id, double value
    //            Affiche sizeof(Packet)


    // TODO 3.2 : Declare une struct 'PacketOptimized' en reordonnant les champs
    //            pour minimiser le padding : double value, int id, char type
    //            Affiche sizeof(PacketOptimized) et compare


    // TODO 3.3 : Declare un array de 10 PacketOptimized et affiche sa taille totale
    //            Calcule combien d'octets on economise vs 10 Packet


    return 0;
}
