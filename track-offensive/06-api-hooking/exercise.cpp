// Chapitre 06 - Exercise : Hook de Fonctions avec LD_PRELOAD
// EDUCATIF - Interception de fonctions de la libc
//
// ETAPE 1 : Compile cette lib en shared library
//   Linux : g++ -std=c++17 -shared -fPIC -o hook.so exercise.cpp -ldl
//   macOS : g++ -std=c++17 -shared -fPIC -o hook.dylib exercise.cpp -ldl
//
// ETAPE 2 : Lance un programme avec le hook
//   Linux : LD_PRELOAD=./hook.so /bin/ls
//   macOS : DYLD_INSERT_LIBRARIES=./hook.dylib DYLD_FORCE_FLAT_NAMESPACE=1 /bin/ls
//
// NOTE : Sur macOS recent, SIP peut bloquer LD_PRELOAD sur les binaires systeme.
// Utilise le test_target.cpp fourni a la place.

#define _GNU_SOURCE
#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// Compteurs globaux
static int open_count = 0;
static int read_count = 0;
static int write_count = 0;
static int malloc_count = 0;

// TODO 1 : Hook de malloc
// Intercepte toutes les allocations memoire
// Log la taille demandee et l'adresse retournee
// ATTENTION : utilise fprintf(stderr, ...) pas cout (sinon recursion infinie)
extern "C" void* malloc(size_t size) {
    // Recupere le vrai malloc
    static auto real_malloc = reinterpret_cast<void*(*)(size_t)>(
        dlsym(RTLD_NEXT, "malloc")
    );

    // TON CODE ICI
    // 1. Incremente malloc_count
    // 2. Appelle real_malloc(size)
    // 3. Log avec fprintf(stderr, ...)
    // 4. Retourne le pointeur

    return real_malloc(size);
}

// TODO 2 : Hook de free
// Intercepte les liberations memoire
extern "C" void free(void* ptr) {
    static auto real_free = reinterpret_cast<void(*)(void*)>(
        dlsym(RTLD_NEXT, "free")
    );

    // TON CODE ICI
    // Log l'adresse liberee

    real_free(ptr);
}

// TODO 3 : Hook de open (ouverture de fichiers)
// Log quel fichier est ouvert et avec quels flags
extern "C" int open(const char* path, int flags, ...) {
    static auto real_open = reinterpret_cast<int(*)(const char*, int, ...)>(
        dlsym(RTLD_NEXT, "open")
    );

    // TON CODE ICI
    // 1. Incremente open_count
    // 2. Log le chemin du fichier
    // 3. Appelle et retourne real_open(path, flags)

    return real_open(path, flags);
}

// TODO 4 : Hook de getenv
// Intercepte les lectures de variables d'environnement
// Log quelle variable est demandee
extern "C" char* getenv(const char* name) {
    static auto real_getenv = reinterpret_cast<char*(*)(const char*)>(
        dlsym(RTLD_NEXT, "getenv")
    );

    // TON CODE ICI
    // Log le nom de la variable demandee

    return real_getenv(name);
}

// TODO 5 : Hook de puts (affichage)
// Intercepte les appels a puts() pour logger ce qui est affiche
extern "C" int puts(const char* str) {
    static auto real_puts = reinterpret_cast<int(*)(const char*)>(
        dlsym(RTLD_NEXT, "puts")
    );

    // TON CODE ICI
    // Log le contenu de str avant de le passer au vrai puts

    return real_puts(str);
}

// Fonction appelee a la fin du programme pour afficher les stats
__attribute__((destructor))
void printStats() {
    fprintf(stderr, "\n[HOOK] === Statistiques ===\n");
    fprintf(stderr, "[HOOK] malloc : %d appels\n", malloc_count);
    fprintf(stderr, "[HOOK] open   : %d appels\n", open_count);
    fprintf(stderr, "[HOOK] read   : %d appels\n", read_count);
    fprintf(stderr, "[HOOK] write  : %d appels\n", write_count);
}
