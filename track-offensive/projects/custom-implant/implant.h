#pragma once
// ==========================================================================
// implant.h - Interface de la simulation d'implant C2 (EDUCATIF)
// ==========================================================================
//
// DISCLAIMER EDUCATIF ⚠️
// Ce fichier fait partie d'une simulation educative d'implant C2.
// Il est concu pour apprendre les architectures reseau et la securite
// dans le cadre de CTF et labs controles.
// UTILISATION STRICTEMENT LIMITEE A LOCALHOST.
// Toute utilisation malveillante est illegale et contraire a l'ethique.
//
// ==========================================================================

#include <string>
#include <vector>
#include <functional>

namespace implant {

// Commandes autorisees par l'implant (whitelist explicite)
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

// Port de connexion (localhost uniquement)
static const int C2_PORT = 4444;
static const char* C2_HOST = "127.0.0.1";

// Taille maximale d'un message (securite basique)
static const size_t MAX_MSG_SIZE = 4096;

// Code de sortie propre
static const std::string CMD_EXIT = "exit";
static const std::string CMD_HELP = "help";

// Verifier si une commande est dans la whitelist
bool isCommandAllowed(const std::string& cmd);

// Executer une commande et capturer stdout (via popen)
// Retourne la sortie ou un message d'erreur
std::string executeCommand(const std::string& cmd);

// Recevoir une ligne depuis le socket fd (jusqu'a '\n' ou MAX_MSG_SIZE)
std::string recvLine(int fd);

// Envoyer une string sur le socket fd (ajoute '\n' automatiquement)
bool sendLine(int fd, const std::string& msg);

// Afficher le banner d'avertissement educatif
void printEducationalBanner();

}  // namespace implant
