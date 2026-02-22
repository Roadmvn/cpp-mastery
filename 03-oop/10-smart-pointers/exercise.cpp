// ============================================================
// Chapitre 10 : Smart Pointers - Exercices
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// Classe de test avec trace de construction/destruction
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

    // TODO 1.1 : Cree un unique_ptr<Ressource> nomme 'r1' avec make_unique
    //            en lui passant "Buffer-A" comme nom


    // TODO 1.2 : Appelle la methode use() sur r1


    // TODO 1.3 : Transfere la propriete de r1 vers r2 avec std::move
    //            Verifie que r1 est null apres le transfert
    //            Format : "r1 est null apres move : OUI/NON"


    // TODO 1.4 : Appelle use() sur r2


    // A la fin du bloc, r2 est detruit automatiquement -> affiche [FREE]
    cout << endl;
}

// ============================================================
// PARTIE 2 : shared_ptr
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : shared_ptr ===" << endl;

    // TODO 2.1 : Cree un shared_ptr<Ressource> nomme 's1' avec make_shared
    //            en lui passant "Cache-B" comme nom


    // TODO 2.2 : Affiche le compteur de references (use_count)
    //            Format : "use_count apres creation : X"


    // TODO 2.3 : Cree 's2' en copiant s1
    //            Affiche le use_count
    //            Format : "use_count apres copie : X"

    {
        // TODO 2.4 : Cree 's3' en copiant s1 dans ce bloc interne
        //            Affiche use_count ici


        // A la sortie du bloc, s3 est detruit -> use_count decrement
    }
    // TODO 2.5 : Affiche use_count apres la sortie du bloc
    //            Format : "use_count apres sortie de bloc : X"


    cout << endl;
}

// ============================================================
// PARTIE 3 : weak_ptr
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : weak_ptr ===" << endl;

    // TODO 3.1 : Cree un shared_ptr<Ressource> nomme 'owner' avec "Socket-C"


    // TODO 3.2 : Cree un weak_ptr<Ressource> nomme 'observer' depuis 'owner'


    // TODO 3.3 : Utilise observer.lock() pour obtenir un shared_ptr temporaire
    //            Si valide, appelle use() et affiche use_count
    //            Format : "Observer peut acceder a la ressource : OUI/NON"


    // TODO 3.4 : Reset le owner (libere la ressource)
    //            Puis essaie de lock() observer de nouveau
    //            Affiche si l'acces est toujours possible
    //            Format : "Apres reset owner, observer peut acceder : OUI/NON"


    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
