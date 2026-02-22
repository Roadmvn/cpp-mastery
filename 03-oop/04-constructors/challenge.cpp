// ============================================================
// Chapitre 04 - Challenge Offensive : Logger avec timestamp auto
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
// ============================================================
// Contexte : Un logger pour operations offensives qui enregistre
// automatiquement le timestamp de creation (constructeur) et
// de fermeture (destructeur). Chaque session a un ID unique.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

enum class LogLevel : uint8_t { DEBUG, INFO, WARNING, CRITICAL };

std::string to_string(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:    return "DEBUG";
        case LogLevel::INFO:     return "INFO";
        case LogLevel::WARNING:  return "WARN";
        case LogLevel::CRITICAL: return "CRIT";
    }
    return "????";
}

class OperationLogger {
private:
    struct LogEntry {
        std::string timestamp;
        LogLevel level;
        std::string message;
    };

    const std::string session_id;
    const std::string operation_name;
    const std::string start_time;
    std::vector<LogEntry> entries;
    bool success = false;

    static std::string generate_session_id() {
        auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
        std::stringstream ss;
        ss << std::hex << (ns % 0xFFFFFFFF);
        return "SES-" + ss.str();
    }

    static std::string current_timestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S")
           << "." << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }

    void print_entry(const LogEntry& entry) const {
        std::cout << "[" << entry.timestamp << "] "
                  << "[" << session_id << "] "
                  << "[" << to_string(entry.level) << "] "
                  << entry.message << std::endl;
    }

public:
    OperationLogger(std::string op_name)
        : session_id(generate_session_id()),
          operation_name(std::move(op_name)),
          start_time(current_timestamp())
    {
        log(LogLevel::INFO, "Session ouverte : " + operation_name);
        log(LogLevel::DEBUG, "Session ID: " + session_id);
    }

    ~OperationLogger() {
        log(LogLevel::INFO,
            "Session fermee : " + operation_name +
            " | Statut: " + (success ? "SUCCES" : "ECHEC") +
            " | Entries: " + std::to_string(entries.size()));
        std::cout << "--- Fin session " << session_id << " ---\n" << std::endl;
    }

    void log(LogLevel level, const std::string& message) {
        LogEntry entry{current_timestamp(), level, message};
        print_entry(entry);
        entries.push_back(std::move(entry));
    }

    void mark_success() { success = true; }

    void dump_summary() const {
        int counts[4] = {0, 0, 0, 0};
        for (const auto& e : entries) {
            counts[static_cast<int>(e.level)]++;
        }

        std::cout << "\n--- Resume session " << session_id << " ---" << std::endl;
        std::cout << "  Operation:  " << operation_name << std::endl;
        std::cout << "  Debut:      " << start_time << std::endl;
        std::cout << "  Entries:    " << entries.size() << std::endl;
        std::cout << "  DEBUG: " << counts[0] << " | INFO: " << counts[1]
                  << " | WARN: " << counts[2] << " | CRIT: " << counts[3] << std::endl;
    }
};

int main() {
    std::cout << "=== Challenge Offensive : Operation Logger ===\n" << std::endl;

    {
        OperationLogger recon("Reconnaissance");
        recon.log(LogLevel::INFO, "Scan de ports initie sur 192.168.1.0/24");
        recon.log(LogLevel::INFO, "Port 22 ouvert sur 192.168.1.10");
        recon.log(LogLevel::INFO, "Port 80 ouvert sur 192.168.1.10");
        recon.log(LogLevel::WARNING, "Port 3389 (RDP) ouvert sur 192.168.1.10");
        recon.log(LogLevel::DEBUG, "Fingerprint: OpenSSH 8.9p1");
        recon.dump_summary();
        recon.mark_success();
    }  // Destructeur appele ici

    {
        OperationLogger exploit("Exploitation");
        exploit.log(LogLevel::INFO, "Tentative d'authentification SSH");
        exploit.log(LogLevel::WARNING, "Echec authentification - user admin");
        exploit.log(LogLevel::CRITICAL, "Alerte IDS detectee, arret de l'operation");
        exploit.dump_summary();
        // Pas de mark_success() -> ECHEC
    }  // Destructeur appele ici

    // Logger dans une boucle pour demontrer la creation/destruction repetee
    std::cout << "=== Sessions multiples ===" << std::endl;
    for (int i = 0; i < 3; ++i) {
        OperationLogger session("Ping-" + std::to_string(i));
        session.log(LogLevel::INFO, "Ping envoye");
        session.mark_success();
    }

    return 0;
}
