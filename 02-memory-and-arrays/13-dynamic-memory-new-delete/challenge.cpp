// ============================================================
// Chapitre 13 : Memoire Dynamique - Challenge Offensive
// ============================================================
// DEFI : Allouer dynamiquement un buffer, y ecrire des donnees,
// le manipuler et le liberer proprement.
//
// C'est le pattern de base utilise dans les loaders : allouer
// un espace memoire, y placer du contenu (payload), l'executer
// ou le transmettre, puis nettoyer.
//
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// Affiche un buffer en hex dump
void hexDump(const char* label, const unsigned char* buf, int size) {
    cout << label << " (" << size << " octets) :" << endl;
    for (int i = 0; i < size; i++) {
        if (i % 16 == 0) {
            if (i > 0) cout << endl;
            cout << "  " << setw(4) << setfill('0') << hex << i << ": ";
        }
        cout << setw(2) << setfill('0') << hex << (int)buf[i] << " ";
    }
    cout << dec << endl << endl;
}

// XOR encode/decode un buffer (operation reversible)
void xorBuffer(unsigned char* buf, int size, unsigned char key) {
    for (int i = 0; i < size; i++) {
        buf[i] ^= key;
    }
}

// Zero out un buffer (securise la memoire avant liberation)
void secureWipe(unsigned char* buf, int size) {
    for (int i = 0; i < size; i++) {
        buf[i] = 0x00;
    }
}

int main() {
    cout << "=== CHALLENGE OFFENSIVE : Buffer Dynamique ===" << endl << endl;

    // --- Etape 1 : Allocation du buffer ---
    cout << "--- Etape 1 : Allocation ---" << endl;
    const int BUFFER_SIZE = 64;
    unsigned char* buffer = new unsigned char[BUFFER_SIZE];

    // Initialiser a zero
    memset(buffer, 0x00, BUFFER_SIZE);
    cout << "Buffer alloue a l'adresse : " << (void*)buffer << endl;
    cout << "Taille : " << BUFFER_SIZE << " octets" << endl << endl;

    // --- Etape 2 : Ecrire des donnees dans le buffer ---
    cout << "--- Etape 2 : Ecriture du payload ---" << endl;

    // Header (4 octets)
    buffer[0] = 0x7F;  // Magic byte
    buffer[1] = 'E';
    buffer[2] = 'L';
    buffer[3] = 'F';   // Simule un en-tete ELF

    // Donnees texte a offset 8
    const char* payload = "HELLO_WORLD";
    memcpy(buffer + 8, payload, strlen(payload));

    // Signature a la fin
    buffer[60] = 0xCA;
    buffer[61] = 0xFE;
    buffer[62] = 0xBA;
    buffer[63] = 0xBE;

    hexDump("Buffer avec payload", buffer, BUFFER_SIZE);

    // --- Etape 3 : Encodage XOR ---
    cout << "--- Etape 3 : Encodage XOR ---" << endl;
    unsigned char key = 0x42;
    cout << "Cle XOR : 0x" << hex << (int)key << dec << endl;

    xorBuffer(buffer, BUFFER_SIZE, key);
    hexDump("Buffer encode", buffer, BUFFER_SIZE);

    // --- Etape 4 : Decodage XOR ---
    cout << "--- Etape 4 : Decodage XOR ---" << endl;
    xorBuffer(buffer, BUFFER_SIZE, key);  // XOR est son propre inverse
    hexDump("Buffer decode", buffer, BUFFER_SIZE);

    // Verifier le header
    cout << "Verification header : ";
    if (buffer[0] == 0x7F && buffer[1] == 'E' &&
        buffer[2] == 'L' && buffer[3] == 'F') {
        cout << "OK (ELF header intact)" << endl;
    } else {
        cout << "ERREUR (header corrompu)" << endl;
    }

    // Verifier la signature
    cout << "Verification signature : ";
    if (buffer[60] == 0xCA && buffer[61] == 0xFE &&
        buffer[62] == 0xBA && buffer[63] == 0xBE) {
        cout << "OK (0xCAFEBABE)" << endl;
    } else {
        cout << "ERREUR (signature corrompue)" << endl;
    }

    // Lire le payload texte
    cout << "Payload : ";
    for (int i = 8; i < 8 + (int)strlen(payload); i++) {
        cout << (char)buffer[i];
    }
    cout << endl << endl;

    // --- Etape 5 : Nettoyage securise ---
    cout << "--- Etape 5 : Nettoyage securise ---" << endl;
    secureWipe(buffer, BUFFER_SIZE);
    hexDump("Buffer apres wipe", buffer, BUFFER_SIZE);

    // --- Etape 6 : Liberation ---
    delete[] buffer;
    buffer = nullptr;
    cout << "Buffer libere et pointeur mis a nullptr" << endl << endl;

    cout << "--- Concepts demontres ---" << endl;
    cout << "1. Allocation dynamique d'un buffer (new[])" << endl;
    cout << "2. Ecriture de donnees a des offsets specifiques" << endl;
    cout << "3. Encodage/decodage XOR (obfuscation basique)" << endl;
    cout << "4. Verification d'integrite (header + signature)" << endl;
    cout << "5. Wipe securise avant liberation (anti-forensics)" << endl;
    cout << "6. Liberation propre (delete[] + nullptr)" << endl;

    return 0;
}
