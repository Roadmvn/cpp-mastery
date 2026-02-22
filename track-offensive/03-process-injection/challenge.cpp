// Chapitre 03 - Challenge : Systeme d'Injection Multi-Commandes avec Protocole
// EDUCATIF - Simulation avancee avec protocole de communication
//
// OBJECTIF : Ameliorer la simulation en ajoutant :
// - Un protocole de communication structure (header + payload)
// - Support multi-commandes sequentielles
// - Logs horodates de chaque operation
// - Detection de timeout
//
// Compile : g++ -std=c++17 -o challenge challenge.cpp
//
// DISCLAIMER : Simulation educative d'IPC.
// A utiliser UNIQUEMENT dans un cadre educatif / CTF / lab autorise.

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <cstdio>

// Protocole de communication structure
enum class MsgType : int {
    NONE = 0,
    COMMAND = 1,     // Commande a executer
    RESULT = 2,      // Resultat d'execution
    HEARTBEAT = 3,   // Verification que le processus est vivant
    SHUTDOWN = 4     // Demande d'arret
};

struct Message {
    MsgType type;
    int sequence;          // Numero de sequence
    time_t timestamp;      // Horodatage
    int payload_size;      // Taille du payload
    char payload[4096];    // Donnees
};

struct SharedChannel {
    Message inbox;         // Message du parent vers l'enfant
    Message outbox;        // Message de l'enfant vers le parent
    bool inbox_ready;
    bool outbox_ready;
    int total_commands;    // Compteur de commandes executees
    bool alive;            // Heartbeat du processus enfant
};

// Fourni : creation memoire partagee
SharedChannel* createChannel() {
    void* mem = mmap(nullptr, sizeof(SharedChannel),
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) return nullptr;
    SharedChannel* ch = static_cast<SharedChannel*>(mem);
    std::memset(ch, 0, sizeof(SharedChannel));
    ch->alive = true;
    return ch;
}

// Fourni : horodatage
std::string timestamp() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&now));
    return std::string(buf);
}

// TODO 1 : Envoie un message structure dans la boite inbox
// Remplit tous les champs du Message (type, sequence, timestamp, payload)
// Met inbox_ready = true
void sendToChild(SharedChannel* ch, MsgType type, const std::string& payload, int seq) {
    // TON CODE ICI
}

// TODO 2 : Envoie un resultat dans la boite outbox
void sendToParent(SharedChannel* ch, MsgType type, const std::string& payload, int seq) {
    // TON CODE ICI
}

// TODO 3 : Processus enfant avec protocole
// Gere les types COMMAND, HEARTBEAT, SHUTDOWN
// Pour COMMAND : execute avec popen, renvoie le resultat
// Pour HEARTBEAT : renvoie "ALIVE" avec le compteur de commandes
// Pour SHUTDOWN : sort proprement
void childProcess(SharedChannel* ch) {
    std::cout << "[" << timestamp() << "][CIBLE:" << getpid() << "] Demarre" << std::endl;

    // TON CODE ICI
}

// TODO 4 : Processus parent avec protocole et timeout
// Envoie des commandes, attend les resultats
// Si pas de reponse en 2 secondes = timeout
// Envoie un heartbeat tous les 3 commandes
void parentProcess(SharedChannel* ch, pid_t childPid) {
    std::cout << "[" << timestamp() << "][CTRL:" << getpid()
              << "] Connecte a PID " << childPid << std::endl;
    usleep(100000);

    const char* commands[] = {
        "whoami", "hostname", "date", "uname -a",
        "echo 'test injection'", "pwd"
    };

    int seq = 0;
    for (const char* cmd : commands) {
        seq++;

        // Envoie heartbeat tous les 3 commandes
        // TON CODE ICI

        // Envoie la commande
        // TON CODE ICI

        // Attend le resultat avec timeout de 2 secondes
        // TON CODE ICI
    }

    // Shutdown
    sendToChild(ch, MsgType::SHUTDOWN, "Fin de session", ++seq);
    waitpid(childPid, nullptr, 0);

    std::cout << "\n[" << timestamp() << "][CTRL] Session terminee. "
              << ch->total_commands << " commandes executees." << std::endl;
}

int main() {
    std::cout << "=== Challenge : Injection avec Protocole ===" << std::endl;
    std::cout << "[!] EDUCATIF UNIQUEMENT" << std::endl;
    std::cout << std::endl;

    SharedChannel* ch = createChannel();
    if (!ch) {
        std::cerr << "Erreur creation channel" << std::endl;
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        childProcess(ch);
        _exit(0);
    } else {
        parentProcess(ch, pid);
    }

    munmap(ch, sizeof(SharedChannel));
    return 0;
}
