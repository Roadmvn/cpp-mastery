// ============================================================
// Mini-projet : Systeme d'Inventaire RPG
// ============================================================
// Compile : g++ -std=c++17 -Wall -Wextra -o inventory main.cpp && ./inventory
// ============================================================

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// ============================================================
// Classes de base et heritees
// ============================================================

class Item {
protected:
    string name;
    double weight;  // en kg
    int    value;   // en or

public:
    Item(const string& n, double w, int v)
        : name(n), weight(w), value(v) {}

    virtual ~Item() = default;

    virtual void display() const = 0;
    virtual void use() = 0;
    virtual string getType() const = 0;

    const string& getName()   const { return name;   }
    double        getWeight() const { return weight;  }
    int           getValue()  const { return value;   }
};

// --- Arme ---

class Weapon : public Item {
    int    damage;
    string range; // "melee", "courte", "longue"
    int    uses_left;

public:
    Weapon(const string& name, double weight, int value, int dmg, const string& rng)
        : Item(name, weight, value), damage(dmg), range(rng), uses_left(5) {}

    void display() const override {
        cout << setw(12) << "[Arme]   "
             << setw(20) << left << name << right
             << " | Deg: " << setw(3) << damage
             << " | Portee: " << setw(8) << range
             << " | Durabilite: " << uses_left << "/5"
             << " | " << value << " or"
             << " | " << weight << " kg" << endl;
    }

    void use() override {
        if (uses_left <= 0) {
            cout << "  " << name << " est brisee ! Tu ne peux plus l'utiliser." << endl;
            return;
        }
        uses_left--;
        cout << "  Tu attaques avec " << name << " ! +" << damage << " degats."
             << " (Durabilite restante : " << uses_left << "/5)" << endl;
    }

    string getType() const override { return "Weapon"; }
    int getDamage() const { return damage; }
};

// --- Armure ---

class Armor : public Item {
    int    defense;
    string slot; // "casque", "cuirasse", "jambières", "bottes"
    bool   equipped;

public:
    Armor(const string& name, double weight, int value, int def, const string& slot_)
        : Item(name, weight, value), defense(def), slot(slot_), equipped(false) {}

    void display() const override {
        cout << setw(12) << "[Armure] "
             << setw(20) << left << name << right
             << " | Def: " << setw(3) << defense
             << " | Slot: " << setw(10) << slot
             << " | " << (equipped ? "[EQUIPE]  " : "[NON EQUIPE]")
             << " | " << value << " or"
             << " | " << weight << " kg" << endl;
    }

    void use() override {
        equipped = !equipped;
        if (equipped)
            cout << "  Tu equipes " << name << ". +" << defense << " defense." << endl;
        else
            cout << "  Tu retires " << name << "." << endl;
    }

    string getType() const override { return "Armor"; }
    int getDefense() const { return defense; }
};

// --- Potion ---

class Potion : public Item {
    int    healing;
    string potion_type; // "soin", "mana", "endurance"
    int    quantity;

public:
    Potion(const string& name, double weight, int value, int hp, const string& type_, int qty = 1)
        : Item(name, weight, value), healing(hp), potion_type(type_), quantity(qty) {}

    void display() const override {
        cout << setw(12) << "[Potion] "
             << setw(20) << left << name << right
             << " | +" << setw(3) << healing
             << " " << setw(10) << potion_type
             << " | x" << quantity
             << "              | " << value << " or"
             << " | " << weight << " kg" << endl;
    }

    void use() override {
        if (quantity <= 0) {
            cout << "  Plus de " << name << " dans ton sac !" << endl;
            return;
        }
        quantity--;
        cout << "  Tu bois " << name << ". +" << healing
             << " " << potion_type << " !"
             << " (Restantes : " << quantity << ")" << endl;
    }

    string getType() const override { return "Potion"; }
    int    getQuantity() const { return quantity; }
};

// ============================================================
// Inventaire
// ============================================================

class Inventory {
    vector<unique_ptr<Item>> items;
    double max_weight;
    string owner;

public:
    Inventory(const string& player, double max_w)
        : max_weight(max_w), owner(player) {}

    // Ajoute un item (prend la propriete)
    bool addItem(unique_ptr<Item> item) {
        if (totalWeight() + item->getWeight() > max_weight) {
            cout << "  Inventaire trop lourd ! Impossible d'ajouter "
                 << item->getName() << "." << endl;
            return false;
        }
        cout << "  " << item->getName() << " ajoute a l'inventaire." << endl;
        items.push_back(std::move(item));
        return true;
    }

    // Retire un item par index
    void removeItem(int index) {
        if (index < 0 || index >= static_cast<int>(items.size())) {
            cout << "  Index invalide." << endl;
            return;
        }
        cout << "  " << items[index]->getName() << " retire de l'inventaire." << endl;
        items.erase(items.begin() + index);
    }

    // Utilise un item par index
    void useItem(int index) {
        if (index < 0 || index >= static_cast<int>(items.size())) {
            cout << "  Index invalide." << endl;
            return;
        }
        items[index]->use();
    }

    // Affiche tout l'inventaire
    void displayAll() const {
        cout << "\n=== Inventaire de " << owner << " ===" << endl;
        if (items.empty()) {
            cout << "  (vide)" << endl;
        } else {
            for (int i = 0; i < static_cast<int>(items.size()); i++) {
                cout << " [" << i << "] ";
                items[i]->display();
            }
        }
        cout << "  Poids: " << fixed << setprecision(1)
             << totalWeight() << "/" << max_weight << " kg"
             << " | Valeur totale: " << totalValue() << " or" << endl;
    }

    // Statistiques de l'inventaire
    void displayStats() const {
        int weapons = 0, armors = 0, potions = 0;
        int total_dmg = 0, total_def = 0;

        for (const auto& item : items) {
            if (item->getType() == "Weapon") {
                weapons++;
                total_dmg += static_cast<Weapon*>(item.get())->getDamage();
            } else if (item->getType() == "Armor") {
                armors++;
                total_def += static_cast<Armor*>(item.get())->getDefense();
            } else {
                potions++;
            }
        }

        cout << "\n=== Statistiques ===" << endl;
        cout << "  Joueur    : " << owner << endl;
        cout << "  Items     : " << items.size() << endl;
        cout << "  Armes     : " << weapons << " (ATK total: " << total_dmg << ")" << endl;
        cout << "  Armures   : " << armors  << " (DEF total: " << total_def << ")" << endl;
        cout << "  Potions   : " << potions << endl;
        cout << "  Poids     : " << fixed << setprecision(1) << totalWeight() << "/" << max_weight << " kg" << endl;
        cout << "  Valeur    : " << totalValue() << " or" << endl;
    }

    double totalWeight() const {
        double total = 0.0;
        for (const auto& item : items) total += item->getWeight();
        return total;
    }

    int totalValue() const {
        int total = 0;
        for (const auto& item : items) total += item->getValue();
        return total;
    }

    int size() const { return static_cast<int>(items.size()); }
};

// ============================================================
// Helpers : creation d'items predefinies
// ============================================================

void addPresetWeapons(Inventory& inv) {
    inv.addItem(make_unique<Weapon>("Epee longue",    2.5, 150, 45, "melee"));
    inv.addItem(make_unique<Weapon>("Arc court",      1.0,  80, 30, "courte"));
    inv.addItem(make_unique<Weapon>("Arbalête lourde",3.0, 200, 60, "longue"));
}

void addPresetArmors(Inventory& inv) {
    inv.addItem(make_unique<Armor>("Casque de fer",   1.5,  60, 15, "casque"));
    inv.addItem(make_unique<Armor>("Cuirasse d'acier",4.0, 180, 40, "cuirasse"));
    inv.addItem(make_unique<Armor>("Bottes de cuir",  0.8,  30, 10, "bottes"));
}

void addPresetPotions(Inventory& inv) {
    inv.addItem(make_unique<Potion>("Potion de soin",  0.3,  20, 50, "PV",    3));
    inv.addItem(make_unique<Potion>("Elixir de mana",  0.3,  35, 80, "PM",    2));
    inv.addItem(make_unique<Potion>("Potion d'endurance", 0.4, 25, 30, "Stamina", 1));
}

// Menu pour ajouter un item custom
void addCustomItem(Inventory& inv) {
    cout << "\nType d'item :" << endl;
    cout << "  1. Arme" << endl;
    cout << "  2. Armure" << endl;
    cout << "  3. Potion" << endl;
    cout << "Choix : ";

    int type_choice;
    if (!(cin >> type_choice)) {
        cin.clear(); cin.ignore(1000, '\n'); return;
    }
    cin.ignore(1000, '\n');

    string name;
    double weight;
    int value;

    cout << "Nom : ";          getline(cin, name);
    cout << "Poids (kg) : ";   cin >> weight;
    cout << "Valeur (or) : ";  cin >> value;

    if (type_choice == 1) {
        int dmg; string range;
        cout << "Degats : ";       cin >> dmg;
        cin.ignore(1000, '\n');
        cout << "Portee (melee/courte/longue) : "; getline(cin, range);
        inv.addItem(make_unique<Weapon>(name, weight, value, dmg, range));
    } else if (type_choice == 2) {
        int def; string slot;
        cout << "Defense : ";      cin >> def;
        cin.ignore(1000, '\n');
        cout << "Slot (casque/cuirasse/jambières/bottes) : "; getline(cin, slot);
        inv.addItem(make_unique<Armor>(name, weight, value, def, slot));
    } else if (type_choice == 3) {
        int hp, qty; string ptype;
        cout << "Points de soin : "; cin >> hp;
        cout << "Quantite : ";        cin >> qty;
        cin.ignore(1000, '\n');
        cout << "Type (PV/PM/Stamina) : "; getline(cin, ptype);
        inv.addItem(make_unique<Potion>(name, weight, value, hp, ptype, qty));
    } else {
        cout << "Type invalide." << endl;
        cin.ignore(1000, '\n');
    }
}

// ============================================================
// Main : boucle de menu
// ============================================================

int main() {
    cout << "=== Systeme d'Inventaire RPG ===" << endl;
    cout << "Nom du joueur : ";
    string player_name;
    getline(cin, player_name);
    if (player_name.empty()) player_name = "Aventurier";

    Inventory inv(player_name, 20.0); // Capacite : 20 kg

    // Items de depart
    cout << "\nChargement de l'inventaire de depart..." << endl;
    inv.addItem(make_unique<Weapon>("Dague",          0.5,  40, 20, "melee"));
    inv.addItem(make_unique<Armor>("Tunique de cuir", 1.0,  25, 8,  "cuirasse"));
    inv.addItem(make_unique<Potion>("Potion de soin", 0.3,  20, 50, "PV", 2));

    bool running = true;
    while (running) {
        cout << "\n=== Menu ===" << endl;
        cout << "  1. Afficher l'inventaire" << endl;
        cout << "  2. Ajouter des items predefinis" << endl;
        cout << "  3. Ajouter un item personnalise" << endl;
        cout << "  4. Utiliser un item" << endl;
        cout << "  5. Supprimer un item" << endl;
        cout << "  6. Statistiques" << endl;
        cout << "  0. Quitter" << endl;
        cout << "Choix : ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');

        switch (choice) {
        case 1:
            inv.displayAll();
            break;

        case 2: {
            cout << "\nAjouter :" << endl;
            cout << "  1. Pack Armes" << endl;
            cout << "  2. Pack Armures" << endl;
            cout << "  3. Pack Potions" << endl;
            cout << "Choix : ";
            int pack;
            if (!(cin >> pack)) { cin.clear(); cin.ignore(1000, '\n'); break; }
            cin.ignore(1000, '\n');
            if (pack == 1) addPresetWeapons(inv);
            else if (pack == 2) addPresetArmors(inv);
            else if (pack == 3) addPresetPotions(inv);
            else cout << "Choix invalide." << endl;
            break;
        }

        case 3:
            addCustomItem(inv);
            break;

        case 4:
            inv.displayAll();
            if (inv.size() == 0) break;
            {
                cout << "Index de l'item a utiliser : ";
                int idx;
                if (!(cin >> idx)) { cin.clear(); cin.ignore(1000, '\n'); break; }
                cin.ignore(1000, '\n');
                inv.useItem(idx);
            }
            break;

        case 5:
            inv.displayAll();
            if (inv.size() == 0) break;
            {
                cout << "Index de l'item a supprimer : ";
                int idx;
                if (!(cin >> idx)) { cin.clear(); cin.ignore(1000, '\n'); break; }
                cin.ignore(1000, '\n');
                inv.removeItem(idx);
            }
            break;

        case 6:
            inv.displayStats();
            break;

        case 0:
            running = false;
            cout << "Au revoir, " << player_name << " !" << endl;
            break;

        default:
            cout << "Option invalide." << endl;
            break;
        }
    }

    return 0;
}
