// ============================================================
// Chapitre 10 : Smart Pointers - Solutions
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Ressource {
    string name;
public:
    explicit Ressource(const string& n) : name(n) {
        cout << "[ALLOC]  Ressource : " << name << endl;
    }
    ~Ressource() {
        cout << "[FREE]   Ressource : " << name << endl;
    }
    void use() const {
        cout << "[USE]    Ressource : " << name << endl;
    }
    const string& getName() const { return name; }
};

// ============================================================
// PARTIE 1 : unique_ptr
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : unique_ptr ===" << endl;

    // 1.1 : Creation avec make_unique
    auto r1 = make_unique<Ressource>("Buffer-A");

    // 1.2 : Utilisation
    r1->use();

    // 1.3 : Transfert de propriete
    auto r2 = std::move(r1);
    cout << "r1 est null apres move : " << (r1 == nullptr ? "OUI" : "NON") << endl;

    // 1.4 : Utilisation via r2
    r2->use();

    cout << "[r2 sort de scope -> destruction automatique]" << endl;
    cout << endl;
}

// ============================================================
// PARTIE 2 : shared_ptr
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : shared_ptr ===" << endl;

    // 2.1 : Creation
    auto s1 = make_shared<Ressource>("Cache-B");
    cout << "use_count apres creation : " << s1.use_count() << endl;

    // 2.2 : Copie
    auto s2 = s1;
    cout << "use_count apres copie : " << s1.use_count() << endl;

    {
        // 2.3 : Copie dans bloc interne
        auto s3 = s1;
        cout << "use_count dans le bloc : " << s1.use_count() << endl;
        // s3 detruit ici
    }

    // 2.4 : Apres sortie du bloc
    cout << "use_count apres sortie de bloc : " << s1.use_count() << endl;

    cout << "[s1 et s2 sortent de scope -> destruction]" << endl;
    cout << endl;
}

// ============================================================
// PARTIE 3 : weak_ptr
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : weak_ptr ===" << endl;

    // 3.1 : Creation du shared_ptr
    auto owner = make_shared<Ressource>("Socket-C");

    // 3.2 : Observation sans propriete
    weak_ptr<Ressource> observer = owner;

    // 3.3 : Acces via lock()
    if (auto locked = observer.lock()) {
        cout << "Observer peut acceder a la ressource : OUI" << endl;
        locked->use();
        cout << "use_count pendant lock : " << locked.use_count() << endl;
    } else {
        cout << "Observer peut acceder a la ressource : NON" << endl;
    }

    // 3.4 : Liberation de l'owner
    owner.reset();
    cout << "[owner reset -> ressource liberee]" << endl;

    if (auto locked = observer.lock()) {
        cout << "Apres reset owner, observer peut acceder : OUI" << endl;
    } else {
        cout << "Apres reset owner, observer peut acceder : NON" << endl;
    }

    cout << endl;
}

// ============================================================
// BONUS : unique_ptr dans un vecteur (pattern classique)
// ============================================================

void bonus() {
    cout << "=== BONUS : vector de unique_ptr ===" << endl;

    vector<unique_ptr<Ressource>> pool;
    pool.push_back(make_unique<Ressource>("Thread-1"));
    pool.push_back(make_unique<Ressource>("Thread-2"));
    pool.push_back(make_unique<Ressource>("Thread-3"));

    cout << "Pool de " << pool.size() << " ressources :" << endl;
    for (const auto& r : pool) {
        r->use();
    }

    pool.erase(pool.begin() + 1); // Libere Thread-2
    cout << "Apres suppression de Thread-2 : " << pool.size() << " ressource(s)" << endl;

    cout << "[pool sort de scope -> destruction des restants]" << endl;
    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    bonus();
    return 0;
}
