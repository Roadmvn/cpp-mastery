// ============================================================
// MINI-PROJET : Programme Bancaire
// Compile : g++ -std=c++17 -o banking main.cpp
// ============================================================

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Constantes
const int MAX_HISTORY = 20;

// Etat du compte
double balance = 0.0;
string history[MAX_HISTORY];
int history_count = 0;

// Prototypes
void deposit(double amount);
void withdraw(double amount);
void show_balance();
void show_history();
void add_to_history(string entry);
int get_transaction_id();

int main() {
    int choix;

    cout << fixed << setprecision(2);

    cout << "========================================" << endl;
    cout << "  Programme Bancaire" << endl;
    cout << "========================================" << endl;
    cout << "Bienvenue ! Votre compte est pret." << endl;

    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Deposer" << endl;
        cout << "2. Retirer" << endl;
        cout << "3. Solde" << endl;
        cout << "4. Historique" << endl;
        cout << "5. Quitter" << endl;
        cout << "Choix : ";
        cin >> choix;

        switch (choix) {
            case 1: {
                double montant;
                cout << "Montant a deposer : ";
                cin >> montant;
                deposit(montant);
                break;
            }
            case 2: {
                double montant;
                cout << "Montant a retirer : ";
                cin >> montant;
                withdraw(montant);
                break;
            }
            case 3:
                show_balance();
                break;
            case 4:
                show_history();
                break;
            case 5:
                cout << "\nSolde final : $" << balance << endl;
                cout << "Merci et a bientot !" << endl;
                break;
            default:
                cout << "Choix invalide." << endl;
        }

    } while (choix != 5);

    return 0;
}

// Compteur de transactions
int get_transaction_id() {
    static int id = 0;
    return ++id;
}

// Ajouter une entree a l'historique
void add_to_history(string entry) {
    if (history_count < MAX_HISTORY) {
        history[history_count] = entry;
        history_count++;
    } else {
        // Decaler tout pour faire de la place
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            history[i] = history[i + 1];
        }
        history[MAX_HISTORY - 1] = entry;
    }
}

// Depot
void deposit(double amount) {
    if (amount <= 0) {
        cout << "Erreur : le montant doit etre positif." << endl;
        return;
    }

    int id = get_transaction_id();
    balance += amount;

    string entry = "#" + to_string(id) + " DEPOT    +$" + to_string(amount).substr(0, to_string(amount).find('.') + 3)
                   + "  (solde: $" + to_string(balance).substr(0, to_string(balance).find('.') + 3) + ")";
    add_to_history(entry);

    cout << "Depot de $" << amount << " effectue." << endl;
    cout << "Nouveau solde : $" << balance << endl;
}

// Retrait
void withdraw(double amount) {
    if (amount <= 0) {
        cout << "Erreur : le montant doit etre positif." << endl;
        return;
    }
    if (amount > balance) {
        cout << "Erreur : solde insuffisant." << endl;
        cout << "Solde actuel : $" << balance << endl;
        cout << "Montant demande : $" << amount << endl;
        return;
    }

    int id = get_transaction_id();
    balance -= amount;

    string entry = "#" + to_string(id) + " RETRAIT  -$" + to_string(amount).substr(0, to_string(amount).find('.') + 3)
                   + "  (solde: $" + to_string(balance).substr(0, to_string(balance).find('.') + 3) + ")";
    add_to_history(entry);

    cout << "Retrait de $" << amount << " effectue." << endl;
    cout << "Nouveau solde : $" << balance << endl;
}

// Afficher le solde
void show_balance() {
    cout << "\n  ========================" << endl;
    cout << "  Solde actuel : $" << balance << endl;
    cout << "  ========================" << endl;
}

// Afficher l'historique
void show_history() {
    cout << "\n  === HISTORIQUE ===" << endl;
    if (history_count == 0) {
        cout << "  Aucune transaction." << endl;
    } else {
        for (int i = 0; i < history_count; i++) {
            cout << "  " << history[i] << endl;
        }
    }
    cout << "  ==================" << endl;
    cout << "  Total : " << history_count << " transaction(s)" << endl;
}
