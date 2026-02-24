// Chapitre 04 — CRTP : Solution
// Compilation : g++ -std=c++20 -Wall -Wextra -o solution solution.cpp

#include <iostream>
#include <string>
#include <numbers>  // std::numbers::pi (C++20)

// ============================================================
// Exercice 1 : Shape CRTP
// ============================================================

template<typename Derived>
class Shape {
public:
    double area() const {
        return static_cast<const Derived*>(this)->compute_area();
    }

    void describe() const {
        std::cout << typeid(Derived).name() << " area = " << area() << "\n";
    }
};

class Circle : public Shape<Circle> {
    double radius_;
public:
    explicit Circle(double r) : radius_(r) {}
    double compute_area() const {
        return std::numbers::pi * radius_ * radius_;
    }
};

class Rectangle : public Shape<Rectangle> {
    double width_, height_;
public:
    Rectangle(double w, double h) : width_(w), height_(h) {}
    double compute_area() const {
        return width_ * height_;
    }
};

class Triangle : public Shape<Triangle> {
    double base_, height_;
public:
    Triangle(double b, double h) : base_(b), height_(h) {}
    double compute_area() const {
        return 0.5 * base_ * height_;
    }
};

// ============================================================
// Exercice 2 : Mixin Comparable
// ============================================================

template<typename Derived>
struct Comparable {
    bool operator!=(const Derived& other) const {
        return !(static_cast<const Derived&>(*this) == other);
    }
    bool operator>(const Derived& other) const {
        return other < static_cast<const Derived&>(*this);
    }
    bool operator<=(const Derived& other) const {
        return !(other < static_cast<const Derived&>(*this));
    }
    bool operator>=(const Derived& other) const {
        return !(static_cast<const Derived&>(*this) < other);
    }
};

class Price : public Comparable<Price> {
    double value_;
public:
    explicit Price(double v) : value_(v) {}
    bool operator<(const Price& o) const  { return value_ < o.value_; }
    bool operator==(const Price& o) const { return value_ == o.value_; }
    double get() const { return value_; }
};

// ============================================================
// Exercice 3 : Compteur d'instances
// ============================================================

template<typename Derived>
class InstanceCounter {
    static inline int active_ = 0;
    static inline int total_  = 0;
protected:
    InstanceCounter()  { ++active_; ++total_; }
    ~InstanceCounter() { --active_; }
    // Copie : crée une nouvelle instance
    InstanceCounter(const InstanceCounter&) { ++active_; ++total_; }
    InstanceCounter& operator=(const InstanceCounter&) = default;
public:
    static int active_count()  { return active_; }
    static int total_created() { return total_; }
};

class Order : public InstanceCounter<Order> {
public:
    int id;
    explicit Order(int i) : id(i) {}
};

class Trade : public InstanceCounter<Trade> {
public:
    int id;
    explicit Trade(int i) : id(i) {}
};

// ============================================================
// Tests
// ============================================================

int main() {
    std::cout << std::boolalpha;

    // Test 1 : Shape
    std::cout << "=== Shape ===\n";
    Circle c(5.0);
    Rectangle r(4.0, 3.0);
    Triangle t(6.0, 4.0);
    c.describe();  // Circle area = 78.5398...
    r.describe();  // Rectangle area = 12
    t.describe();  // Triangle area = 12

    // Template function qui fonctionne avec tous les shapes
    auto print_area = [](const auto& shape) {
        std::cout << "  area = " << shape.area() << "\n";
    };
    print_area(c);
    print_area(r);
    print_area(t);

    // Test 2 : Comparable / Price
    std::cout << "\n=== Comparable ===\n";
    Price p1(100.0), p2(200.0), p3(100.0);

    std::cout << "p1 < p2  : " << (p1 < p2)  << "\n";  // true
    std::cout << "p1 > p2  : " << (p1 > p2)  << "\n";  // false
    std::cout << "p1 <= p2 : " << (p1 <= p2) << "\n";  // true
    std::cout << "p1 >= p2 : " << (p1 >= p2) << "\n";  // false
    std::cout << "p1 == p3 : " << (p1 == p3) << "\n";  // true
    std::cout << "p1 != p2 : " << (p1 != p2) << "\n";  // true

    // Test 3 : InstanceCounter
    std::cout << "\n=== InstanceCounter ===\n";
    {
        Order o1(1), o2(2), o3(3);
        Trade t1(10), t2(20);

        std::cout << "Order active: " << Order::active_count() << "\n";  // 3
        std::cout << "Trade active: " << Trade::active_count() << "\n";  // 2

        Order o4 = o1;  // copie
        std::cout << "Order active (after copy): " << Order::active_count() << "\n"; // 4
    }
    std::cout << "Order active (after scope): " << Order::active_count() << "\n"; // 0
    std::cout << "Order total created: " << Order::total_created() << "\n";       // 4
    std::cout << "Trade total created: " << Trade::total_created() << "\n";       // 2

    return 0;
}
