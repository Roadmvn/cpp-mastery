// ============================================================
// Challenge Offensif : Encode/Decode de buffers avec templates
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
// ============================================================
// Contexte : Tu interceptes des buffers reseau. Les donnees
// peuvent etre des int32, uint8, float, double... Tu dois pouvoir
// encoder et decoder n'importe quel type generiquement sans
// dupliquer le code. C'est exactement ce que font les parsers
// de protocoles binaires (FIX, ITCH, OUCH).
//
// Techniques :
//   - template<typename T> pour la genericite
//   - reinterpret_cast pour la manipulation binaire
//   - XOR cipher simple pour l'obfuscation
//   - Serialisation/deserialisation de buffers bruts
// ============================================================

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <string>
#include <array>
using namespace std;

// ============================================================
// 1. Serialisation generique : ecrire n'importe quel type en bytes
// ============================================================

// Ecrit la representation binaire de 'val' dans 'buffer' a partir de 'offset'
template<typename T>
void serialize(uint8_t* buffer, int& offset, T val) {
    memcpy(buffer + offset, &val, sizeof(T));
    offset += static_cast<int>(sizeof(T));
}

// Lit la representation binaire depuis 'buffer' a partir de 'offset'
template<typename T>
T deserialize(const uint8_t* buffer, int& offset) {
    T val;
    memcpy(&val, buffer + offset, sizeof(T));
    offset += static_cast<int>(sizeof(T));
    return val;
}

// ============================================================
// 2. XOR cipher generique : encode/decode un array de n'importe quel type
// ============================================================

// Encode chaque byte de chaque element en XOR avec la cle
template<typename T>
void xorEncode(T* data, int count, uint8_t key) {
    uint8_t* raw = reinterpret_cast<uint8_t*>(data);
    int total_bytes = count * static_cast<int>(sizeof(T));
    for (int i = 0; i < total_bytes; i++) {
        raw[i] ^= key;
    }
}

// XOR est son propre inverse : decode == encode
template<typename T>
void xorDecode(T* data, int count, uint8_t key) {
    xorEncode(data, count, key);
}

// ============================================================
// 3. Affichage hexadecimal generique d'un buffer
// ============================================================

template<typename T>
void printHex(const T* data, int count, const string& label) {
    const uint8_t* raw = reinterpret_cast<const uint8_t*>(data);
    int total = count * static_cast<int>(sizeof(T));
    cout << label << " [" << total << " bytes] : ";
    for (int i = 0; i < total; i++) {
        cout << hex << uppercase << setfill('0') << setw(2)
             << static_cast<int>(raw[i]) << " ";
    }
    cout << dec << endl;
}

// ============================================================
// 4. Checksum generique : somme de tous les bytes
// ============================================================

template<typename T>
uint32_t checksum(const T* data, int count) {
    const uint8_t* raw = reinterpret_cast<const uint8_t*>(data);
    int total = count * static_cast<int>(sizeof(T));
    uint32_t sum = 0;
    for (int i = 0; i < total; i++) {
        sum += raw[i];
    }
    return sum;
}

// ============================================================
// 5. Comparaison d'arrays generique
// ============================================================

template<typename T>
bool arrayEquals(const T* a, const T* b, int count) {
    return memcmp(a, b, count * sizeof(T)) == 0;
}

// ============================================================
// Demo : Simulation d'un paquet reseau binaire
// ============================================================

struct PacketHeader {
    uint16_t magic;    // 0xDEAD
    uint8_t  version;
    uint8_t  type;
    uint32_t payload_len;
};

int main() {
    cout << "=== Challenge : Buffer Encode/Decode avec Templates ===" << endl;

    // --- DEMO 1 : Serialisation generique ---
    cout << "\n--- Demo 1 : Serialisation de types mixtes ---" << endl;

    uint8_t buffer[64] = {};
    int offset = 0;

    uint16_t id     = 0xBEEF;
    float    price  = 185.50f;
    uint32_t qty    = 1000;
    double   notional = 185500.0;

    serialize(buffer, offset, id);
    serialize(buffer, offset, price);
    serialize(buffer, offset, qty);
    serialize(buffer, offset, notional);

    cout << "Donnees serializees (" << offset << " bytes) :" << endl;
    cout << "  id=" << hex << id << dec
         << "  price=" << price
         << "  qty=" << qty
         << "  notional=" << notional << endl;

    cout << "Buffer hex : ";
    for (int i = 0; i < offset; i++) {
        cout << hex << uppercase << setfill('0') << setw(2)
             << static_cast<int>(buffer[i]) << " ";
    }
    cout << dec << endl;

    // Deserialisation
    int read_offset = 0;
    uint16_t r_id      = deserialize<uint16_t>(buffer, read_offset);
    float    r_price   = deserialize<float>   (buffer, read_offset);
    uint32_t r_qty     = deserialize<uint32_t>(buffer, read_offset);
    double   r_notional= deserialize<double>  (buffer, read_offset);

    cout << "Donnees deserialisees :" << endl;
    cout << "  id=" << hex << r_id << dec
         << "  price=" << r_price
         << "  qty=" << r_qty
         << "  notional=" << r_notional << endl;
    cout << "Integrite : " << (id == r_id && price == r_price && qty == r_qty ? "OK" : "FAIL") << endl;

    // --- DEMO 2 : XOR cipher sur differents types ---
    cout << "\n--- Demo 2 : XOR cipher generique ---" << endl;

    const uint8_t KEY = 0xAB;

    // int32
    int32_t prices[] = { 185, 380, 140, 250, 95 };
    int count = 5;
    cout << "Avant encodage : ";
    for (int i = 0; i < count; i++) cout << prices[i] << " ";
    cout << endl;

    printHex(prices, count, "Hex brut   ");

    xorEncode(prices, count, KEY);
    printHex(prices, count, "Hex encode ");

    cout << "Apres encodage (illisible) : ";
    for (int i = 0; i < count; i++) cout << prices[i] << " ";
    cout << endl;

    xorDecode(prices, count, KEY);
    cout << "Apres decodage : ";
    for (int i = 0; i < count; i++) cout << prices[i] << " ";
    cout << endl;

    // float
    cout << endl;
    float rates[] = { 1.05f, 2.10f, 0.75f };
    int rcount = 3;
    cout << "Rates originaux : ";
    for (int i = 0; i < rcount; i++) cout << rates[i] << " ";
    cout << endl;
    printHex(rates, rcount, "Hex brut   ");
    xorEncode(rates, rcount, KEY);
    printHex(rates, rcount, "Hex encode ");
    xorDecode(rates, rcount, KEY);
    cout << "Rates restaures : ";
    for (int i = 0; i < rcount; i++) cout << rates[i] << " ";
    cout << endl;

    // --- DEMO 3 : Checksum generique ---
    cout << "\n--- Demo 3 : Checksum de buffers ---" << endl;

    uint8_t data_u8[]  = { 0x01, 0x02, 0x03, 0x04, 0xFF };
    uint16_t data_u16[] = { 0x0102, 0x0304 };
    uint32_t data_u32[] = { 0x01020304 };

    cout << "uint8  checksum : " << hex << checksum(data_u8, 5) << dec << endl;
    cout << "uint16 checksum : " << hex << checksum(data_u16, 2) << dec << endl;
    cout << "uint32 checksum : " << hex << checksum(data_u32, 1) << dec << endl;

    // --- DEMO 4 : Paquet reseau complet ---
    cout << "\n--- Demo 4 : Paquet reseau binaire (header + payload) ---" << endl;

    uint8_t packet[128] = {};
    int pkt_offset = 0;

    // Header
    PacketHeader hdr;
    hdr.magic       = 0xDEAD;
    hdr.version     = 1;
    hdr.type        = 0x42; // type ORDER
    hdr.payload_len = sizeof(float) + sizeof(uint32_t);

    serialize(packet, pkt_offset, hdr.magic);
    serialize(packet, pkt_offset, hdr.version);
    serialize(packet, pkt_offset, hdr.type);
    serialize(packet, pkt_offset, hdr.payload_len);

    // Payload
    float   px  = 185.50f;
    uint32_t qt = 500;
    serialize(packet, pkt_offset, px);
    serialize(packet, pkt_offset, qt);

    cout << "Paquet envoye (" << pkt_offset << " bytes) :" << endl;
    cout << "  magic=0xDEAD version=" << (int)hdr.version
         << " type=0x" << hex << (int)hdr.type << dec
         << " payload_len=" << hdr.payload_len << endl;
    cout << "  payload : price=" << px << " qty=" << qt << endl;

    // Reception et parsing
    int rd = 0;
    uint16_t r_magic  = deserialize<uint16_t>(packet, rd);
    uint8_t  r_ver    = deserialize<uint8_t> (packet, rd);
    uint8_t  r_type   = deserialize<uint8_t> (packet, rd);
    uint32_t r_plen   = deserialize<uint32_t>(packet, rd);
    float    r_px     = deserialize<float>   (packet, rd);
    uint32_t r_qt     = deserialize<uint32_t>(packet, rd);

    cout << "Paquet recu et parse :" << endl;
    cout << "  magic=0x" << hex << r_magic << dec
         << " version=" << (int)r_ver
         << " type=0x" << hex << (int)r_type << dec
         << " payload_len=" << r_plen << endl;
    cout << "  payload : price=" << r_px << " qty=" << r_qt << endl;
    cout << "Magic valide : " << (r_magic == 0xDEAD ? "OUI" : "NON") << endl;

    // --- DEMO 5 : arrayEquals generique ---
    cout << "\n--- Demo 5 : Comparaison de buffers ---" << endl;

    int32_t original[] = { 10, 20, 30, 40 };
    int32_t copie[]    = { 10, 20, 30, 40 };
    int32_t different[]= { 10, 20, 99, 40 };

    cout << "original == copie    : " << (arrayEquals(original, copie,    4) ? "OUI" : "NON") << endl;
    cout << "original == different: " << (arrayEquals(original, different, 4) ? "OUI" : "NON") << endl;

    cout << "\n=== Fin du challenge ===" << endl;

    return 0;
}
