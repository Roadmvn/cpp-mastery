// Chapitre 04 — CRTP : Exercices
// Compilation : g++ -std=c++20 -Wall -Wextra -o exercise exercise.cpp

#include <iostream>
#include <string>
#include <chrono>

// ============================================================
// Exercice 1 : CRTP de base — Shape avec area() et describe()
//
// Créer une classe de base Shape<Derived> avec :
//   - double area() : appelle static_cast<Derived*>(this)->compute_area()
//   - void describe() : affiche le nom du type + son aire
//
// Dériver Circle et Rectangle qui implémentent compute_area().
// ============================================================

// TODO : base CRTP
// template<typename Derived>
// class Shape {
// public:
//     double area() { ... }
//     void describe() { ... }
// };

// TODO : Circle
// class Circle : public Shape<Circle> {
//     double radius_;
// public:
//     Circle(double r) : radius_(r) {}
//     double compute_area() const { return 3.14159 * radius_ * radius_; }
// };

// TODO : Rectangle
// class Rectangle : public Shape<Rectangle> { ... };


// ============================================================
// Exercice 2 : Mixin Comparable
//
// Créer un mixin Comparable<Derived> qui fournit >, <=, >=, !=
// à partir des opérateurs < et == que la dérivée doit implémenter.
//
// Tester avec une classe Price.
// ============================================================

// TODO : mixin
// template<typename Derived>
// struct Comparable {
//     bool operator!=(const Derived& other) const { ... }
//     bool operator>(const Derived& other) const { ... }
//     bool operator<=(const Derived& other) const { ... }
//     bool operator>=(const Derived& other) const { ... }
// };

// TODO : Price qui hérite de Comparable<Price>
// class Price : public Comparable<Price> {
//     double value_;
// public:
//     explicit Price(double v) : value_(v) {}
//     bool operator<(const Price& o) const { return value_ < o.value_; }
//     bool operator==(const Price& o) const { return value_ == o.value_; }
//     double get() const { return value_; }
// };


// ============================================================
// Exercice 3 : Compteur d'instances via CRTP
//
// Créer un mixin InstanceCounter<Derived> qui :
//   - Compte les instances actives (créées moins détruites)
//   - Compte le total créé depuis le début du programme
//   - Expose static int active_count() et static int total_created()
//
// Tester avec deux classes distinctes Order et Trade.
// ============================================================

// TODO : mixin InstanceCounter
// template<typename Derived>
// class InstanceCounter {
//     static inline int active_  = 0;
//     static inline int total_   = 0;
// protected:
//     InstanceCounter()  { ++active_; ++total_; }
//     ~InstanceCounter() { --active_; }
//     InstanceCounter(const InstanceCounter&) { ++active_; ++total_; }
// public:
//     static int active_count()  { return active_; }
//     static int total_created() { return total_; }
// };

// TODO : Order et Trade
// class Order : public InstanceCounter<Order> { ... };
// class Trade : public InstanceCounter<Trade> { ... };


// ============================================================
// Tests
// ============================================================

int main() {
    // Test 1
    // Circle c(5.0);
    // Rectangle r(4.0, 3.0);
    // c.describe();    // "Circle area = 78.5398"
    // r.describe();    // "Rectangle area = 12"

    // Test 2
    // Price p1(100.0), p2(200.0);
    // std::cout << (p1 < p2)  << "\n";   // 1
    // std::cout << (p1 > p2)  << "\n";   // 0
    // std::cout << (p1 <= p2) << "\n";   // 1
    // std::cout << (p1 != p2) << "\n";   // 1

    // Test 3
    // {
    //     Order o1, o2, o3;
    //     Trade t1, t2;
    //     std::cout << "Order active: " << Order::active_count() << "\n";  // 3
    //     std::cout << "Trade active: " << Trade::active_count() << "\n";  // 2
    // }
    // std::cout << "Order active after scope: " << Order::active_count() << "\n";  // 0
    // std::cout << "Order total:  " << Order::total_created() << "\n";  // 3

    std::cout << "Decommentez les tests apres implementation.\n";
    return 0;
}
