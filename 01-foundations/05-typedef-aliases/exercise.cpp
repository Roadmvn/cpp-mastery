// ============================================================
//  Chapitre 05 -- Exercices : Typedef & Aliases
//  Compile avec : g++ -std=c++11 -o exercise exercise.cpp
// ============================================================

#include <iostream>
#include <string>
#include <cstdint>

// ============================================================
//  PARTIE 1 : Typedef basiques (ancien style)
// ============================================================
//
//  Cree les typedef suivants :
//  - Score       -> int
//  - PlayerName  -> std::string
//  - Health      -> double
//
//  Puis dans le main(), cree une variable de chaque type et affiche-les.
//
//  Ecris ton code ici :

// typedef int Score;
// typedef ...
// typedef ...


// ============================================================
//  PARTIE 2 : Refaire avec "using" (style moderne)
// ============================================================
//
//  Cree les memes alias mais avec "using" :
//  - Level      -> int
//  - Weapon     -> std::string
//  - Damage     -> double
//
//  Puis dans le main(), cree une variable de chaque type et affiche-les.
//
//  Ecris ton code ici :

// using Level = int;
// using ...
// using ...


// ============================================================
//  PARTIE 3 : Alias pour un mini systeme de trading
// ============================================================
//
//  Cree les alias suivants avec "using" :
//  - Price    -> double
//  - Volume   -> int
//  - Symbol   -> std::string
//
//  Puis dans le main() :
//  1. Cree 3 variables : un prix (BTC a 43250.50), un volume (1500),
//     et un symbole ("BTC/USD")
//  2. Affiche les 3 variables de maniere lisible
//  3. Cree une deuxieme serie pour ETH et affiche aussi
//
//  Ecris ton code ici :

// using Price = ...;
// using Volume = ...;
// using Symbol = ...;


// ============================================================
//  MAIN -- Decommente et complete au fur et a mesure
// ============================================================

int main() {
    std::cout << "=== PARTIE 1 : Typedef ===" << std::endl;
    // Exemple attendu :
    // Score player_score = 9500;
    // PlayerName name = "ShadowX";
    // Health hp = 87.5;
    // std::cout << name << " | Score: " << player_score << " | HP: " << hp << std::endl;

    std::cout << std::endl;
    std::cout << "=== PARTIE 2 : Using ===" << std::endl;
    // Exemple attendu :
    // Level lvl = 42;
    // Weapon wpn = "Excalibur";
    // Damage dmg = 156.8;
    // std::cout << "Niveau " << lvl << " | Arme: " << wpn << " | Degats: " << dmg << std::endl;

    std::cout << std::endl;
    std::cout << "=== PARTIE 3 : Mini systeme de trading ===" << std::endl;
    // Exemple attendu :
    // Price  btc_price  = 43250.50;
    // Volume btc_volume = 1500;
    // Symbol btc_symbol = "BTC/USD";
    // std::cout << btc_symbol << " : " << btc_price << " USD | Volume : " << btc_volume << std::endl;

    return 0;
}
