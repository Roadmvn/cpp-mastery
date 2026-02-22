// ============================================================
//  Chapitre 05 -- Challenge : Simuler les types Windows API
//  Compile avec : g++ -std=c++11 -o challenge challenge.cpp
// ============================================================
//
//  OBJECTIF :
//  Simuler les types de l'API Windows en creant des alias.
//  Ca te prepare a lire du vrai code Windows sans etre perdu
//  par les DWORD, HANDLE, BOOL, LPSTR...
//
//  ETAPES :
//
//  1. Cree les alias suivants :
//     - DWORD   -> unsigned long
//     - HANDLE  -> void*
//     - BOOL    -> int
//     - LPSTR   -> char*
//     (+ les constantes TRUE = 1 et FALSE = 0)
//
//  2. Cree une struct "ProcessInfo" avec ces champs :
//     - pid        (DWORD)    -- identifiant du processus
//     - name       (LPSTR)    -- nom du processus
//     - handle     (HANDLE)   -- handle vers le processus
//     - is_running (BOOL)     -- le processus tourne-t-il ?
//
//  3. Cree une fonction display_process(ProcessInfo& p)
//     qui affiche les infos du processus
//
//  4. Dans le main(), cree 3 processus simulees et affiche-les
//
//  EXEMPLE DE SORTIE :
//
//  === PROCESS LIST ===
//  [PID: 4]     System          | Handle: 0x1000 | Running: YES
//  [PID: 1337]  malware.exe     | Handle: 0x2000 | Running: YES
//  [PID: 9999]  notepad.exe     | Handle: 0x0    | Running: NO
//  === 3 processus affiches ===
//
// ============================================================

#include <iostream>
#include <cstdint>

// -- A TOI DE JOUER --
// Cree les alias, la struct, la fonction d'affichage et le main()

int main() {
    std::cout << "=== PROCESS LIST ===" << std::endl;

    // Cree tes ProcessInfo ici et affiche-les

    std::cout << "=== FIN ===" << std::endl;

    return 0;
}
