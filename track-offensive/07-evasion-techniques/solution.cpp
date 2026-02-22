// Chapitre 07 - Solution : Techniques d'Evasion
// EDUCATIF - CTF / Labs de securite uniquement
//
// Compile :
//   g++ -std=c++17 -o evasion_solution solution.cpp
//   ./evasion_solution

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cstring>

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

// XOR est son propre inverse : la meme fonction encode ET decode
std::string xorDecode(const std::vector<uint8_t>& encoded, uint8_t key) {
    std::string result(encoded.size(), '\0');
    for (size_t i = 0; i < encoded.size(); ++i) {
        result[i] = static_cast<char>(encoded[i] ^ key);
    }
    return result;
}

// Encode une string pour generer les tableaux statiques
std::vector<uint8_t> xorEncode(const std::string& input, uint8_t key) {
    std::vector<uint8_t> result(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
        result[i] = static_cast<uint8_t>(input[i]) ^ key;
    }
    return result;
}

// "whoami" XOR 0x55 → stocke dans le binaire, pas de string lisible
static const std::vector<uint8_t> ENCODED_CMD = {
    0x22, 0x13, 0x08, 0x14, 0x12, 0x14
};
static const uint8_t XOR_KEY = 0x55;

// ============================================================
// SECTION 2 : Timing check
// ============================================================

bool isSandboxTiming() {
    const int SLEEP_MS = 2000;
    const int THRESHOLD_MS = 1500;

    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS));
    auto end = std::chrono::steady_clock::now();

    long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>
                        (end - start).count();

    std::cout << "[TIMING] Temps mesure : " << elapsed << "ms"
              << " (attendu : " << SLEEP_MS << "ms)\n";

    return elapsed < THRESHOLD_MS;
}

// ============================================================
// SECTION 3 : Detection de VM par heuristiques
// ============================================================

int getCpuCount() {
#ifdef _WIN32
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return static_cast<int>(si.dwNumberOfProcessors);
#else
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    return (n > 0) ? static_cast<int>(n) : 1;
#endif
}

double getRamGB() {
#ifdef _WIN32
    MEMORYSTATUSEX ms;
    ms.dwLength = sizeof(ms);
    if (GlobalMemoryStatusEx(&ms)) {
        return static_cast<double>(ms.ullTotalPhys) / (1024.0 * 1024.0 * 1024.0);
    }
    return 0.0;
#elif defined(__APPLE__)
    int64_t mem = 0;
    size_t len = sizeof(mem);
    if (sysctlbyname("hw.memsize", &mem, &len, nullptr, 0) == 0) {
        return static_cast<double>(mem) / (1024.0 * 1024.0 * 1024.0);
    }
    return 0.0;
#else
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        return static_cast<double>(si.totalram) * si.mem_unit
               / (1024.0 * 1024.0 * 1024.0);
    }
    return 0.0;
#endif
}

bool hasSuspiciousHostname() {
    char hostname[256] = {};
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        return false;
    }

    std::string h(hostname);
    std::transform(h.begin(), h.end(), h.begin(), ::tolower);

    static const std::vector<std::string> patterns = {
        "sandbox", "malware", "analysis", "virus",
        "cuckoo", "anyrun", "hybrid", "vmware-analysis"
    };

    for (const auto& p : patterns) {
        if (h.find(p) != std::string::npos) {
            std::cout << "[VM-CHECK] Hostname suspect : \"" << hostname
                      << "\" contient \"" << p << "\"\n";
            return true;
        }
    }
    return false;
}

bool isVM() {
    int score = 0;

    int cpus = getCpuCount();
    double ram_gb = getRamGB();
    bool bad_host = hasSuspiciousHostname();

    if (cpus < 2) {
        score += 1;
        std::cout << "[VM-CHECK] CPU count faible : " << cpus << " (+1 pt)\n";
    }
    if (ram_gb > 0.1 && ram_gb < 2.0) {
        score += 1;
        std::cout << "[VM-CHECK] RAM faible : " << ram_gb << " GB (+1 pt)\n";
    }
    if (bad_host) {
        score += 2;
    }

    std::cout << "[VM-CHECK] CPUs=" << cpus
              << " RAM=" << ram_gb << "GB"
              << " HostnameSuspect=" << (bad_host ? "oui" : "non")
              << " Score=" << score << "/4\n";

    return score >= 2;
}

// ============================================================
// MAIN : pipeline d'evasion complet
// ============================================================
int main() {
    std::cout << "=== Demo Techniques d'Evasion (EDUCATIF) ===\n\n";

    // --- Demo de l'encodage XOR ---
    std::cout << "--- Encodage XOR ---\n";
    std::string test = "hello_world";
    auto encoded = xorEncode(test, XOR_KEY);
    std::cout << "[XOR] Original  : \"" << test << "\"\n";
    std::cout << "[XOR] Encode    : [";
    for (size_t i = 0; i < encoded.size(); ++i) {
        std::cout << "0x" << std::hex << (int)encoded[i];
        if (i + 1 < encoded.size()) std::cout << ", ";
    }
    std::cout << std::dec << "]\n";
    std::cout << "[XOR] Decode    : \"" << xorDecode(encoded, XOR_KEY) << "\"\n\n";

    // --- Decodage de la commande embarquee ---
    std::string cmd = xorDecode(ENCODED_CMD, XOR_KEY);
    std::cout << "[XOR] Commande embarquee decodee : \"" << cmd << "\"\n\n";

    // --- Timing check ---
    std::cout << "--- Timing Check ---\n";
    std::cout << "[TIMING] Sleep 2s en cours...\n";
    bool sandbox_timing = isSandboxTiming();
    if (sandbox_timing) {
        std::cout << "[TIMING] SANDBOX DETECTEE ! Arret.\n";
        return 1;
    }
    std::cout << "[TIMING] OK - environnement temps reel.\n\n";

    // --- Detection de VM ---
    std::cout << "--- Detection de VM ---\n";
    bool vm = isVM();
    if (vm) {
        std::cout << "[VM] Environnement suspect. Arret.\n";
        return 1;
    }
    std::cout << "[VM] Environnement normal detecte.\n\n";

    std::cout << "=== Tous les checks passes. Logique principale simulee. ===\n";
    return 0;
}
