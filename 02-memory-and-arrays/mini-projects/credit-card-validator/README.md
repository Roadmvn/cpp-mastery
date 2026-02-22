# Mini-projet : Validateur de Carte Bancaire (Algorithme de Luhn)

## Objectif

Implementer l'**algorithme de Luhn** pour verifier si un numero de carte bancaire est valide. C'est l'algorithme utilise par Visa, Mastercard, American Express depuis 1954.

## Concepts utilises

- Arrays de chiffres
- Operateurs modulo et division entiere
- Boucles et index
- Fonctions de validation

## L'algorithme de Luhn

```
Numero : 4 5 3 9 5 7 8 8 0 3 4 3 6 4 6 7
         ← Parcours de droite a gauche ←

Etape 1 : Doubler un chiffre sur deux (en partant de l'avant-dernier)
          Positions paires (0-indexed depuis la droite) : inchangees
          Positions impaires                            : x2

Etape 2 : Si le double depasse 9, soustraire 9

Etape 3 : Sommer tous les chiffres

Etape 4 : Si somme % 10 == 0 → VALIDE
```

## Schema ASCII

```
Numero original :  4  5  3  9  5  7  8  8  0  3  4  3  6  4  6  7
                   |     |     |     |     |     |     |     |
Index depuis droite: 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
                   |     |     |     |     |     |     |     |
Pair/Impair (droite): I  P  I  P  I  P  I  P  I  P  I  P  I  P  I  P

Doublement (impairs):
  5*2=10 → 10-9=1    9*2=18 → 18-9=9    7*2=14 → 14-9=5
  8*2=16 → 16-9=7    3*2=6              3*2=6     4*2=8

Valeurs finales :  4  1  3  9  5  5  8  7  0  6  4  6  6  8  6  7
                   ↑___________________________________________________↑
                                         Somme = 85

85 % 10 = 5 ≠ 0 → INVALIDE (exemple modifie pour la demo)

Numero valide : 4532015112830366
  Somme finale = 40 → 40 % 10 = 0 → VALIDE
```

## Numeros de test

| Numero               | Type        | Attendu  |
|----------------------|-------------|----------|
| 4532015112830366     | Visa        | VALIDE   |
| 5425233430109903     | Mastercard  | VALIDE   |
| 374251018720955      | Amex        | VALIDE   |
| 1234567890123456     | Fictif      | INVALIDE |
| 0000000000000000     | Zeros       | INVALIDE |

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o validator main.cpp && ./validator
```
