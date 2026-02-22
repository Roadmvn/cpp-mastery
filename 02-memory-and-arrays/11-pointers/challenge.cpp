// ============================================================
// Chapitre 11 : Pointeurs - Challenge Offensive
// ============================================================
// DEFI : Parcourir et manipuler un buffer avec arithmetique
// de pointeurs — la base de la manipulation memoire.
//
// En securite offensive, comprendre comment naviguer en memoire
// avec des pointeurs est fondamental : injection, lecture de
// buffers, parcours de structures en memoire...
//
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

// Affiche un buffer en hexadecimal (comme un hex dump)
void hexDump(const unsigned char* buffer, int size) {
    for (int i = 0; i < size; i++) {
        if (i % 16 == 0) {
            if (i > 0) cout << endl;
            cout << "  " << setw(4) << setfill('0') << hex << i << ": ";
        }
        cout << setw(2) << setfill('0') << hex
             << (int)buffer[i] << " ";
    }
    cout << dec << endl;
}

// Cherche un pattern dans un buffer (comme un mini scanner memoire)
int findPattern(const unsigned char* buffer, int bufferSize,
                const unsigned char* pattern, int patternSize) {
    for (int i = 0; i <= bufferSize - patternSize; i++) {
        bool found = true;
        for (int j = 0; j < patternSize; j++) {
            if (*(buffer + i + j) != *(pattern + j)) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}

int main() {
    cout << "=== CHALLENGE OFFENSIVE : Manipulation de buffer ===" << endl << endl;

    // --- Partie 1 : Creer et remplir un buffer avec arithmetique de pointeurs ---
    cout << "--- Partie 1 : Ecriture avec pointeurs ---" << endl;

    const int BUFFER_SIZE = 64;
    unsigned char buffer[BUFFER_SIZE];

    // Remplir avec des zeros en utilisant un pointeur
    unsigned char* ptr = buffer;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        *(ptr + i) = 0x00;
    }

    // Ecrire un message a l'offset 0
    const char* message = "PAYLOAD_DATA";
    int msgLen = strlen(message);
    for (int i = 0; i < msgLen; i++) {
        *(ptr + i) = (unsigned char)message[i];
    }

    // Ecrire un marqueur a l'offset 32
    unsigned char marker[] = {0xDE, 0xAD, 0xBE, 0xEF};
    for (int i = 0; i < 4; i++) {
        *(ptr + 32 + i) = marker[i];
    }

    // Ecrire un compteur a l'offset 48
    for (int i = 0; i < 8; i++) {
        *(ptr + 48 + i) = (unsigned char)(0x41 + i);  // A, B, C, D...
    }

    cout << "Buffer apres ecriture :" << endl;
    hexDump(buffer, BUFFER_SIZE);
    cout << endl;

    // --- Partie 2 : Lire des donnees a differents offsets ---
    cout << "--- Partie 2 : Lecture avec pointeurs ---" << endl;

    // Lire le message au debut
    cout << "Message a offset 0 : ";
    char* readPtr = (char*)buffer;
    while (*readPtr != 0x00) {
        cout << *readPtr;
        readPtr++;
    }
    cout << endl;

    // Lire le marqueur a offset 32
    cout << "Marqueur a offset 32 : 0x";
    for (int i = 0; i < 4; i++) {
        cout << hex << setw(2) << setfill('0') << (int)*(buffer + 32 + i);
    }
    cout << dec << endl;

    // Lire le compteur a offset 48
    cout << "Donnees a offset 48 : ";
    for (int i = 0; i < 8; i++) {
        cout << (char)*(buffer + 48 + i);
    }
    cout << endl << endl;

    // --- Partie 3 : Recherche de pattern dans le buffer ---
    cout << "--- Partie 3 : Pattern scanning ---" << endl;

    unsigned char searchPattern[] = {0xDE, 0xAD, 0xBE, 0xEF};
    int offset = findPattern(buffer, BUFFER_SIZE, searchPattern, 4);

    if (offset >= 0) {
        cout << "Pattern 0xDEADBEEF trouve a l'offset " << offset << endl;
    } else {
        cout << "Pattern non trouve" << endl;
    }

    unsigned char textPattern[] = "PAYLOAD";
    offset = findPattern(buffer, BUFFER_SIZE, textPattern, 7);
    if (offset >= 0) {
        cout << "Pattern 'PAYLOAD' trouve a l'offset " << offset << endl;
    }
    cout << endl;

    // --- Partie 4 : Reinterpreter des donnees (type punning) ---
    cout << "--- Partie 4 : Reinterpretation de donnees ---" << endl;

    // Ecrire un int a offset 56 via un pointeur int*
    int* intPtr = (int*)(buffer + 56);
    *intPtr = 0x48465421;  // "HFT!" en ASCII (little-endian)

    cout << "Int ecrit a offset 56 : 0x" << hex << *intPtr << dec << endl;
    cout << "Octets individuels : ";
    for (int i = 0; i < 4; i++) {
        cout << (char)*(buffer + 56 + i);
    }
    cout << endl << endl;

    cout << "Buffer final :" << endl;
    hexDump(buffer, BUFFER_SIZE);
    cout << endl;

    cout << "--- Concepts offensifs demontres ---" << endl;
    cout << "1. Ecriture a des offsets arbitraires (base de l'injection)" << endl;
    cout << "2. Lecture de donnees brutes (base de l'exfiltration)" << endl;
    cout << "3. Pattern scanning (base du signature matching)" << endl;
    cout << "4. Type punning (reinterpreter des octets comme differents types)" << endl;

    return 0;
}
