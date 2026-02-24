// Chapitre 06 — Perfect Forwarding : Exercices
// Compilation : g++ -std=c++20 -Wall -Wextra -o exercise exercise.cpp
//
// Instructions : implementer les TODO dans l'ordre des parties.
// Decommentez les tests au fur et a mesure.

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// ============================================================
// Utilitaire : detecter si une valeur est passee comme lvalue ou rvalue
// ============================================================

void check(const std::string& s) { std::cout << "\"" << s << "\" -> lvalue\n"; }
void check(std::string&& s)      { std::cout << "\"" << s << "\" -> rvalue\n"; }

// ============================================================
// Partie 1 : observer la perte de rvalue sans forward
//
// Implementer bad_wrapper() qui appelle check(val) sans std::forward.
// Observation attendue : meme en passant une rvalue, check() recoit une lvalue.
// Raison : "val" a un nom -> c'est une lvalue ici, peu importe son origine.
// ============================================================

// TODO : decommenter et implementer
// template<typename T>
// void bad_wrapper(T&& val) {
//     check(val);  // val est une lvalue ici (elle a un nom)
// }


// ============================================================
// Partie 2 : wrapper correct avec std::forward
//
// Implementer perfect_wrapper() qui preserve la categorie de val.
// std::forward<T>(val) :
//   - si T = string&  (lvalue deduit) -> retransmet comme lvalue
//   - si T = string   (rvalue deduit) -> retransmet comme rvalue
// ============================================================

// TODO : decommenter et implementer
// template<typename T>
// void perfect_wrapper(T&& val) {
//     check(std::forward<T>(val));
// }


// ============================================================
// Partie 3 : factory function avec perfect forwarding
//
// Implementer make_pair_custom<T, U>(first, second)
// qui retourne std::pair<T, U> en forwardant les deux arguments.
//
// Note : la deduction de T et U depuis T&& peut donner T = X&.
// Il faut utiliser std::decay_t pour deduire le type "propre".
// ============================================================

// TODO : decommenter et implementer
// template<typename T, typename U>
// std::pair<???, ???> make_pair_custom(T&& first, U&& second) {
//     return { std::forward<T>(first), std::forward<U>(second) };
// }


// ============================================================
// Partie 4 : type move-only pour tester emplace_back
//
// MoveOnly ne peut pas etre copie, seulement move.
// Cela force l'utilisation de move semantics ou de perfect forwarding.
// ============================================================

struct MoveOnly {
    int value;

    explicit MoveOnly(int v) : value(v) {}

    MoveOnly(const MoveOnly&) = delete;             // copie interdite
    MoveOnly& operator=(const MoveOnly&) = delete;

    MoveOnly(MoveOnly&& o) noexcept : value(o.value) { o.value = -1; }
    MoveOnly& operator=(MoveOnly&& o) noexcept {
        value = o.value;
        o.value = -1;
        return *this;
    }
};

// ============================================================
// Partie 5 : compteur d'operations pour comparaison emplace/push
// ============================================================

struct Tracked {
    std::string name;
    static inline int constructions = 0;
    static inline int copies        = 0;
    static inline int moves         = 0;

    explicit Tracked(std::string n) : name(std::move(n)) { ++constructions; }
    Tracked(const Tracked& o) : name(o.name)              { ++constructions; ++copies; }
    Tracked(Tracked&& o) noexcept : name(std::move(o.name)) { ++constructions; ++moves; }

    static void reset() { constructions = copies = moves = 0; }
    static void print(const char* label) {
        std::cout << label
                  << " -> constructions=" << constructions
                  << " copies=" << copies
                  << " moves=" << moves << "\n";
    }
};

// ============================================================
// main : tests a decommenter au fur et a mesure
// ============================================================

int main() {
    // --- Partie 1 : bad_wrapper (perd la rvalue) ---
    // std::string s = "hello";
    // std::cout << "=== bad_wrapper ===\n";
    // bad_wrapper(s);                   // attendu : lvalue (correct)
    // bad_wrapper(std::string("hi"));   // attendu : lvalue (INCORRECT - rvalue perdue)

    // --- Partie 2 : perfect_wrapper (preserve la categorie) ---
    // std::cout << "\n=== perfect_wrapper ===\n";
    // perfect_wrapper(s);                   // attendu : lvalue
    // perfect_wrapper(std::string("hi"));   // attendu : rvalue

    // --- Partie 3 : make_pair_custom ---
    // std::cout << "\n=== make_pair_custom ===\n";
    // std::string key = "AAPL";
    // auto p = make_pair_custom(key, 142.50);
    // std::cout << p.first << " = " << p.second << "\n";
    //
    // auto p2 = make_pair_custom(std::string("TSLA"), 300.0);
    // std::cout << p2.first << " = " << p2.second << "\n";

    // --- Partie 4 : MoveOnly dans un vector ---
    // std::cout << "\n=== MoveOnly + emplace_back ===\n";
    // std::vector<MoveOnly> v;
    // v.reserve(3);
    //
    // // emplace_back construit directement : OK (pas de copie)
    // v.emplace_back(10);
    // v.emplace_back(20);
    //
    // // push_back avec rvalue : OK via move
    // v.push_back(MoveOnly{30});
    //
    // // push_back avec lvalue : ERREUR de compilation (copie supprimee)
    // // MoveOnly m{40};
    // // v.push_back(m);  // ERREUR: call to deleted constructor
    //
    // for (const auto& obj : v) {
    //     std::cout << "value=" << obj.value << "\n";
    // }

    // --- Partie 5 : push_back vs emplace_back avec Tracked ---
    // std::cout << "\n=== push_back vs emplace_back (Tracked) ===\n";
    // std::vector<Tracked> tv;
    // tv.reserve(4);
    //
    // Tracked::reset();
    // tv.push_back(Tracked("push-rvalue"));   // Tracked("...") est une rvalue
    // Tracked::print("push_back(Tracked(...))");
    // // Attendu : constructions=2, copies=0, moves=1
    // //   1 ctor pour Tracked("push-rvalue")
    // //   1 move pour l'inserer dans le vecteur
    //
    // Tracked::reset();
    // tv.emplace_back("emplace");              // construit directement en place
    // Tracked::print("emplace_back(\"emplace\")");
    // // Attendu : constructions=1, copies=0, moves=0
    // //   1 seul ctor, directement dans la memoire du vecteur
    //
    // Tracked t{"lvalue"};
    // Tracked::reset();
    // tv.push_back(t);                         // t est une lvalue : copie
    // Tracked::print("push_back(lvalue)");
    // // Attendu : copies=1

    std::cout << "Decommentez les tests apres implementation de chaque partie.\n";
    return 0;
}
