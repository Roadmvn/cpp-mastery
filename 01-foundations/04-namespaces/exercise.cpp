// ============================================================
//  Chapitre 04 -- Exercices : Namespaces
//  Compile avec : g++ -std=c++11 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
//  PARTIE 1 : Creer un namespace "math_utils"
// ============================================================
//
//  Cree un namespace "math_utils" qui contient :
//  - Une fonction add(int a, int b) qui retourne la somme
//  - Une fonction multiply(int a, int b) qui retourne le produit
//
//  Dans le main(), appelle ces fonctions avec :: et affiche les resultats.
//
//  Ecris ton code ici :

// namespace math_utils {
//     ...
// }


// ============================================================
//  PARTIE 2 : Deux namespaces avec la meme fonction
// ============================================================
//
//  Cree deux namespaces :
//  - "french" avec une fonction greet() qui affiche "Bonjour !"
//  - "english" avec une fonction greet() qui affiche "Hello !"
//
//  Dans le main(), appelle les deux fonctions avec :: pour montrer
//  qu'il n'y a pas de conflit.
//
//  Ecris ton code ici :

// namespace french {
//     ...
// }

// namespace english {
//     ...
// }


// ============================================================
//  PARTIE 3 : Namespace imbrique
// ============================================================
//
//  Cree un namespace imbrique : company::trading::utils
//  Dedans, cree une fonction format_price(double price) qui retourne
//  un string au format "Prix : XX.XX USD"
//
//  Dans le main(), appelle cette fonction et affiche le resultat.
//
//  Astuce : utilise std::to_string() pour convertir un double en string
//
//  Ecris ton code ici :

// namespace company {
//     namespace trading {
//         namespace utils {
//             ...
//         }
//     }
// }


// ============================================================
//  MAIN -- Decommente et complete au fur et a mesure
// ============================================================

int main() {
    std::cout << "=== PARTIE 1 : math_utils ===" << std::endl;
    // Exemple attendu :
    // std::cout << "5 + 3 = " << math_utils::add(5, 3) << std::endl;
    // std::cout << "5 * 3 = " << math_utils::multiply(5, 3) << std::endl;

    std::cout << std::endl;
    std::cout << "=== PARTIE 2 : Deux namespaces ===" << std::endl;
    // Exemple attendu :
    // french::greet();
    // english::greet();

    std::cout << std::endl;
    std::cout << "=== PARTIE 3 : Namespace imbrique ===" << std::endl;
    // Exemple attendu :
    // std::cout << company::trading::utils::format_price(42567.89) << std::endl;

    return 0;
}
