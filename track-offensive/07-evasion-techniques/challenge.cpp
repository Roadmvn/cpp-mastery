// Chapitre 07 - Challenge : XOR Encoder/Decoder + Detection de VM
// EDUCATIF - CTF / Labs de securite uniquement
//
// Compile :
//   g++ -std=c++17 -o challenge challenge.cpp
//   ./challenge
//
// ============================================================
// CHALLENGE DESCRIPTION
// ============================================================
//
// Tu dois implementer un outil complet de:
//
//  PARTIE A - XOR Encoder/Decoder interactif
//    - L'utilisateur entre une string et une cle (0-255)
//    - Le programme affiche la version encodee (hex) ET decodee
//    - Il verifie que encode(decode(s)) == s
//    - Genere le code C++ du tableau statique correspondant
//
//  PARTIE B - Detecteur de VM enrichi
//    Ajouter ces heuristiques supplementaires :
//    a) Verifier si des variables d'env d'analyse sont presentes
//       (CUCKOO, SANDBOX, ANALYSIS_ENV, etc.)
//    b) Verifier si le repertoire /tmp contient des patterns suspects
//       (pillow, panda, etc.)  Linux uniquement, skip sur macOS
//    c) Calculer un score final et afficher un rapport detaille
//
//  PARTIE C - Demonstration pedagogique
//    - Encoder la string "connect_to_c2" avec ta cle choisie
//    - Decoder a la volee et afficher
//    - Montrer comment un outil de strings ne voit PAS la string originale
//
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <climits>
    #ifdef __APPLE__
        #include <sys/types.h>
        #include <sys/sysctl.h>
    #else
        #include <sys/sysinfo.h>
    #endif
#endif

// ============================================================
// PARTIE A : XOR Encoder/Decoder
// ============================================================

// TODO A1 : Implementer xorTransform (encode ET decode, c'est la meme operation)
std::vector<uint8_t> xorTransform(const std::string& input, uint8_t key) {
    // TON CODE ICI
    return {};
}

// TODO A2 : Afficher un vecteur de bytes en hexadecimal
void printHex(const std::vector<uint8_t>& data) {
    // TON CODE ICI
    // Format attendu : 0x22 0x13 0x08 ...
}

// TODO A3 : Generer le code C++ d'un tableau statique
// Output attendu :
//   static const std::vector<uint8_t> ENCODED = {
//       0x22, 0x13, 0x08, 0x14, 0x12, 0x14
//   };
void generateCppArray(const std::vector<uint8_t>& data, const std::string& varname) {
    // TON CODE ICI
}

// ============================================================
// PARTIE B : Detecteur de VM enrichi
// ============================================================

struct VMReport {
    int cpu_count;
    double ram_gb;
    bool suspicious_hostname;
    bool suspicious_env_vars;
    int score;
    std::vector<std::string> indicators;
};

// TODO B1 : Verifier les variables d'environnement d'analyse
bool checkSuspiciousEnvVars(VMReport& report) {
    static const std::vector<std::string> suspect_vars = {
        "CUCKOO", "SANDBOX", "ANALYSIS_ENV", "MALWARE_ANALYSIS", "PANDA"
    };

    // TON CODE ICI
    // Pour chaque var dans suspect_vars :
    //   getenv(var.c_str()) != nullptr  var presente  suspect
    // Ajouter les indicateurs dans report.indicators
    // Retourner true si au moins une variable trouvee

    return false;
}

// TODO B2 : Assemblage du rapport complet
VMReport buildVMReport() {
    VMReport report = {};

    // TON CODE ICI
    // 1. Remplir cpu_count, ram_gb, suspicious_hostname, suspicious_env_vars
    // 2. Calculer le score :
    //    cpu_count < 2      +1
    //    ram_gb < 2         +1
    //    suspicious_hostname  +2
    //    suspicious_env_vars  +2
    // 3. Retourner le rapport

    return report;
}

// TODO B3 : Afficher le rapport de maniere lisible
void printReport(const VMReport& r) {
    // TON CODE ICI
    // Format :
    // === Rapport de Detection ===
    // CPUs          : X
    // RAM           : X.XX GB
    // Hostname      : suspect / normal
    // Env vars      : suspect / normal
    // Indicateurs   : ...
    // Score         : X/6
    // Verdict       : ENVIRONNEMENT SUSPECT / NORMAL
}

// ============================================================
// PARTIE C : Demo pedagogique
// ============================================================

void demoStringObfuscation() {
    // TON CODE ICI
    // 1. Choisir une cle (ex: 0xAB)
    // 2. Encoder "connect_to_c2" avec xorTransform
    // 3. Afficher :
    //    - La string originale
    //    - Les bytes encodes en hex
    //    - Le code C++ du tableau statique
    //    - La string decodee depuis le tableau
    // 4. Ajouter un commentaire indiquant que 'strings ./challenge' ne verra pas "connect_to_c2"
}

// ============================================================
// MAIN
// ============================================================
int main() {
    std::cout << "=== Challenge 07 : Evasion Techniques (EDUCATIF) ===\n\n";

    // --- Partie A : interface interactive ---
    std::cout << "--- PARTIE A : XOR Encoder/Decoder ---\n";
    std::cout << "Entrez une string : ";
    std::string input;
    std::getline(std::cin, input);

    std::cout << "Entrez la cle XOR (0-255) : ";
    int key_int;
    std::cin >> key_int;
    std::cin.ignore();
    uint8_t key = static_cast<uint8_t>(key_int & 0xFF);

    // TON CODE ICI : appeler xorTransform, afficher les resultats, generer le tableau C++

    std::cout << "\n--- PARTIE B : Detection de VM ---\n";
    // TON CODE ICI : buildVMReport() et printReport()

    std::cout << "\n--- PARTIE C : Demo string obfuscation ---\n";
    demoStringObfuscation();

    return 0;
}
