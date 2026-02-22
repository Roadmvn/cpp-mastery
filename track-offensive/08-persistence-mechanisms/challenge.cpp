// Chapitre 08 - Challenge : Gestionnaire de Persistance Complet
// EDUCATIF - CTF / Labs de securite uniquement
//
// IMPORTANT : Ce programme agit UNIQUEMENT sur ta propre crontab.
//             Aucun privilege root. Aucune modification systeme.
//             N'utilise PAS ce code sur un systeme qui ne t'appartient pas.
//
// Compile :
//   g++ -std=c++17 -o challenge challenge.cpp
//   ./challenge
//
// ============================================================
// CHALLENGE DESCRIPTION
// ============================================================
//
// Implemente un gestionnaire de persistance educatif avec :
//
//  PARTIE A - Cron avance
//    - Ajouter une entree cron avec validation du format
//      (verifier que les 5 premiers champs sont valides : * ou chiffres)
//    - Lister les entrees avec index numero (pour faciliter la suppression)
//    - Supprimer par index
//    - Supprimer TOUTES les entrees contenant un tag specifique
//
//  PARTIE B - Scanner de persistance
//    Implementer un scanner qui cherche dans les emplacements courants :
//    a) Crontab utilisateur (crontab -l)
//    b) ~/.bashrc et ~/.zshrc : chercher des lignes suspectes
//       (lignes contenant "nohup", "&", "curl", "wget", "/tmp/")
//    c) ~/Library/LaunchAgents/ (macOS) : lister les .plist
//    d) Afficher un rapport "persistence scan"
//
//  PARTIE C - Tagger les entrees
//    - Ajouter un tag dans le commentaire : # [EDU-TAG]
//    - Permet de retrouver et supprimer facilement toutes les entrees du lab
//    Exemple d'entree taguee :
//      * * * * * echo "hello" >> /tmp/test.txt  # [EDU-TAG]
//
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <sys/stat.h>

static const std::string EDU_TAG = "# [EDU-TAG]";

// ============================================================
// UTILITAIRES DE BASE (a reimplementer ou reutiliser)
// ============================================================

std::string runCommand(const std::string& cmd) {
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return result;
    char buf[256];
    while (fgets(buf, sizeof(buf), pipe)) result += buf;
    pclose(pipe);
    return result;
}

std::string readCrontab() {
    return runCommand("crontab -l 2>/dev/null");
}

void writeCrontab(const std::string& content) {
    char tmpfile[] = "/tmp/crontab_challenge_XXXXXX";
    int fd = mkstemp(tmpfile);
    if (fd < 0) return;
    write(fd, content.c_str(), content.size());
    close(fd);
    system(("crontab " + std::string(tmpfile)).c_str());
    unlink(tmpfile);
}

// ============================================================
// PARTIE A : Gestion avancee des cron entries
// ============================================================

// TODO A1 : Valider le format d'une entree cron
// Une entree valide commence par 5 champs (ou @reboot, @hourly, etc.)
// Retourner true si le format semble correct
bool isValidCronEntry(const std::string& entry) {
    // TON CODE ICI
    // Cas speciaux acceptes : lignes commencant par @reboot, @hourly, @daily, @weekly, @monthly
    // Cas general : verifier qu'il y a au moins 6 tokens (5 champs + commande)
    // Les 5 premiers tokens doivent etre "*" ou des chiffres/plages valides
    return false;  // placeholder
}

// TODO A2 : Lister les entrees avec index
// Format :
//   [0] * * * * * echo hello
//   [1] @reboot /chemin/cmd
std::vector<std::string> listCronEntriesIndexed() {
    // TON CODE ICI
    // Retourner un vecteur des entrees actives (non vides, non commentaires)
    return {};
}

// TODO A3 : Supprimer une entree par index
bool removeCronByIndex(int index) {
    // TON CODE ICI
    // 1. Obtenir le vecteur indexe
    // 2. Verifier que index est valide
    // 3. Retrouver la ligne exacte dans la crontab et la supprimer
    return false;
}

// TODO A4 : Supprimer toutes les entrees taguees [EDU-TAG]
int removeAllTaggedEntries() {
    // TON CODE ICI
    // Supprimer toutes les lignes contenant EDU_TAG
    // Retourner le nombre de lignes supprimees
    return 0;
}

// TODO A5 : Ajouter avec tag
bool addTaggedCronEntry(const std::string& entry) {
    // TON CODE ICI
    // 1. Valider avec isValidCronEntry()
    // 2. Ajouter le EDU_TAG en commentaire en fin de ligne
    // 3. Verifier les doublons
    // 4. Ajouter a la crontab
    return false;
}

// ============================================================
// PARTIE B : Scanner de persistance
// ============================================================

struct PersistenceReport {
    std::vector<std::string> cron_entries;
    std::vector<std::string> suspicious_shell_lines;
    std::vector<std::string> launch_agents;  // macOS
};

// TODO B1 : Scanner les fichiers shell
void scanShellFiles(PersistenceReport& report) {
    // TON CODE ICI
    // Verifier ~/.bashrc, ~/.zshrc, ~/.bash_profile, ~/.profile
    // Pour chaque fichier existant, lire ligne par ligne
    // Marquer les lignes contenant : "nohup", " &", "curl", "wget", "/tmp/"
    // Ajouter dans report.suspicious_shell_lines avec format "fichier:ligne_num: contenu"
}

// TODO B2 : Scanner LaunchAgents (macOS)
void scanLaunchAgents(PersistenceReport& report) {
    // TON CODE ICI
    // Verifier ~/Library/LaunchAgents/ (macOS uniquement)
    // Lister les fichiers .plist presents
    // Sur Linux, indiquer "non applicable"
}

// TODO B3 : Generer et afficher le rapport complet
void runPersistenceScan() {
    PersistenceReport report;

    std::cout << "[SCAN] Analyse des points de persistance...\n\n";

    // Crontab
    report.cron_entries = listCronEntriesIndexed();
    std::cout << "[CRON] " << report.cron_entries.size() << " entree(s) active(s)\n";
    for (const auto& e : report.cron_entries) {
        std::cout << "  " << e << "\n";
    }

    // Shell files
    scanShellFiles(report);
    std::cout << "\n[SHELL] " << report.suspicious_shell_lines.size() << " ligne(s) suspecte(s)\n";
    for (const auto& l : report.suspicious_shell_lines) {
        std::cout << "  " << l << "\n";
    }

    // LaunchAgents
    scanLaunchAgents(report);
    std::cout << "\n[LAUNCHAGENTS] " << report.launch_agents.size() << " fichier(s)\n";
    for (const auto& f : report.launch_agents) {
        std::cout << "  " << f << "\n";
    }

    std::cout << "\n[SCAN] Termine.\n";
}

// ============================================================
// MAIN
// ============================================================
int main() {
    std::cout << "=== Challenge 08 : Persistance Avancee (EDUCATIF) ===\n";
    std::cout << "Agit UNIQUEMENT sur ta propre crontab. Aucun privilege root.\n\n";

    int choice = 0;
    while (true) {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Lister les entrees cron (avec index)\n";
        std::cout << "2. Ajouter une entree taguee [EDU-TAG]\n";
        std::cout << "3. Supprimer une entree par index\n";
        std::cout << "4. Supprimer toutes les entrees [EDU-TAG]\n";
        std::cout << "5. Scanner les points de persistance\n";
        std::cout << "0. Quitter\n";
        std::cout << "Choix : ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                auto entries = listCronEntriesIndexed();
                if (entries.empty()) {
                    std::cout << "[INFO] Crontab vide.\n";
                } else {
                    for (size_t i = 0; i < entries.size(); ++i) {
                        std::cout << "[" << i << "] " << entries[i] << "\n";
                    }
                }
                break;
            }
            case 2: {
                std::cout << "Entree cron (sans le tag) : ";
                std::string entry;
                std::getline(std::cin, entry);
                bool ok = addTaggedCronEntry(entry);
                std::cout << (ok ? "[OK] Ajoutee avec tag.\n" : "[ERREUR] Echec (format invalide ou deja presente).\n");
                break;
            }
            case 3: {
                std::cout << "Index a supprimer : ";
                int idx;
                std::cin >> idx;
                std::cin.ignore();
                bool ok = removeCronByIndex(idx);
                std::cout << (ok ? "[OK] Supprimee.\n" : "[ERREUR] Index invalide.\n");
                break;
            }
            case 4: {
                int n = removeAllTaggedEntries();
                std::cout << "[OK] " << n << " entree(s) [EDU-TAG] supprimee(s).\n";
                break;
            }
            case 5:
                runPersistenceScan();
                break;
            default:
                std::cout << "Choix invalide.\n";
        }
    }

    return 0;
}
