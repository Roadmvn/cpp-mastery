// =============================================================
// Challenge Offensive : Recherche de signature dans un buffer
// =============================================================
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// =============================================================
// Contexte : Tu analyses un dump memoire (simule) pour chercher des
// signatures connues (magic bytes). C'est la base de la detection
// de malware et du forensic : scanner un buffer octet par octet
// pour trouver des patterns specifiques.
//
// Signatures recherchees :
// - ELF binary  : 0x7F 0x45 0x4C 0x46
// - PE/Windows  : 0x4D 0x5A (MZ header)
// - PDF         : 0x25 0x50 0x44 0x46 (%PDF)
// - PNG image   : 0x89 0x50 0x4E 0x47
// =============================================================

#include <iostream>
#include <iomanip>
using namespace std;

// Recherche d'un pattern dans un buffer (recherche lineaire sur bytes)
// Retourne l'offset du debut du pattern, ou -1 si non trouve
int findPattern(const unsigned char buffer[], int bufferSize,
                const unsigned char pattern[], int patternSize) {
    for (int i = 0; i <= bufferSize - patternSize; i++) {
        bool match = true;
        for (int j = 0; j < patternSize; j++) {
            if (buffer[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

// Recherche de TOUTES les occurrences d'un pattern
int findAllPatterns(const unsigned char buffer[], int bufferSize,
                    const unsigned char pattern[], int patternSize,
                    int results[], int maxResults) {
    int found = 0;
    for (int i = 0; i <= bufferSize - patternSize && found < maxResults; i++) {
        bool match = true;
        for (int j = 0; j < patternSize; j++) {
            if (buffer[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            results[found] = i;
            found++;
        }
    }
    return found;
}

// Affiche un extrait du buffer en hexadecimal
void hexDump(const unsigned char buffer[], int offset, int length) {
    cout << hex << setfill('0');
    for (int i = 0; i < length; i++) {
        cout << setw(2) << (int)buffer[offset + i] << " ";
    }
    cout << dec << setfill(' ');
}

int main() {
    // Dump memoire simule (128 octets)
    // On y a cache plusieurs "fichiers" a differents offsets
    unsigned char memDump[] = {
        // Offset 0x00 : donnees random
        0x00, 0x01, 0x02, 0x03, 0xFF, 0xFE, 0xFD, 0xFC,
        0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,
        // Offset 0x10 : ELF binary cache ici
        0x7F, 0x45, 0x4C, 0x46, 0x02, 0x01, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // Offset 0x20 : donnees random
        0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11,
        0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
        // Offset 0x30 : PDF cache ici
        0x25, 0x50, 0x44, 0x46, 0x2D, 0x31, 0x2E, 0x34,
        0x0A, 0x25, 0xC4, 0xE5, 0xF2, 0xE5, 0xEB, 0xA7,
        // Offset 0x40 : PE (MZ) cache ici
        0x4D, 0x5A, 0x90, 0x00, 0x03, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
        // Offset 0x50 : PNG cache ici
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
        0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
        // Offset 0x60 : un deuxieme MZ cache
        0x00, 0x00, 0x00, 0x00, 0x4D, 0x5A, 0x90, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xDE, 0xAD, 0xBE, 0xEF,
        // Offset 0x70 : padding
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xCA, 0xFE, 0xBA, 0xBE, 0x00, 0x00, 0x00, 0x00
    };
    int dumpSize = sizeof(memDump);

    // Signatures a rechercher
    unsigned char sigELF[] = {0x7F, 0x45, 0x4C, 0x46};
    unsigned char sigMZ[]  = {0x4D, 0x5A};
    unsigned char sigPDF[] = {0x25, 0x50, 0x44, 0x46};
    unsigned char sigPNG[] = {0x89, 0x50, 0x4E, 0x47};
    unsigned char sigCAFE[] = {0xCA, 0xFE, 0xBA, 0xBE}; // Java class / Mach-O

    cout << "=== Scanner de signatures memoire ===" << endl;
    cout << "Taille du dump : " << dumpSize << " octets" << endl;
    cout << endl;

    // --- Scan de chaque signature ---
    struct Signature {
        const char* name;
        unsigned char* bytes;
        int size;
        const char* description;
    };

    Signature sigs[] = {
        {"ELF",      sigELF,  4, "Linux/Unix executable"},
        {"MZ (PE)",  sigMZ,   2, "Windows executable"},
        {"PDF",      sigPDF,  4, "Document PDF"},
        {"PNG",      sigPNG,  4, "Image PNG"},
        {"CAFEBABE", sigCAFE, 4, "Java class / Mach-O fat binary"}
    };
    int nbSigs = sizeof(sigs) / sizeof(sigs[0]);

    int totalFound = 0;
    cout << "--- Resultats du scan ---" << endl;

    for (int s = 0; s < nbSigs; s++) {
        int results[10];
        int found = findAllPatterns(memDump, dumpSize,
                                    sigs[s].bytes, sigs[s].size,
                                    results, 10);

        if (found > 0) {
            totalFound += found;
            for (int r = 0; r < found; r++) {
                cout << "[FOUND] " << sigs[s].name << " (" << sigs[s].description
                     << ") a l'offset 0x" << hex << setw(2) << setfill('0')
                     << results[r] << dec << setfill(' ') << endl;
                cout << "        Bytes: ";
                int contextLen = (results[r] + 16 <= dumpSize) ? 16 : dumpSize - results[r];
                hexDump(memDump, results[r], contextLen);
                cout << endl;
            }
        } else {
            cout << "[-----] " << sigs[s].name << " non trouve" << endl;
        }
    }

    // --- Resume ---
    cout << "\n--- Resume ---" << endl;
    cout << "Signatures detectees : " << totalFound << endl;
    cout << "Taille scannee       : " << dumpSize << " octets" << endl;

    // Detection de patterns suspects
    cout << "\n--- Analyse complementaire ---" << endl;
    unsigned char deadbeef[] = {0xDE, 0xAD, 0xBE, 0xEF};
    int dbOffset = findPattern(memDump, dumpSize, deadbeef, 4);
    if (dbOffset != -1) {
        cout << "[WARN] Pattern 0xDEADBEEF detecte a l'offset 0x"
             << hex << dbOffset << dec
             << " (marqueur de debug/sentinel)" << endl;
    }

    // Compter les octets nuls (zones non initialisees ou padding)
    int nullCount = 0;
    for (int i = 0; i < dumpSize; i++) {
        if (memDump[i] == 0x00) nullCount++;
    }
    cout << "Octets nuls : " << nullCount << "/" << dumpSize
         << " (" << (nullCount * 100 / dumpSize) << "%)" << endl;

    return 0;
}
