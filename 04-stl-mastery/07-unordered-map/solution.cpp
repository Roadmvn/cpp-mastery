// ============================================================
// Unordered Map — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// PARTIE 1 : Operations de base
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : Operations de base ===" << endl;

    // 1. Creer la map
    unordered_map<string, int> scores;

    // 2. Inserer
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores.insert({"Charlie", 92});

    // 3. Acceder
    cout << "Bob : " << scores["Bob"] << endl;

    // 4. Verifier existence
    cout << "Diana existe (count) ? " << scores.count("Diana") << endl;

    auto it = scores.find("Diana");
    cout << "Diana existe (find) ? " << (it != scores.end() ? "oui" : "non") << endl;

    // 5. Ajouter et modifier
    scores["Diana"] = 88;
    scores["Bob"] = 90;

    // 6. Supprimer
    scores.erase("Charlie");

    // 7. Iterer
    cout << "Tous les scores :" << endl;
    for (auto& [name, score] : scores) {
        cout << "  " << name << " : " << score << endl;
    }

    cout << endl;
}

// ============================================================
// PARTIE 2 : Frequency counter
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : Frequency counter ===" << endl;

    // 1-2. Compter les caracteres
    string s = "abracadabra";
    unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }

    // 3. Afficher
    cout << "Frequences de \"" << s << "\" :" << endl;
    for (auto& [ch, count] : freq) {
        cout << "  '" << ch << "' : " << count << endl;
    }

    // 4. Caractere le plus frequent
    char most_freq = ' ';
    int max_count = 0;
    for (auto& [ch, count] : freq) {
        if (count > max_count) {
            max_count = count;
            most_freq = ch;
        }
    }
    cout << "Plus frequent : '" << most_freq << "' (" << max_count << " fois)" << endl;

    // 5. Frequence des mots
    vector<string> fruits = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    unordered_map<string, int> word_freq;
    for (const string& w : fruits) {
        word_freq[w]++;
    }

    cout << "Frequences des fruits :" << endl;
    for (auto& [word, count] : word_freq) {
        cout << "  " << word << " : " << count << endl;
    }

    cout << endl;
}

// ============================================================
// PARTIE 3 : Grouper par propriete
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : Grouper ===" << endl;

    vector<pair<string, string>> students = {
        {"Alice", "Info"}, {"Bob", "Math"}, {"Charlie", "Info"},
        {"Diana", "Math"}, {"Eve", "Info"}
    };

    // Grouper par filiere
    unordered_map<string, vector<string>> groups;
    for (auto& [name, field] : students) {
        groups[field].push_back(name);
    }

    // Afficher
    for (auto& [field, names] : groups) {
        cout << field << " : ";
        for (int i = 0; i < (int)names.size(); i++) {
            cout << names[i];
            if (i < (int)names.size() - 1) cout << ", ";
        }
        cout << endl;
    }

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
