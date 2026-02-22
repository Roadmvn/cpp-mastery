// ============================================================
// Challenge Offensive : Generateur de Cibles Aleatoires
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
// Contexte : Tu developpes un outil de reconnaissance qui genere
// des combinaisons IP/port aleatoires pour un scan autorise.
// L'outil doit generer N cibles avec des contraintes :
//   - IPs dans un sous-reseau donne (ex: 10.0.0.0/24)
//   - Ports dans une liste de ports courants
//   - Affichage formate pour un rapport
//
// Sortie attendue (exemple, valeurs aleatoires) :
//   === Generateur de Cibles ===
//   Sous-reseau : 10.0.0.0/24
//   Nombre de cibles : 5
//
//   [1] 10.0.0.142:443
//   [2] 10.0.0.87:22
//   [3] 10.0.0.201:8080
//   [4] 10.0.0.33:80
//   [5] 10.0.0.156:443
//
//   Statistiques :
//   - Port min scanne : 22
//   - Port max scanne : 8080
//   - Plage IP : 10.0.0.33 - 10.0.0.201
// ============================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main() {
    srand(time(0));

    // Ports courants a scanner
    int ports[] = {22, 80, 443, 8080, 8443, 3306, 5432, 6379, 27017};
    int nb_ports = 9;

    // Configuration
    int nb_cibles = 5;
    std::string base_ip = "10.0.0.";

    std::cout << "=== Generateur de Cibles ===" << std::endl;
    std::cout << "Sous-reseau : " << base_ip << "0/24" << std::endl;
    std::cout << "Nombre de cibles : " << nb_cibles << std::endl;
    std::cout << std::endl;

    // Tracking pour les statistiques
    int port_min = 99999;
    int port_max = 0;
    int ip_min = 255;
    int ip_max = 0;

    for (int i = 0; i < nb_cibles; ++i) {
        // Generer un dernier octet entre 1 et 254 (pas .0 ni .255)
        int octet = rand() % 254 + 1;

        // Choisir un port aleatoire dans la liste
        int port_index = rand() % nb_ports;
        int port = ports[port_index];

        // Affichage
        std::cout << "[" << (i + 1) << "] "
                  << base_ip << octet << ":" << port << std::endl;

        // Mettre a jour les stats
        port_min = std::min(port_min, port);
        port_max = std::max(port_max, port);
        ip_min = std::min(ip_min, octet);
        ip_max = std::max(ip_max, octet);
    }

    // Statistiques finales
    std::cout << "\nStatistiques :" << std::endl;
    std::cout << "- Port min scanne : " << port_min << std::endl;
    std::cout << "- Port max scanne : " << port_max << std::endl;
    std::cout << "- Plage IP : " << base_ip << ip_min
              << " - " << base_ip << ip_max << std::endl;

    return 0;
}
