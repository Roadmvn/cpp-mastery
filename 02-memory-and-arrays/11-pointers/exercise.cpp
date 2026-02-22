// ============================================================
// Chapitre 11 : Pointeurs - Exercices
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
// ============================================================

#include <iostream>
using namespace std;

// ============================================================
// PARTIE 1 : Declaration et dereferencement
// ============================================================
// Declare des variables et des pointeurs, affiche valeurs et adresses

void partie1() {
    cout << "=== PARTIE 1 : Pointeurs de base ===" << endl;

    // TODO: Declare int x = 42
    // TODO: Declare un pointeur int* p qui pointe vers x
    // TODO: Affiche :
    //   - La valeur de x
    //   - L'adresse de x (avec &x)
    //   - La valeur de p (l'adresse stockee)
    //   - La valeur pointee *p
    //   - L'adresse du pointeur lui-meme &p
    // TODO: Modifie x a travers le pointeur : *p = 100
    // TODO: Affiche x pour verifier que ca a change

    cout << endl;
}

// ============================================================
// PARTIE 2 : Arithmetique des pointeurs
// ============================================================
// Parcours un array en utilisant uniquement l'arithmetique de pointeurs

void partie2() {
    cout << "=== PARTIE 2 : Arithmetique des pointeurs ===" << endl;

    // TODO: Declare int arr[6] = {5, 15, 25, 35, 45, 55}
    // TODO: Declare int* p = arr (pointe vers le debut)
    // TODO: Parcours l'array avec une boucle :
    //       affiche *(p + i) pour chaque element
    // TODO: Affiche aussi l'adresse (p + i) pour voir la progression

    cout << endl;
}

// ============================================================
// PARTIE 3 : Pointeur en parametre de fonction
// ============================================================
// Implemente une fonction qui utilise des pointeurs pour modifier
// des variables (style C)

// TODO: Implemente void tripler(int* p) qui triple la valeur pointee
// TODO: Implemente void ordonner(int* a, int* b) qui met le plus petit
//       dans *a et le plus grand dans *b

void partie3() {
    cout << "=== PARTIE 3 : Pointeurs en parametres ===" << endl;

    // TODO: Teste tripler() sur un int
    // TODO: Teste ordonner() sur deux int (ex: 50 et 20 → 20 et 50)

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
