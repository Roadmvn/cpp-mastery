// Chapitre 01 - Exercise : Wrappers d'APIs Systeme
// EDUCATIF - Simulation cross-platform des APIs Win32
//
// Compile : g++ -std=c++17 -o exercise exercise.cpp

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <pwd.h>
#include <ctime>
#include <sys/utsname.h>

namespace WinAPI {

    // TODO 1 : Implemente GetCurrentProcessId()
    // Retourne le PID du processus courant
    // Indice : utilise getpid()
    unsigned long GetCurrentProcessId() {
        // TON CODE ICI
        return 0;
    }

    // TODO 2 : Implemente GetComputerNameA()
    // Remplit buffer avec le nom de la machine
    // Indice : utilise gethostname()
    bool GetComputerNameA(char* buffer, unsigned long* size) {
        // TON CODE ICI
        return false;
    }

    // TODO 3 : Implemente GetUserNameA()
    // Remplit buffer avec le nom de l'utilisateur courant
    // Indice : utilise getlogin() ou getpwuid(getuid())
    bool GetUserNameA(char* buffer, unsigned long* size) {
        // TON CODE ICI
        return false;
    }

    // TODO 4 : Implemente GetCurrentDirectoryA()
    // Remplit buffer avec le repertoire courant
    // Retourne la taille de la string, 0 en cas d'erreur
    // Indice : utilise getcwd()
    unsigned long GetCurrentDirectoryA(unsigned long size, char* buffer) {
        // TON CODE ICI
        return 0;
    }

    // TODO 5 : Implemente GetEnvironmentVariableA()
    // Recupere une variable d'environnement par son nom
    // Retourne la taille de la valeur, 0 si non trouvee
    // Indice : utilise getenv()
    unsigned long GetEnvironmentVariableA(const char* name, char* buffer, unsigned long size) {
        // TON CODE ICI
        return 0;
    }

    // TODO 6 : Implemente GetSystemInfo()
    // Affiche les infos systeme : OS, architecture, version
    // Indice : utilise uname()
    void GetSystemInfo() {
        // TON CODE ICI
    }

    // TODO 7 : Implemente GetTickCount()
    // Retourne le temps depuis le boot en millisecondes
    // Indice : utilise clock_gettime(CLOCK_MONOTONIC, ...)
    unsigned long GetTickCount() {
        // TON CODE ICI
        return 0;
    }
}

int main() {
    std::cout << "=== Exercise : Wrappers API Systeme ===" << std::endl;
    std::cout << std::endl;

    // Test TODO 1
    std::cout << "[*] PID : " << WinAPI::GetCurrentProcessId() << std::endl;

    // Test TODO 2
    char hostname[256];
    unsigned long hostnameSize = sizeof(hostname);
    if (WinAPI::GetComputerNameA(hostname, &hostnameSize)) {
        std::cout << "[*] Hostname : " << hostname << std::endl;
    } else {
        std::cout << "[!] GetComputerNameA non implemente" << std::endl;
    }

    // Test TODO 3
    char username[256];
    unsigned long usernameSize = sizeof(username);
    if (WinAPI::GetUserNameA(username, &usernameSize)) {
        std::cout << "[*] User : " << username << std::endl;
    } else {
        std::cout << "[!] GetUserNameA non implemente" << std::endl;
    }

    // Test TODO 4
    char cwd[1024];
    unsigned long cwdLen = WinAPI::GetCurrentDirectoryA(sizeof(cwd), cwd);
    if (cwdLen > 0) {
        std::cout << "[*] CWD : " << cwd << std::endl;
    } else {
        std::cout << "[!] GetCurrentDirectoryA non implemente" << std::endl;
    }

    // Test TODO 5
    char envBuf[256];
    unsigned long envLen = WinAPI::GetEnvironmentVariableA("HOME", envBuf, sizeof(envBuf));
    if (envLen > 0) {
        std::cout << "[*] HOME : " << envBuf << std::endl;
    } else {
        std::cout << "[!] GetEnvironmentVariableA non implemente" << std::endl;
    }

    // Test TODO 6
    std::cout << "[*] System Info :" << std::endl;
    WinAPI::GetSystemInfo();

    // Test TODO 7
    std::cout << "[*] Uptime (ms) : " << WinAPI::GetTickCount() << std::endl;

    return 0;
}
