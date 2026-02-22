// Chapitre 04 - Networking TCP/UDP - SOLUTION
// Compilation: g++ -std=c++17 -O2 -o net solution.cpp && ./net

#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
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
// SOLUTION 1 : UDP Sender
// =============================================================
void udp_sender(int port, int n_messages) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); return; }

    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    for (int i = 0; i < n_messages; i++) {
        auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        MarketData data{100.0 + i * 0.01, (i % 100) + 1, i, now, "AAPL"};

        sendto(sock, &data, sizeof(data), 0,
               (struct sockaddr*)&addr, sizeof(addr));
    }

    std::cout << "[Sender] Envoye " << n_messages << " messages UDP" << std::endl;
    close(sock);
}

// =============================================================
// SOLUTION 2 : UDP Receiver
// =============================================================
void udp_receiver(int port, int n_messages, std::atomic<bool>& ready) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); return; }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sock);
        return;
    }

    ready.store(true);

    MarketData data;
    int received = 0;

    for (int i = 0; i < n_messages; i++) {
        ssize_t n = recvfrom(sock, &data, sizeof(data), 0, nullptr, nullptr);
        if (n == sizeof(data)) {
            received++;
            if (received == 1) {
                std::cout << "[Receiver] Premier: " << data.symbol
                          << " " << data.quantity << " @ " << data.price << std::endl;
            }
        }
    }

    std::cout << "[Receiver] Dernier:  " << data.symbol
              << " " << data.quantity << " @ " << std::fixed << std::setprecision(2)
              << data.price << std::endl;
    std::cout << "[Receiver] Recu " << received << "/" << n_messages << " messages" << std::endl;

    close(sock);
}

// =============================================================
// SOLUTION 3 : Latence UDP round-trip
// =============================================================
void latency_test(int port) {
    std::atomic<bool> server_ready{false};
    constexpr int N_SAMPLES = 1000;

    // Echo server
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

        for (int i = 0; i < N_SAMPLES; i++) {
            recvfrom(sock, &data, sizeof(data), 0,
                     (struct sockaddr*)&client_addr, &client_len);
            sendto(sock, &data, sizeof(data), 0,
                   (struct sockaddr*)&client_addr, client_len);
        }
        close(sock);
    });

    while (!server_ready.load()) std::this_thread::yield();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Client: mesure RTT
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    std::vector<double> latencies;
    latencies.reserve(N_SAMPLES);

    for (int i = 0; i < N_SAMPLES; i++) {
        MarketData data{100.0 + i, i, i, 0, "TEST"};

        auto start = std::chrono::high_resolution_clock::now();

        sendto(sock, &data, sizeof(data), 0,
               (struct sockaddr*)&addr, sizeof(addr));

        MarketData response;
        recvfrom(sock, &response, sizeof(response), 0, nullptr, nullptr);

        auto end = std::chrono::high_resolution_clock::now();
        double rtt_us = std::chrono::duration<double, std::micro>(end - start).count();
        latencies.push_back(rtt_us);
    }

    close(sock);
    server.join();

    // Statistiques
    std::sort(latencies.begin(), latencies.end());
    double sum = std::accumulate(latencies.begin(), latencies.end(), 0.0);
    double avg = sum / latencies.size();
    double min = latencies.front();
    double max = latencies.back();
    double p50 = latencies[latencies.size() / 2];
    double p99 = latencies[(size_t)(latencies.size() * 0.99)];

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "UDP Round-Trip Latency (" << N_SAMPLES << " samples):" << std::endl;
    std::cout << "  Min:  " << min << " us" << std::endl;
    std::cout << "  Avg:  " << avg << " us" << std::endl;
    std::cout << "  p50:  " << p50 << " us" << std::endl;
    std::cout << "  p99:  " << p99 << " us" << std::endl;
    std::cout << "  Max:  " << max << " us" << std::endl;
}

int main() {
    std::cout << "=== Solution 1 & 2: UDP Sender/Receiver ===" << std::endl;
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

    std::cout << "\n=== Solution 3: UDP Latency Test ===" << std::endl;
    latency_test(12346);

    return 0;
}
