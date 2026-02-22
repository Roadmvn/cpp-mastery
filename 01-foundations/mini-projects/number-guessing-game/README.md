# Mini-Projet : Jeu de Devinette 🎲

## Description

Le programme genere un nombre aleatoire entre 1 et 100.
L'utilisateur doit le deviner avec des indices "plus haut" / "plus bas".
Un compteur d'essais mesure la performance.

## Concepts utilises

- **Nombres aleatoires** (rand, srand, time)
- **Boucle do-while** (boucle de jeu)
- **Conditions if/else** (indices)
- **Compteur** (variable incrementee)
- **Validation d'entree** (plage 1-100)

## Compilation et execution

```bash
g++ -std=c++17 -o guessing-game main.cpp
./guessing-game
```

## Regles du jeu

1. Le programme choisit un nombre entre 1 et 100
2. L'utilisateur entre sa proposition
3. Le programme repond "Plus haut !" ou "Plus bas !"
4. Quand le nombre est trouve, le score (nombre d'essais) s'affiche
5. Option pour rejouer
