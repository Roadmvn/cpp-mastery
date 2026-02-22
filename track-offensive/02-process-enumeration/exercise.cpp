// Chapitre 02 - Exercise : Enumeration de Processus
// EDUCATIF - Lister et analyser les processus du systeme
//
// Compile : g++ -std=c++17 -o exercise exercise.cpp

#include <iostream>
#include <string>
#include <vector>
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

// TODO 1 : Implemente l'enumeration des processus
// Utilise popen avec "ps -eo pid,ppid,user,%cpu,%mem,comm"
// Parse chaque ligne et remplis un vector<ProcessInfo>
std::vector<ProcessInfo> enumerateProcesses() {
    std::vector<ProcessInfo> processes;
    // TON CODE ICI
    return processes;
}

// TODO 2 : Trouve le processus avec le plus de CPU
// Retourne le ProcessInfo avec la valeur cpu la plus elevee
ProcessInfo findTopCPU(const std::vector<ProcessInfo>& procs) {
    ProcessInfo top{};
    // TON CODE ICI
    return top;
}

// TODO 3 : Trouve le processus avec le plus de memoire
ProcessInfo findTopMemory(const std::vector<ProcessInfo>& procs) {
    ProcessInfo top{};
    // TON CODE ICI
    return top;
}

// TODO 4 : Filtre les processus par utilisateur
// Retourne uniquement les processus appartenant a l'utilisateur donne
std::vector<ProcessInfo> filterByUser(const std::vector<ProcessInfo>& procs,
                                       const std::string& user) {
    std::vector<ProcessInfo> filtered;
    // TON CODE ICI
    return filtered;
}

// TODO 5 : Cherche un processus par nom (partiel)
// Retourne tous les processus dont le nom contient 'name'
std::vector<ProcessInfo> findByName(const std::vector<ProcessInfo>& procs,
                                     const std::string& name) {
    std::vector<ProcessInfo> found;
    // TON CODE ICI
    return found;
}

// TODO 6 : Trouve les processus enfants d'un PID donne
std::vector<ProcessInfo> findChildren(const std::vector<ProcessInfo>& procs, int parentPid) {
    std::vector<ProcessInfo> children;
    // TON CODE ICI
    return children;
}

void printProcess(const ProcessInfo& p) {
    printf("  PID: %-6d  PPID: %-6d  User: %-10s  CPU: %5.1f%%  MEM: %5.1f%%  CMD: %s\n",
           p.pid, p.ppid, p.user.c_str(), p.cpu, p.mem, p.command.c_str());
}

int main() {
    std::cout << "=== Exercise : Enumeration de Processus ===" << std::endl;
    std::cout << std::endl;

    // Enumeration
    auto procs = enumerateProcesses();
    std::cout << "[*] Processus trouves : " << procs.size() << std::endl;

    if (procs.empty()) {
        std::cout << "[!] Aucun processus - implemente enumerateProcesses()" << std::endl;
        return 1;
    }

    // Top CPU
    std::cout << std::endl << "[*] Top CPU :" << std::endl;
    auto topCpu = findTopCPU(procs);
    printProcess(topCpu);

    // Top Memory
    std::cout << std::endl << "[*] Top Memoire :" << std::endl;
    auto topMem = findTopMemory(procs);
    printProcess(topMem);

    // Mon processus
    int myPid = getpid();
    std::cout << std::endl << "[*] Mon PID : " << myPid << std::endl;

    // Enfants de PID 1
    std::cout << std::endl << "[*] Enfants de PID 1 :" << std::endl;
    auto children = findChildren(procs, 1);
    for (const auto& c : children) {
        printProcess(c);
    }

    // Recherche de "bash" ou "zsh"
    std::cout << std::endl << "[*] Shells actifs :" << std::endl;
    auto shells = findByName(procs, "sh");
    for (const auto& s : shells) {
        printProcess(s);
    }

    return 0;
}
