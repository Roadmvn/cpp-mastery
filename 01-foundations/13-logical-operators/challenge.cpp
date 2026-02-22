// ============================================================
// Challenge Offensive : Validation Multi-Criteres d'une Cible
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
// Contexte : Ton outil de pentest automatise doit evaluer si
// une cible est exploitable en verifiant plusieurs criteres.
// Chaque critere est un booleen ou une valeur numerique.
//
// Criteres d'exploitation :
//   1. Port ouvert (port_open)
//   2. Service identifie (service_known)
//   3. Version vulnerable (version < seuil)
//   4. Pas de firewall/WAF detecte (!firewall_detected)
//   5. Pas de rate limiting (!rate_limited)
//
// Niveaux de decision :
//   - EXPLOIT  : tous les criteres OK
//   - MANUAL   : port + service OK, mais obstacle (firewall/rate limit)
//   - RECON    : port ouvert mais service inconnu
//   - SKIP     : port ferme
//
// Sortie attendue :
//   === Target Assessment ===
//   IP       : 192.168.1.100
//   Port     : 22 (OPEN)
//   Service  : OpenSSH 7.6
//   Firewall : NON
//   Rate Lim.: NON
//
//   [CHECK] Port ouvert         : PASS
//   [CHECK] Service identifie   : PASS
//   [CHECK] Version vulnerable  : PASS (7.6 < 8.0)
//   [CHECK] Pas de firewall     : PASS
//   [CHECK] Pas de rate limit   : PASS
//
//   Score    : 5/5
//   Decision : EXPLOIT
//   Methode  : CVE-2018-15473 (User Enumeration)
// ============================================================

#include <iostream>
#include <string>

int main() {
    // Donnees de la cible (normalement recues d'un scan)
    std::string ip = "192.168.1.100";
    int port = 22;
    bool port_open = true;
    std::string service = "OpenSSH";
    double version = 7.6;
    double version_vuln_max = 8.0;  // Versions < 8.0 sont vulnerables
    bool service_known = true;
    bool firewall_detected = false;
    bool rate_limited = false;

    std::cout << "=== Target Assessment ===" << std::endl;
    std::cout << "IP       : " << ip << std::endl;
    std::cout << "Port     : " << port
              << (port_open ? " (OPEN)" : " (CLOSED)") << std::endl;
    std::cout << "Service  : " << service << " " << version << std::endl;
    std::cout << "Firewall : " << (firewall_detected ? "OUI" : "NON") << std::endl;
    std::cout << "Rate Lim.: " << (rate_limited ? "OUI" : "NON") << std::endl;
    std::cout << std::endl;

    // Evaluation de chaque critere
    int score = 0;

    // Check 1 : Port ouvert
    bool check_port = port_open;
    std::cout << "[CHECK] Port ouvert         : "
              << (check_port ? "PASS" : "FAIL") << std::endl;
    if (check_port) ++score;

    // Check 2 : Service identifie
    bool check_service = port_open && service_known;
    std::cout << "[CHECK] Service identifie   : "
              << (check_service ? "PASS" : "FAIL") << std::endl;
    if (check_service) ++score;

    // Check 3 : Version vulnerable (court-circuit si service inconnu)
    bool check_version = check_service && (version < version_vuln_max);
    std::cout << "[CHECK] Version vulnerable  : "
              << (check_version ? "PASS" : "FAIL");
    if (check_version) {
        std::cout << " (" << version << " < " << version_vuln_max << ")";
    }
    std::cout << std::endl;
    if (check_version) ++score;

    // Check 4 : Pas de firewall
    bool check_firewall = !firewall_detected;
    std::cout << "[CHECK] Pas de firewall     : "
              << (check_firewall ? "PASS" : "FAIL") << std::endl;
    if (check_firewall) ++score;

    // Check 5 : Pas de rate limiting
    bool check_rate = !rate_limited;
    std::cout << "[CHECK] Pas de rate limit   : "
              << (check_rate ? "PASS" : "FAIL") << std::endl;
    if (check_rate) ++score;

    std::cout << std::endl;
    std::cout << "Score    : " << score << "/5" << std::endl;

    // Decision basee sur les combinaisons logiques
    bool all_clear = check_port && check_service && check_version
                  && check_firewall && check_rate;

    bool has_obstacle = (firewall_detected || rate_limited);

    bool partial = check_port && check_service && check_version && has_obstacle;

    bool recon_only = check_port && !check_service;

    std::string decision;
    std::string methode;

    if (all_clear) {
        decision = "EXPLOIT";
        methode = "CVE-2018-15473 (User Enumeration)";
    } else if (partial) {
        decision = "MANUAL";
        methode = "Tentative manuelle avec evasion";
    } else if (recon_only) {
        decision = "RECON";
        methode = "Fingerprinting supplementaire requis";
    } else {
        decision = "SKIP";
        methode = "Aucune";
    }

    std::cout << "Decision : " << decision << std::endl;
    std::cout << "Methode  : " << methode << std::endl;

    return 0;
}
