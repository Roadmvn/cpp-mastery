// Chapitre 04 - Solution : Systeme de Plugins Dynamiques
// EDUCATIF - Chargement dynamique de shared libraries
//
// ETAPE 1 : Compile le plugin
//   Linux : g++ -std=c++17 -shared -fPIC -o plugin.so plugin_lib.cpp
//   macOS : g++ -std=c++17 -shared -fPIC -o plugin.dylib plugin_lib.cpp
//
// ETAPE 2 : Compile et lance
//   g++ -std=c++17 -o solution solution.cpp -ldl

#include <iostream>
#include <string>
#include <dlfcn.h>
#include <vector>

using PluginNameFunc = const char* (*)();
using PluginExecFunc = int (*)(const char*);
using PluginCleanupFunc = void (*)();

struct Plugin {
    void* handle;
    std::string path;
    PluginNameFunc getName;
    PluginExecFunc execute;
    PluginCleanupFunc cleanup;
};

// TODO 2 : Charger un plugin
Plugin loadPlugin(const std::string& path) {
    Plugin p{};
    p.path = path;

    p.handle = dlopen(path.c_str(), RTLD_NOW);
    if (!p.handle) {
        std::cerr << "[!] dlopen erreur : " << dlerror() << std::endl;
        return p;
    }

    p.getName = reinterpret_cast<PluginNameFunc>(dlsym(p.handle, "plugin_name"));
    p.execute = reinterpret_cast<PluginExecFunc>(dlsym(p.handle, "execute"));
    p.cleanup = reinterpret_cast<PluginCleanupFunc>(dlsym(p.handle, "cleanup"));

    std::cout << "[*] Plugin charge depuis " << path << std::endl;
    return p;
}

// TODO 3 : Decharger un plugin
void unloadPlugin(Plugin& p) {
    if (!p.handle) return;

    if (p.cleanup) {
        p.cleanup();
    }

    dlclose(p.handle);
    p.handle = nullptr;
    std::cout << "[*] Plugin decharge : " << p.path << std::endl;
}

// TODO 4 : Inspection des symboles
void inspectPlugin(const std::string& path) {
    std::cout << "[*] Inspection de : " << path << std::endl;

    void* handle = dlopen(path.c_str(), RTLD_NOW);
    if (!handle) {
        std::cout << "[!] Impossible de charger : " << dlerror() << std::endl;
        return;
    }

    std::vector<std::string> expectedSymbols = {
        "plugin_name", "plugin_description", "execute",
        "cleanup", "init", "version"
    };

    for (const auto& sym : expectedSymbols) {
        void* ptr = dlsym(handle, sym.c_str());
        if (ptr) {
            std::cout << "    [+] " << sym << " : TROUVE" << std::endl;
        } else {
            std::cout << "    [-] " << sym << " : absent" << std::endl;
        }
    }

    dlclose(handle);
}

int main() {
    std::cout << "=== Solution : Chargeur de Plugins ===" << std::endl;
    std::cout << std::endl;

#ifdef __APPLE__
    std::string pluginPath = "./plugin.dylib";
#else
    std::string pluginPath = "./plugin.so";
#endif

    // Inspection
    inspectPlugin(pluginPath);
    std::cout << std::endl;

    // Chargement
    Plugin p = loadPlugin(pluginPath);
    if (!p.handle) {
        std::cerr << "[!] Compile d'abord plugin_lib.cpp en shared library" << std::endl;
        return 1;
    }

    // Utilisation
    if (p.getName) {
        std::cout << "[*] Plugin : " << p.getName() << std::endl;
    }
    if (p.execute) {
        std::cout << std::endl;
        p.execute("Hello depuis le chargeur!");
    }

    // Dechargement
    std::cout << std::endl;
    unloadPlugin(p);

    return 0;
}
