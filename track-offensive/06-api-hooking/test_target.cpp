// Chapitre 06 - Programme cible pour tester le hook
// Compile : g++ -std=c++17 -o test_target test_target.cpp
//
// Utilisation avec hook :
//   Linux : LD_PRELOAD=./hook.so ./test_target
//   macOS : DYLD_INSERT_LIBRARIES=./hook.dylib DYLD_FORCE_FLAT_NAMESPACE=1 ./test_target

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>

int main() {
    std::cout << "=== Programme Cible ===" << std::endl;

    // Allocations memoire (declenchent le hook malloc)
    auto* ptr = new int(42);
    auto* arr = new char[256];
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Strings (utilisent malloc en interne)
    std::string msg = "Hello World depuis le programme cible";
    puts(msg.c_str());

    // Variables d'environnement
    const char* home = getenv("HOME");
    const char* user = getenv("USER");
    const char* shell = getenv("SHELL");

    std::cout << "HOME  = " << (home ? home : "null") << std::endl;
    std::cout << "USER  = " << (user ? user : "null") << std::endl;
    std::cout << "SHELL = " << (shell ? shell : "null") << std::endl;

    // Nettoyage
    delete ptr;
    delete[] arr;

    std::cout << "Programme termine." << std::endl;
    return 0;
}
