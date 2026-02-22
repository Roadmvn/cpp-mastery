// ==========================================================================
// server.cpp - Serveur C2 Educatif
// ==========================================================================
//
// DISCLAIMER EDUCATIF 
// Ce serveur est une simulation educative d'infrastructure C2.
// - Ecoute UNIQUEMENT sur 127.0.0.1:4444 (localhost)
// - Accepte une seule connexion a la fois (simplicite pedagogique)
// - Communication en clair (pour la lisibilite)
// - Concu pour CTF et labs de securite controles
// Toute utilisation malveillante est illegale.
//
// Compile : g++ -std=c++17 -o server server.cpp
// Usage   : ./server
//           (puis lancer ./client dans un autre terminal)
//
// ==========================================================================

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// ============================================================
// Configuration
// ============================================================

static const int    C2_PORT      = 4444;
static const char*  C2_HOST      = "127.0.0.1";  // localhost UNIQUEMENT
static const size_t MAX_BUF      = 4096;
static const std::string CMD_EXIT = "exit";
static const std::string CMD_HELP = "help";

// ============================================================
// Utilitaires reseau
// ============================================================

// Recevoir une ligne (jusqu'a '\n')
std::string recvLine(int fd) {
    std::string line;
    char c;
    while (line.size() < MAX_BUF) {
        ssize_t n = recv(fd, &c, 1, 0);
        if (n <= 0) break;
        if (c == '\n') break;
        if (c != '\r') line += c;
    }
    return line;
}

// Envoyer une ligne (avec '\n' final)
bool sendLine(int fd, const std::string& msg) {
    std::string data = msg + "\n";
    ssize_t sent = send(fd, data.c_str(), data.size(), 0);
    return sent == static_cast<ssize_t>(data.size());
}

// ============================================================
// Affichage
// ============================================================

void printBanner() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║     SERVEUR C2 EDUCATIF - USAGE CTF/LAB UNIQUEMENT      ║\n";
    std::cout << "║                                                          ║\n";
    std::cout << "║  Ecoute : " << C2_HOST << ":" << C2_PORT << "                           ║\n";
    std::cout << "║  Mode   : une connexion a la fois                        ║\n";
    std::cout << "║  Proto  : texte clair (pedagogique)                      ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
}

void printHelp() {
    std::cout << "\n[C2] Commandes disponibles cote serveur :\n";
    std::cout << "  whoami   - utilisateur courant\n";
    std::cout << "  ls       - liste du repertoire\n";
    std::cout << "  pwd      - repertoire courant\n";
    std::cout << "  id       - UID/GID\n";
    std::cout << "  hostname - nom de la machine\n";
    std::cout << "  uname -a - info systeme\n";
    std::cout << "  date     - date et heure\n";
    std::cout << "  uptime   - duree de fonctionnement\n";
    std::cout << "  help     - cette aide\n";
    std::cout << "  exit     - terminer la session\n\n";
}

// ============================================================
// Boucle de session C2
// ============================================================

void handleSession(int client_fd) {
    std::cout << "[C2-SERVER] Client connecte !\n";

    // Recevoir le message d'identification de l'implant
    std::string hello = recvLine(client_fd);
    if (!hello.empty()) {
        std::cout << "[C2-SERVER] Message initial : " << hello << "\n";
    }

    printHelp();

    // Boucle principale : l'operateur tape des commandes
    while (true) {
        std::cout << "\n[C2] Entrez une commande (ou 'exit') : ";
        std::cout.flush();

        std::string cmd;
        if (!std::getline(std::cin, cmd)) {
            // EOF sur stdin
            std::cout << "\n[C2-SERVER] EOF sur stdin. Fermeture.\n";
            sendLine(client_fd, CMD_EXIT);
            break;
        }

        if (cmd.empty()) continue;

        if (cmd == "help") {
            printHelp();
            continue;
        }

        // Envoyer la commande au client
        if (!sendLine(client_fd, cmd)) {
            std::cerr << "[C2-SERVER] Erreur d'envoi. Client deconnecte ?\n";
            break;
        }

        if (cmd == CMD_EXIT) {
            std::cout << "[C2-SERVER] Commande exit envoyee.\n";
            break;
        }

        // Recevoir le resultat
        std::string result = recvLine(client_fd);
        if (result.empty()) {
            std::cout << "[C2-SERVER] Connexion fermee par le client.\n";
            break;
        }

        std::cout << "[C2] Resultat :\n" << result << "\n";
    }
}

// ============================================================
// MAIN
// ============================================================

int main() {
    printBanner();

    // --- Creer le socket serveur ---
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "[C2-SERVER] socket() : " << strerror(errno) << "\n";
        return 1;
    }

    // Permettre la reutilisation immediate du port (evite TIME_WAIT)
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // --- Bind sur localhost uniquement ---
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(C2_PORT);

    // Bind UNIQUEMENT sur 127.0.0.1 (pas 0.0.0.0)
    if (inet_pton(AF_INET, C2_HOST, &addr.sin_addr) <= 0) {
        std::cerr << "[C2-SERVER] inet_pton() : " << strerror(errno) << "\n";
        close(server_fd);
        return 1;
    }

    if (bind(server_fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        std::cerr << "[C2-SERVER] bind() : " << strerror(errno) << "\n";
        std::cerr << "[C2-SERVER] Le port " << C2_PORT << " est peut-etre deja utilise.\n";
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        std::cerr << "[C2-SERVER] listen() : " << strerror(errno) << "\n";
        close(server_fd);
        return 1;
    }

    std::cout << "[C2-SERVER] Serveur C2 educatif - " << C2_HOST << ":" << C2_PORT << "\n";
    std::cout << "[C2-SERVER] Attente de connexion (lancer ./client dans un autre terminal)...\n";

    // --- Accepter une connexion ---
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);
    if (client_fd < 0) {
        std::cerr << "[C2-SERVER] accept() : " << strerror(errno) << "\n";
        close(server_fd);
        return 1;
    }

    // --- Gerer la session ---
    handleSession(client_fd);

    // --- Nettoyage ---
    close(client_fd);
    close(server_fd);
    std::cout << "[C2-SERVER] Session terminee. Au revoir.\n";
    return 0;
}
