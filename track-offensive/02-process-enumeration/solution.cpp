// Chapitre 02 - Solution : Enumeration de Processus
// EDUCATIF - Lister et analyser les processus du systeme
//
// Compile : g++ -std=c++17 -o solution solution.cpp

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

// TODO 1 : Enumeration des processus
std::vector<ProcessInfo> enumerateProcesses() {
    std::vector<ProcessInfo> processes;

    FILE* pipe = popen("ps -eo pid,ppid,user,%cpu,%mem,comm 2>/dev/null", "r");
    if (!pipe) return processes;

    char line[512];
    // Sauter le header
    if (fgets(line, sizeof(line), pipe) == nullptr) {
        pclose(pipe);
        return processes;
    }

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

// TODO 2 : Top CPU
ProcessInfo findTopCPU(const std::vector<ProcessInfo>& procs) {
    if (procs.empty()) return {};
    return *std::max_element(procs.begin(), procs.end(),
        [](const ProcessInfo& a, const ProcessInfo& b) {
            return a.cpu < b.cpu;
        });
}

// TODO 3 : Top Memoire
ProcessInfo findTopMemory(const std::vector<ProcessInfo>& procs) {
    if (procs.empty()) return {};
    return *std::max_element(procs.begin(), procs.end(),
        [](const ProcessInfo& a, const ProcessInfo& b) {
            return a.mem < b.mem;
        });
}

// TODO 4 : Filtre par utilisateur
std::vector<ProcessInfo> filterByUser(const std::vector<ProcessInfo>& procs,
                                       const std::string& user) {
    std::vector<ProcessInfo> filtered;
    for (const auto& p : procs) {
        if (p.user == user) {
            filtered.push_back(p);
        }
    }
    return filtered;
}

// TODO 5 : Recherche par nom
std::vector<ProcessInfo> findByName(const std::vector<ProcessInfo>& procs,
                                     const std::string& name) {
    std::vector<ProcessInfo> found;
    for (const auto& p : procs) {
        if (p.command.find(name) != std::string::npos) {
            found.push_back(p);
        }
    }
    return found;
}

// TODO 6 : Enfants d'un processus
std::vector<ProcessInfo> findChildren(const std::vector<ProcessInfo>& procs, int parentPid) {
    std::vector<ProcessInfo> children;
    for (const auto& p : procs) {
        if (p.ppid == parentPid) {
            children.push_back(p);
        }
    }
    return children;
}

void printProcess(const ProcessInfo& p) {
    printf("  PID: %-6d  PPID: %-6d  User: %-10s  CPU: %5.1f%%  MEM: %5.1f%%  CMD: %s\n",
           p.pid, p.ppid, p.user.c_str(), p.cpu, p.mem, p.command.c_str());
}

int main() {
    std::cout << "=== Solution : Enumeration de Processus ===" << std::endl;
    std::cout << std::endl;

    auto procs = enumerateProcesses();
    std::cout << "[*] Processus trouves : " << procs.size() << std::endl;

    // Top CPU
    std::cout << std::endl << "[*] Top CPU :" << std::endl;
    printProcess(findTopCPU(procs));

    // Top Memory
    std::cout << std::endl << "[*] Top Memoire :" << std::endl;
    printProcess(findTopMemory(procs));

    // Mon PID
    int myPid = getpid();
    std::cout << std::endl << "[*] Mon PID : " << myPid << std::endl;

    // Enfants de PID 1
    std::cout << std::endl << "[*] Enfants de PID 1 :" << std::endl;
    auto children = findChildren(procs, 1);
    for (const auto& c : children) {
        printProcess(c);
    }

    // Shells actifs
    std::cout << std::endl << "[*] Shells actifs :" << std::endl;
    auto shells = findByName(procs, "sh");
    for (const auto& s : shells) {
        printProcess(s);
    }

    return 0;
}
