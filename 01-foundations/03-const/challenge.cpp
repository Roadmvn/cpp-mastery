// ============================================================
// CHALLENGE : Configuration d'un Scanner Reseau
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// OBJECTIF :
// Creer un programme qui configure et simule un scanner
// de ports reseau fictif en utilisant des constantes.
//
// Ce genre d'outil (nmap, masscan) utilise des constantes
// pour definir les limites du scan. Ici on simule le
// comportement avec des prints.
//
// Usage educatif uniquement.
// ============================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Configuration du scanner (constantes)
    constexpr int PORT_MIN = 1;
    constexpr int PORT_MAX = 1024;
    constexpr int TIMEOUT_MS = 500;
    constexpr int MAX_THREADS = 8;
    const string TARGET_IP = "192.168.1.1";
    const string SCAN_TYPE = "TCP SYN";

    // Ports "connus" a mettre en avant (constantes)
    constexpr int PORT_FTP = 21;
    constexpr int PORT_SSH = 22;
    constexpr int PORT_HTTP = 80;
    constexpr int PORT_HTTPS = 443;

    // Affichage de la configuration
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║         NETWORK SCANNER v1.0             ║" << endl;
    cout << "╠══════════════════════════════════════════╣" << endl;
    cout << "║  Cible      : " << TARGET_IP << "                ║" << endl;
    cout << "║  Ports      : " << PORT_MIN << " - " << PORT_MAX << "                 ║" << endl;
    cout << "║  Timeout    : " << TIMEOUT_MS << " ms                    ║" << endl;
    cout << "║  Threads    : " << MAX_THREADS << "                          ║" << endl;
    cout << "║  Type       : " << SCAN_TYPE << "                   ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << endl;

    // Simulation du scan (on ne scanne que les ports connus)
    cout << "[*] Demarrage du scan sur " << TARGET_IP << "..." << endl;
    cout << "[*] Plage : " << PORT_MIN << "-" << PORT_MAX
         << " (" << PORT_MAX - PORT_MIN + 1 << " ports)" << endl;
    cout << endl;

    // Boucle de simulation sur les ports connus
    int ports_connus[] = {PORT_FTP, PORT_SSH, PORT_HTTP, PORT_HTTPS};
    string noms[] = {"FTP", "SSH", "HTTP", "HTTPS"};
    bool ouverts[] = {false, true, true, true};

    for (int i = 0; i < 4; i++) {
        if (ouverts[i]) {
            cout << "[+] Port " << ports_connus[i]
                 << " (" << noms[i] << ") : OUVERT" << endl;
        } else {
            cout << "[-] Port " << ports_connus[i]
                 << " (" << noms[i] << ") : FERME" << endl;
        }
    }

    cout << endl;
    cout << "[*] Scan termine." << endl;
    cout << "[*] " << PORT_MAX - PORT_MIN + 1 << " ports scannes, "
         << 3 << " ouverts, " << 1 << " ferme." << endl;

    return 0;
}
