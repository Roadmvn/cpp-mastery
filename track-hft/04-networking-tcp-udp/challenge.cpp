// Chapitre 04 - Networking TCP/UDP - CHALLENGE
// UDP market data sender/receiver avec statistiques de latence
// Compilation: g++ -std=c++17 -O2 -o challenge challenge.cpp && ./challenge

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
#include <arpa/inet.h>
#include <unistd.h>

struct MarketData {
    double bid_price;
    double ask_price;
    int bid_size;
    int ask_size;
    long sequence;
    long send_timestamp_ns;
    char symbol[8];
};

class UDPMarketDataFeed {
    int port_;
    std::atomic<bool> running_{false};

public:
    explicit UDPMarketDataFeed(int port) : port_(port) {}

    // Sender: simule un exchange feed
    void run_sender(int n_ticks) {
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) { perror("socket"); return; }

        // Augmenter le buffer d'envoi
        int buf_size = 1024 * 1024;
        setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &buf_size, sizeof(buf_size));

        struct sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_);
        inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

        double base_price = 150.00;

        for (int i = 0; i < n_ticks; i++) {
            // Simuler un prix qui bouge
            double mid = base_price + (i % 100) * 0.01 - 0.50;
            double spread = 0.01;

            auto now = std::chrono::high_resolution_clock::now();
            long ts = std::chrono::duration_cast<std::chrono::nanoseconds>(
                now.time_since_epoch()).count();

            MarketData tick{};
            tick.bid_price = mid - spread / 2;
            tick.ask_price = mid + spread / 2;
            tick.bid_size = 100 + (i * 7) % 900;
            tick.ask_size = 100 + (i * 13) % 900;
            tick.sequence = i;
            tick.send_timestamp_ns = ts;
            std::strncpy(tick.symbol, "AAPL", 7);

            sendto(sock, &tick, sizeof(tick), 0,
                   (struct sockaddr*)&addr, sizeof(addr));

            // Petit delai pour simuler un flux realiste
            if (i % 100 == 0) {
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            }
        }

        close(sock);
        std::cout << "[Feed] Envoye " << n_ticks << " ticks" << std::endl;
    }

    // Receiver: capture et mesure la latence
    void run_receiver(int n_ticks, std::atomic<bool>& ready) {
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) { perror("socket"); return; }

        int opt = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        int buf_size = 1024 * 1024;
        setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &buf_size, sizeof(buf_size));

        struct sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            perror("bind");
            close(sock);
            return;
        }

        ready.store(true);

        std::vector<double> latencies;
        latencies.reserve(n_ticks);
        int received = 0;
        int out_of_order = 0;
        long last_seq = -1;
        double total_volume = 0;

        MarketData tick;
        for (int i = 0; i < n_ticks; i++) {
            ssize_t n = recvfrom(sock, &tick, sizeof(tick), 0, nullptr, nullptr);
            if (n != sizeof(tick)) continue;

            auto now = std::chrono::high_resolution_clock::now();
            long recv_ts = std::chrono::duration_cast<std::chrono::nanoseconds>(
                now.time_since_epoch()).count();

            double latency_us = (recv_ts - tick.send_timestamp_ns) / 1000.0;
            latencies.push_back(latency_us);

            if (tick.sequence <= last_seq) out_of_order++;
            last_seq = tick.sequence;
            total_volume += tick.bid_size + tick.ask_size;
            received++;
        }

        close(sock);

        // Statistiques
        std::sort(latencies.begin(), latencies.end());
        double sum = std::accumulate(latencies.begin(), latencies.end(), 0.0);

        std::cout << "\n╔══════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║  UDP MARKET DATA FEED STATISTICS               ║" << std::endl;
        std::cout << "╚══════════════════════════════════════════════════╝" << std::endl;

        std::cout << std::fixed;
        std::cout << "\n--- Reception ---" << std::endl;
        std::cout << "  Recu:         " << received << "/" << n_ticks << " ticks" << std::endl;
        std::cout << "  Perte:        " << std::setprecision(2)
                  << (1.0 - (double)received / n_ticks) * 100 << "%" << std::endl;
        std::cout << "  Out of order: " << out_of_order << std::endl;
        std::cout << "  Symbol:       " << tick.symbol << std::endl;

        if (!latencies.empty()) {
            std::cout << "\n--- Latence (us) ---" << std::endl;
            std::cout << std::setprecision(1);
            std::cout << "  Min:  " << latencies.front() << std::endl;
            std::cout << "  Avg:  " << sum / latencies.size() << std::endl;
            std::cout << "  p50:  " << latencies[latencies.size() / 2] << std::endl;
            std::cout << "  p90:  " << latencies[(size_t)(latencies.size() * 0.90)] << std::endl;
            std::cout << "  p99:  " << latencies[(size_t)(latencies.size() * 0.99)] << std::endl;
            std::cout << "  Max:  " << latencies.back() << std::endl;

            // Histogramme
            std::cout << "\n--- Distribution ---" << std::endl;
            double bounds[] = {0, 5, 10, 20, 50, 100, 500, 10000};
            for (int b = 0; b < 7; b++) {
                int count = 0;
                for (double l : latencies) {
                    if (l >= bounds[b] && l < bounds[b + 1]) count++;
                }
                double pct = 100.0 * count / latencies.size();
                std::cout << "  " << std::setw(5) << (int)bounds[b]
                          << "-" << std::setw(5) << (int)bounds[b + 1] << " us: ";
                int bars = (int)(pct / 2);
                for (int i = 0; i < bars; i++) std::cout << "█";
                std::cout << " " << std::setprecision(1) << pct << "%" << std::endl;
            }
        }

        std::cout << "\n--- Dernier tick ---" << std::endl;
        std::cout << std::setprecision(2);
        std::cout << "  Bid: " << tick.bid_size << " @ " << tick.bid_price << std::endl;
        std::cout << "  Ask: " << tick.ask_size << " @ " << tick.ask_price << std::endl;
        std::cout << "  Spread: " << (tick.ask_price - tick.bid_price) * 100 << " bps" << std::endl;
    }
};

int main() {
    std::cout << "╔══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  UDP MARKET DATA FEED CHALLENGE               ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════╝" << std::endl;

    constexpr int PORT = 12350;
    constexpr int N_TICKS = 50000;

    UDPMarketDataFeed feed(PORT);
    std::atomic<bool> ready{false};

    std::thread receiver([&]() {
        feed.run_receiver(N_TICKS, ready);
    });

    while (!ready.load()) std::this_thread::yield();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    feed.run_sender(N_TICKS);

    receiver.join();

    return 0;
}
