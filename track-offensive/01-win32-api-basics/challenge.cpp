// Chapitre 01 - Challenge : Collecteur d'Informations Systeme
// EDUCATIF - Simulation d'un outil de reconnaissance
//
// OBJECTIF : Creer un programme qui collecte un maximum d'informations
// sur le systeme local, comme le ferait un outil de reconnaissance.
//
// Compile : g++ -std=c++17 -o challenge challenge.cpp
//
// DISCLAIMER : Cet exercice simule un outil de collecte d'infos systeme.
// A utiliser UNIQUEMENT dans un cadre educatif / CTF / lab autorise.

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstdio>

// CHALLENGE : Implemente toutes les fonctions de collecte
// Chaque fonction doit retourner les informations demandees sous forme de string

struct SystemReport {
    std::string hostname;
    std::string username;
    std::string uid;
    std::string gid;
    std::string home_dir;
    std::string shell;
    std::string cwd;
    std::string os_info;
    std::string arch;
    std::string uptime;
    std::vector<std::string> env_vars;
    std::vector<std::string> groups;
    std::string locale;
};

// TODO 1 : Collecte les infos de base (hostname, user, uid, gid, home, shell)
void collectBasicInfo(SystemReport& report) {
    // TON CODE ICI
}

// TODO 2 : Collecte les infos OS (nom, version, architecture)
void collectOSInfo(SystemReport& report) {
    // TON CODE ICI
}

// TODO 3 : Collecte les variables d'environnement "interessantes"
// (PATH, SHELL, TERM, LANG, HOME, USER, EDITOR, SSH_CONNECTION)
void collectEnvVars(SystemReport& report) {
    // TON CODE ICI
}

// TODO 4 : Collecte les groupes de l'utilisateur
void collectGroups(SystemReport& report) {
    // TON CODE ICI
}

// TODO 5 : Verifie si certains outils de securite sont presents
// (cherche des binaires comme curl, wget, python3, gcc, nmap, ssh)
// Utilise popen avec "which <tool>" pour verifier
std::map<std::string, bool> checkInstalledTools() {
    std::map<std::string, bool> tools;
    // TON CODE ICI
    return tools;
}

// TODO 6 : Genere un rapport texte formate
void generateReport(const SystemReport& report, const std::map<std::string, bool>& tools) {
    std::cout << "╔══════════════════════════════════════════╗" << std::endl;
    std::cout << "║     RAPPORT DE RECONNAISSANCE SYSTEME    ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;

    // TON CODE ICI - Affiche toutes les infos de maniere formatee
}

int main() {
    std::cout << "[*] Demarrage de la collecte d'informations..." << std::endl;
    std::cout << "[!] EDUCATIF UNIQUEMENT - Lab/CTF autorise" << std::endl;
    std::cout << std::endl;

    SystemReport report;

    collectBasicInfo(report);
    collectOSInfo(report);
    collectEnvVars(report);
    collectGroups(report);
    auto tools = checkInstalledTools();

    generateReport(report, tools);

    return 0;
}
