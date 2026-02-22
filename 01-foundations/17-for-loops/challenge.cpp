// ============================================================
// CHALLENGE OFFENSIVE : Scanner de ports fictif
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// Simulation d'un scan de ports reseau (style nmap).
// Le programme "scanne" les ports 1-1024 et affiche un statut
// aleatoire (ouvert/ferme/filtre) pour chacun.
// Les ports courants sont identifies par leur service.
//
// Exercice PEDAGOGIQUE. Un vrai scanner utiliserait des sockets.
//
// Usage educatif uniquement.
// ============================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string get_service(int port) {
    switch (port) {
        case 21:   return "FTP";
        case 22:   return "SSH";
        case 23:   return "Telnet";
        case 25:   return "SMTP";
        case 53:   return "DNS";
        case 80:   return "HTTP";
        case 110:  return "POP3";
        case 143:  return "IMAP";
        case 443:  return "HTTPS";
        case 445:  return "SMB";
        case 993:  return "IMAPS";
        case 995:  return "POP3S";
        case 3306: return "MySQL";
        case 3389: return "RDP";
        default:   return "";
    }
}

int main() {
    srand(time(0));

    int port_debut, port_fin;
    cout << "========================================" << endl;
    cout << "  Port Scanner Simulator v1.0" << endl;
    cout << "========================================" << endl;
    cout << "Port debut (ex: 1)    : ";
    cin >> port_debut;
    cout << "Port fin   (ex: 1024) : ";
    cin >> port_fin;

    if (port_debut < 1) port_debut = 1;
    if (port_fin > 65535) port_fin = 65535;

    cout << "\nScanning ports " << port_debut << "-" << port_fin << "..." << endl;
    cout << "----------------------------------------" << endl;

    int open_count = 0;
    int closed_count = 0;
    int filtered_count = 0;

    for (int port = port_debut; port <= port_fin; port++) {
        int status = rand() % 100;
        // 5% open, 85% closed, 10% filtered (realiste)

        string state;
        if (status < 5) {
            state = "OPEN";
            open_count++;
        } else if (status < 90) {
            state = "CLOSED";
            closed_count++;
            continue;  // N'affiche pas les ports fermes (comme nmap)
        } else {
            state = "FILTERED";
            filtered_count++;
        }

        string service = get_service(port);
        cout << "  Port " << port << "/tcp";
        cout << "\t" << state;
        if (!service.empty()) {
            cout << "\t" << service;
        }
        cout << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << "Scan termine." << endl;
    cout << "  Ouverts   : " << open_count << endl;
    cout << "  Fermes    : " << closed_count << endl;
    cout << "  Filtres   : " << filtered_count << endl;
    cout << "  Total     : " << (port_fin - port_debut + 1) << " ports scannes" << endl;
    cout << "========================================" << endl;
    cout << "Note : En vrai, utilise nmap pour scanner." << endl;
    cout << "Ici c'est juste pour pratiquer les boucles for." << endl;

    return 0;
}
