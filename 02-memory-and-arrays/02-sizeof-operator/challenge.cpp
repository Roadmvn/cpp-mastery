// =============================================================
// Challenge Offensive : Analyse memoire de structures de donnees
// =============================================================
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// =============================================================
// Contexte : Tu fais du reverse engineering sur un protocole binaire.
// Tu dois analyser la taille memoire de differentes structures pour
// comprendre comment les donnees sont disposees et trouver les offsets
// corrects pour extraire les champs.
// =============================================================

#include <iostream>
#include <cstring>
using namespace std;

// Structure 1 : Header de paquet reseau (mal ordonnee)
struct PacketHeaderBad {
    char version;        // 1 octet
    int sequence;        // 4 octets
    char flags;          // 1 octet
    double timestamp;    // 8 octets
    short length;        // 2 octets
};

// Structure 2 : Header de paquet reseau (optimisee)
struct PacketHeaderGood {
    double timestamp;    // 8 octets
    int sequence;        // 4 octets
    short length;        // 2 octets
    char version;        // 1 octet
    char flags;          // 1 octet
};

// Structure 3 : Credential interceptee
struct Credential {
    char username[32];
    char password_hash[64];
    int privilege_level;
    bool is_admin;
};

// Structure 4 : Entry de table d'allocation (simulee)
struct AllocationEntry {
    void* address;
    size_t size;
    char tag[8];
    bool in_use;
};

int main() {
    cout << "=== Analyse memoire offensive ===" << endl;
    cout << endl;

    // --- Analyse du padding ---
    cout << "--- Padding et alignement ---" << endl;
    cout << "PacketHeaderBad  : " << sizeof(PacketHeaderBad)  << " octets" << endl;
    cout << "PacketHeaderGood : " << sizeof(PacketHeaderGood) << " octets" << endl;

    size_t sommeChampsBad = sizeof(char) + sizeof(int) + sizeof(char)
                          + sizeof(double) + sizeof(short);
    cout << "Somme brute des champs : " << sommeChampsBad << " octets" << endl;
    cout << "Padding gaspille (Bad) : "
         << sizeof(PacketHeaderBad) - sommeChampsBad << " octets" << endl;
    cout << "Padding gaspille (Good): "
         << sizeof(PacketHeaderGood) - sommeChampsBad << " octets" << endl;

    // --- Calcul des offsets manuels ---
    cout << "\n--- Offsets des champs (PacketHeaderGood) ---" << endl;
    PacketHeaderGood pkt;
    char* base = reinterpret_cast<char*>(&pkt);
    cout << "timestamp : offset " << (reinterpret_cast<char*>(&pkt.timestamp) - base) << endl;
    cout << "sequence  : offset " << (reinterpret_cast<char*>(&pkt.sequence) - base) << endl;
    cout << "length    : offset " << (reinterpret_cast<char*>(&pkt.length) - base) << endl;
    cout << "version   : offset " << (reinterpret_cast<char*>(&pkt.version) - base) << endl;
    cout << "flags     : offset " << (reinterpret_cast<char*>(&pkt.flags) - base) << endl;

    // --- Analyse de la structure Credential ---
    cout << "\n--- Structure Credential ---" << endl;
    cout << "sizeof(Credential)  : " << sizeof(Credential) << " octets" << endl;
    Credential cred;
    char* credBase = reinterpret_cast<char*>(&cred);
    cout << "username        : offset " << (reinterpret_cast<char*>(&cred.username) - credBase)
         << ", taille " << sizeof(cred.username) << endl;
    cout << "password_hash   : offset " << (reinterpret_cast<char*>(&cred.password_hash) - credBase)
         << ", taille " << sizeof(cred.password_hash) << endl;
    cout << "privilege_level : offset " << (reinterpret_cast<char*>(&cred.privilege_level) - credBase)
         << ", taille " << sizeof(cred.privilege_level) << endl;
    cout << "is_admin        : offset " << (reinterpret_cast<char*>(&cred.is_admin) - credBase)
         << ", taille " << sizeof(cred.is_admin) << endl;

    // --- Simulation : lire un champ a partir d'un buffer brut ---
    cout << "\n--- Simulation extraction de champ ---" << endl;
    // On remplit une structure puis on la lit comme un buffer brut
    PacketHeaderGood original;
    original.timestamp = 1677654321.123;
    original.sequence = 42;
    original.length = 1024;
    original.version = 2;
    original.flags = 0x0F;

    // "Buffer brut" recu sur le reseau
    char rawBuffer[sizeof(PacketHeaderGood)];
    memcpy(rawBuffer, &original, sizeof(PacketHeaderGood));

    // Extraction manuelle par offsets
    double* ts = reinterpret_cast<double*>(rawBuffer + 0);
    int* seq = reinterpret_cast<int*>(rawBuffer + 8);
    short* len = reinterpret_cast<short*>(rawBuffer + 12);
    char ver = rawBuffer[14];
    char flg = rawBuffer[15];

    cout << "Timestamp extrait : " << *ts << endl;
    cout << "Sequence extraite : " << *seq << endl;
    cout << "Length extraite   : " << *len << endl;
    cout << "Version extraite  : " << (int)ver << endl;
    cout << "Flags extraits    : 0x" << hex << (int)(unsigned char)flg << dec << endl;

    // --- Resume memoire total ---
    cout << "\n--- Resume total ---" << endl;
    cout << "AllocationEntry  : " << sizeof(AllocationEntry) << " octets" << endl;
    cout << "1000 entries     : " << sizeof(AllocationEntry) * 1000 << " octets ("
         << sizeof(AllocationEntry) * 1000 / 1024 << " KB)" << endl;

    return 0;
}
