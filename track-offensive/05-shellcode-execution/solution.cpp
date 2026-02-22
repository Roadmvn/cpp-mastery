// Chapitre 05 - Solution : Execution de Shellcode Educatif
// EDUCATIF - Le shellcode fait UNIQUEMENT exit(0)
//
// Compile : g++ -std=c++17 -o solution solution.cpp

#include <iostream>
#include <cstring>
#include <cstdint>
#include <sys/mman.h>
#include <unistd.h>

// TODO 1 : Allocation memoire
void* allocateMemory(size_t size) {
    void* mem = mmap(nullptr, size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) return nullptr;
    return mem;
}

// TODO 2 : Copie en memoire
void copyToMemory(void* dest, const unsigned char* src, size_t len) {
    std::memcpy(dest, src, len);
}

// TODO 3 : Rendre executable
bool makeExecutable(void* mem, size_t size) {
    return mprotect(mem, size, PROT_READ | PROT_EXEC) == 0;
}

// TODO 4 : Dump hexadecimal
void hexDump(const unsigned char* data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && i % 16 == 0) std::cout << std::endl;
        if (i % 16 == 0) printf("    %04zx: ", i);
        printf("%02x ", data[i]);
        if (i % 8 == 7 && i % 16 != 15) std::cout << " ";
    }
    std::cout << std::endl;
}

// TODO 5 : Desassemblage simplifie
void disassemble(const unsigned char* code, size_t len) {
    std::cout << "[*] Desassemblage simplifie :" << std::endl;
    size_t i = 0;
    while (i < len) {
        printf("    %04zx: ", i);

        // xor rdi, rdi (48 31 ff)
        if (i + 2 < len && code[i] == 0x48 && code[i+1] == 0x31 && code[i+2] == 0xff) {
            std::cout << "48 31 ff          xor rdi, rdi" << std::endl;
            i += 3;
        }
        // mov rax, imm32 (48 c7 c0 XX XX XX XX)
        else if (i + 6 < len && code[i] == 0x48 && code[i+1] == 0xc7 && code[i+2] == 0xc0) {
            uint32_t imm = *reinterpret_cast<const uint32_t*>(&code[i+3]);
            printf("48 c7 c0 %02x %02x %02x %02x  mov rax, 0x%x\n",
                   code[i+3], code[i+4], code[i+5], code[i+6], imm);
            i += 7;
        }
        // syscall (0f 05)
        else if (i + 1 < len && code[i] == 0x0f && code[i+1] == 0x05) {
            std::cout << "0f 05             syscall" << std::endl;
            i += 2;
        }
        else {
            printf("%02x                db 0x%02x\n", code[i], code[i]);
            i++;
        }
    }
}

int main() {
    std::cout << "=== Solution : Shellcode Educatif ===" << std::endl;
    std::cout << "[!] Le shellcode fait UNIQUEMENT exit(0)" << std::endl;
    std::cout << std::endl;

#ifdef __APPLE__
    unsigned char shellcode[] = {
        0x48, 0x31, 0xff,
        0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x02,
        0x0f, 0x05
    };
#else
    unsigned char shellcode[] = {
        0x48, 0x31, 0xff,
        0x48, 0xc7, 0xc0, 0x3c, 0x00, 0x00, 0x00,
        0x0f, 0x05
    };
#endif

    size_t sc_len = sizeof(shellcode);

    std::cout << "[*] Shellcode (" << sc_len << " octets) :" << std::endl;
    hexDump(shellcode, sc_len);
    std::cout << std::endl;

    disassemble(shellcode, sc_len);
    std::cout << std::endl;

    size_t pageSize = sysconf(_SC_PAGESIZE);
    void* mem = allocateMemory(pageSize);
    if (!mem) {
        std::cerr << "[!] mmap echoue" << std::endl;
        return 1;
    }
    std::cout << "[*] Memoire allouee a : " << mem << std::endl;

    copyToMemory(mem, shellcode, sc_len);
    std::cout << "[*] Shellcode copie" << std::endl;

    if (!makeExecutable(mem, pageSize)) {
        std::cerr << "[!] mprotect echoue" << std::endl;
        munmap(mem, pageSize);
        return 1;
    }
    std::cout << "[*] Memoire rendue executable" << std::endl;

    std::cout << "[*] Execution... (exit(0))" << std::endl;
    auto func = reinterpret_cast<void(*)()>(mem);
    func();

    munmap(mem, pageSize);
    return 0;
}
