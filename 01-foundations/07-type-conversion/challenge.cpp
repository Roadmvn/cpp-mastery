// ============================================================
// Challenge Offensive : Manipulation de Donnees Brutes
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
// Contexte : En analyse offensive, tu recois souvent des donnees
// brutes (octets, adresses memoire) qu'il faut convertir entre
// types pour les interpreter correctement.
//
// Ce challenge simule la lecture d'un header de paquet reseau
// ou les donnees sont stockees comme des octets bruts.
// ============================================================

#include <iostream>
#include <cstdint>

int main() {
    // Simulation d'un buffer brut (4 octets representant une adresse IPv4)
    uint8_t ip_bytes[4] = {192, 168, 1, 42};

    // Afficher l'adresse IP lisible depuis les octets bruts
    std::cout << "=== Analyse de paquet ===" << std::endl;
    std::cout << "IP : "
              << static_cast<int>(ip_bytes[0]) << "."
              << static_cast<int>(ip_bytes[1]) << "."
              << static_cast<int>(ip_bytes[2]) << "."
              << static_cast<int>(ip_bytes[3]) << std::endl;

    // Convertir les 4 octets en un seul entier 32 bits (big-endian)
    // 192.168.1.42 -> 0xC0A8012A
    uint32_t ip_as_int = (static_cast<uint32_t>(ip_bytes[0]) << 24)
                       | (static_cast<uint32_t>(ip_bytes[1]) << 16)
                       | (static_cast<uint32_t>(ip_bytes[2]) << 8)
                       | (static_cast<uint32_t>(ip_bytes[3]));

    std::cout << "IP (uint32) : " << ip_as_int << std::endl;
    std::cout << "IP (hex)    : 0x" << std::hex << ip_as_int << std::dec << std::endl;

    // Simulation d'un port sur 2 octets (big-endian)
    uint8_t port_bytes[2] = {0x01, 0xBB};  // Port 443 (HTTPS)

    uint16_t port = (static_cast<uint16_t>(port_bytes[0]) << 8)
                  | static_cast<uint16_t>(port_bytes[1]);

    std::cout << "Port : " << port << std::endl;  // 443

    // Conversion inverse : extraire les octets d'un entier
    uint32_t target_ip = 0x0A000164;  // 10.0.1.100

    uint8_t oct1 = static_cast<uint8_t>((target_ip >> 24) & 0xFF);
    uint8_t oct2 = static_cast<uint8_t>((target_ip >> 16) & 0xFF);
    uint8_t oct3 = static_cast<uint8_t>((target_ip >> 8) & 0xFF);
    uint8_t oct4 = static_cast<uint8_t>(target_ip & 0xFF);

    std::cout << "\nTarget : "
              << static_cast<int>(oct1) << "."
              << static_cast<int>(oct2) << "."
              << static_cast<int>(oct3) << "."
              << static_cast<int>(oct4) << std::endl;

    // Simulation : lire un caractere depuis un buffer brut
    uint8_t raw_buffer[] = {0x48, 0x45, 0x4C, 0x4C, 0x4F};  // "HELLO" en ASCII
    std::cout << "\nPayload : ";
    for (int i = 0; i < 5; ++i) {
        std::cout << static_cast<char>(raw_buffer[i]);
    }
    std::cout << std::endl;

    // Detecter le type de protocole (simplification)
    uint8_t protocol_id = 6;  // 6 = TCP, 17 = UDP
    std::cout << "\nProtocole (id=" << static_cast<int>(protocol_id) << ") : ";
    if (protocol_id == 6) {
        std::cout << "TCP" << std::endl;
    } else if (protocol_id == 17) {
        std::cout << "UDP" << std::endl;
    } else {
        std::cout << "INCONNU" << std::endl;
    }

    return 0;
}
