// Chapitre 05 - Exercise : Execution de Shellcode Educatif
// EDUCATIF - Le shellcode fait UNIQUEMENT exit(0)
//
// Compile : g++ -std=c++17 -o exercise exercise.cpp
//
// DISCLAIMER : Exercice purement educatif pour comprendre
// les protections memoire et l'execution de code machine.

#include <iostream>
#include <cstring>
#include <cstdint>
#include <sys/mman.h>
#include <unistd.h>

// TODO 1 : Alloue une page de memoire avec mmap
// Permissions initiales : PROT_READ | PROT_WRITE (pas executable!)
// Flags : MAP_PRIVATE | MAP_ANONYMOUS
// Retourne le pointeur, ou nullptr si echoue
void* allocateMemory(size_t size) {
    // TON CODE ICI
    return nullptr;
}

// TODO 2 : Copie un buffer dans la zone allouee
// Utilise memcpy pour copier les octets
void copyToMemory(void* dest, const unsigned char* src, size_t len) {
    // TON CODE ICI
}

// TODO 3 : Rend la memoire executable avec mprotect
// Change les permissions de RW- a R-X
// Retourne true si succes, false sinon
bool makeExecutable(void* mem, size_t size) {
    // TON CODE ICI
    return false;
}

// TODO 4 : Affiche un dump hexadecimal du buffer
// Format : "00 01 02 03 04 05 06 07  08 09 0a 0b 0c 0d 0e 0f"
// Avec une nouvelle ligne tous les 16 octets
void hexDump(const unsigned char* data, size_t len) {
    // TON CODE ICI
}

// TODO 5 : Decode les instructions du shellcode exit(0)
// Pour chaque groupe d'octets connu, affiche l'instruction assembleur
// correspondante (desassemblage manuel simplifie)
void disassemble(const unsigned char* code, size_t len) {
    std::cout << "[*] Desassemblage simplifie :" << std::endl;
    // TON CODE ICI
    // Indice pour x86_64 :
    // 48 31 ff        xor rdi, rdi
    // 48 c7 c0 XX...  mov rax, XX...
    // 0f 05           syscall
}

int main() {
    std::cout << "=== Exercise : Shellcode Educatif ===" << std::endl;
    std::cout << "[!] Le shellcode fait UNIQUEMENT exit(0)" << std::endl;
    std::cout << std::endl;

    // Shellcode exit(0)
#ifdef __APPLE__
    unsigned char shellcode[] = {
        0x48, 0x31, 0xff,                                  // xor rdi, rdi
        0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x02,         // mov rax, 0x2000001
        0x0f, 0x05                                          // syscall
    };
#else
    unsigned char shellcode[] = {
        0x48, 0x31, 0xff,                                  // xor rdi, rdi
        0x48, 0xc7, 0xc0, 0x3c, 0x00, 0x00, 0x00,         // mov rax, 60
        0x0f, 0x05                                          // syscall
    };
#endif

    size_t sc_len = sizeof(shellcode);

    // Affichage hex
    std::cout << "[*] Shellcode (" << sc_len << " octets) :" << std::endl;
    hexDump(shellcode, sc_len);
    std::cout << std::endl;

    // Desassemblage
    disassemble(shellcode, sc_len);
    std::cout << std::endl;

    // Allocation
    size_t pageSize = sysconf(_SC_PAGESIZE);
    void* mem = allocateMemory(pageSize);
    if (!mem) {
        std::cout << "[!] Implemente allocateMemory()" << std::endl;
        return 1;
    }
    std::cout << "[*] Memoire allouee a : " << mem << std::endl;

    // Copie
    copyToMemory(mem, shellcode, sc_len);
    std::cout << "[*] Shellcode copie" << std::endl;

    // Rendre executable
    if (!makeExecutable(mem, pageSize)) {
        std::cout << "[!] Implemente makeExecutable()" << std::endl;
        munmap(mem, pageSize);
        return 1;
    }
    std::cout << "[*] Memoire rendue executable" << std::endl;

    // Execution
    std::cout << "[*] Execution... (le programme va se terminer avec exit(0))" << std::endl;
    auto func = reinterpret_cast<void(*)()>(mem);
    func();

    // Jamais atteint
    munmap(mem, pageSize);
    return 0;
}
