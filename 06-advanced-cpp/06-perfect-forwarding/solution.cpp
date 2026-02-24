// Chapitre 06 — Perfect Forwarding : Solution complete
// Compilation : g++ -std=c++20 -Wall -Wextra -o solution solution.cpp
//
// Ce fichier explique chaque decision : pourquoi forward ici, pourquoi move la,
// quelle difference emplace/push fait sur le compteur d'operations.

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>

// ============================================================
// Utilitaire de diagnostic : detecter lvalue / rvalue
// ============================================================

void check(const std::string& s) { std::cout << "\"" << s << "\" -> lvalue\n"; }
void check(std::string&& s)      { std::cout << "\"" << s << "\" -> rvalue\n"; }

// ============================================================
// Partie 1 : bad_wrapper sans std::forward
//
// Probleme : "val" a un nom dans le corps de bad_wrapper.
// Avoir un nom = etre une lvalue, QUELLE QUE SOIT la categorie d'origine.
// Resultat : une rvalue fournie par l'appelant devient une lvalue ici,
// et check(val) appelle toujours la surcharge const string&.
// ============================================================

template<typename T>
void bad_wrapper(T&& val) {
    // val EST une lvalue ici, meme si l'appelant a passe une rvalue.
    // Le compilateur a deduit T = string (pour une rvalue entree),
    // donc T&& = string&&, mais val lui-meme EST une lvalue avec un nom.
    check(val);
}

// ============================================================
// Partie 2 : perfect_wrapper avec std::forward
//
// std::forward<T>(val) :
//   - Si T a ete deduit comme string& (lvalue en entree)  -> retransmet comme lvalue
//   - Si T a ete deduit comme string  (rvalue en entree)  -> retransmet comme rvalue
//
// C'est exactement ce que l'on veut : preserver la categorie d'origine.
// ============================================================

template<typename T>
void perfect_wrapper(T&& val) {
    check(std::forward<T>(val));
    // Equivalent manuel pour comprendre ce que fait forward :
    // if constexpr (std::is_lvalue_reference_v<T>)
    //     check(val);              // lvalue : pas de cast
    // else
    //     check(std::move(val));   // rvalue : cast en rvalue reference
}

// ============================================================
// Partie 3 : make_pair_custom
//
// std::decay_t<T> supprime les references et const/volatile
// pour obtenir le type "propre" a stocker dans la paire.
//
// Sans decay :
//   make_pair_custom(s, 1.0)  ->  T = string&, U = double
//   retourne pair<string&, double>  <- reference pendante !
//
// Avec decay :
//   make_pair_custom(s, 1.0)  ->  T = string&, decay = string
//   retourne pair<string, double>  <- copie, correct
// ============================================================

template<typename T, typename U>
std::pair<std::decay_t<T>, std::decay_t<U>> make_pair_custom(T&& first, U&& second) {
    // forward preserve la categorie pour construire l'element de la paire :
    // - si first est une lvalue : copie dans la paire
    // - si first est une rvalue : move dans la paire
    return { std::forward<T>(first), std::forward<U>(second) };
}

// ============================================================
// Partie 4 : MoveOnly dans un vector
//
// Un type move-only ne peut pas etre copie.
// emplace_back(args...) : construit in-place, pas de copie ni de move
//                          de l'objet entier (seulement le ctor appele)
// push_back(rvalue)     : move l'objet dans le vecteur
// push_back(lvalue)     : copie -> ERREUR DE COMPILATION pour MoveOnly
// ============================================================

struct MoveOnly {
    int value;

    explicit MoveOnly(int v) : value(v) {}

    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;

    MoveOnly(MoveOnly&& o) noexcept : value(o.value) { o.value = -1; }
    MoveOnly& operator=(MoveOnly&& o) noexcept {
        value = o.value;
        o.value = -1;
        return *this;
    }
};

// ============================================================
// Partie 5 : Tracked — compteur d'operations
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
// main
// ============================================================

int main() {
    // Partie 1 : bad_wrapper perd la rvalue-ness
    std::cout << "=== bad_wrapper ===\n";
    std::string s = "hello";
    bad_wrapper(s);                   // lvalue -> lvalue : correct
    bad_wrapper(std::string("hi"));  // rvalue -> LVALUE : perdue !
    // Sortie attendue :
    //   "hello" -> lvalue
    //   "hi"    -> lvalue   <- bad : la rvalue est devenue lvalue

    // Partie 2 : perfect_wrapper preserve la categorie
    std::cout << "\n=== perfect_wrapper ===\n";
    perfect_wrapper(s);                   // lvalue -> lvalue : correct
    perfect_wrapper(std::string("hi")); // rvalue -> rvalue : correct
    // Sortie attendue :
    //   "hello" -> lvalue
    //   "hi"    -> rvalue   <- correct : rvalue preservee

    // Partie 3 : make_pair_custom
    std::cout << "\n=== make_pair_custom ===\n";
    std::string key = "AAPL";
    auto p = make_pair_custom(key, 142.50);
    // key est une lvalue : COPIE dans la paire (key reste valide)
    std::cout << p.first << " = " << p.second << "\n";

    auto p2 = make_pair_custom(std::string("TSLA"), 300.0);
    // string("TSLA") est une rvalue : MOVE dans la paire (pas de copie)
    std::cout << p2.first << " = " << p2.second << "\n";

    // Partie 4 : MoveOnly
    std::cout << "\n=== MoveOnly + vecteur ===\n";
    std::vector<MoveOnly> v;
    v.reserve(3);

    v.emplace_back(10);       // construit MoveOnly(10) directement en place : OK
    v.emplace_back(20);       // idem
    v.push_back(MoveOnly{30}); // MoveOnly{30} est une rvalue : move dans le vecteur
    // v.push_back(v[0]);     // ERREUR : copie impossible, MoveOnly non copiable

    for (const auto& obj : v) {
        std::cout << "  value=" << obj.value << "\n";
    }
    // Sortie attendue : 10, 20, 30

    // Partie 5 : push_back vs emplace_back
    std::cout << "\n=== push_back vs emplace_back ===\n";
    std::vector<Tracked> tv;
    tv.reserve(4);

    // push_back avec un temporaire :
    //   1. Tracked("push-rvalue") : 1 construction
    //   2. move du temporaire dans le vecteur : 1 move
    Tracked::reset();
    tv.push_back(Tracked("push-rvalue"));
    Tracked::print("push_back(Tracked(...))");
    // Attendu : constructions=2 copies=0 moves=1

    // emplace_back avec les args du constructeur :
    //   1. Tracked("emplace") construit directement en place : 1 seule construction
    //   Pas de move de l'objet entier.
    Tracked::reset();
    tv.emplace_back("emplace");
    Tracked::print("emplace_back(\"emplace\")");
    // Attendu : constructions=1 copies=0 moves=0  <- gagne un move !

    // push_back avec une lvalue : force une copie
    Tracked t{"lvalue"};
    Tracked::reset();
    tv.push_back(t);
    Tracked::print("push_back(lvalue)");
    // Attendu : constructions=1 copies=1 moves=0

    // push_back avec std::move : move, pas de copie
    Tracked t2{"moved"};
    Tracked::reset();
    tv.push_back(std::move(t2));
    Tracked::print("push_back(std::move(...))");
    // Attendu : constructions=1 copies=0 moves=1

    // Conclusion :
    //   emplace_back("literal") > push_back("literal")  : 1 ctor vs 1 ctor + 1 move
    //   emplace_back(std::move(t)) == push_back(std::move(t)) : les deux font 1 move

    return 0;
}
