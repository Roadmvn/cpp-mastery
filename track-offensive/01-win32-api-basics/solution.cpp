// Chapitre 01 - Solution : Wrappers d'APIs Systeme
// EDUCATIF - Simulation cross-platform des APIs Win32
//
// Compile : g++ -std=c++17 -o solution solution.cpp

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <pwd.h>
#include <ctime>
#include <sys/utsname.h>

namespace WinAPI {

    // TODO 1 : GetCurrentProcessId
    unsigned long GetCurrentProcessId() {
        return static_cast<unsigned long>(getpid());
    }

    // TODO 2 : GetComputerNameA
    bool GetComputerNameA(char* buffer, unsigned long* size) {
        if (gethostname(buffer, *size) == 0) {
            *size = std::strlen(buffer);
            return true;
        }
        return false;
    }

    // TODO 3 : GetUserNameA
    bool GetUserNameA(char* buffer, unsigned long* size) {
        const char* user = getlogin();
        if (!user) {
            struct passwd* pw = getpwuid(getuid());
            user = pw ? pw->pw_name : nullptr;
        }
        if (user) {
            std::strncpy(buffer, user, *size - 1);
            buffer[*size - 1] = '\0';
            *size = std::strlen(buffer);
            return true;
        }
        return false;
    }

    // TODO 4 : GetCurrentDirectoryA
    unsigned long GetCurrentDirectoryA(unsigned long size, char* buffer) {
        if (getcwd(buffer, size)) {
            return std::strlen(buffer);
        }
        return 0;
    }

    // TODO 5 : GetEnvironmentVariableA
    unsigned long GetEnvironmentVariableA(const char* name, char* buffer, unsigned long size) {
        const char* val = getenv(name);
        if (val) {
            std::strncpy(buffer, val, size - 1);
            buffer[size - 1] = '\0';
            return std::strlen(buffer);
        }
        return 0;
    }

    // TODO 6 : GetSystemInfo
    void GetSystemInfo() {
        struct utsname info;
        if (uname(&info) == 0) {
            std::cout << "    OS       : " << info.sysname << std::endl;
            std::cout << "    Node     : " << info.nodename << std::endl;
            std::cout << "    Release  : " << info.release << std::endl;
            std::cout << "    Version  : " << info.version << std::endl;
            std::cout << "    Machine  : " << info.machine << std::endl;
        }
    }

    // TODO 7 : GetTickCount
    unsigned long GetTickCount() {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return static_cast<unsigned long>(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    }
}

int main() {
    std::cout << "=== Solution : Wrappers API Systeme ===" << std::endl;
    std::cout << std::endl;

    std::cout << "[*] PID : " << WinAPI::GetCurrentProcessId() << std::endl;

    char hostname[256];
    unsigned long hostnameSize = sizeof(hostname);
    if (WinAPI::GetComputerNameA(hostname, &hostnameSize)) {
        std::cout << "[*] Hostname : " << hostname << std::endl;
    }

    char username[256];
    unsigned long usernameSize = sizeof(username);
    if (WinAPI::GetUserNameA(username, &usernameSize)) {
        std::cout << "[*] User : " << username << std::endl;
    }

    char cwd[1024];
    if (WinAPI::GetCurrentDirectoryA(sizeof(cwd), cwd) > 0) {
        std::cout << "[*] CWD : " << cwd << std::endl;
    }

    char envBuf[256];
    if (WinAPI::GetEnvironmentVariableA("HOME", envBuf, sizeof(envBuf)) > 0) {
        std::cout << "[*] HOME : " << envBuf << std::endl;
    }

    std::cout << "[*] System Info :" << std::endl;
    WinAPI::GetSystemInfo();

    std::cout << "[*] Uptime (ms) : " << WinAPI::GetTickCount() << std::endl;

    return 0;
}
