// Chapitre 04 - Networking TCP/UDP
// Compilation: g++ -std=c++17 -O2 -o net exercise.cpp && ./net

#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <atomic>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>

struct MarketData {
    double price;
    int quantity;
    int order_id;
    long timestamp;
    char symbol[8];
};

// =============================================================
// EXERCICE 1 : UDP Sender
// =============================================================
// Envoie des MarketData via UDP vers 127.0.0.1:port

void udp_sender(int port, int n_messages) {
    // TODO:
    // 1. Creer un socket UDP: socket(AF_INET, SOCK_DGRAM, 0)
    // 2. Configurer l'adresse destination (127.0.0.1:port)
    //    struct sockaddr_in addr{};
    //    addr.sin_family = AF_INET;
    //    addr.sin_port = htons(port);
    //    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    // 3. Boucle: envoyer n_messages MarketData avec sendto()
    // 4. Fermer le socket: close(sock)

    std::cout << "[Sender] TODO: Implemente l'envoi UDP" << std::endl;
}

// =============================================================
// EXERCICE 2 : UDP Receiver
// =============================================================
// Recoit des MarketData via UDP sur le port specifie

void udp_receiver(int port, int n_messages, std::atomic<bool>& ready) {
    // TODO:
    // 1. Creer un socket UDP: socket(AF_INET, SOCK_DGRAM, 0)
    // 2. Activer SO_REUSEADDR:
    //    int opt = 1;
    //    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // 3. Bind sur 0.0.0.0:port
    // 4. Signaler que le receiver est pret: ready.store(true)
    // 5. Boucle: recevoir n_messages avec recvfrom()
    //    Afficher le premier et le dernier message recu
    // 6. Fermer le socket

    ready.store(true);
    std::cout << "[Receiver] TODO: Implemente la reception UDP" << std::endl;
}

// =============================================================
// EXERCICE 3 : Mesurer la latence UDP round-trip
// =============================================================
// Le sender envoie un message, le receiver le renvoie immediatement
// On mesure le temps aller-retour

void latency_test(int port) {
    std::atomic<bool> server_ready{false};

    // Echo server (renvoie ce qu'il recoit)
    std::thread server([&]() {
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        int opt = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        struct sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;
        bind(sock, (struct sockaddr*)&addr, sizeof(addr));

        server_ready.store(true);

        struct sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        MarketData data;

        for (int i = 0; i < 1000; i++) {
            recvfrom(sock, &data, sizeof(data), 0,
                     (struct sockaddr*)&client_addr, &client_len);
            sendto(sock, &data, sizeof(data), 0,
                   (struct sockaddr*)&client_addr, client_len);
        }
        close(sock);
    });

    while (!server_ready.load()) std::this_thread::yield();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // TODO: Client - mesure le round-trip time
    // 1. Creer un socket UDP
    // 2. Pour chaque iteration:
    //    a. Enregistrer le timestamp avant sendto
    //    b. Envoyer un MarketData
    //    c. Recevoir la reponse avec recvfrom
    //    d. Enregistrer le timestamp apres recvfrom
    //    e. Calculer la difference (RTT)
    // 3. Afficher la latence moyenne, min et max

    std::cout << "[Latency] TODO: Implemente le test de latence" << std::endl;

    server.join();
}

int main() {
    std::cout << "=== Exercice 1 & 2: UDP Sender/Receiver ===" << std::endl;
    {
        constexpr int PORT = 12345;
        constexpr int N = 100;
        std::atomic<bool> ready{false};

        std::thread receiver(udp_receiver, PORT, N, std::ref(ready));
        while (!ready.load()) std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        udp_sender(PORT, N);
        receiver.join();
    }

    std::cout << "\n=== Exercice 3: UDP Latency Test ===" << std::endl;
    latency_test(12346);

    return 0;
}
