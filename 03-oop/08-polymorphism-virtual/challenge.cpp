// ============================================================
// Chapitre 08 - Challenge Offensive : Handler polymorphe
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================
// Contexte : Un framework C2 doit gerer differents protocoles
// de communication (HTTP, DNS, SMB). Le polymorphisme permet
// d'avoir un code client unique qui fonctionne avec n'importe
// quel protocole via une interface commune.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <iomanip>

class ProtocolHandler {
protected:
    std::string name;
    bool connected = false;
    int bytes_sent = 0;
    int bytes_received = 0;

public:
    explicit ProtocolHandler(std::string n) : name(std::move(n)) {}
    virtual ~ProtocolHandler() = default;

    virtual bool connect(const std::string& target) = 0;
    virtual bool send(const std::string& data) = 0;
    virtual std::string receive() = 0;
    virtual void disconnect() = 0;

    virtual void print_stats() const {
        std::cout << "  [" << name << "] Connected: " << (connected ? "Y" : "N")
                  << " | TX: " << bytes_sent << "B"
                  << " | RX: " << bytes_received << "B" << std::endl;
    }

    const std::string& get_name() const { return name; }
    bool is_connected() const { return connected; }
};

class HttpHandler : public ProtocolHandler {
private:
    std::string user_agent;
    std::string base_url;

public:
    HttpHandler(std::string ua = "Mozilla/5.0")
        : ProtocolHandler("HTTP"), user_agent(std::move(ua)) {}

    bool connect(const std::string& target) override {
        base_url = "https://" + target;
        std::cout << "  [HTTP] Connexion a " << base_url << std::endl;
        std::cout << "  [HTTP] User-Agent: " << user_agent << std::endl;
        connected = true;
        return true;
    }

    bool send(const std::string& data) override {
        if (!connected) return false;
        std::cout << "  [HTTP] POST " << base_url << "/api/data"
                  << " (" << data.size() << " bytes)" << std::endl;
        bytes_sent += static_cast<int>(data.size());
        return true;
    }

    std::string receive() override {
        if (!connected) return "";
        std::string response = "{\"status\":\"ok\",\"tasks\":[]}";
        bytes_received += static_cast<int>(response.size());
        std::cout << "  [HTTP] Reponse recue: " << response.size() << " bytes" << std::endl;
        return response;
    }

    void disconnect() override {
        std::cout << "  [HTTP] Fermeture de la session" << std::endl;
        connected = false;
    }
};

class DnsHandler : public ProtocolHandler {
private:
    std::string domain;

    std::string encode_to_subdomain(const std::string& data) const {
        std::string encoded;
        for (char c : data) {
            char buf[3];
            snprintf(buf, sizeof(buf), "%02x", static_cast<unsigned char>(c));
            encoded += buf;
        }
        return encoded;
    }

public:
    DnsHandler() : ProtocolHandler("DNS") {}

    bool connect(const std::string& target) override {
        domain = target;
        std::cout << "  [DNS] Canal DNS configure via " << domain << std::endl;
        connected = true;
        return true;
    }

    bool send(const std::string& data) override {
        if (!connected) return false;
        std::string subdomain = encode_to_subdomain(data);
        // Decouper en labels de 63 chars max (norme DNS)
        std::string query;
        for (size_t i = 0; i < subdomain.size(); i += 60) {
            if (!query.empty()) query += ".";
            query += subdomain.substr(i, 60);
        }
        query += "." + domain;
        std::cout << "  [DNS] TXT query: " << query.substr(0, 50) << "..." << std::endl;
        bytes_sent += static_cast<int>(data.size());
        return true;
    }

    std::string receive() override {
        if (!connected) return "";
        std::string response = "NOOP";
        bytes_received += static_cast<int>(response.size());
        std::cout << "  [DNS] TXT response: " << response << std::endl;
        return response;
    }

    void disconnect() override {
        std::cout << "  [DNS] Canal DNS ferme" << std::endl;
        connected = false;
    }
};

class SmbHandler : public ProtocolHandler {
private:
    std::string share_path;

public:
    SmbHandler() : ProtocolHandler("SMB") {}

    bool connect(const std::string& target) override {
        share_path = "\\\\" + target + "\\IPC$";
        std::cout << "  [SMB] Connexion a " << share_path << std::endl;
        std::cout << "  [SMB] Named pipe: \\pipe\\srvsvc" << std::endl;
        connected = true;
        return true;
    }

    bool send(const std::string& data) override {
        if (!connected) return false;
        std::cout << "  [SMB] Ecriture pipe: " << data.size() << " bytes" << std::endl;
        bytes_sent += static_cast<int>(data.size());
        return true;
    }

    std::string receive() override {
        if (!connected) return "";
        std::string response = "ACK";
        bytes_received += static_cast<int>(response.size());
        std::cout << "  [SMB] Lecture pipe: " << response << std::endl;
        return response;
    }

    void disconnect() override {
        std::cout << "  [SMB] Deconnexion du share" << std::endl;
        connected = false;
    }
};

// Fonction generique qui fonctionne avec N'IMPORTE QUEL protocole
void execute_beacon_cycle(ProtocolHandler& handler, const std::string& target) {
    std::cout << "\n=== Beacon cycle via " << handler.get_name() << " ===" << std::endl;

    handler.connect(target);
    handler.send("checkin:hostname=PC01;user=admin;pid=1234");
    std::string tasks = handler.receive();
    handler.send("result:task_id=1;status=complete");
    handler.print_stats();
    handler.disconnect();
}

int main() {
    std::cout << "=== Challenge Offensive : Protocol Handlers Polymorphes ===" << std::endl;

    HttpHandler http("Mozilla/5.0 (Windows NT 10.0; Win64; x64)");
    DnsHandler dns;
    SmbHandler smb;

    execute_beacon_cycle(http, "c2.example.com");
    execute_beacon_cycle(dns, "data.legit-domain.com");
    execute_beacon_cycle(smb, "192.168.1.10");

    // Utilisation polymorphe via vector de pointeurs
    std::cout << "\n=== Multi-protocol fallback ===" << std::endl;
    std::vector<std::unique_ptr<ProtocolHandler>> handlers;
    handlers.push_back(std::make_unique<HttpHandler>());
    handlers.push_back(std::make_unique<DnsHandler>());
    handlers.push_back(std::make_unique<SmbHandler>());

    std::string target = "fallback.example.com";
    for (auto& h : handlers) {
        std::cout << "\nTentative via " << h->get_name() << "..." << std::endl;
        if (h->connect(target)) {
            h->send("ping");
            h->receive();
            h->disconnect();
            std::cout << "Succes via " << h->get_name() << std::endl;
            break;
        }
    }

    return 0;
}
