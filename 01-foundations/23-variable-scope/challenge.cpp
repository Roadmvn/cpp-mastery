// ============================================================
// CHALLENGE OFFENSIVE : Compteur de connexions & config globale
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// Simulation d'un serveur C2 (Command & Control) simplifie.
// - Configuration globale (IP, port, delai)
// - Compteur static de connexions
// - Gestion de sessions avec portee locale
//
// Exercice PEDAGOGIQUE pour comprendre les differentes portees.
// Un vrai C2 serait beaucoup plus complexe (crypto, stealth, etc.).
//
// Usage educatif uniquement.
// ============================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// --- Configuration globale du "serveur" ---
string SERVER_IP = "10.0.0.1";
int SERVER_PORT = 4444;
int MAX_CONNECTIONS = 5;
bool VERBOSE = true;

// Compteur de connexions avec static
int new_connection(string client_ip) {
    static int total_connections = 0;
    static int active_connections = 0;

    total_connections++;
    active_connections++;

    if (VERBOSE) {
        cout << "[+] Nouvelle connexion de " << client_ip << endl;
        cout << "    Session ID   : " << total_connections << endl;
        cout << "    Actives      : " << active_connections
             << "/" << MAX_CONNECTIONS << endl;
    }

    return total_connections;
}

// Simuler la fermeture d'une connexion
void close_connection(int session_id) {
    // On ne peut pas acceder a active_connections ici
    // car elle est static locale a new_connection()
    // C'est une limitation du scope local
    if (VERBOSE) {
        cout << "[-] Session " << session_id << " fermee" << endl;
    }
}

// Generer un "beacon" avec des infos systeme fictives
string generate_beacon() {
    static int beacon_count = 0;
    beacon_count++;

    // Variables locales au beacon
    string hostname = "WORKSTATION-" + to_string(rand() % 100);
    string os = "Windows 10";
    int pid = 1000 + rand() % 9000;

    string beacon = "";
    beacon += "Beacon #" + to_string(beacon_count) + " | ";
    beacon += "Host: " + hostname + " | ";
    beacon += "OS: " + os + " | ";
    beacon += "PID: " + to_string(pid);

    return beacon;
}

// Log avec compteur static
void log_event(string event) {
    static int log_id = 0;
    log_id++;

    cout << "[LOG " << log_id << "] " << event << endl;
}

int main() {
    srand(time(0));

    cout << "========================================" << endl;
    cout << "  C2 Server Simulator" << endl;
    cout << "========================================" << endl;
    cout << "Config :" << endl;
    cout << "  IP   : " << SERVER_IP << endl;
    cout << "  Port : " << SERVER_PORT << endl;
    cout << "  Max  : " << MAX_CONNECTIONS << " connexions" << endl;
    cout << "========================================" << endl;

    log_event("Serveur demarre sur " + SERVER_IP + ":" + to_string(SERVER_PORT));

    // Simuler des connexions entrantes
    string clients[] = {"192.168.1.10", "192.168.1.25", "10.0.5.3"};

    for (int i = 0; i < 3; i++) {
        cout << "\n--- Connexion entrante ---" << endl;
        int sid = new_connection(clients[i]);
        log_event("Session " + to_string(sid) + " ouverte pour " + clients[i]);

        // Recevoir un beacon
        string beacon = generate_beacon();
        cout << "    " << beacon << endl;
        log_event("Beacon recu : " + beacon);
    }

    // Fermer une session
    cout << "\n--- Fermeture ---" << endl;
    close_connection(1);
    log_event("Session 1 terminee");

    // Nouvelle connexion apres fermeture
    cout << "\n--- Nouvelle connexion ---" << endl;
    int sid = new_connection("172.16.0.50");
    string beacon = generate_beacon();
    cout << "    " << beacon << endl;
    log_event("Session " + to_string(sid) + " active");

    cout << "\n========================================" << endl;
    cout << "Remarque :" << endl;
    cout << "- SERVER_IP/PORT : globales (config)" << endl;
    cout << "- total_connections : static (persistante)" << endl;
    cout << "- beacon_count : static (compteur persistant)" << endl;
    cout << "- hostname, pid : locales (recreees a chaque appel)" << endl;
    cout << "========================================" << endl;

    return 0;
}
