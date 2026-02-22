# Operateurs Arithmetiques

## Pourquoi c'est important

En HFT, chaque calcul de P&L, spread, ou taille de position passe par des operations
arithmetiques. Une erreur de priorite ou un overflow non detecte et tu perds de l'argent
reel. En offensive, manipuler des adresses memoire c'est de l'arithmetique brute sur des
entiers -- un decalage de 1 et tu lis la mauvaise zone memoire.

---

## Les operateurs de base

```
  Operateur    Nom              Exemple      Resultat
 ┌───────────┬─────────────────┬────────────┬──────────┐
 │     +     │ Addition        │  10 + 3    │    13    │
 │     -     │ Soustraction    │  10 - 3    │     7    │
 │     *     │ Multiplication  │  10 * 3    │    30    │
 │     /     │ Division        │  10 / 3    │     3    │  <-- Division entiere !
 │     %     │ Modulo (reste)  │  10 % 3    │     1    │
 └───────────┴─────────────────┴────────────┴──────────┘
```

**Piege classique** : la division entre deux `int` donne un `int`. Le resultat est tronque,
pas arrondi.

```cpp
int a = 10 / 3;      // 3 (pas 3.333...)
double b = 10.0 / 3; // 3.333... (un des operandes est double)
double c = 10 / 3;   // 3.0 (division entiere PUIS conversion en double)
```

Le modulo `%` ne marche qu'avec des entiers. Pour les flottants, utilise `fmod()` du
chapitre 09.

---

## Increment / Decrement (++ et --)

```
  Position       Syntaxe      Effet
 ┌─────────────┬────────────┬──────────────────────────────┐
 │ Pre-incr.   │  ++i       │ Incremente PUIS retourne     │
 │ Post-incr.  │  i++       │ Retourne PUIS incremente     │
 │ Pre-decr.   │  --i       │ Decremente PUIS retourne     │
 │ Post-decr.  │  i--       │ Retourne PUIS decremente     │
 └─────────────┴────────────┴──────────────────────────────┘
```

```cpp
int i = 5;
int a = ++i;  // i passe a 6, a = 6
int b = i++;  // b = 6 (valeur avant), i passe a 7
```

En HFT, `++i` est prefere a `i++` pour les iterateurs car il evite une copie temporaire.
Pour les `int` c'est identique, mais la bonne habitude se prend tot.

---

## Operateurs d'affectation composes

Ces raccourcis combinent une operation et une affectation :

```cpp
int x = 100;
x += 10;   // x = x + 10  -> 110
x -= 5;    // x = x - 5   -> 105
x *= 2;    // x = x * 2   -> 210
x /= 3;    // x = x / 3   -> 70
x %= 4;    // x = x % 4   -> 2
```

---

## Priorite des operateurs (rappel maths)

```
  Priorite (haute -> basse)
 ┌─────────────────────────────┐
 │  1. ()         Parentheses  │
 │  2. ++ --      Unaires      │
 │  3. * / %      Multiplic.   │
 │  4. + -        Addition     │
 │  5. = += -=    Affectation  │
 └─────────────────────────────┘
```

En cas de doute, mets des parentheses. Code lisible > code malin.

---

## Exemple complet commente

```cpp
#include <iostream>

int main() {
    // Donnees d'un trade
    double entry_price = 150.25;    // Prix d'achat
    double exit_price  = 152.80;    // Prix de vente
    int    quantity    = 100;        // Nombre d'actions
    double fee_rate   = 0.001;      // Frais : 0.1%

    // Calcul du P&L brut
    double pnl_brut = (exit_price - entry_price) * quantity;

    // Calcul des frais (achat + vente)
    double frais_achat = entry_price * quantity * fee_rate;
    double frais_vente = exit_price * quantity * fee_rate;
    double frais_total = frais_achat + frais_vente;

    // P&L net
    double pnl_net = pnl_brut - frais_total;

    // Rendement en pourcentage
    double rendement = (pnl_net / (entry_price * quantity)) * 100;

    std::cout << "--- Rapport de Trade ---" << std::endl;
    std::cout << "P&L brut  : " << pnl_brut << " USD" << std::endl;
    std::cout << "Frais     : " << frais_total << " USD" << std::endl;
    std::cout << "P&L net   : " << pnl_net << " USD" << std::endl;
    std::cout << "Rendement : " << rendement << " %" << std::endl;

    return 0;
}
```

Sortie :
```
--- Rapport de Trade ---
P&L brut  : 255 USD
Frais     : 30.305 USD
P&L net   : 224.695 USD
Rendement : 1.49497 %
```

---

## Checkpoint

1. **Que donne `7 / 2` en C++ si les deux operandes sont des `int` ?**
   > `3`. La division entiere tronque le resultat. Pour obtenir `3.5`, il faut au moins un `double` : `7.0 / 2`.

2. **Quelle est la difference entre `++i` et `i++` ?**
   > `++i` incremente d'abord puis retourne la nouvelle valeur. `i++` retourne l'ancienne valeur puis incremente. En pratique, ca compte quand l'expression est utilisee dans une affectation ou un argument.

3. **Que vaut `x` apres : `int x = 10; x += 5; x *= 2;` ?**
   > `x = 30`. D'abord `x += 5` donne 15, puis `x *= 2` donne 30.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret.
