// ============================================================
//  Chapitre 05 -- Solutions : Typedef & Aliases
//  Compile avec : g++ -std=c++11 -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
#include <cstdint>

// ============================================================
//  PARTIE 1 : Typedef basiques (ancien style)
// ============================================================

typedef int Score;
typedef std::string PlayerName;
typedef double Health;

// ============================================================
//  PARTIE 2 : Using (style moderne C++11)
// ============================================================

using Level  = int;
using Weapon = std::string;
using Damage = double;

// ============================================================
//  PARTIE 3 : Alias pour un mini systeme de trading
// ============================================================

using Price  = double;
using Volume = int;
using Symbol = std::string;

// ============================================================
//  MAIN
// ============================================================

int main() {
    // --- PARTIE 1 ---
    std::cout << "=== PARTIE 1 : Typedef ===" << std::endl;

    Score player_score = 9500;
    PlayerName name = "ShadowX";
    Health hp = 87.5;

    std::cout << name << " | Score: " << player_score << " | HP: " << hp << std::endl;

    // On peut utiliser les alias exactement comme les types originaux
    Score bonus = 200;
    player_score += bonus;
    std::cout << "Score apres bonus : " << player_score << std::endl;

    // --- PARTIE 2 ---
    std::cout << std::endl;
    std::cout << "=== PARTIE 2 : Using ===" << std::endl;

    Level lvl = 42;
    Weapon wpn = "Excalibur";
    Damage dmg = 156.8;

    std::cout << "Niveau " << lvl << " | Arme: " << wpn << " | Degats: " << dmg << std::endl;

    // Les alias sont interchangeables avec le type original
    double raw_damage = dmg;  // Pas d'erreur, Damage == double
    std::cout << "Degats bruts (double) : " << raw_damage << std::endl;

    // --- PARTIE 3 ---
    std::cout << std::endl;
    std::cout << "=== PARTIE 3 : Mini systeme de trading ===" << std::endl;

    // Bitcoin
    Price  btc_price  = 43250.50;
    Volume btc_volume = 1500;
    Symbol btc_symbol = "BTC/USD";

    std::cout << btc_symbol << " : " << btc_price
              << " USD | Volume : " << btc_volume << " lots" << std::endl;

    // Ethereum
    Price  eth_price  = 3245.67;
    Volume eth_volume = 800;
    Symbol eth_symbol = "ETH/USD";

    std::cout << eth_symbol << " : " << eth_price
              << " USD | Volume : " << eth_volume << " lots" << std::endl;

    // Solana
    Price  sol_price  = 98.42;
    Volume sol_volume = 5000;
    Symbol sol_symbol = "SOL/USD";

    std::cout << sol_symbol << " : " << sol_price
              << " USD | Volume : " << sol_volume << " lots" << std::endl;

    return 0;
}
