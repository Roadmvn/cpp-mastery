// Chapitre 07 - Exercise : Techniques d'Evasion
// EDUCATIF - CTF / Labs de securite uniquement
//
// Compile :
//   g++ -std=c++17 -o evasion_exercise exercise.cpp
//   ./evasion_exercise
//
// Objectif : implementer les 3 mecanismes d'evasion vus en cours

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #ifdef __APPLE__
        #include <sys/types.h>
        #include <sys/sysctl.h>
    #else
        #include <sys/sysinfo.h>
    #endif
#endif

// ============================================================
// SECTION 1 : Obfuscation XOR de strings
// ============================================================

// TODO 1 : Implementer xorDecode
// La fonction doit appliquer XOR byte par byte avec la cle donnee
// Note : XOR est son propre inverse, encoder = decoder
std::string xorDecode(const std::vector<uint8_t>& encoded, uint8_t key) {
    // TON CODE ICI
    // 1. Creer une string result de meme taille que encoded
    // 2. Pour chaque byte : result[i] = encoded[i] ^ key
    // 3. Retourner result

    return "";  // placeholder
}

// String "whoami" encodee avec XOR key=0x55
// Tu peux generer tes propres strings encodees avec le challenge.cpp
static const std::vector<uint8_t> ENCODED_CMD = {
    0x22, 0x13, 0x08, 0x14, 0x12, 0x14  // "whoami" XOR 0x55
};
static const uint8_t XOR_KEY = 0x55;

// ============================================================
// SECTION 2 : Timing check
// ============================================================

// TODO 2 : Implementer isSandboxTiming
// Mesure le temps reel ecoule apres un sleep de SLEEP_DURATION_MS ms
// Si le temps mesure est inferieur a THRESHOLD_MS → sandbox acceleree
bool isSandboxTiming() {
    const int SLEEP_DURATION_MS = 2000;
    const int THRESHOLD_MS = 1500;

    // TON CODE ICI
    // 1. Capturer l'heure de debut avec std::chrono::steady_clock::now()
    // 2. Faire sleep : std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION_MS))
    // 3. Capturer l'heure de fin
    // 4. Calculer elapsed_ms avec duration_cast<milliseconds>
    // 5. Retourner elapsed_ms < THRESHOLD_MS

    return false;  // placeholder
}

// ============================================================
// SECTION 3 : Detection de VM par heuristiques
// ============================================================

// TODO 3a : Compter les CPUs disponibles
int getCpuCount() {
    // TON CODE ICI
    // macOS/Linux : utiliser sysconf(_SC_NPROCESSORS_ONLN)
    // Windows     : utiliser GetSystemInfo()
    // Retourner le nombre de processeurs logiques

    return 0;  // placeholder
}

// TODO 3b : Obtenir la RAM totale en GB
double getRamGB() {
    // TON CODE ICI
    // Linux  : lire /proc/meminfo ou utiliser sysinfo()
    // macOS  : utiliser sysctl hw.memsize via sysctlbyname()
    // Windows: utiliser GlobalMemoryStatusEx()
    //
    // Pour une impl simple cross-platform, retourner 0.0 si impossible

    return 0.0;  // placeholder
}

// TODO 3c : Detecter des patterns suspects dans le hostname
bool hasSuspiciousHostname() {
    // TON CODE ICI
    // 1. Recuperer le hostname avec gethostname()
    // 2. Convertir en minuscules
    // 3. Verifier si le hostname contient un des patterns suspects :
    //    {"sandbox", "malware", "analysis", "virus", "cuckoo", "anyrun"}
    // 4. Retourner true si un pattern est trouve

    return false;  // placeholder
}

// TODO 3d : Calculer le score de suspicion et decider
// Scoring : CPU < 2 → +1 pt | RAM < 2 GB → +1 pt | hostname suspect → +2 pts
// Si score >= 2 → VM probable
bool isVM() {
    int score = 0;

    int cpus = getCpuCount();
    double ram_gb = getRamGB();
    bool bad_host = hasSuspiciousHostname();

    // TON CODE ICI : calculer le score selon les regles ci-dessus

    std::cout << "[VM-CHECK] CPUs=" << cpus
              << " RAM=" << ram_gb << "GB"
              << " HostnameSuspect=" << (bad_host ? "oui" : "non")
              << " Score=" << score << "/4\n";

    return score >= 2;
}

// ============================================================
// MAIN : pipeline d'evasion
// ============================================================
int main() {
    std::cout << "=== Demo Techniques d'Evasion (EDUCATIF) ===\n\n";

    // Test 1 : Decodage XOR
    std::cout << "[XOR] Decodage de la commande cachee...\n";
    std::string cmd = xorDecode(ENCODED_CMD, XOR_KEY);
    std::cout << "[XOR] Commande decodee : \"" << cmd << "\"\n\n";

    // Test 2 : Timing check
    std::cout << "[TIMING] Sleep 2 secondes en cours...\n";
    bool sandbox_timing = isSandboxTiming();
    if (sandbox_timing) {
        std::cout << "[TIMING] SANDBOX DETECTEE : temps ecoule trop court !\n";
        std::cout << "[TIMING] Arret du programme.\n";
        return 1;
    }
    std::cout << "[TIMING] Timing OK - pas de sandbox acceleree detectee.\n\n";

    // Test 3 : Detection de VM
    std::cout << "[VM] Analyse de l'environnement...\n";
    bool vm = isVM();
    if (vm) {
        std::cout << "[VM] ENVIRONNEMENT SUSPECT detecte. Arret.\n";
        return 1;
    }
    std::cout << "[VM] Environnement semble normal.\n\n";

    std::cout << "=== Tous les checks passes. Logique principale. ===\n";
    return 0;
}
