// =============================================================
// Challenge Offensive : Matrice d'adjacence - Mapper un reseau
// =============================================================
// Compile : g++ -std=c++17 -o challenge challenge.cpp && ./challenge
// =============================================================
// Contexte : Tu fais de la reconnaissance reseau. Tu as identifie
// 6 machines sur un reseau et tu dois mapper les connexions entre
// elles sous forme de matrice d'adjacence.
//
// Matrice d'adjacence : matrix[i][j] = 1 si i est connecte a j
// C'est la representation standard d'un graphe en memoire.
// =============================================================

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    const int N = 6; // Nombre de machines

    string hosts[N] = {
        "gateway",    // 0
        "web-srv",    // 1
        "db-srv",     // 2
        "file-srv",   // 3
        "dev-box",    // 4
        "admin-pc"    // 5
    };

    // Matrice d'adjacence (0 = pas de connexion, 1 = connexion)
    // Reseau fictif :
    // - gateway connecte a tout le monde (point d'entree)
    // - web-srv connecte a db-srv (backend)
    // - file-srv connecte a dev-box et admin-pc
    // - admin-pc connecte a db-srv (acces admin)
    int adj[N][N] = {
        // gw  web  db  file dev  adm
        {  0,   1,   1,   1,   1,   1 }, // gateway
        {  1,   0,   1,   0,   0,   0 }, // web-srv
        {  1,   1,   0,   0,   0,   1 }, // db-srv
        {  1,   0,   0,   0,   1,   1 }, // file-srv
        {  1,   0,   0,   1,   0,   0 }, // dev-box
        {  1,   0,   1,   1,   0,   0 }  // admin-pc
    };

    // --- Affichage de la matrice ---
    cout << "=== Matrice d'adjacence du reseau ===" << endl;
    cout << setw(12) << " ";
    for (int j = 0; j < N; j++) {
        cout << setw(5) << hosts[j].substr(0, 4);
    }
    cout << endl;

    for (int i = 0; i < N; i++) {
        cout << setw(12) << hosts[i];
        for (int j = 0; j < N; j++) {
            cout << setw(5) << adj[i][j];
        }
        cout << endl;
    }

    // --- Degre de chaque noeud (nombre de connexions) ---
    cout << "\n=== Degre de chaque machine ===" << endl;
    for (int i = 0; i < N; i++) {
        int degree = 0;
        for (int j = 0; j < N; j++) {
            degree += adj[i][j];
        }
        cout << setw(12) << hosts[i] << " : " << degree << " connexion(s)";
        if (degree >= N - 1) cout << " [HUB]";
        if (degree == 1) cout << " [FEUILLE]";
        cout << endl;
    }

    // --- Trouver les chemins de longueur 2 (accessibles en 2 sauts) ---
    // Si adj[i][k] == 1 et adj[k][j] == 1, alors i peut atteindre j en 2 sauts via k
    int reach2[N][N] = {};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            for (int k = 0; k < N; k++) {
                if (adj[i][k] == 1 && adj[k][j] == 1) {
                    reach2[i][j] = 1;
                    break;
                }
            }
        }
    }

    cout << "\n=== Accessibilite en 2 sauts ===" << endl;
    cout << setw(12) << " ";
    for (int j = 0; j < N; j++) {
        cout << setw(5) << hosts[j].substr(0, 4);
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << setw(12) << hosts[i];
        for (int j = 0; j < N; j++) {
            cout << setw(5) << reach2[i][j];
        }
        cout << endl;
    }

    // --- Identification des points critiques ---
    cout << "\n=== Analyse de securite ===" << endl;

    // Machine la plus connectee = cible prioritaire
    int maxDeg = 0;
    int hubIdx = 0;
    for (int i = 0; i < N; i++) {
        int deg = 0;
        for (int j = 0; j < N; j++) deg += adj[i][j];
        if (deg > maxDeg) {
            maxDeg = deg;
            hubIdx = i;
        }
    }
    cout << "Cible prioritaire : " << hosts[hubIdx]
         << " (" << maxDeg << " connexions)" << endl;

    // Machines isolees (connectees uniquement au gateway)
    cout << "\nMachines faiblement connectees :" << endl;
    for (int i = 1; i < N; i++) {
        int deg = 0;
        for (int j = 0; j < N; j++) deg += adj[i][j];
        if (deg <= 2) {
            cout << "  " << hosts[i] << " (seulement " << deg << " connexion(s))" << endl;
        }
    }

    // Chemin d'attaque : depuis gateway, quelles machines atteignables directement ?
    cout << "\nChemins d'attaque depuis " << hosts[0] << " :" << endl;
    for (int j = 1; j < N; j++) {
        if (adj[0][j] == 1) {
            cout << "  " << hosts[0] << " -> " << hosts[j];
            // Et depuis la, ou peut-on aller ?
            bool first = true;
            for (int k = 0; k < N; k++) {
                if (k != 0 && k != j && adj[j][k] == 1) {
                    if (first) { cout << " -> {"; first = false; }
                    else cout << ", ";
                    cout << hosts[k];
                }
            }
            if (!first) cout << "}";
            cout << endl;
        }
    }

    // --- Graphe ASCII ---
    cout << "\n=== Topologie ASCII ===" << endl;
    cout << "          [gateway]" << endl;
    cout << "         /  |   |  \\" << endl;
    cout << "        /   |   |   \\" << endl;
    cout << "  [web-srv] | [file] [dev-box]" << endl;
    cout << "       |    |   |  \\" << endl;
    cout << "       |    |   |   \\" << endl;
    cout << "      [db-srv]  [admin-pc]" << endl;
    cout << "           \\       /" << endl;
    cout << "            \\     /" << endl;
    cout << "          (connexion directe)" << endl;

    return 0;
}
