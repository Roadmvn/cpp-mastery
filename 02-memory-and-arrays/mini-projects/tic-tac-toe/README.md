# Mini-projet : Morpion (Tic-Tac-Toe)

## Objectif

Implementer un jeu de morpion complet en 2 joueurs avec un tableau 3x3, detection de victoire et match nul, et affichage ASCII.

## Concepts utilises

- Array 2D `char board[3][3]`
- Boucles imbriquees pour la detection de victoire
- Input utilisateur et validation
- Logique de jeu tour par tour

## Schema ASCII du plateau

```
       Col 0   Col 1   Col 2
         |       |
Lig 0    1   |   2   |   3
       ---+---+---+---+---
Lig 1    4   |   5   |   6
       ---+---+---+---+---
Lig 2    7   |   8   |   9

Les cases sont numerotees 1-9 pour la saisie.
Mapping : case N -> ligne (N-1)/3, colonne (N-1)%3
```

## Regles de victoire

```
Lignes :     Colonnes :    Diagonales :

X X X        X . .         X . .     . . X
. . .        X . .         . X .     . X .
. . .        X . .         . . X     X . .

8 combinaisons gagnantes au total.
Match nul : plateau plein, personne n'a gagne.
```

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o tictactoe main.cpp && ./tictactoe
```
