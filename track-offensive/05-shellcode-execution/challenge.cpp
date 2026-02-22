// Chapitre 05 - Challenge : Analyseur et Runner de Shellcode
// EDUCATIF - Analyse statique et execution controlee de shellcode exit(0)
//
// OBJECTIF : Creer un outil qui :
// - Lit un shellcode depuis un format hex string
// - L'analyse (taille, pattern detection)
// - L'affiche en hex dump
// - Le desassemble (simplifie)
// - L'execute de maniere controlee
//
// Compile : g++ -std=c++17 -o challenge challenge.cpp
//
// DISCLAIMER : UNIQUEMENT pour shellcode exit(0) educatif.
// Cet outil est une demonstration de manipulation de memoire.

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>
#include <sys/mman.h>
#include <unistd.h>
#include <sstream>
#include <iomanip>

// TODO 1 : Parse une string hexadecimale en bytes
// Input : "48 31 ff 48 c7 c0 3c 00 00 00 0f 05"
// Output : vector contenant les octets correspondants
std::vector<unsigned char> parseHexString(const std::string& hex) {
    std::vector<unsigned char> bytes;
    // TON CODE ICI
    return bytes;
}

// TODO 2 : Convertis des bytes en string hexadecimale
std::string bytesToHex(const std::vector<unsigned char>& bytes) {
    std::string result;
    // TON CODE ICI
    return result;
}

// TODO 3 : Analyse statique du shellcode
// Detecte des patterns connus :
// - 0f 05 = syscall
// - cd 80 = int 0x80 (ancien syscall 32 bits)
// - 48 31 XX = xor reg64, reg64 (mise a zero)
// - cc = int3 (breakpoint)
// Affiche les patterns trouves avec leur offset
void analyzeShellcode(const std::vector<unsigned char>& code) {
    std::cout << "[*] Analyse statique :" << std::endl;
    std::cout << "    Taille : " << code.size() << " octets" << std::endl;
    // TON CODE ICI
}

// TODO 4 : Detecte si le shellcode contient des NOP (0x90)
// Calcule le ratio de NOP par rapport a la taille totale
// Un ratio eleve peut indiquer un NOP sled
void detectNopSled(const std::vector<unsigned char>& code) {
    // TON CODE ICI
}

// TODO 5 : Execution securisee avec fork
// Fork un processus enfant qui execute le shellcode
// Le parent attend et rapporte le code de retour
// Cela isole l'execution du shellcode
void secureExecute(const std::vector<unsigned char>& code) {
    std::cout << "[*] Execution securisee (dans un fork)..." << std::endl;
    // TON CODE ICI
    // 1. fork()
    // 2. Enfant : mmap, memcpy, mprotect, execute
    // 3. Parent : waitpid, rapporte le status
}

int main() {
    std::cout << "=== Challenge : Analyseur de Shellcode ===" << std::endl;
    std::cout << "[!] EDUCATIF - exit(0) uniquement" << std::endl;
    std::cout << std::endl;

    // Shellcode exit(0) en format hex string
#ifdef __APPLE__
    std::string hexCode = "48 31 ff 48 c7 c0 01 00 00 02 0f 05";
#else
    std::string hexCode = "48 31 ff 48 c7 c0 3c 00 00 00 0f 05";
#endif

    std::cout << "[*] Input hex : " << hexCode << std::endl;
    std::cout << std::endl;

    // Parse
    auto code = parseHexString(hexCode);
    if (code.empty()) {
        std::cout << "[!] Implemente parseHexString()" << std::endl;
        return 1;
    }

    std::cout << "[*] Bytes parses : " << code.size() << std::endl;
    std::cout << "[*] Verification : " << bytesToHex(code) << std::endl;
    std::cout << std::endl;

    // Analyse
    analyzeShellcode(code);
    std::cout << std::endl;

    // Detection NOP
    detectNopSled(code);
    std::cout << std::endl;

    // Execution
    secureExecute(code);

    return 0;
}
