// ============================================================
// Mini-projet : Validateur de carte bancaire - Algorithme de Luhn
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o validator main.cpp && ./validator
// ============================================================

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Retourne le type de carte selon le prefixe
string detectCardType(const string& number) {
    if (number.size() >= 1 && number[0] == '4')
        return "Visa";
    if (number.size() >= 2 && number.substr(0, 2) >= "51" && number.substr(0, 2) <= "55")
        return "Mastercard";
    if (number.size() >= 2 && (number.substr(0, 2) == "34" || number.substr(0, 2) == "37"))
        return "American Express";
    if (number.size() >= 4 && number.substr(0, 4) == "6011")
        return "Discover";
    return "Inconnue";
}

// Valide un numero de carte avec l'algorithme de Luhn
// Retourne true si valide
bool luhn(const string& number) {
    int n = static_cast<int>(number.size());
    if (n < 13 || n > 19) return false;

    // Verifier que tous les caracteres sont des chiffres
    for (char c : number) {
        if (!isdigit(c)) return false;
    }

    // Extraire les chiffres dans un array
    int digits[19] = {};
    for (int i = 0; i < n; i++) {
        digits[i] = number[i] - '0';
    }

    // Appliquer l'algorithme de Luhn
    // Parcourir de droite a gauche
    // Les chiffres a position impaire depuis la droite sont doubles
    int sum = 0;
    bool double_it = false; // Le dernier chiffre (checksum) n'est pas double

    for (int i = n - 1; i >= 0; i--) {
        int d = digits[i];
        if (double_it) {
            d *= 2;
            if (d > 9) d -= 9;
        }
        sum += d;
        double_it = !double_it;
    }

    return (sum % 10 == 0);
}

// Affiche les etapes de l'algorithme pour pedagogie
void showLuhnSteps(const string& number) {
    int n = static_cast<int>(number.size());
    cout << "\nDetail de l'algorithme :" << endl;
    cout << "  Chiffres originaux : ";
    for (char c : number) cout << c << " ";
    cout << endl;

    cout << "  Apres Luhn        : ";
    bool double_it = false;
    int total = 0;
    int processed[19] = {};
    for (int i = n - 1; i >= 0; i--) {
        int d = number[i] - '0';
        if (double_it) {
            d *= 2;
            if (d > 9) d -= 9;
        }
        processed[i] = d;
        total += d;
        double_it = !double_it;
    }
    for (int i = 0; i < n; i++) cout << processed[i] << " ";
    cout << endl;
    cout << "  Somme = " << total << "  |  " << total << " % 10 = " << total % 10 << endl;
}

// Retirer les espaces et tirets d'un numero saisi
string sanitize(const string& raw) {
    string clean;
    for (char c : raw) {
        if (c != ' ' && c != '-') clean += c;
    }
    return clean;
}

// Valide et affiche le resultat pour un numero donne
void validate(const string& raw) {
    string number = sanitize(raw);
    bool valid = luhn(number);
    string type = detectCardType(number);

    cout << "Numero : " << raw << endl;
    cout << "Type   : " << type << endl;
    cout << "Statut : " << (valid ? "[VALIDE]" : "[INVALIDE]") << endl;
}

int main() {
    cout << "=== Validateur de Carte Bancaire (Algorithme de Luhn) ===" << endl;

    // --- Tests avec numeros connus ---
    cout << "\n--- Numeros de test ---" << endl;

    string test_cards[] = {
        "4532015112830366",   // Visa valide
        "5425233430109903",   // Mastercard valide
        "374251018720955",    // Amex valide
        "6011000990139424",   // Discover valide
        "1234567890123456",   // Fictif invalide
        "4532015112830367",   // Visa modifie (dernier chiffre +1) : invalide
        "0000000000000000",   // Zeros : invalide
    };
    int n_tests = 7;

    for (int i = 0; i < n_tests; i++) {
        cout << "\n";
        validate(test_cards[i]);
    }

    // --- Detail pedagogique sur un numero valide ---
    cout << "\n--- Detail de l'algorithme sur 4532015112830366 ---" << endl;
    showLuhnSteps("4532015112830366");

    // --- Mode interactif ---
    cout << "\n--- Mode interactif ---" << endl;
    cout << "Entre un numero de carte (ou 'q' pour quitter) :" << endl;

    string input;
    while (true) {
        cout << "\nNumero : ";
        if (!getline(cin, input) || input == "q" || input == "Q") {
            break;
        }
        if (input.empty()) continue;
        string clean = sanitize(input);
        if (clean.empty()) {
            cout << "Numero vide." << endl;
            continue;
        }
        validate(input);
        if (luhn(clean)) {
            showLuhnSteps(clean);
        }
    }

    cout << "Au revoir." << endl;
    return 0;
}
