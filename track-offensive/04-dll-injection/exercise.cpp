// Chapitre 04 - Exercise : Systeme de Plugins Dynamiques
// EDUCATIF - Chargement dynamique de shared libraries
//
// ETAPE 1 : Compile le plugin
//   Linux : g++ -std=c++17 -shared -fPIC -o plugin.so plugin_lib.cpp
//   macOS : g++ -std=c++17 -shared -fPIC -o plugin.dylib plugin_lib.cpp
//
// ETAPE 2 : Compile et lance ce fichier
//   Linux : g++ -std=c++17 -o exercise exercise.cpp -ldl
//   macOS : g++ -std=c++17 -o exercise exercise.cpp -ldl
//
// NOTE : Tu dois d'abord creer plugin_lib.cpp (voir TODO 1)

#include <iostream>
#include <string>
#include <dlfcn.h>
#include <vector>

// Types de fonctions attendues dans les plugins
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

// TODO 1 : Cree un fichier plugin_lib.cpp separement avec :
// - extern "C" const char* plugin_name() → retourne le nom du plugin
// - extern "C" int execute(const char* arg) → affiche l'argument et retourne 0
// - extern "C" void cleanup() → affiche un message de nettoyage

// TODO 2 : Charge un plugin depuis un chemin
// Utilise dlopen avec RTLD_NOW
// Resous les symboles "plugin_name", "execute", "cleanup" avec dlsym
// Retourne un Plugin rempli, ou un Plugin avec handle = nullptr en cas d'erreur
Plugin loadPlugin(const std::string& path) {
    Plugin p{};
    p.path = path;
    // TON CODE ICI
    return p;
}

// TODO 3 : Decharge un plugin
// Appelle cleanup si disponible, puis dlclose
void unloadPlugin(Plugin& p) {
    // TON CODE ICI
}

// TODO 4 : Liste les symboles disponibles dans une lib
// Charge la lib et essaie de resoudre une liste de noms de fonctions
// Affiche lesquels sont trouves et lesquels ne le sont pas
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
        // TON CODE ICI - Affiche si le symbole est trouve ou non
    }

    dlclose(handle);
}

int main() {
    std::cout << "=== Exercise : Chargeur de Plugins ===" << std::endl;
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
        std::cout << "[!] Plugin non charge. As-tu compile plugin_lib.cpp ?" << std::endl;
        std::cout << "    Cree plugin_lib.cpp puis compile-le en shared library." << std::endl;
        return 1;
    }

    // Utilisation
    if (p.getName) {
        std::cout << "[*] Plugin : " << p.getName() << std::endl;
    }
    if (p.execute) {
        p.execute("Hello depuis le chargeur!");
    }

    // Dechargement
    unloadPlugin(p);

    return 0;
}
