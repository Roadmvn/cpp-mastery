// ============================================================
//  Chapitre 04 -- Solutions : Namespaces
//  Compile avec : g++ -std=c++11 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>

// ============================================================
//  PARTIE 1 : Namespace math_utils
// ============================================================

namespace math_utils {
    // Addition de deux entiers
    int add(int a, int b) {
        return a + b;
    }

    // Multiplication de deux entiers
    int multiply(int a, int b) {
        return a * b;
    }
}

// ============================================================
//  PARTIE 2 : Deux namespaces avec la meme fonction
// ============================================================

namespace french {
    // Salutation en francais
    void greet() {
        std::cout << "Bonjour !" << std::endl;
    }
}

namespace english {
    // Salutation en anglais
    void greet() {
        std::cout << "Hello !" << std::endl;
    }
}

// ============================================================
//  PARTIE 3 : Namespace imbrique
// ============================================================

namespace company {
    namespace trading {
        namespace utils {
            // Formate un prix en string lisible
            std::string format_price(double price) {
                // to_string donne beaucoup de decimales, on garde tel quel
                // (le formatage precis viendra dans un chapitre ulterieur)
                return "Prix : " + std::to_string(price) + " USD";
            }
        }
    }
}

// ============================================================
//  MAIN
// ============================================================

int main() {
    std::cout << "=== PARTIE 1 : math_utils ===" << std::endl;

    // Appel des fonctions via l'operateur ::
    std::cout << "5 + 3 = " << math_utils::add(5, 3) << std::endl;
    std::cout << "5 * 3 = " << math_utils::multiply(5, 3) << std::endl;
    std::cout << "10 + 20 = " << math_utils::add(10, 20) << std::endl;
    std::cout << "7 * 8 = " << math_utils::multiply(7, 8) << std::endl;

    std::cout << std::endl;
    std::cout << "=== PARTIE 2 : Deux namespaces ===" << std::endl;

    // Meme nom de fonction, pas de conflit grace a ::
    french::greet();    // Affiche "Bonjour !"
    english::greet();   // Affiche "Hello !"

    std::cout << std::endl;
    std::cout << "=== PARTIE 3 : Namespace imbrique ===" << std::endl;

    // Chemin complet vers la fonction imbriquee
    std::string formatted = company::trading::utils::format_price(42567.89);
    std::cout << formatted << std::endl;

    // On peut aussi creer un alias pour raccourcir
    namespace ctu = company::trading::utils;
    std::cout << ctu::format_price(1234.56) << std::endl;
    std::cout << ctu::format_price(99.99) << std::endl;

    return 0;
}
