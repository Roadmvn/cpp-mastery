// ============================================================
// Chapitre 09 - Solution : Classes Abstraites et Interfaces
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ============================================================
// PARTIE 1 : Classe abstraite Forme
// ============================================================

class Forme {
public:
    virtual ~Forme() = default;
    virtual double aire() const = 0;
    virtual std::string description() const = 0;

    void afficher() const {
        std::cout << description() << " | Aire: " << aire() << std::endl;
    }
};

class Rectangle : public Forme {
    double largeur, hauteur;
public:
    Rectangle(double l, double h) : largeur(l), hauteur(h) {}
    double aire() const override { return largeur * hauteur; }
    std::string description() const override {
        return "Rectangle " + std::to_string(largeur) + "x" + std::to_string(hauteur);
    }
};

class Cercle : public Forme {
    double rayon;
public:
    explicit Cercle(double r) : rayon(r) {}
    double aire() const override { return 3.14159265 * rayon * rayon; }
    std::string description() const override {
        return "Cercle R=" + std::to_string(rayon);
    }
};

class Triangle : public Forme {
    double base, hauteur;
public:
    Triangle(double b, double h) : base(b), hauteur(h) {}
    double aire() const override { return base * hauteur / 2.0; }
    std::string description() const override {
        return "Triangle B=" + std::to_string(base) + " H=" + std::to_string(hauteur);
    }
};

// ============================================================
// PARTIE 2 : Interfaces
// ============================================================

class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual std::string to_string() const = 0;
};

class IComparable {
public:
    virtual ~IComparable() = default;
    virtual bool est_superieur(const IComparable& other) const = 0;
};

class Note : public IPrintable, public IComparable {
    double valeur;
public:
    explicit Note(double v) : valeur(v) {
        if (valeur < 0) valeur = 0;
        if (valeur > 20) valeur = 20;
    }

    double get_valeur() const { return valeur; }

    std::string to_string() const override {
        return "Note: " + std::to_string(valeur).substr(0, 5) + "/20";
    }

    bool est_superieur(const IComparable& other) const override {
        const auto* other_note = dynamic_cast<const Note*>(&other);
        if (!other_note) return false;
        return valeur > other_note->valeur;
    }
};

// ============================================================
// PARTIE 3 : Notification abstraite
// ============================================================

class Notification {
public:
    virtual ~Notification() = default;
    virtual void envoyer(const std::string& message) = 0;

    void envoyer_urgente(const std::string& msg) {
        envoyer("[URGENT] " + msg);
    }

    void envoyer_info(const std::string& msg) {
        envoyer("[INFO] " + msg);
    }
};

class EmailNotif : public Notification {
public:
    void envoyer(const std::string& message) override {
        std::cout << "  EMAIL -> " << message << std::endl;
    }
};

class SmsNotif : public Notification {
public:
    void envoyer(const std::string& message) override {
        std::cout << "  SMS   -> " << message << std::endl;
    }
};

class SlackNotif : public Notification {
public:
    void envoyer(const std::string& message) override {
        std::cout << "  SLACK -> " << message << std::endl;
    }
};

int main() {
    std::cout << "=== PARTIE 1 : Formes abstraites ===" << std::endl;
    std::vector<std::unique_ptr<Forme>> formes;
    formes.push_back(std::make_unique<Rectangle>(10, 5));
    formes.push_back(std::make_unique<Cercle>(7));
    formes.push_back(std::make_unique<Triangle>(6, 4));

    double total = 0;
    for (const auto& f : formes) {
        f->afficher();
        total += f->aire();
    }
    std::cout << "Total des aires: " << total << std::endl;

    std::cout << "\n=== PARTIE 2 : Interfaces ===" << std::endl;
    Note n1(15.5), n2(12.0), n3(18.0);
    std::cout << n1.to_string() << std::endl;
    std::cout << n2.to_string() << std::endl;
    std::cout << n3.to_string() << std::endl;

    std::cout << n1.to_string() << " > " << n2.to_string() << " ? "
              << (n1.est_superieur(n2) ? "Oui" : "Non") << std::endl;
    std::cout << n2.to_string() << " > " << n3.to_string() << " ? "
              << (n2.est_superieur(n3) ? "Oui" : "Non") << std::endl;

    std::cout << "\n=== PARTIE 3 : Notifications ===" << std::endl;
    std::vector<std::unique_ptr<Notification>> canaux;
    canaux.push_back(std::make_unique<EmailNotif>());
    canaux.push_back(std::make_unique<SmsNotif>());
    canaux.push_back(std::make_unique<SlackNotif>());

    for (auto& c : canaux) {
        c->envoyer_info("Deploiement termine");
    }

    std::cout << std::endl;
    for (auto& c : canaux) {
        c->envoyer_urgente("Serveur down!");
    }

    return 0;
}
