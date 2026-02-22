// Chapitre 06 - Challenge : Systeme de Hooking avec Filtrage
// EDUCATIF - Hook avance avec regles de filtrage configurables
//
// OBJECTIF : Creer un programme standalone (pas LD_PRELOAD) qui
// demontre le concept de hooking avec des tables de fonctions
// et un systeme de filtrage/logging
//
// Compile : g++ -std=c++17 -o challenge challenge.cpp -ldl
//
// DISCLAIMER : Demonstration educative du concept de hooking.

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cstdio>
#include <cstring>

// Systeme de hooks base sur des callbacks (sans LD_PRELOAD)
// Simule le concept de hooking avec un dispatch table

enum class HookAction {
    ALLOW,       // Laisser passer
    BLOCK,       // Bloquer l'appel
    LOG_ONLY,    // Logger mais laisser passer
    MODIFY       // Modifier les arguments
};

struct HookRule {
    std::string function_name;
    HookAction action;
    std::string pattern;  // Pattern a matcher (ex: chemin de fichier)
    std::string description;
};

// Classe qui simule un systeme de hooking
class HookEngine {
private:
    std::vector<HookRule> rules_;
    std::map<std::string, int> call_counts_;
    bool verbose_;

public:
    HookEngine(bool verbose = true) : verbose_(verbose) {}

    // TODO 1 : Ajoute une regle de hook
    void addRule(const std::string& func, HookAction action,
                 const std::string& pattern, const std::string& desc) {
        // TON CODE ICI
    }

    // TODO 2 : Evalue les regles pour un appel donne
    // Retourne l'action a effectuer pour cet appel
    // Si plusieurs regles matchent, la plus restrictive gagne
    // (BLOCK > MODIFY > LOG_ONLY > ALLOW)
    HookAction evaluate(const std::string& func, const std::string& arg) {
        // TON CODE ICI
        return HookAction::ALLOW;
    }

    // TODO 3 : Simule un appel de fonction hooke
    // Affiche ce qui se passe selon l'action
    std::string hookCall(const std::string& func, const std::string& arg) {
        call_counts_[func]++;
        HookAction action = evaluate(func, arg);

        // TON CODE ICI selon action :
        // ALLOW    "PASS: func(arg)"
        // BLOCK    "BLOCKED: func(arg)"
        // LOG_ONLY  log + "PASS: func(arg)"
        // MODIFY   "MODIFIED: func(arg) -> func(modified_arg)"

        return "";
    }

    // TODO 4 : Affiche les statistiques d'appels
    void printStats() const {
        std::cout << "\n=== Hook Statistics ===" << std::endl;
        // TON CODE ICI - Affiche le nombre d'appels par fonction
    }

    // TODO 5 : Exporte les regles en format texte
    void exportRules() const {
        std::cout << "\n=== Hook Rules ===" << std::endl;
        // TON CODE ICI - Affiche chaque regle avec son action
    }
};

// Simulation d'un programme surveille par le hook engine
void simulateMonitoredProgram(HookEngine& engine) {
    std::cout << "\n=== Simulation de Programme Surveille ===" << std::endl;

    // Simule des appels de fonctions
    engine.hookCall("open", "/etc/passwd");
    engine.hookCall("open", "/tmp/data.txt");
    engine.hookCall("open", "/etc/shadow");
    engine.hookCall("connect", "192.168.1.1:80");
    engine.hookCall("connect", "10.0.0.1:4444");
    engine.hookCall("exec", "/bin/sh");
    engine.hookCall("exec", "/usr/bin/python3");
    engine.hookCall("getenv", "HOME");
    engine.hookCall("getenv", "AWS_SECRET_KEY");
    engine.hookCall("write", "/tmp/output.log");
    engine.hookCall("write", "/etc/crontab");
}

int main() {
    std::cout << "=== Challenge : Hook Engine ===" << std::endl;
    std::cout << "[!] EDUCATIF UNIQUEMENT" << std::endl;
    std::cout << std::endl;

    HookEngine engine(true);

    // Configure les regles de surveillance
    engine.addRule("open", HookAction::LOG_ONLY, "/etc/", "Surveille acces /etc/");
    engine.addRule("open", HookAction::BLOCK, "/etc/shadow", "Bloque acces shadow");
    engine.addRule("connect", HookAction::LOG_ONLY, "", "Log toutes les connexions");
    engine.addRule("connect", HookAction::BLOCK, ":4444", "Bloque port 4444 (suspect)");
    engine.addRule("exec", HookAction::BLOCK, "/bin/sh", "Bloque execution shell");
    engine.addRule("getenv", HookAction::LOG_ONLY, "AWS_", "Log acces credentials AWS");
    engine.addRule("write", HookAction::BLOCK, "/etc/", "Bloque ecriture dans /etc/");

    engine.exportRules();

    simulateMonitoredProgram(engine);

    engine.printStats();

    return 0;
}
