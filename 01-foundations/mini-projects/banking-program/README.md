# Mini-Projet : Programme Bancaire 🏦

## Description

Simulation d'un compte bancaire avec depot, retrait, consultation
du solde et historique des transactions. Gestion des erreurs
(solde insuffisant, montants invalides).

## Concepts utilises

- **Variables et types** (double pour le solde, string pour l'historique)
- **Boucle do-while** (menu principal)
- **Fonctions** (une par operation)
- **Tableaux** (historique des transactions)
- **Switch** (selection d'operation)
- **Validation** (montants positifs, solde suffisant)
- **Variable static** (compteur de transactions)

## Compilation et execution

```bash
g++ -std=c++17 -o banking main.cpp
./banking
```

## Fonctionnalites

- Depot (credit)
- Retrait (debit avec verification de solde)
- Consultation du solde
- Historique des 20 dernieres transactions
- Validation de tous les montants
