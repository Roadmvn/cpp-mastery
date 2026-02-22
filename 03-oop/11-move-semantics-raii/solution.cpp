// ============================================================
// Chapitre 11 : Move Semantics et RAII - Solutions
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <string>
#include <utility>
#include <cstring>
#include <stdexcept>
using namespace std;

// ============================================================
// PARTIE 1 : lvalue vs rvalue
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : lvalue vs rvalue ===" << endl;

    // a = lvalue, 10 = rvalue
    int a = 10;
    // b = lvalue, a+5 = rvalue (temporaire)
    int b = a + 5;
    // s1 = lvalue, "hello" = rvalue
    string s1 = "hello";
    // s2 = lvalue, s1 = lvalue -> COPIE
    string s2 = s1;

    cout << "a=" << a << " b=" << b << " s1=" << s1 << " s2=" << s2 << endl;

    // std::move caste s1 en rvalue -> MOVE : s1 sera vide apres
    string s3 = std::move(s1);
    cout << "s3 (apres move de s1) : \"" << s3 << "\"" << endl;
    cout << "s1 apres move : \"" << s1 << "\" (vide)" << endl;

    cout << endl;
}

// ============================================================
// PARTIE 2 : DynArray avec copy et move
// ============================================================

class DynArray {
    int* data;
    int  size;

public:
    DynArray(int sz, int fill_value)
        : data(new int[sz]), size(sz) {
        for (int i = 0; i < sz; i++) data[i] = fill_value;
        cout << "  [CONSTRUCT] DynArray size=" << size << endl;
    }

    ~DynArray() {
        delete[] data;
        cout << "  [DESTRUCT]  DynArray size=" << size << endl;
    }

    // Copy constructor : allocation + copie element par element
    DynArray(const DynArray& other)
        : data(new int[other.size]), size(other.size) {
        memcpy(data, other.data, size * sizeof(int));
        cout << "  [COPY]      DynArray size=" << size << endl;
    }

    // Move constructor : vol des pointeurs, O(1)
    DynArray(DynArray&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "  [MOVE]      DynArray size=" << size << endl;
    }

    // Copy assignment
    DynArray& operator=(const DynArray& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = new int[size];
        memcpy(data, other.data, size * sizeof(int));
        cout << "  [COPY=]     DynArray size=" << size << endl;
        return *this;
    }

    // Move assignment
    DynArray& operator=(DynArray&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        cout << "  [MOVE=]     DynArray size=" << size << endl;
        return *this;
    }

    void print(const string& label) const {
        cout << "  " << label << " : [";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "] size=" << size << endl;
    }

    bool isValid() const { return data != nullptr; }
};

void partie2() {
    cout << "=== PARTIE 2 : Copy et Move Constructor ===" << endl;

    DynArray original(5, 42);
    original.print("original");

    DynArray copie = original;
    copie.print("copie");
    original.print("original apres copie");

    DynArray moved = std::move(original);
    moved.print("moved");
    cout << "  original valide apres move : " << (original.isValid() ? "OUI" : "NON") << endl;

    cout << "  [sortie de scope -> destructeurs appeles]" << endl;
    cout << endl;
}

// ============================================================
// PARTIE 3 : RAII SocketGuard
// ============================================================

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

class SocketGuard {
    FakeSocket* sock;

public:
    explicit SocketGuard(int port)
        : sock(new FakeSocket(port)) {}

    ~SocketGuard() {
        if (sock) {
            sock->close();
            delete sock;
        }
    }

    // Pas de copie : une connexion = un proprietaire
    SocketGuard(const SocketGuard&)            = delete;
    SocketGuard& operator=(const SocketGuard&) = delete;

    // Move : transfert de propriete
    SocketGuard(SocketGuard&& other) noexcept
        : sock(other.sock) {
        other.sock = nullptr;
    }

    SocketGuard& operator=(SocketGuard&& other) noexcept {
        if (this == &other) return *this;
        if (sock) { sock->close(); delete sock; }
        sock = other.sock;
        other.sock = nullptr;
        return *this;
    }

    void send(const string& msg) {
        if (!sock) throw runtime_error("SocketGuard invalide");
        sock->send(msg);
    }

    bool valid() const { return sock != nullptr; }
};

void partie3() {
    cout << "=== PARTIE 3 : RAII SocketGuard ===" << endl;

    {
        SocketGuard conn(8080);
        conn.send("GET / HTTP/1.1");
        conn.send("Host: target.local");
        cout << "  [conn sort de scope -> fermeture automatique]" << endl;
    }

    // Move entre guards
    cout << "\n  Test move de SocketGuard :" << endl;
    SocketGuard g1(9090);
    g1.send("ping");
    SocketGuard g2 = std::move(g1);
    cout << "  g1 valide apres move : " << (g1.valid() ? "OUI" : "NON") << endl;
    g2.send("pong");
    cout << "  [g1, g2 sortent de scope]" << endl;

    cout << endl;
}

// ============================================================
// BONUS : std::move dans une fonction de retour
// ============================================================

DynArray createArray(int size, int val) {
    DynArray local(size, val);
    // NRVO (Named Return Value Optimization) : le compilateur peut
    // eviter la copie/move. Sinon, move est utilise implicitement.
    return local;
}

void bonus() {
    cout << "=== BONUS : Return Value Optimization (RVO) ===" << endl;
    DynArray result = createArray(3, 7);
    result.print("result");
    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();
    bonus();
    return 0;
}
