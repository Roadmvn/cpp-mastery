// ============================================================
// Chapitre 06 - Challenge Offensive : Config avec validation
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================
// Contexte : Un framework offensif a besoin d'une classe de
// configuration robuste avec validation stricte de chaque
// parametre. Mauvaise config = operation grille.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class C2Config {
private:
    std::string callback_host;
    uint16_t callback_port = 443;
    int sleep_ms = 5000;
    int jitter_pct = 10;
    std::string user_agent = "Mozilla/5.0";
    std::string protocol = "https";
    int max_retries = 3;
    std::vector<std::string> allowed_protocols = {"http", "https", "dns", "smb"};

    bool is_valid_host(const std::string& host) const {
        if (host.empty()) return false;
        if (host.length() > 253) return false;
        for (char c : host) {
            if (!std::isalnum(c) && c != '.' && c != '-' && c != ':') return false;
        }
        return true;
    }

    bool is_valid_protocol(const std::string& proto) const {
        return std::find(allowed_protocols.begin(), allowed_protocols.end(), proto)
               != allowed_protocols.end();
    }

public:
    C2Config() = default;

    explicit C2Config(std::string host) {
        set_callback_host(std::move(host));
    }

    // Getters (const)
    const std::string& get_callback_host() const { return callback_host; }
    uint16_t get_callback_port() const { return callback_port; }
    int get_sleep_ms() const { return sleep_ms; }
    int get_jitter_pct() const { return jitter_pct; }
    const std::string& get_user_agent() const { return user_agent; }
    const std::string& get_protocol() const { return protocol; }
    int get_max_retries() const { return max_retries; }

    // Setters avec validation stricte
    bool set_callback_host(std::string host) {
        if (!is_valid_host(host)) {
            std::cerr << "[CONFIG ERROR] Host invalide: '" << host << "'" << std::endl;
            return false;
        }
        callback_host = std::move(host);
        return true;
    }

    bool set_callback_port(uint16_t port) {
        if (port == 0) {
            std::cerr << "[CONFIG ERROR] Port 0 interdit" << std::endl;
            return false;
        }
        callback_port = port;
        return true;
    }

    bool set_sleep_ms(int ms) {
        if (ms < 100) {
            std::cerr << "[CONFIG ERROR] Sleep < 100ms trop agressif (detection IDS)" << std::endl;
            return false;
        }
        if (ms > 86400000) {  // 24h
            std::cerr << "[CONFIG ERROR] Sleep > 24h trop long" << std::endl;
            return false;
        }
        sleep_ms = ms;
        return true;
    }

    bool set_jitter_pct(int pct) {
        if (pct < 0 || pct > 50) {
            std::cerr << "[CONFIG ERROR] Jitter doit etre entre 0 et 50%" << std::endl;
            return false;
        }
        jitter_pct = pct;
        return true;
    }

    bool set_user_agent(std::string ua) {
        if (ua.empty()) {
            std::cerr << "[CONFIG ERROR] User-Agent vide (trop suspect)" << std::endl;
            return false;
        }
        if (ua.length() > 512) {
            std::cerr << "[CONFIG ERROR] User-Agent trop long (> 512 chars)" << std::endl;
            return false;
        }
        user_agent = std::move(ua);
        return true;
    }

    bool set_protocol(std::string proto) {
        if (!is_valid_protocol(proto)) {
            std::cerr << "[CONFIG ERROR] Protocole inconnu: '" << proto
                      << "' (supportes: http, https, dns, smb)" << std::endl;
            return false;
        }
        protocol = std::move(proto);
        return true;
    }

    bool set_max_retries(int r) {
        if (r < 0 || r > 100) {
            std::cerr << "[CONFIG ERROR] Max retries hors limites (0-100)" << std::endl;
            return false;
        }
        max_retries = r;
        return true;
    }

    // Validation globale
    bool validate() const {
        if (callback_host.empty()) {
            std::cerr << "[VALIDATION] Callback host non defini" << std::endl;
            return false;
        }
        if (callback_port == 0) {
            std::cerr << "[VALIDATION] Port non defini" << std::endl;
            return false;
        }
        return true;
    }

    void print() const {
        std::cout << "=== C2 Configuration ===" << std::endl;
        std::cout << "  Host:       " << callback_host << std::endl;
        std::cout << "  Port:       " << callback_port << std::endl;
        std::cout << "  Protocol:   " << protocol << std::endl;
        std::cout << "  Sleep:      " << sleep_ms << "ms (+/- " << jitter_pct << "%)" << std::endl;
        std::cout << "  User-Agent: " << user_agent << std::endl;
        std::cout << "  Retries:    " << max_retries << std::endl;
        std::cout << "  Valid:      " << (validate() ? "OUI" : "NON") << std::endl;
    }
};

int main() {
    std::cout << "=== Challenge Offensive : C2 Config ===" << std::endl;

    // Config valide
    C2Config cfg("c2.example.com");
    cfg.set_callback_port(8443);
    cfg.set_sleep_ms(30000);
    cfg.set_jitter_pct(25);
    cfg.set_protocol("https");
    cfg.set_user_agent("Mozilla/5.0 (Windows NT 10.0; Win64; x64)");
    cfg.set_max_retries(5);
    cfg.print();

    // Test des validations
    std::cout << "\n=== Tests de validation ===" << std::endl;
    C2Config bad;

    bad.set_callback_host("");           // Refuse
    bad.set_callback_port(0);            // Refuse
    bad.set_sleep_ms(10);                // Trop agressif
    bad.set_jitter_pct(80);              // Hors limites
    bad.set_user_agent("");              // Vide
    bad.set_protocol("ftp");             // Non supporte
    bad.set_max_retries(-5);             // Negatif

    std::cout << "\n--- Config invalide ---" << std::endl;
    bad.print();

    // Config DNS covert channel
    std::cout << "\n=== Config DNS tunnel ===" << std::endl;
    C2Config dns("ns1.legit-domain.com");
    dns.set_protocol("dns");
    dns.set_callback_port(53);
    dns.set_sleep_ms(60000);   // Lent pour etre discret
    dns.set_jitter_pct(40);    // Fort jitter
    dns.print();

    return 0;
}
