// Chapitre 08 - Exercise : Mecanismes de Persistance
// EDUCATIF - CTF / Labs de securite uniquement
//
// IMPORTANT : Ce programme agit UNIQUEMENT sur ta propre crontab
//             (crontab -l / crontab -). Aucun acces root requis.
//             N'utilise PAS ce code sur un systeme qui ne t'appartient pas.
//
// Compile :
//   g++ -std=c++17 -o persistence_exercise exercise.cpp
//   ./persistence_exercise
//
// Note : fonctionne sur Linux et macOS. Windows non supporte (pas de crontab).

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

// ============================================================
// UTILITAIRE : executer une commande et capturer la sortie
// ============================================================

// TODO 1 : Implementer runCommand
// Utilise popen() pour executer cmd et capturer stdout
// Retourne la sortie complete sous forme de string
std::string runCommand(const std::string& cmd) {
    // TON CODE ICI
    // 1. popen(cmd.c_str(), "r")
    // 2. Lire par blocs de 128 chars
    // 3. Concatener dans une string result
    // 4. pclose()
    // 5. Retourner result

    return "";  // placeholder
}

// ============================================================
// SECTION CRONTAB
// ============================================================

// TODO 2 : Lire la crontab actuelle
// Retourne le contenu complet de la crontab utilisateur
// Si aucune crontab, retourne une string vide
std::string readCrontab() {
    // TON CODE ICI
    // Utiliser runCommand("crontab -l 2>/dev/null")
    // Note : "2>/dev/null" evite l'erreur "no crontab for user"

    return "";  // placeholder
}

// TODO 3 : Ecrire la crontab
// Remplace la crontab entiere par le contenu fourni
// Methode : echo "contenu" | crontab -
void writeCrontab(const std::string& content) {
    // TON CODE ICI
    // Methode recommandee :
    // 1. Ecrire content dans un fichier temporaire /tmp/crontab_tmp_XXXX
    // 2. system("crontab /tmp/crontab_tmp_XXXX")
    // 3. Supprimer le fichier temporaire
}

// TODO 4 : Ajouter une entree cron
// Ne duplique pas si l'entree existe deja (verifier avec find())
// Retourne true si l'entree a ete ajoutee, false si elle existait deja
bool addCronEntry(const std::string& entry) {
    // TON CODE ICI
    // 1. Lire la crontab actuelle
    // 2. Verifier si entry est deja presente (content.find(entry) != string::npos)
    // 3. Si non presente : ajouter la ligne, writeCrontab()
    // 4. Retourner le resultat

    return false;  // placeholder
}

// TODO 5 : Supprimer une entree cron
// Supprime la premiere ligne contenant le pattern donne
// Retourne true si quelque chose a ete supprime
bool removeCronEntry(const std::string& pattern) {
    // TON CODE ICI
    // 1. Lire la crontab ligne par ligne
    // 2. Reconstruire sans les lignes contenant le pattern
    // 3. Ecrire la nouvelle crontab
    // 4. Retourner (lignes_avant != lignes_apres)

    return false;  // placeholder
}

// TODO 6 : Lister les entrees cron (ligne par ligne)
void listCronEntries() {
    // TON CODE ICI
    // Afficher les lignes non vides et non commentees de la crontab
    // Format :
    //   [CRON] * * * * * /chemin/commande
    //   [CRON] @reboot /chemin/autre
}

// ============================================================
// MAIN : menu interactif
// ============================================================
int main() {
    std::cout << "=== Gestionnaire de Cron (EDUCATIF) ===\n";
    std::cout << "Agit UNIQUEMENT sur ta propre crontab utilisateur.\n\n";

    int choice = 0;
    while (true) {
        std::cout << "\n1. Lister les entrees cron\n";
        std::cout << "2. Ajouter une entree cron\n";
        std::cout << "3. Supprimer une entree cron\n";
        std::cout << "4. Afficher la crontab brute\n";
        std::cout << "0. Quitter\n";
        std::cout << "Choix : ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0) break;

        if (choice == 1) {
            // TON CODE ICI : appeler listCronEntries()
        } else if (choice == 2) {
            std::cout << "Entree a ajouter (ex: '* * * * * echo hello'): ";
            std::string entry;
            std::getline(std::cin, entry);
            // TON CODE ICI : appeler addCronEntry(), afficher le resultat
        } else if (choice == 3) {
            std::cout << "Pattern a supprimer (ex: 'echo hello'): ";
            std::string pattern;
            std::getline(std::cin, pattern);
            // TON CODE ICI : appeler removeCronEntry(), afficher le resultat
        } else if (choice == 4) {
            std::cout << readCrontab() << "\n";
        }
    }

    return 0;
}
