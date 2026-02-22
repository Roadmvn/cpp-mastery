# Mini-Projet : Calculatrice CLI 🧮

## Description

Calculatrice en ligne de commande avec un menu interactif.
Supporte les operations de base (+, -, *, /, %), la puissance,
et gere proprement la division par zero.

## Concepts utilises

- **Variables et types** (int, double, char)
- **Boucle do-while** (menu principal)
- **Switch** (selection d'operation)
- **Fonctions** (une par operation)
- **Validation d'entree** (division par zero)
- **Break/continue** (controle de flux)

## Compilation et execution

```bash
g++ -std=c++17 -o calculator main.cpp
./calculator
```

## Fonctionnalites

- Addition, soustraction, multiplication, division
- Modulo (reste de la division entiere)
- Puissance (x^n)
- Gestion de la division par zero
- Menu en boucle jusqu'a ce que l'utilisateur quitte
