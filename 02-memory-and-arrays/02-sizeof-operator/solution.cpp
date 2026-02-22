// =============================================================
// Solution : L'operateur sizeof
// =============================================================
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// =============================================================

#include <iostream>
using namespace std;

struct Packet {
    char type;
    int id;
    double value;
};

struct PacketOptimized {
    double value;
    int id;
    char type;
};

int main() {
    // ==========================================================
    // PARTIE 1 : sizeof sur les types fondamentaux
    // ==========================================================

    // 1.1
    cout << "=== Types fondamentaux ===" << endl;
    cout << "char   : " << sizeof(char)   << " octet(s)" << endl;
    cout << "short  : " << sizeof(short)  << " octet(s)" << endl;
    cout << "int    : " << sizeof(int)    << " octet(s)" << endl;
    cout << "long   : " << sizeof(long)   << " octet(s)" << endl;
    cout << "float  : " << sizeof(float)  << " octet(s)" << endl;
    cout << "double : " << sizeof(double) << " octet(s)" << endl;
    cout << "bool   : " << sizeof(bool)   << " octet(s)" << endl;

    // 1.2
    cout << "\n=== Pointeur ===" << endl;
    cout << "int*   : " << sizeof(int*) << " octet(s)" << endl;

    // 1.3
    cout << "\n=== Types etendus ===" << endl;
    cout << "long long   : " << sizeof(long long)   << " octet(s)" << endl;
    cout << "long double : " << sizeof(long double)  << " octet(s)" << endl;

    // ==========================================================
    // PARTIE 2 : sizeof sur les arrays
    // ==========================================================

    int numbers[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    double values[5] = {1.1, 2.2, 3.3, 4.4, 5.5};

    // 2.1
    cout << "\n=== Arrays ===" << endl;
    cout << "sizeof(numbers) : " << sizeof(numbers) << " octets" << endl;
    cout << "sizeof(values)  : " << sizeof(values)  << " octets" << endl;

    // 2.2
    cout << "numbers : " << sizeof(numbers) / sizeof(numbers[0]) << " elements" << endl;
    cout << "values  : " << sizeof(values) / sizeof(values[0])   << " elements" << endl;

    // 2.3
    char buffer[100];
    cout << "sizeof(buffer[100]) : " << sizeof(buffer) << " octets" << endl;

    // ==========================================================
    // PARTIE 3 : sizeof sur les structs
    // ==========================================================

    // 3.1
    cout << "\n=== Structs ===" << endl;
    cout << "sizeof(Packet)          : " << sizeof(Packet) << " octets" << endl;

    // 3.2
    cout << "sizeof(PacketOptimized) : " << sizeof(PacketOptimized) << " octets" << endl;
    cout << "Difference              : "
         << sizeof(Packet) - sizeof(PacketOptimized) << " octets economises" << endl;

    // 3.3
    Packet arrP[10];
    PacketOptimized arrPO[10];
    cout << "\n=== Arrays de structs ===" << endl;
    cout << "10 x Packet          : " << sizeof(arrP)  << " octets" << endl;
    cout << "10 x PacketOptimized : " << sizeof(arrPO) << " octets" << endl;
    cout << "Economie totale      : "
         << sizeof(arrP) - sizeof(arrPO) << " octets" << endl;

    return 0;
}
