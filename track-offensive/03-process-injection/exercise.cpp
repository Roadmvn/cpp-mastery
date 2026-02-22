// Chapitre 03 - Exercise : Simulation d'Injection avec Shared Memory
// EDUCATIF - Communication inter-processus avec memoire partagee
//
// Compile : g++ -std=c++17 -o exercise exercise.cpp

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <cstdio>
#include <signal.h>

// Structure en memoire partagee (simule la zone "injectee")
struct SharedPayload {
    bool ready;           // Le parent a ecrit une commande
    bool done;            // L'enfant a fini d'executer
    bool shutdown;        // Signal d'arret
    char command[256];    // Commande "injectee"
    char result[4096];    // Resultat de l'execution
};

// TODO 1 : Cree une zone de memoire partagee avec mmap
// Utilise MAP_SHARED | MAP_ANONYMOUS pour creer une zone partagee entre parent et enfant
// Retourne un pointeur vers SharedPayload
SharedPayload* createSharedMemory() {
    // TON CODE ICI
    // Indice : mmap(nullptr, sizeof(SharedPayload), PROT_READ | PROT_WRITE,
    //               MAP_SHARED | MAP_ANONYMOUS, -1, 0)
    return nullptr;
}

// TODO 2 : Logique du processus enfant ("processus cible")
// L'enfant boucle en verifiant shared->ready
// Quand ready == true : execute la commande avec popen, ecrit le resultat
// Met done = true, ready = false
// Sort de la boucle quand shutdown == true
void childProcess(SharedPayload* shared) {
    std::cout << "[CIBLE PID:" << getpid() << "] Processus demarre, en attente..." << std::endl;

    // TON CODE ICI
    // Boucle tant que !shutdown
    //   Si ready : execute command, ecrit dans result, met done=true, ready=false
    //   Sinon : usleep(10000) pour ne pas consommer le CPU
}

// TODO 3 : Logique du processus parent ("injecteur")
// Le parent ecrit des commandes dans shared->command, met ready = true
// Attend que done == true, puis lit le resultat
void parentProcess(SharedPayload* shared, pid_t childPid) {
    std::cout << "[INJECTEUR PID:" << getpid() << "] Cible : PID " << childPid << std::endl;
    usleep(100000); // Laisse l'enfant demarrer

    const char* commands[] = {"whoami", "hostname", "date", "ls -la"};

    for (const char* cmd : commands) {
        std::cout << "\n[INJECTEUR] Injection de commande : " << cmd << std::endl;

        // TON CODE ICI
        // 1. Copie cmd dans shared->command
        // 2. Met shared->ready = true
        // 3. Attend que shared->done == true (boucle + usleep)
        // 4. Affiche shared->result
        // 5. Met shared->done = false
    }

    // Arret
    shared->shutdown = true;
    shared->ready = true;

    waitpid(childPid, nullptr, 0);
    std::cout << "\n[INJECTEUR] Cible terminee." << std::endl;
}

int main() {
    std::cout << "=== Exercise : Simulation d'Injection (Shared Memory) ===" << std::endl;
    std::cout << "[!] EDUCATIF UNIQUEMENT - Simulation IPC" << std::endl;
    std::cout << std::endl;

    // Cree la memoire partagee
    SharedPayload* shared = createSharedMemory();
    if (!shared) {
        std::cout << "[!] Implemente createSharedMemory()" << std::endl;
        return 1;
    }

    // Initialise
    shared->ready = false;
    shared->done = false;
    shared->shutdown = false;

    // Fork
    pid_t pid = fork();
    if (pid == 0) {
        childProcess(shared);
        _exit(0);
    } else {
        parentProcess(shared, pid);
    }

    // Libere la memoire partagee
    munmap(shared, sizeof(SharedPayload));

    return 0;
}
