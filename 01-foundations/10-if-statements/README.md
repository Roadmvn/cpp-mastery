# Conditions if/else 🔀

## Pourquoi c'est important

En HFT, chaque decision de trading est un `if` : si le prix passe sous le seuil, acheter.
Si le spread depasse la limite, annuler. Si le risque depasse le budget, couper la position.
Un `if` mal ecrit et tu rates un signal ou pire, tu executes au mauvais moment. En offensive,
les conditions controlent tout : si le port est ouvert, scanner. Si le service est
vulnerable, exploiter. Si la detection est active, pivoter.

---

## if basique

```cpp
if (condition) {
    // Execute si condition est vraie (true / non-zero)
}
```

```
  condition
     │
     ▼
  ┌──────┐   true    ┌────────────┐
  │ test │ ────────> │  bloc if   │ ───> suite
  └──────┘           └────────────┘
     │ false
     ▼
   suite
```

```cpp
double prix = 150.25;
double seuil = 150.00;

if (prix > seuil) {
    std::cout << "Prix au-dessus du seuil !" << std::endl;
}
```

---

## if / else

```cpp
if (condition) {
    // Si vrai
} else {
    // Si faux
}
```

```
  condition
     │
     ├─ true ──> bloc if ───────> suite
     │
     └─ false ─> bloc else ─────> suite
```

```cpp
int volume = 5000;
int seuil_volume = 10000;

if (volume >= seuil_volume) {
    std::cout << "Volume suffisant pour trader" << std::endl;
} else {
    std::cout << "Volume trop faible, on attend" << std::endl;
}
```

---

## if / else if / else

Quand tu as plus de 2 cas, enchaine les `else if`. Le premier qui matche s'execute,
les autres sont ignores.

```
  condition1
     │
     ├─ true ──> bloc 1 ───────────────> suite
     │
     └─ false ─> condition2
                    │
                    ├─ true ──> bloc 2 ─> suite
                    │
                    └─ false ─> else ───> suite
```

```cpp
double variation = -2.5;  // Variation du prix en %

if (variation > 1.0) {
    std::cout << "Hausse significative -> SIGNAL ACHAT" << std::endl;
} else if (variation < -1.0) {
    std::cout << "Baisse significative -> SIGNAL VENTE" << std::endl;
} else {
    std::cout << "Variation neutre -> PAS DE SIGNAL" << std::endl;
}
```

---

## Conditions imbriquees

On peut mettre des `if` dans des `if`. Utile mais attention a la lisibilite :
pas plus de 2-3 niveaux sinon c'est illisible.

```cpp
bool marche_ouvert = true;
double prix = 152.30;
double budget = 20000;
int quantite = 100;

if (marche_ouvert) {
    double cout_total = prix * quantite;
    if (cout_total <= budget) {
        std::cout << "ACHAT : " << quantite << " @ " << prix << std::endl;
    } else {
        std::cout << "BUDGET INSUFFISANT" << std::endl;
    }
} else {
    std::cout << "MARCHE FERME" << std::endl;
}
```

---

## Operateurs de comparaison (rappel)

```
  Operateur   Signification       Exemple
 ┌───────────┬───────────────────┬──────────────────┐
 │    ==     │ Egal a            │ prix == 100.0    │
 │    !=     │ Different de      │ status != "OK"   │
 │    >      │ Superieur         │ volume > 1000    │
 │    <      │ Inferieur         │ spread < 0.01    │
 │    >=     │ Superieur ou egal │ age >= 18        │
 │    <=     │ Inferieur ou egal │ risk <= max_risk │
 └───────────┴───────────────────┴──────────────────┘
```

**Piege classique** : `=` c'est l'affectation, `==` c'est la comparaison.
`if (x = 5)` assigne 5 a x et est toujours vrai. Le compilateur previent
avec un warning.

---

## Exemple complet commente

```cpp
#include <iostream>
#include <string>

int main() {
    double prix_actuel = 148.50;
    double prix_moyen  = 150.00;
    int volume = 15000;
    int seuil_volume = 10000;

    std::cout << "=== Analyse de Signal ===" << std::endl;
    std::cout << "Prix : " << prix_actuel << " | Moyenne : " << prix_moyen << std::endl;
    std::cout << "Volume : " << volume << std::endl;

    // Premiere condition : le volume doit etre suffisant
    if (volume >= seuil_volume) {
        // Deuxieme condition : direction du signal
        double ecart = ((prix_actuel - prix_moyen) / prix_moyen) * 100;

        if (ecart > 1.0) {
            std::cout << "SIGNAL : ACHAT (ecart +" << ecart << "%)" << std::endl;
        } else if (ecart < -1.0) {
            std::cout << "SIGNAL : VENTE (ecart " << ecart << "%)" << std::endl;
        } else {
            std::cout << "SIGNAL : NEUTRE (ecart " << ecart << "%)" << std::endl;
        }
    } else {
        std::cout << "PAS DE SIGNAL : volume insuffisant" << std::endl;
    }

    return 0;
}
```

---

## Checkpoint ✅

1. **Que se passe-t-il si tu ecris `if (x = 5)` au lieu de `if (x == 5)` ?**
   > `x = 5` est une affectation, pas une comparaison. x prend la valeur 5, et comme 5 est non-zero (true), le bloc if s'execute toujours. C'est un bug classique.

2. **Combien de niveaux d'imbrication maximum recommandes ?**
   > 2 a 3 maximum. Au-dela, le code devient illisible. Il vaut mieux utiliser des `else if` ou extraire la logique dans des fonctions.

3. **Dans une chaine `if / else if / else`, combien de blocs s'executent ?**
   > Un seul. Le premier dont la condition est vraie. Si aucune condition n'est vraie, le bloc `else` (s'il existe) s'execute.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret.
