# Mini-Projet : Pierre-Feuille-Ciseaux 

## Description

Jeu classique Pierre-Feuille-Ciseaux contre l'ordinateur.
Mode "meilleur des 3" ou "meilleur des 5" avec score en temps reel.

## Concepts utilises

- **Nombres aleatoires** (choix de l'ordinateur)
- **Boucle while** (manches jusqu'a victoire)
- **Fonctions** (logique de jeu, affichage)
- **Switch** (resolution des manches)
- **Conditions** (qui gagne?)
- **Strings** (affichage des choix)

## Compilation et execution

```bash
g++ -std=c++17 -o rps main.cpp
./rps
```

## Regles

- Pierre bat Ciseaux
- Ciseaux bat Feuille
- Feuille bat Pierre
- Egalite = la manche ne compte pas
- Premier a atteindre le score cible gagne
