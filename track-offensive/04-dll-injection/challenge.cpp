// Chapitre 04 - Challenge : Gestionnaire de Plugins Multi-Libraries
// EDUCATIF - Systeme de plugins avec registre et execution chainee
//
// OBJECTIF : Creer un systeme qui :
// - Charge plusieurs plugins depuis un repertoire
// - Les enregistre dans un registre
// - Peut les executer tous ou individuellement
// - Gere les erreurs de chargement
//
// Compile :
//   1. g++ -std=c++17 -shared -fPIC -o plugin.so plugin_lib.cpp (ou .dylib)
//   2. g++ -std=c++17 -o challenge challenge.cpp -ldl
//
// DISCLAIMER : Demonstration educative du chargement dynamique.

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <dlfcn.h>

using NameFunc = const char* (*)();
using ExecFunc = int (*)(const char*);
using CleanFunc = void (*)();

struct PluginInfo {
    void* handle;
    std::string path;
    std::string name;
    NameFunc getName;
    ExecFunc execute;
    CleanFunc cleanup;
};

class PluginManager {
private:
    std::map<std::string, PluginInfo> plugins_;

public:
    // TODO 1 : Charge un plugin et l'enregistre dans le registre
    // La cle du registre = le nom retourne par plugin_name()
    // Si plugin_name n'existe pas, utilise le chemin comme cle
    bool loadPlugin(const std::string& path) {
        // TON CODE ICI
        return false;
    }

    // TODO 2 : Decharge un plugin par son nom
    bool unloadPlugin(const std::string& name) {
        // TON CODE ICI
        return false;
    }

    // TODO 3 : Execute un plugin specifique par son nom
    int executePlugin(const std::string& name, const std::string& arg) {
        // TON CODE ICI
        return -1;
    }

    // TODO 4 : Execute TOUS les plugins charges
    void executeAll(const std::string& arg) {
        // TON CODE ICI
    }

    // TODO 5 : Liste tous les plugins charges
    void listPlugins() const {
        std::cout << "[*] Plugins charges : " << plugins_.size() << std::endl;
        // TON CODE ICI - Affiche nom et chemin de chaque plugin
    }

    // TODO 6 : Decharge tous les plugins proprement
    void unloadAll() {
        // TON CODE ICI
    }

    ~PluginManager() {
        unloadAll();
    }
};

int main() {
    std::cout << "=== Challenge : Plugin Manager ===" << std::endl;
    std::cout << "[!] EDUCATIF UNIQUEMENT" << std::endl;
    std::cout << std::endl;

    PluginManager manager;

#ifdef __APPLE__
    std::string ext = ".dylib";
#else
    std::string ext = ".so";
#endif

    // Charge le plugin de demo
    std::string pluginPath = "./plugin" + ext;
    if (manager.loadPlugin(pluginPath)) {
        std::cout << "[+] Plugin charge avec succes" << std::endl;
    } else {
        std::cout << "[!] Erreur de chargement. Compile d'abord plugin_lib.cpp" << std::endl;
        return 1;
    }

    std::cout << std::endl;
    manager.listPlugins();

    std::cout << std::endl;
    std::cout << "[*] Execution de tous les plugins :" << std::endl;
    manager.executeAll("argument_de_test");

    std::cout << std::endl;
    manager.unloadAll();

    return 0;
}
