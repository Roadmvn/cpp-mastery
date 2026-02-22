// Chapitre 02 - Challenge : Detecteur de Processus Suspects
// EDUCATIF - Analyser les processus pour identifier des anomalies
//
// OBJECTIF : Creer un outil qui enumere les processus et detecte des
// patterns potentiellement suspects (processus sans parent, noms inhabituels, etc.)
//
// Compile : g++ -std=c++17 -o challenge challenge.cpp
//
// DISCLAIMER : Simulation educative d'analyse de processus.
// A utiliser UNIQUEMENT dans un cadre educatif / CTF / lab autorise.

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <unistd.h>

struct ProcessInfo {
    int pid;
    int ppid;
    std::string user;
    std::string command;
    float cpu;
    float mem;
};

// Fourni : enumeration de base
std::vector<ProcessInfo> enumerateProcesses() {
    std::vector<ProcessInfo> processes;
    FILE* pipe = popen("ps -eo pid,ppid,user,%cpu,%mem,comm 2>/dev/null", "r");
    if (!pipe) return processes;
    char line[512];
    if (fgets(line, sizeof(line), pipe) == nullptr) { pclose(pipe); return processes; }
    while (fgets(line, sizeof(line), pipe)) {
        ProcessInfo proc;
        char user[64], cmd[256];
        if (sscanf(line, "%d %d %63s %f %f %255s",
                   &proc.pid, &proc.ppid, user, &proc.cpu, &proc.mem, cmd) >= 6) {
            proc.user = user;
            proc.command = cmd;
            processes.push_back(proc);
        }
    }
    pclose(pipe);
    return processes;
}

// TODO 1 : Construis un arbre de processus (map de PPID -> liste de PIDs enfants)
std::map<int, std::vector<int>> buildProcessTree(const std::vector<ProcessInfo>& procs) {
    std::map<int, std::vector<int>> tree;
    // TON CODE ICI
    return tree;
}

// TODO 2 : Trouve les processus "orphelins"
// Un orphelin = son PPID n'existe pas dans la liste des PIDs
// (sauf PID 0 et PID 1 qui sont speciaux)
std::vector<ProcessInfo> findOrphans(const std::vector<ProcessInfo>& procs) {
    std::vector<ProcessInfo> orphans;
    // TON CODE ICI
    return orphans;
}

// TODO 3 : Detecte les processus gourmands (CPU > 50% ou MEM > 10%)
std::vector<ProcessInfo> findResourceHogs(const std::vector<ProcessInfo>& procs) {
    std::vector<ProcessInfo> hogs;
    // TON CODE ICI
    return hogs;
}

// TODO 4 : Compte les processus par utilisateur
std::map<std::string, int> countByUser(const std::vector<ProcessInfo>& procs) {
    std::map<std::string, int> counts;
    // TON CODE ICI
    return counts;
}

// TODO 5 : Affiche l'arbre de processus de maniere recursive
// Affiche avec indentation pour montrer la hierarchie
void printTree(const std::vector<ProcessInfo>& procs,
               const std::map<int, std::vector<int>>& tree,
               int rootPid, int depth) {
    // TON CODE ICI
}

// TODO 6 : Detecte des noms de processus connus comme outils de securite
// Liste : "tcpdump", "wireshark", "nmap", "snort", "ossec", "clamd", "falcon"
std::vector<ProcessInfo> detectSecurityTools(const std::vector<ProcessInfo>& procs) {
    std::vector<ProcessInfo> detected;
    // TON CODE ICI
    return detected;
}

int main() {
    std::cout << "=== Challenge : Analyseur de Processus ===" << std::endl;
    std::cout << "[!] EDUCATIF UNIQUEMENT" << std::endl;
    std::cout << std::endl;

    auto procs = enumerateProcesses();
    std::cout << "[*] Total processus : " << procs.size() << std::endl;

    // Arbre
    auto tree = buildProcessTree(procs);
    std::cout << std::endl << "[*] Arbre de processus (depuis PID 1) :" << std::endl;
    printTree(procs, tree, 1, 0);

    // Orphelins
    auto orphans = findOrphans(procs);
    std::cout << std::endl << "[*] Processus orphelins : " << orphans.size() << std::endl;

    // Resource hogs
    auto hogs = findResourceHogs(procs);
    std::cout << std::endl << "[*] Processus gourmands : " << hogs.size() << std::endl;

    // Par utilisateur
    auto counts = countByUser(procs);
    std::cout << std::endl << "[*] Processus par utilisateur :" << std::endl;
    for (const auto& [user, count] : counts) {
        std::cout << "    " << user << " : " << count << std::endl;
    }

    // Outils de securite
    auto security = detectSecurityTools(procs);
    std::cout << std::endl << "[*] Outils de securite detectes : " << security.size() << std::endl;

    return 0;
}
