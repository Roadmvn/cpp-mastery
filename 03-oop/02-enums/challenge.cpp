// ============================================================
// Chapitre 02 - Challenge Offensive : Enum pour Payloads
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================
// Contexte : Dans un framework offensif (type Metasploit/Cobalt Strike),
// on categorise les payloads par type, architecture et methode
// d'injection. Les enums typent tout ca proprement.
// ============================================================

#include <iostream>
#include <string>
#include <vector>

enum class PayloadType : uint8_t {
    SHELLCODE = 0,
    DLL       = 1,
    SCRIPT    = 2,
    EXE       = 3
};

enum class Arch : uint8_t {
    X86    = 0,
    X64    = 1,
    ARM64  = 2
};

enum class InjectionMethod : uint8_t {
    PROCESS_HOLLOW     = 0,
    DLL_INJECTION      = 1,
    THREAD_HIJACK      = 2,
    APC_QUEUE          = 3,
    REFLECTIVE_LOAD    = 4
};

enum class EncodingType : uint8_t {
    NONE       = 0,
    XOR        = 1,
    AES_256    = 2,
    RC4        = 3
};

std::string to_string(PayloadType t) {
    switch (t) {
        case PayloadType::SHELLCODE: return "Shellcode";
        case PayloadType::DLL:       return "DLL";
        case PayloadType::SCRIPT:    return "Script";
        case PayloadType::EXE:       return "Executable";
    }
    return "Unknown";
}

std::string to_string(Arch a) {
    switch (a) {
        case Arch::X86:   return "x86";
        case Arch::X64:   return "x64";
        case Arch::ARM64: return "ARM64";
    }
    return "Unknown";
}

std::string to_string(InjectionMethod m) {
    switch (m) {
        case InjectionMethod::PROCESS_HOLLOW:  return "Process Hollowing";
        case InjectionMethod::DLL_INJECTION:   return "DLL Injection";
        case InjectionMethod::THREAD_HIJACK:   return "Thread Hijacking";
        case InjectionMethod::APC_QUEUE:       return "APC Queue";
        case InjectionMethod::REFLECTIVE_LOAD: return "Reflective Loading";
    }
    return "Unknown";
}

std::string to_string(EncodingType e) {
    switch (e) {
        case EncodingType::NONE:    return "None";
        case EncodingType::XOR:     return "XOR";
        case EncodingType::AES_256: return "AES-256";
        case EncodingType::RC4:     return "RC4";
    }
    return "Unknown";
}

struct PayloadConfig {
    std::string name;
    PayloadType type;
    Arch arch;
    InjectionMethod method;
    EncodingType encoding;
    size_t size_bytes;

    void print() const {
        std::cout << "--- Payload: " << name << " ---" << std::endl;
        std::cout << "  Type:      " << to_string(type) << std::endl;
        std::cout << "  Arch:      " << to_string(arch) << std::endl;
        std::cout << "  Injection: " << to_string(method) << std::endl;
        std::cout << "  Encoding:  " << to_string(encoding) << std::endl;
        std::cout << "  Size:      " << size_bytes << " bytes" << std::endl;
    }

    bool is_compatible(Arch target_arch) const {
        if (arch == target_arch) return true;
        // x86 peut tourner sur x64 (WoW64)
        if (arch == Arch::X86 && target_arch == Arch::X64) return true;
        return false;
    }
};

bool needs_loader(PayloadType t) {
    switch (t) {
        case PayloadType::SHELLCODE: return false;  // Execution directe
        case PayloadType::DLL:       return true;   // Besoin d'un loader
        case PayloadType::SCRIPT:    return true;   // Besoin d'un interprete
        case PayloadType::EXE:       return true;   // Besoin de CreateProcess
    }
    return false;
}

InjectionMethod best_method_for(PayloadType t) {
    switch (t) {
        case PayloadType::SHELLCODE: return InjectionMethod::APC_QUEUE;
        case PayloadType::DLL:       return InjectionMethod::REFLECTIVE_LOAD;
        case PayloadType::SCRIPT:    return InjectionMethod::PROCESS_HOLLOW;
        case PayloadType::EXE:       return InjectionMethod::PROCESS_HOLLOW;
    }
    return InjectionMethod::PROCESS_HOLLOW;
}

int main() {
    std::cout << "=== Challenge Offensive : Payload Manager ===" << std::endl;

    std::vector<PayloadConfig> payloads = {
        {"reverse_tcp_x64",  PayloadType::SHELLCODE, Arch::X64, InjectionMethod::APC_QUEUE,
         EncodingType::XOR,     512},
        {"mimikatz_loader",  PayloadType::DLL,       Arch::X64, InjectionMethod::REFLECTIVE_LOAD,
         EncodingType::AES_256, 1048576},
        {"powershell_amsi",  PayloadType::SCRIPT,    Arch::X64, InjectionMethod::PROCESS_HOLLOW,
         EncodingType::RC4,     2048},
        {"beacon_x86",      PayloadType::SHELLCODE, Arch::X86, InjectionMethod::THREAD_HIJACK,
         EncodingType::AES_256, 4096},
    };

    std::cout << "\n--- Inventaire des payloads ---" << std::endl;
    for (const auto& p : payloads) {
        p.print();
        std::cout << "  Loader requis: " << (needs_loader(p.type) ? "Oui" : "Non") << std::endl;
        std::cout << "  Methode recommandee: " << to_string(best_method_for(p.type)) << std::endl;
        std::cout << std::endl;
    }

    // Test de compatibilite
    std::cout << "--- Test de compatibilite (cible: x64) ---" << std::endl;
    Arch cible = Arch::X64;
    for (const auto& p : payloads) {
        std::cout << p.name << " [" << to_string(p.arch) << "] -> "
                  << (p.is_compatible(cible) ? "COMPATIBLE" : "INCOMPATIBLE")
                  << std::endl;
    }

    // Taille totale des enums dans le struct
    std::cout << "\n--- Taille memoire ---" << std::endl;
    std::cout << "PayloadType:     " << sizeof(PayloadType)     << " byte" << std::endl;
    std::cout << "Arch:            " << sizeof(Arch)            << " byte" << std::endl;
    std::cout << "InjectionMethod: " << sizeof(InjectionMethod) << " byte" << std::endl;
    std::cout << "EncodingType:    " << sizeof(EncodingType)    << " byte" << std::endl;
    std::cout << "4 enums uint8_t = " << 4 * sizeof(uint8_t)
              << " bytes (vs " << 4 * sizeof(int) << " bytes avec int)" << std::endl;

    return 0;
}
