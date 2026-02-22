// Chapitre 08 - Solution : Mecanismes de Persistance
// EDUCATIF - CTF / Labs de securite uniquement
//
// IMPORTANT : Ce programme agit UNIQUEMENT sur ta propre crontab
//             utilisateur. Aucun acces root requis.
//             N'utilise PAS ce code sur un systeme qui ne t'appartient pas.
//
// Compile :
//   g++ -std=c++17 -o persistence_solution solution.cpp
//   ./persistence_solution

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <climits>
#include <unistd.h>

// ============================================================
// UTILITAIRE : executer une commande et capturer la sortie
// ============================================================

std::string runCommand(const std::string& cmd) {
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return result;

    char buf[256];
    while (fgets(buf, sizeof(buf), pipe) != nullptr) {
        result += buf;
    }
    pclose(pipe);
    return result;
}

// ============================================================
// SECTION CRONTAB
// ============================================================

std::string readCrontab() {
    // "2>/dev/null" evite le message "no crontab for user" quand elle est vide
    return runCommand("crontab -l 2>/dev/null");
}

void writeCrontab(const std::string& content) {
    // Creer un fichier temporaire unique
    char tmpfile[] = "/tmp/crontab_tmp_XXXXXX";
    int fd = mkstemp(tmpfile);
    if (fd < 0) {
        std::cerr << "[ERREUR] Impossible de creer le fichier temporaire\n";
        return;
    }

    // Ecrire le contenu dans le fichier temporaire
    write(fd, content.c_str(), content.size());
    close(fd);

    // Charger la crontab depuis le fichier temporaire
    std::string cmd = "crontab " + std::string(tmpfile);
    int ret = system(cmd.c_str());
    if (ret != 0) {
        std::cerr << "[ERREUR] crontab a echoue (code " << ret << ")\n";
    }

    // Nettoyer
    unlink(tmpfile);
}

bool addCronEntry(const std::string& entry) {
    std::string current = readCrontab();

    // Verifier si l'entree existe deja
    if (current.find(entry) != std::string::npos) {
        std::cout << "[INFO] L'entree existe deja dans la crontab.\n";
        return false;
    }

    // S'assurer que le contenu actuel se termine par un newline
    if (!current.empty() && current.back() != '\n') {
        current += '\n';
    }

    current += entry + "\n";
    writeCrontab(current);
    return true;
}

bool removeCronEntry(const std::string& pattern) {
    std::string current = readCrontab();
    std::istringstream iss(current);
    std::string line;
    std::string new_content;
    int removed = 0;

    while (std::getline(iss, line)) {
        if (line.find(pattern) != std::string::npos) {
            std::cout << "[INFO] Supprime : " << line << "\n";
            removed++;
        } else {
            new_content += line + "\n";
        }
    }

    if (removed > 0) {
        writeCrontab(new_content);
        return true;
    }
    return false;
}

void listCronEntries() {
    std::string crontab = readCrontab();
    if (crontab.empty()) {
        std::cout << "[INFO] Crontab vide ou inexistante.\n";
        return;
    }

    std::istringstream iss(crontab);
    std::string line;
    int count = 0;

    while (std::getline(iss, line)) {
        // Ignorer les lignes vides et les commentaires
        if (line.empty() || line[0] == '#') continue;
        std::cout << "[CRON] " << line << "\n";
        count++;
    }

    if (count == 0) {
        std::cout << "[INFO] Aucune entree active (seulement des commentaires).\n";
    }
}

// ============================================================
// DEMO : modification de .bashrc (lecture seule, sans modifier)
// ============================================================

void showBashrcInfo() {
    const char* home = std::getenv("HOME");
    if (!home) {
        std::cout << "[INFO] HOME non defini.\n";
        return;
    }

    std::string bashrc = std::string(home) + "/.bashrc";
    std::string zshrc  = std::string(home) + "/.zshrc";

    std::cout << "[BASHRC] Fichiers shell detectes :\n";

    // Verifier l'existence sans ouvrir
    if (access(bashrc.c_str(), F_OK) == 0) {
        std::cout << "  " << bashrc << " (existe)\n";
    }
    if (access(zshrc.c_str(), F_OK) == 0) {
        std::cout << "  " << zshrc << " (existe)\n";
    }

    std::cout << "[BASHRC] Pour ajouter une persistence dans .bashrc :\n";
    std::cout << "  echo 'nohup /chemin/payload &' >> ~/.bashrc\n";
    std::cout << "[INFO] Ce programme ne modifie PAS ces fichiers.\n";
}

// ============================================================
// DEMO : explication d'un service systemd
// ============================================================

void showSystemdInfo() {
    std::cout << "[SYSTEMD] Exemple de service de persistance :\n\n";
    std::cout << "  Fichier : /etc/systemd/system/edu-demo.service\n\n";
    std::cout << "  [Unit]\n";
    std::cout << "  Description=Demo educatif\n";
    std::cout << "  After=network.target\n\n";
    std::cout << "  [Service]\n";
    std::cout << "  Type=simple\n";
    std::cout << "  ExecStart=/usr/bin/bash /chemin/script.sh\n";
    std::cout << "  Restart=always\n";
    std::cout << "  RestartSec=30\n\n";
    std::cout << "  [Install]\n";
    std::cout << "  WantedBy=multi-user.target\n\n";
    std::cout << "[SYSTEMD] Commandes de gestion :\n";
    std::cout << "  systemctl enable edu-demo   # activer au boot\n";
    std::cout << "  systemctl start edu-demo    # demarrer maintenant\n";
    std::cout << "  systemctl status edu-demo   # voir l'etat\n";
    std::cout << "  systemctl list-units --type=service  # lister tous\n";
}

// ============================================================
// MAIN : menu interactif
// ============================================================
int main() {
    std::cout << "=== Gestionnaire de Persistance (EDUCATIF) ===\n";
    std::cout << "Ce programme agit UNIQUEMENT sur ta propre crontab utilisateur.\n\n";

    int choice = 0;
    while (true) {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Lister les entrees cron\n";
        std::cout << "2. Ajouter une entree cron\n";
        std::cout << "3. Supprimer une entree cron\n";
        std::cout << "4. Afficher la crontab brute\n";
        std::cout << "5. Info sur .bashrc/.zshrc (lecture seule)\n";
        std::cout << "6. Exemple service systemd\n";
        std::cout << "0. Quitter\n";
        std::cout << "Choix : ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 0:
                std::cout << "Au revoir.\n";
                return 0;

            case 1:
                listCronEntries();
                break;

            case 2: {
                std::cout << "Entree a ajouter (ex: '* * * * * echo hello >> /tmp/test.txt')\n";
                std::cout << "> ";
                std::string entry;
                std::getline(std::cin, entry);
                if (entry.empty()) {
                    std::cout << "[INFO] Entree vide, annulee.\n";
                    break;
                }
                bool added = addCronEntry(entry);
                std::cout << (added ? "[OK] Entree ajoutee.\n" : "[INFO] Deja presente.\n");
                break;
            }

            case 3: {
                std::cout << "Pattern a supprimer : ";
                std::string pattern;
                std::getline(std::cin, pattern);
                bool removed = removeCronEntry(pattern);
                std::cout << (removed ? "[OK] Entree supprimee.\n" : "[INFO] Rien a supprimer.\n");
                break;
            }

            case 4:
                std::cout << "--- Crontab brute ---\n" << readCrontab() << "---\n";
                break;

            case 5:
                showBashrcInfo();
                break;

            case 6:
                showSystemdInfo();
                break;

            default:
                std::cout << "Choix invalide.\n";
        }
    }

    return 0;
}
