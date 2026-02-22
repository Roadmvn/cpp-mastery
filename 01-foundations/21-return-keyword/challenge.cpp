// ============================================================
// CHALLENGE OFFENSIVE : Encodeur/Decodeur XOR
// Fichier : challenge.cpp
// Compile : g++ -std=c++17 -o challenge challenge.cpp
// ============================================================
//
// CONTEXTE :
// Le XOR est l'operation de base en cryptographie et en malware.
// Propriete magique : A XOR K = B, et B XOR K = A
// Encoder et decoder utilisent la meme operation !
//
// C'est utilise en Red Team pour :
// - Obfusquer des payloads
// - Chiffrer des communications simples
// - Cacher des strings dans un binaire
//
// Ce n'est PAS un chiffrement securise (facilement cassable).
// Exercice PEDAGOGIQUE sur les fonctions et le return.
//
// Usage educatif uniquement.
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// Encode/decode un caractere avec XOR
char xor_char(char c, char key) {
    return c ^ key;  // Operateur XOR bit a bit
}

// Encode/decode une string complete avec une cle
string xor_cipher(string input, char key) {
    if (input.empty()) return "";
    if (key == 0) return input;  // XOR avec 0 ne change rien

    string output = "";
    for (int i = 0; i < (int)input.length(); i++) {
        output += xor_char(input[i], key);
    }
    return output;
}

// Encode avec une cle multi-caracteres (plus robuste)
string xor_cipher_multi(string input, string key) {
    if (input.empty()) return "";
    if (key.empty()) return input;

    string output = "";
    for (int i = 0; i < (int)input.length(); i++) {
        char k = key[i % key.length()];  // Cle cyclique
        output += xor_char(input[i], k);
    }
    return output;
}

// Affiche une string en hexadecimal
string to_hex(string s) {
    string hex = "";
    char hex_chars[] = "0123456789ABCDEF";
    for (int i = 0; i < (int)s.length(); i++) {
        unsigned char c = s[i];
        hex += hex_chars[c >> 4];
        hex += hex_chars[c & 0x0F];
        hex += ' ';
    }
    return hex;
}

int main() {
    cout << "========================================" << endl;
    cout << "  XOR Encoder/Decoder" << endl;
    cout << "========================================" << endl;

    // --- Test 1 : XOR avec cle simple ---
    string message = "Hello, World!";
    char key = 0x42;  // Cle = 'B'

    cout << "\n--- Cle simple (0x42) ---" << endl;
    cout << "Original  : " << message << endl;

    string encoded = xor_cipher(message, key);
    cout << "Encode    : " << to_hex(encoded) << endl;

    string decoded = xor_cipher(encoded, key);
    cout << "Decode    : " << decoded << endl;

    // Verification
    cout << "Match     : " << (decoded == message ? "OUI" : "NON") << endl;

    // --- Test 2 : XOR avec cle multi ---
    string secret = "cmd.exe /c whoami";
    string multi_key = "SEC";

    cout << "\n--- Cle multi (\"" << multi_key << "\") ---" << endl;
    cout << "Original  : " << secret << endl;

    string enc2 = xor_cipher_multi(secret, multi_key);
    cout << "Encode    : " << to_hex(enc2) << endl;

    string dec2 = xor_cipher_multi(enc2, multi_key);
    cout << "Decode    : " << dec2 << endl;
    cout << "Match     : " << (dec2 == secret ? "OUI" : "NON") << endl;

    // --- Demonstration du probleme du XOR simple ---
    cout << "\n--- Pourquoi XOR simple est faible ---" << endl;
    string repeated = "AAAAAAAAAA";
    string enc3 = xor_cipher(repeated, key);
    cout << "Input     : " << repeated << endl;
    cout << "Encode    : " << to_hex(enc3) << endl;
    cout << "Remarque  : Tous les octets sont identiques !" << endl;
    cout << "Un analyste peut deviner la cle facilement." << endl;

    cout << "\n========================================" << endl;
    cout << "XOR n'est PAS un vrai chiffrement." << endl;
    cout << "Pour du vrai crypto : AES, ChaCha20, etc." << endl;
    cout << "========================================" << endl;

    return 0;
}
