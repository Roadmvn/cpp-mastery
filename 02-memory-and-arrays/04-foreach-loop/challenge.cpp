// =============================================================
// Challenge Offensive : Analyse de logs systeme
// =============================================================
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// =============================================================
// Contexte : Tu analyses les logs d'un serveur compromis.
// Chaque log est une string avec un format : "LEVEL|source|message"
// Tu dois parser ces logs, compter les erreurs par source,
// et identifier les patterns suspects.
// =============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Logs du serveur (format: "LEVEL|source|message")
    string logs[] = {
        "INFO|auth|User admin logged in",
        "ERROR|auth|Failed login attempt for root",
        "ERROR|auth|Failed login attempt for root",
        "ERROR|auth|Failed login attempt for root",
        "WARN|firewall|Port scan detected from 10.0.0.5",
        "INFO|web|GET /index.html 200",
        "ERROR|web|GET /admin/config 403",
        "ERROR|auth|Failed login attempt for admin",
        "WARN|firewall|Unusual traffic from 10.0.0.5",
        "INFO|web|GET /api/users 200",
        "ERROR|auth|Failed login attempt for root",
        "ERROR|auth|Failed login attempt for root",
        "WARN|firewall|Port scan detected from 10.0.0.5",
        "INFO|auth|User guest logged in",
        "ERROR|web|POST /upload 500",
        "ERROR|auth|Account locked: root",
        "WARN|system|High CPU usage detected",
        "ERROR|web|GET /../../etc/passwd 400",
        "INFO|web|GET /index.html 200",
        "ERROR|auth|Failed login attempt for admin"
    };
    int nbLogs = sizeof(logs) / sizeof(logs[0]);

    cout << "=== Analyse de logs (" << nbLogs << " entrees) ===" << endl;

    // --- Comptage par niveau ---
    int infoCount = 0, warnCount = 0, errorCount = 0;
    for (const auto& log : logs) {
        if (log.substr(0, 4) == "INFO") infoCount++;
        else if (log.substr(0, 4) == "WARN") warnCount++;
        else if (log.substr(0, 5) == "ERROR") errorCount++;
    }

    cout << "\n--- Repartition par niveau ---" << endl;
    cout << "INFO  : " << infoCount << endl;
    cout << "WARN  : " << warnCount << endl;
    cout << "ERROR : " << errorCount << endl;

    // --- Comptage d'erreurs par source ---
    // Sources connues : auth, web, firewall, system
    string sources[] = {"auth", "web", "firewall", "system"};
    int sourceErrors[4] = {0, 0, 0, 0};
    int nbSources = sizeof(sources) / sizeof(sources[0]);

    for (const auto& log : logs) {
        if (log.substr(0, 5) != "ERROR") continue;

        for (int s = 0; s < nbSources; s++) {
            // Chercher "|source|" dans le log
            string pattern = "|" + sources[s] + "|";
            if (log.find(pattern) != string::npos) {
                sourceErrors[s]++;
                break;
            }
        }
    }

    cout << "\n--- Erreurs par source ---" << endl;
    for (int s = 0; s < nbSources; s++) {
        cout << sources[s] << " : " << sourceErrors[s] << " erreur(s)" << endl;
    }

    // --- Detection de brute force ---
    int failedRoot = 0;
    int failedAdmin = 0;
    for (const auto& log : logs) {
        if (log.find("Failed login attempt for root") != string::npos) failedRoot++;
        if (log.find("Failed login attempt for admin") != string::npos) failedAdmin++;
    }

    cout << "\n--- Detection brute force ---" << endl;
    cout << "Tentatives echouees root  : " << failedRoot << endl;
    cout << "Tentatives echouees admin : " << failedAdmin << endl;

    if (failedRoot >= 3) {
        cout << "[ALERTE] Brute force detecte sur compte root !" << endl;
    }
    if (failedAdmin >= 3) {
        cout << "[ALERTE] Brute force detecte sur compte admin !" << endl;
    }

    // --- Detection de path traversal ---
    cout << "\n--- Detection d'attaques ---" << endl;
    for (const auto& log : logs) {
        if (log.find("../") != string::npos || log.find("..\\") != string::npos) {
            cout << "[ALERTE] Path traversal detecte : " << log << endl;
        }
        if (log.find("Port scan") != string::npos) {
            cout << "[ALERTE] Scan de ports : " << log << endl;
        }
    }

    // --- Resume visuel ---
    cout << "\n--- Severite (barre ASCII) ---" << endl;
    cout << "INFO  [";
    for (int i = 0; i < infoCount; i++) cout << "=";
    cout << "] " << infoCount << endl;

    cout << "WARN  [";
    for (int i = 0; i < warnCount; i++) cout << "#";
    cout << "] " << warnCount << endl;

    cout << "ERROR [";
    for (int i = 0; i < errorCount; i++) cout << "!";
    cout << "] " << errorCount << endl;

    // --- Recommandations ---
    cout << "\n--- Recommandations ---" << endl;
    if (failedRoot >= 3)
        cout << "-> Bloquer l'IP source des tentatives de brute force" << endl;
    if (errorCount > nbLogs / 2)
        cout << "-> Taux d'erreur critique (>" << nbLogs / 2 << "), investigation immediate" << endl;
    else
        cout << "-> Taux d'erreur acceptable, continuer le monitoring" << endl;

    return 0;
}
