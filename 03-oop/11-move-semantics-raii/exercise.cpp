// ============================================================
// Chapitre 11 : Move Semantics et RAII - Exercices
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
// ============================================================

#include <iostream>
#include <string>
#include <utility>
#include <cstring>
using namespace std;

// ============================================================
// PARTIE 1 : Identifier lvalue et rvalue
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : lvalue vs rvalue ===" << endl;

    // Les lignes suivantes sont deja ecrites.
    // Pour chaque expression marquee, indique dans un commentaire :
    // "lvalue" ou "rvalue"

    int a = 10;           // a = ?, 10 = ?
    int b = a + 5;        // b = ?, a+5 = ?
    string s1 = "hello";  // s1 = ?, "hello" = ?
    string s2 = s1;       // s2 = ?, s1 = ?    -> copie ou move ?

    // TODO : Affiche les valeurs pour confirmer que le code compile
    cout << "a=" << a << " b=" << b << " s1=" << s1 << " s2=" << s2 << endl;

    // TODO : Utilise std::move pour transferer s1 vers s3
    //        Affiche s3 et confirme que s1 est vide apres le move

    cout << endl;
}

// ============================================================
// PARTIE 2 : Implementer une classe avec copy et move
// ============================================================

class DynArray {
    int* data;
    int  size;

public:
    // Constructeur
    DynArray(int sz, int fill_value)
        : data(new int[sz]), size(sz) {
        for (int i = 0; i < sz; i++) data[i] = fill_value;
        cout << "  [CONSTRUCT] DynArray size=" << size << endl;
    }

    // Destructeur
    ~DynArray() {
        delete[] data;
        cout << "  [DESTRUCT]  DynArray size=" << size << endl;
    }

    // TODO 2.1 : Implemente le copy constructor
    //            Alloue un nouvel array et copie les elements
    //            Affiche "[COPY] DynArray size=X"
    DynArray(const DynArray& other) = delete; // Remplace par ton implementation

    // TODO 2.2 : Implemente le move constructor
    //            Vole les pointeurs de 'other', met other.data = nullptr
    //            Affiche "[MOVE] DynArray size=X"
    DynArray(DynArray&& other) noexcept = delete; // Remplace par ton implementation

    // TODO 2.3 : Implemente le copy assignment operator
    DynArray& operator=(const DynArray& other) = delete;

    // TODO 2.4 : Implemente le move assignment operator
    DynArray& operator=(DynArray&& other) noexcept = delete;

    void print(const string& label) const {
        cout << "  " << label << " : [";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "] size=" << size << endl;
    }

    int getSize() const { return size; }
    bool isValid() const { return data != nullptr; }
};

void partie2() {
    cout << "=== PARTIE 2 : Copy et Move Constructor ===" << endl;

    DynArray original(5, 42);
    original.print("original");

    // TODO : Decommente apres avoir implemente copy/move
    // DynArray copie = original;
    // copie.print("copie");
    // original.print("original apres copie");

    // DynArray moved = move(original);
    // moved.print("moved");
    // cout << "original valide apres move : " << (original.isValid() ? "OUI" : "NON") << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : RAII - classe qui encapsule une ressource
// ============================================================

// Simule une ressource systeme (connexion, fichier, etc.)
struct FakeSocket {
    int port;
    bool connected;
    FakeSocket(int p) : port(p), connected(true) {
        cout << "  [SOCKET OPEN]  port=" << port << endl;
    }
    void close() {
        if (connected) {
            connected = false;
            cout << "  [SOCKET CLOSE] port=" << port << endl;
        }
    }
    void send(const string& msg) {
        if (connected)
            cout << "  [SEND] port=" << port << " -> " << msg << endl;
    }
};

// TODO 3.1 : Implemente la classe SocketGuard (RAII wrapper)
//            - Constructeur : prend un port, ouvre le socket
//            - Destructeur  : ferme le socket (toujours, meme en cas d'exception)
//            - Pas de copy (= delete)
//            - move possible
//            - Methode send(const string&) qui delegue a FakeSocket

class SocketGuard {
    // TODO : membres et methodes
};

void partie3() {
    cout << "=== PARTIE 3 : RAII SocketGuard ===" << endl;

    // TODO : Cree un SocketGuard sur le port 8080
    //        Envoie quelques messages
    //        Laisse-le sortir de scope -> fermeture automatique

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    return 0;
}
