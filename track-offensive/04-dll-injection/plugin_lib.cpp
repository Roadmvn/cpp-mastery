// Chapitre 04 - Plugin Library (shared library)
// Compile :
//   Linux : g++ -std=c++17 -shared -fPIC -o plugin.so plugin_lib.cpp
//   macOS : g++ -std=c++17 -shared -fPIC -o plugin.dylib plugin_lib.cpp

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>

extern "C" {

    const char* plugin_name() {
        return "DemoPlugin v1.0";
    }

    const char* plugin_description() {
        return "Plugin educatif de demonstration pour dlopen/dlsym";
    }

    int execute(const char* arg) {
        std::cout << "[PLUGIN] Argument recu : " << arg << std::endl;
        std::cout << "[PLUGIN] PID du processus hote : " << getpid() << std::endl;
        std::cout << "[PLUGIN] Code execute depuis la shared library !" << std::endl;
        return 0;
    }

    void cleanup() {
        std::cout << "[PLUGIN] Nettoyage des ressources." << std::endl;
    }
}
