// ==========================================================================
// client.cpp - Client C2 (Implant Simule) Educatif
// ==========================================================================
//
// DISCLAIMER EDUCATIF 
// Ce client est une simulation educative d'implant C2.
// - Se connecte UNIQUEMENT sur 127.0.0.1:4444 (localhost)
// - Commandes limitees a une whitelist explicite
// - Concu pour CTF et labs de securite controles
// - NE JAMAIS utiliser en dehors d'un environnement de lab isole
// Toute utilisation malveillante est illegale.
//
// Compile : g++ -std=c++17 -o client client.cpp
// Usage   : ./client  (apres avoir lance ./server)
//
// ==========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// ============================================================
// Configuration et whitelist
// ============================================================

static const int    C2_PORT  = 4444;
static const char*  C2_HOST  = "127.0.0.1";  // localhost UNIQUEMENT
static const size_t MAX_BUF  = 4096;

// Whitelist de commandes acceptees par l'implant
static const std::vector<std::string> ALLOWED_COMMANDS = {
    "whoami",
    "ls",
    "pwd",
    "id",
    "hostname",
    "uname -a",
    "date",
    "uptime"
};

static const std::string CMD_EXIT = "exit";
static const std::string CMD_HELP = "help";

// ============================================================
// Utilitaires
// ============================================================

// Recevoir une ligne depuis le socket (jusqu'a '\n')
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

// Envoyer une ligne sur le socket (avec '\n')
bool sendLine(int fd, const std::string& msg) {
    std::string data = msg + "\n";
    ssize_t sent = send(fd, data.c_str(), data.size(), 0);
    return sent == static_cast<ssize_t>(data.size());
}

// Verifier si une commande est dans la whitelist
bool isAllowed(const std::string& cmd) {
    std::string trimmed = cmd;
    // Supprimer les espaces/newlines de debut et fin
    while (!trimmed.empty() && (trimmed.front() == ' ' || trimmed.front() == '\n' || trimmed.front() == '\r'))
        trimmed.erase(trimmed.begin());
    while (!trimmed.empty() && (trimmed.back() == ' ' || trimmed.back() == '\n' || trimmed.back() == '\r'))
        trimmed.pop_back();

    for (const auto& allowed : ALLOWED_COMMANDS) {
        if (trimmed == allowed) return true;
    }
    return false;
}

// Executer une commande et capturer stdout
std::string execCommand(const std::string& cmd) {
    if (!isAllowed(cmd)) {
        std::string err = "[CLIENT] Commande refusee (hors whitelist) : \"" + cmd + "\"";
        std::cerr << err << "\n";
        return err + "\n";
    }

    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        return "[CLIENT] Erreur : popen() a echoue\n";
    }

    char buf[256];
    while (fgets(buf, sizeof(buf), pipe) != nullptr) {
        result += buf;
    }
    pclose(pipe);

    if (result.empty()) result = "(pas de sortie)\n";
    return result;
}

// ============================================================
// Banner
// ============================================================

void printBanner() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║    CLIENT C2 (IMPLANT SIMULE) - USAGE CTF/LAB SEUL      ║\n";
    std::cout << "║                                                          ║\n";
    std::cout << "║  Cible   : " << C2_HOST << ":" << C2_PORT << "                           ║\n";
    std::cout << "║  Whitelist: whoami|ls|pwd|id|hostname|uname -a|date      ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
}

// ============================================================
// MAIN - Boucle principale du client
// ============================================================

int main() {
    printBanner();

    // --- Creer le socket ---
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "[CLIENT] socket() : " << strerror(errno) << "\n";
        return 1;
    }

    // --- Connexion au serveur C2 (localhost uniquement) ---
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(C2_PORT);

    if (inet_pton(AF_INET, C2_HOST, &server_addr.sin_addr) <= 0) {
        std::cerr << "[CLIENT] Adresse invalide.\n";
        close(sock);
        return 1;
    }

    std::cout << "[CLIENT] Connexion vers " << C2_HOST << ":" << C2_PORT << "...\n";

    if (connect(sock, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        std::cerr << "[CLIENT] connect() : " << strerror(errno) << "\n";
        std::cerr << "[CLIENT] Verifier que le serveur tourne : ./server\n";
        close(sock);
        return 1;
    }

    std::cout << "[CLIENT] Connecte au serveur C2. Attente de commandes...\n";

    // Envoyer le message d'identification
    std::string hello = "[CLIENT] Connecte. Commandes autorisees: whoami|ls|pwd|id|hostname|uname -a|date|uptime|exit";
    sendLine(sock, hello);

    // --- Boucle de reception/execution des commandes ---
    while (true) {
        std::string cmd = recvLine(sock);

        if (cmd.empty()) {
            std::cout << "[CLIENT] Connexion fermee par le serveur.\n";
            break;
        }

        std::cout << "[CLIENT] Commande recue : \"" << cmd << "\"\n";

        // Commande de terminaison
        if (cmd == CMD_EXIT) {
            std::cout << "[CLIENT] Deconnexion sur demande du serveur.\n";
            break;
        }

        // Commande d'aide : retourner la liste des commandes autorisees
        if (cmd == CMD_HELP) {
            std::string help = "Commandes autorisees : ";
            for (size_t i = 0; i < ALLOWED_COMMANDS.size(); ++i) {
                help += ALLOWED_COMMANDS[i];
                if (i + 1 < ALLOWED_COMMANDS.size()) help += ", ";
            }
            sendLine(sock, help);
            continue;
        }

        // Executer la commande (whitelist verifiee dans execCommand)
        std::string output = execCommand(cmd);
        std::cout << "[CLIENT] Resultat a envoyer : " << output.size() << " bytes\n";

        if (!sendLine(sock, output)) {
            std::cerr << "[CLIENT] Erreur d'envoi du resultat.\n";
            break;
        }
    }

    close(sock);
    std::cout << "[CLIENT] Socket ferme. Fin.\n";
    return 0;
}
