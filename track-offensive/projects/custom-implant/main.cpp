// ==========================================================================
// main.cpp - Simulation d'implant C2 (EDUCATIF)
// ==========================================================================
//
// DISCLAIMER EDUCATIF 
// Ce programme est une SIMULATION EDUCATIVE uniquement.
// - Communication EXCLUSIVEMENT sur 127.0.0.1 (localhost)
// - Commandes limitees a une whitelist explicite
// - Concu pour CTF, labs de securite, et formation
// - NE JAMAIS utiliser en dehors d'un environnement de lab controle
// - Toute utilisation malveillante est illegale
//
// Architecture :
//   [Serveur C2] ──── TCP localhost:4444 ──── [Implant (ce fichier)]
//
// Compile :
//   g++ -std=c++17 -o implant main.cpp
//
// Utilisation :
//   1. Lancer d'abord un serveur : nc -lvp 4444  OU  le server.cpp du projet c2
//   2. Lancer l'implant : ./implant
//   3. Envoyer des commandes depuis le serveur (whoami, ls, pwd, id)
//   4. Envoyer "exit" pour terminer proprement
//
// ==========================================================================

#include "implant.h"

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

// ============================================================
// Implementations des fonctions de implant.h
// ============================================================

namespace implant {

bool isCommandAllowed(const std::string& cmd) {
    // Trim les espaces de debut/fin
    std::string trimmed = cmd;
    while (!trimmed.empty() && (trimmed.front() == ' ' || trimmed.front() == '\n' || trimmed.front() == '\r'))
        trimmed.erase(trimmed.begin());
    while (!trimmed.empty() && (trimmed.back() == ' ' || trimmed.back() == '\n' || trimmed.back() == '\r'))
        trimmed.pop_back();

    for (const auto& allowed : ALLOWED_COMMANDS) {
        if (trimmed == allowed) return true;
    }
    return false;
}

std::string executeCommand(const std::string& cmd) {
    if (!isCommandAllowed(cmd)) {
        return "[IMPLANT] Commande non autorisee : \"" + cmd +
               "\". Whitelist : whoami, ls, pwd, id, hostname, uname -a, date, uptime\n";
    }

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        return "[IMPLANT] Erreur popen()\n";
    }

    std::string result;
    char buf[256];
    while (fgets(buf, sizeof(buf), pipe) != nullptr) {
        result += buf;
    }
    pclose(pipe);

    if (result.empty()) result = "(pas de sortie)\n";
    return result;
}

std::string recvLine(int fd) {
    std::string line;
    char c;
    while (line.size() < MAX_MSG_SIZE) {
        ssize_t n = recv(fd, &c, 1, 0);
        if (n <= 0) break;
        if (c == '\n') break;
        if (c != '\r') line += c;
    }
    return line;
}

bool sendLine(int fd, const std::string& msg) {
    std::string data = msg + "\n";
    ssize_t sent = send(fd, data.c_str(), data.size(), 0);
    return sent == static_cast<ssize_t>(data.size());
}

void printEducationalBanner() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║  SIMULATION D'IMPLANT C2 - USAGE EDUCATIF UNIQUEMENT    ║\n";
    std::cout << "║                                                          ║\n";
    std::cout << "║  - Connexion : localhost (127.0.0.1) UNIQUEMENT          ║\n";
    std::cout << "║  - Commandes : whitelist explicite seulement             ║\n";
    std::cout << "║  - Objectif  : comprendre les architectures C2           ║\n";
    std::cout << "║  - Usage     : CTF / labs de securite controles          ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
}

}  // namespace implant

// ============================================================
// Boucle principale de l'implant
// ============================================================

int main() {
    implant::printEducationalBanner();

    // --- Creation du socket TCP ---
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "[IMPLANT] Erreur : socket() = " << strerror(errno) << "\n";
        return 1;
    }

    // --- Connexion au serveur C2 (localhost uniquement) ---
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(implant::C2_PORT);

    if (inet_pton(AF_INET, implant::C2_HOST, &server_addr.sin_addr) <= 0) {
        std::cerr << "[IMPLANT] Erreur : adresse invalide.\n";
        close(sock);
        return 1;
    }

    std::cout << "[IMPLANT] Connexion vers " << implant::C2_HOST
              << ":" << implant::C2_PORT << "...\n";

    if (connect(sock, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        std::cerr << "[IMPLANT] Connexion echouee : " << strerror(errno) << "\n";
        std::cerr << "[IMPLANT] Verifier que le serveur C2 tourne sur port " << implant::C2_PORT << "\n";
        close(sock);
        return 1;
    }

    std::cout << "[IMPLANT] Connecte au serveur C2. Attente de commandes...\n";

    // --- Envoyer un message d'identification ---
    implant::sendLine(sock, "[IMPLANT] Connecte. Commandes: whoami|ls|pwd|id|hostname|uname -a|date|uptime|exit");

    // --- Boucle de reception et execution des commandes ---
    while (true) {
        std::string cmd = implant::recvLine(sock);

        if (cmd.empty()) {
            std::cout << "[IMPLANT] Connexion fermee par le serveur.\n";
            break;
        }

        std::cout << "[IMPLANT] Commande recue : \"" << cmd << "\"\n";

        if (cmd == implant::CMD_EXIT) {
            implant::sendLine(sock, "[IMPLANT] Deconnexion propre.");
            break;
        }

        if (cmd == implant::CMD_HELP) {
            std::string help = "Commandes autorisees : ";
            for (size_t i = 0; i < implant::ALLOWED_COMMANDS.size(); ++i) {
                help += implant::ALLOWED_COMMANDS[i];
                if (i + 1 < implant::ALLOWED_COMMANDS.size()) help += ", ";
            }
            implant::sendLine(sock, help);
            continue;
        }

        // Executer la commande (whitelist verifiee dans executeCommand)
        std::string output = implant::executeCommand(cmd);
        implant::sendLine(sock, output);
    }

    close(sock);
    std::cout << "[IMPLANT] Socket ferme. Fin.\n";
    return 0;
}
