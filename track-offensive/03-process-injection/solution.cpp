// Chapitre 03 - Solution : Simulation d'Injection avec Shared Memory
// EDUCATIF - Communication inter-processus avec memoire partagee
//
// Compile : g++ -std=c++17 -o solution solution.cpp

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <cstdio>

struct SharedPayload {
    bool ready;
    bool done;
    bool shutdown;
    char command[256];
    char result[4096];
};

// TODO 1 : Memoire partagee
SharedPayload* createSharedMemory() {
    void* mem = mmap(nullptr, sizeof(SharedPayload),
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) return nullptr;
    return static_cast<SharedPayload*>(mem);
}

// TODO 2 : Processus enfant
void childProcess(SharedPayload* shared) {
    std::cout << "[CIBLE PID:" << getpid() << "] Processus demarre, en attente..." << std::endl;

    while (!shared->shutdown) {
        if (shared->ready) {
            if (shared->shutdown) break;

            std::cout << "[CIBLE] Execute : " << shared->command << std::endl;

            // Execute la commande
            std::string result;
            FILE* fp = popen(shared->command, "r");
            if (fp) {
                char buf[128];
                while (fgets(buf, sizeof(buf), fp)) {
                    result += buf;
                }
                pclose(fp);
            } else {
                result = "Erreur d'execution\n";
            }

            // Ecrit le resultat
            std::strncpy(shared->result, result.c_str(), sizeof(shared->result) - 1);
            shared->result[sizeof(shared->result) - 1] = '\0';
            shared->done = true;
            shared->ready = false;
        } else {
            usleep(10000); // 10ms
        }
    }

    std::cout << "[CIBLE] Arret." << std::endl;
}

// TODO 3 : Processus parent
void parentProcess(SharedPayload* shared, pid_t childPid) {
    std::cout << "[INJECTEUR PID:" << getpid() << "] Cible : PID " << childPid << std::endl;
    usleep(100000);

    const char* commands[] = {"whoami", "hostname", "date", "ls -la"};

    for (const char* cmd : commands) {
        std::cout << "\n[INJECTEUR] Injection de commande : " << cmd << std::endl;

        // Ecrit la commande
        std::strncpy(shared->command, cmd, sizeof(shared->command) - 1);
        shared->command[sizeof(shared->command) - 1] = '\0';
        shared->ready = true;

        // Attend le resultat
        while (!shared->done) {
            usleep(10000);
        }

        std::cout << "[INJECTEUR] Resultat :" << std::endl;
        std::cout << shared->result;
        shared->done = false;
    }

    shared->shutdown = true;
    shared->ready = true;

    waitpid(childPid, nullptr, 0);
    std::cout << "\n[INJECTEUR] Cible terminee." << std::endl;
}

int main() {
    std::cout << "=== Solution : Simulation d'Injection (Shared Memory) ===" << std::endl;
    std::cout << "[!] EDUCATIF UNIQUEMENT - Simulation IPC" << std::endl;
    std::cout << std::endl;

    SharedPayload* shared = createSharedMemory();
    if (!shared) {
        std::cerr << "Erreur mmap" << std::endl;
        return 1;
    }

    shared->ready = false;
    shared->done = false;
    shared->shutdown = false;

    pid_t pid = fork();
    if (pid == 0) {
        childProcess(shared);
        _exit(0);
    } else {
        parentProcess(shared, pid);
    }

    munmap(shared, sizeof(SharedPayload));
    return 0;
}
