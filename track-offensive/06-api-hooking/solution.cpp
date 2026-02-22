// Chapitre 06 - Solution : Hook de Fonctions avec LD_PRELOAD
// EDUCATIF - Interception de fonctions de la libc
//
// Compile en shared library :
//   Linux : g++ -std=c++17 -shared -fPIC -o hook.so solution.cpp -ldl
//   macOS : g++ -std=c++17 -shared -fPIC -o hook.dylib solution.cpp -ldl
//
// Utilisation :
//   Linux : LD_PRELOAD=./hook.so ./test_target
//   macOS : DYLD_INSERT_LIBRARIES=./hook.dylib DYLD_FORCE_FLAT_NAMESPACE=1 ./test_target

#define _GNU_SOURCE
#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static int open_count = 0;
static int read_count = 0;
static int write_count = 0;
static int malloc_count = 0;
static size_t total_alloc = 0;

// TODO 1 : Hook de malloc
extern "C" void* malloc(size_t size) {
    static auto real_malloc = reinterpret_cast<void*(*)(size_t)>(
        dlsym(RTLD_NEXT, "malloc")
    );

    malloc_count++;
    total_alloc += size;
    void* ptr = real_malloc(size);

    // Log seulement les grosses allocations pour eviter le spam
    if (size > 64) {
        fprintf(stderr, "[HOOK] malloc(%zu) = %p\n", size, ptr);
    }
    return ptr;
}

// TODO 2 : Hook de free
extern "C" void free(void* ptr) {
    static auto real_free = reinterpret_cast<void(*)(void*)>(
        dlsym(RTLD_NEXT, "free")
    );

    if (ptr) {
        // Log seulement si ptr non-null
        // fprintf(stderr, "[HOOK] free(%p)\n", ptr); // Decommente si besoin
    }
    real_free(ptr);
}

// TODO 3 : Hook de open
extern "C" int open(const char* path, int flags, ...) {
    static auto real_open = reinterpret_cast<int(*)(const char*, int, ...)>(
        dlsym(RTLD_NEXT, "open")
    );

    open_count++;
    fprintf(stderr, "[HOOK] open(\"%s\", 0x%x)\n", path, flags);
    return real_open(path, flags);
}

// TODO 4 : Hook de getenv
extern "C" char* getenv(const char* name) {
    static auto real_getenv = reinterpret_cast<char*(*)(const char*)>(
        dlsym(RTLD_NEXT, "getenv")
    );

    char* val = real_getenv(name);
    fprintf(stderr, "[HOOK] getenv(\"%s\") = \"%s\"\n",
            name, val ? val : "(null)");
    return val;
}

// TODO 5 : Hook de puts
extern "C" int puts(const char* str) {
    static auto real_puts = reinterpret_cast<int(*)(const char*)>(
        dlsym(RTLD_NEXT, "puts")
    );

    fprintf(stderr, "[HOOK] puts(\"%s\")\n", str);
    return real_puts(str);
}

__attribute__((destructor))
void printStats() {
    fprintf(stderr, "\n[HOOK] === Statistiques ===\n");
    fprintf(stderr, "[HOOK] malloc : %d appels (%zu bytes total)\n", malloc_count, total_alloc);
    fprintf(stderr, "[HOOK] open   : %d appels\n", open_count);
}
