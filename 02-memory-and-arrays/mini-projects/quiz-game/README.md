# Mini-projet : Quiz Interactif

## Objectif

Implementer un quiz interactif avec 10 questions a choix multiples stockees dans des arrays, suivi du score et affichage du resultat final.

## Concepts utilises

- Arrays de strings (`string questions[]`, `string answers[]`)
- Arrays 2D de strings pour les choix multiples
- Boucles et conditions
- Compteur de score

## Structure des donnees

```
questions[10]      : Les questions
choices[10][4]     : 4 choix (A/B/C/D) par question
correct[10]        : La bonne reponse ('A', 'B', 'C' ou 'D')

questions[0] = "Que signifie HTML ?"
choices[0][0] = "A) HyperText Markup Language"
choices[0][1] = "B) High Tech Modern Language"
choices[0][2] = "C) HyperText Machine Link"
choices[0][3] = "D) Home Tool Markup Language"
correct[0]   = 'A'
```

## Systeme de score

```
Score final      Evaluation
-----------      ----------
10/10            Parfait !
8-9/10           Excellent !
6-7/10           Bien !
4-5/10           Moyen...
0-3/10           Revise tes bases !
```

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o quiz main.cpp && ./quiz
```
