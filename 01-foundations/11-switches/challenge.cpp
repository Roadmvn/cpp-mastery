// ============================================================
// Challenge Offensive : Menu d'un Outil de Reconnaissance
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
// Contexte : Tu developpes un outil de reconnaissance reseau
// avec un menu interactif. L'utilisateur choisit une action
// et l'outil simule l'execution.
//
// Sortie attendue (exemple avec choix = 2) :
//   === ReconTool v1.0 ===
//   [1] Scan de ports
//   [2] Lookup DNS
//   [3] Whois
//   [4] Banner grabbing
//   [5] Traceroute
//   [0] Quitter
//
//   Choix : 2
//
//   === DNS Lookup ===
//   Cible   : example.com
//   Type    : A Record
//   Resultat: 93.184.216.34
//   TTL     : 3600s
//   Status  : OK
// ============================================================

#include <iostream>
#include <string>

int main() {
    std::cout << "=== ReconTool v1.0 ===" << std::endl;
    std::cout << "[1] Scan de ports" << std::endl;
    std::cout << "[2] Lookup DNS" << std::endl;
    std::cout << "[3] Whois" << std::endl;
    std::cout << "[4] Banner grabbing" << std::endl;
    std::cout << "[5] Traceroute" << std::endl;
    std::cout << "[0] Quitter" << std::endl;
    std::cout << std::endl;

    int choix;
    std::cout << "Choix : ";
    std::cin >> choix;

    std::string cible = "example.com";
    std::cout << std::endl;

    switch (choix) {
        case 1: {
            std::cout << "=== Port Scanner ===" << std::endl;
            std::cout << "Cible : " << cible << std::endl;
            std::cout << "Range : 1-1024" << std::endl;
            std::cout << std::endl;

            // Simulation de resultats
            std::cout << "PORT     STATE    SERVICE" << std::endl;
            std::cout << "22/tcp   open     ssh" << std::endl;
            std::cout << "80/tcp   open     http" << std::endl;
            std::cout << "443/tcp  open     https" << std::endl;
            std::cout << std::endl;
            std::cout << "3 ports ouverts sur 1024 scannes" << std::endl;
            break;
        }

        case 2: {
            std::cout << "=== DNS Lookup ===" << std::endl;
            std::cout << "Cible   : " << cible << std::endl;
            std::cout << "Type    : A Record" << std::endl;
            std::cout << "Resultat: 93.184.216.34" << std::endl;
            std::cout << "TTL     : 3600s" << std::endl;
            std::cout << "Status  : OK" << std::endl;
            break;
        }

        case 3: {
            std::cout << "=== Whois Lookup ===" << std::endl;
            std::cout << "Domaine     : " << cible << std::endl;
            std::cout << "Registrar   : ICANN" << std::endl;
            std::cout << "Creation    : 1995-08-14" << std::endl;
            std::cout << "Expiration  : 2025-08-13" << std::endl;
            std::cout << "Name Server : a.iana-servers.net" << std::endl;
            break;
        }

        case 4: {
            std::cout << "=== Banner Grabbing ===" << std::endl;
            std::cout << "Cible : " << cible << ":80" << std::endl;
            std::cout << std::endl;
            std::cout << "HTTP/1.1 200 OK" << std::endl;
            std::cout << "Server: nginx/1.24.0" << std::endl;
            std::cout << "Content-Type: text/html" << std::endl;
            std::cout << "X-Powered-By: Express" << std::endl;
            std::cout << std::endl;
            std::cout << "Serveur identifie : nginx 1.24.0" << std::endl;
            break;
        }

        case 5: {
            std::cout << "=== Traceroute ===" << std::endl;
            std::cout << "Cible : " << cible << std::endl;
            std::cout << std::endl;
            std::cout << " 1   192.168.1.1      1.2 ms" << std::endl;
            std::cout << " 2   10.0.0.1         5.4 ms" << std::endl;
            std::cout << " 3   172.16.0.1      12.8 ms" << std::endl;
            std::cout << " 4   93.184.216.34   24.1 ms" << std::endl;
            std::cout << std::endl;
            std::cout << "4 sauts, destination atteinte" << std::endl;
            break;
        }

        case 0:
            std::cout << "Au revoir." << std::endl;
            break;

        default:
            std::cout << "Option invalide : " << choix << std::endl;
            break;
    }

    return 0;
}
