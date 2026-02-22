// ============================================================
// Strings Avancees — Solutions
// Compile : g++ -std=c++17 -o solution solution.cpp && ./solution
// ============================================================

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

// ============================================================
// PARTIE 1 : substr, find, replace
// ============================================================

void partie1() {
    cout << "=== PARTIE 1 : substr, find, replace ===" << endl;

    // 1. Creer la string
    string s = "competitive-programming-is-awesome";
    cout << "Original : " << s << endl;

    // 2. Extraire "programming" avec substr
    size_t pos = s.find("programming");
    if (pos != string::npos) {
        string extracted = s.substr(pos, 11);  // "programming" = 11 chars
        cout << "Extrait : " << extracted << endl;
    }

    // 3. Remplacer "awesome" par "essential"
    size_t aw_pos = s.find("awesome");
    if (aw_pos != string::npos) {
        s.replace(aw_pos, 7, "essential");  // "awesome" = 7 chars
    }
    cout << "Apres replace : " << s << endl;

    // 4. Trouver chaque '-'
    cout << "Positions des '-' : ";
    size_t search_pos = 0;
    while ((search_pos = s.find('-', search_pos)) != string::npos) {
        cout << search_pos << " ";
        search_pos++;
    }
    cout << endl;

    // 5. Compter les voyelles
    int vowels = 0;
    string vowel_set = "aeiouAEIOU";
    for (char c : s) {
        if (vowel_set.find(c) != string::npos) {
            vowels++;
        }
    }
    cout << "Nombre de voyelles : " << vowels << endl;

    cout << endl;
}

// ============================================================
// PARTIE 2 : stringstream et parsing
// ============================================================

void partie2() {
    cout << "=== PARTIE 2 : stringstream ===" << endl;

    // 1. Parser une adresse IP
    string ip = "192.168.1.1";
    stringstream ss(ip);
    string octet;
    vector<int> octets;

    while (getline(ss, octet, '.')) {
        octets.push_back(stoi(octet));
    }

    // 2. Afficher chaque octet
    cout << "IP : " << ip << endl;
    for (int i = 0; i < (int)octets.size(); i++) {
        cout << "  Octet " << i << " : " << octets[i] << endl;
    }

    // 3. Parser "nom:Alice age:30 score:95.5"
    string data = "nom:Alice age:30 score:95.5";
    stringstream ss2(data);
    string token;
    string name;
    int age = 0;
    double score = 0.0;

    while (ss2 >> token) {
        size_t colon = token.find(':');
        string key = token.substr(0, colon);
        string value = token.substr(colon + 1);

        if (key == "nom") name = value;
        else if (key == "age") age = stoi(value);
        else if (key == "score") score = stod(value);
    }

    // 4. Construire le resultat
    stringstream builder;
    builder << name << " [" << age << "] -> " << score;
    cout << "Resultat : " << builder.str() << endl;

    cout << endl;
}

// ============================================================
// PARTIE 3 : Conversions et manipulation de caracteres
// ============================================================

void partie3() {
    cout << "=== PARTIE 3 : Conversions ===" << endl;

    // 1. string -> int -> calcul -> string
    string num_str = "12345";
    int num = stoi(num_str) * 2;
    string result = to_string(num);
    cout << num_str << " * 2 = " << result << endl;

    // 2. Compter et convertir
    string text = "Hello World 123";
    int letters = 0, digits = 0, spaces = 0;

    for (char c : text) {
        if (isalpha(c)) letters++;
        else if (isdigit(c)) digits++;
        else if (isspace(c)) spaces++;
    }
    cout << "\"" << text << "\"" << endl;
    cout << "  Lettres: " << letters << ", Chiffres: " << digits
         << ", Espaces: " << spaces << endl;

    // Conversion en majuscules
    string upper = text;
    for (char& c : upper) {
        c = toupper(c);
    }
    cout << "  Majuscules: " << upper << endl;

    // 3. vector<int> -> string avec tirets
    vector<int> nums = {10, 20, 30};
    stringstream ss;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > 0) ss << "-";
        ss << nums[i];
    }
    cout << "Vector en string : " << ss.str() << endl;

    cout << endl;
}

int main() {
    partie1();
    partie2();
    partie3();

    return 0;
}
