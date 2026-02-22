# Operateur Ternaire ❓

## Pourquoi c'est important

En HFT, le ternaire est partout pour les decisions inline : `side = signal > 0 ? BUY : SELL`.
C'est plus compact qu'un if/else pour une affectation simple, et dans du code a haute
performance chaque ligne compte pour la lisibilite. En offensive, pareil : `status = port_open ? "OPEN" : "CLOSED"`. C'est du sucre syntaxique, mais quand tu lis 500 lignes
de code, la concision fait la difference.

---

## Syntaxe

```
  condition ? valeur_si_vrai : valeur_si_faux
```

```
  condition
     │
     ├─ true ──> valeur_si_vrai
     │
     └─ false ─> valeur_si_faux
```

C'est un if/else compresse en une seule expression.

```cpp
// Avec if/else (4 lignes)
std::string direction;
if (signal > 0) {
    direction = "BUY";
} else {
    direction = "SELL";
}

// Avec ternaire (1 ligne)
std::string direction = (signal > 0) ? "BUY" : "SELL";
```

---

## Quand utiliser le ternaire ?

```
  BON usage (simple, lisible) :
 ┌──────────────────────────────────────────────┐
 │ int max = (a > b) ? a : b;                  │
 │ std::string s = (x > 0) ? "positif" : "neg";│
 │ double fee = vip ? 0.0005 : 0.001;          │
 └──────────────────────────────────────────────┘

  MAUVAIS usage (illisible, a eviter) :
 ┌──────────────────────────────────────────────┐
 │ int r = a > b ? (c > d ? c : d) : (e > f    │
 │         ? e : f);  // Illisible !            │
 └──────────────────────────────────────────────┘
```

**Regle** : si le ternaire ne tient pas sur une ligne ou est dur a lire,
utilise un if/else. Le ternaire est fait pour les cas simples.

---

## Ternaire imbrique (avec precaution)

On peut imbriquer un ternaire dans un autre. Maximum un niveau sinon c'est
illisible.

```cpp
int score = 85;

// Un niveau d'imbrication : encore acceptable
std::string grade = (score >= 90) ? "A"
                  : (score >= 80) ? "B"
                  : (score >= 70) ? "C"
                  :                 "F";

std::cout << "Grade : " << grade << std::endl;  // "B"
```

L'indentation aide a la lisibilite. Mais si ca devient plus complexe,
passe en if/else.

---

## Ternaire dans cout

Le ternaire marche directement dans les expressions, y compris `cout` :

```cpp
int temperature = 35;
std::cout << "Il fait " << ((temperature > 30) ? "chaud" : "frais") << std::endl;

bool logged_in = true;
std::cout << "Status : " << (logged_in ? "connecte" : "deconnecte") << std::endl;
```

Les parentheses autour du ternaire dans `cout` sont importantes pour eviter
les ambiguites avec `<<`.

---

## Exemple complet commente

```cpp
#include <iostream>
#include <string>

int main() {
    // Donnees d'un trade
    double signal_strength = -0.75;  // Negatif = bearish, positif = bullish
    double prix = 150.25;
    int position_actuelle = 100;     // Nombre d'actions detenues

    // Direction determinee par le ternaire
    std::string direction = (signal_strength > 0) ? "BUY" : "SELL";

    // Quantite : plus le signal est fort, plus on trade
    double abs_signal = (signal_strength > 0) ? signal_strength : -signal_strength;
    int quantite = (abs_signal > 0.5) ? 100 : 50;

    // Urgence du signal
    std::string urgence = (abs_signal > 0.8) ? "URGENT"
                        : (abs_signal > 0.5) ? "NORMAL"
                        :                      "FAIBLE";

    std::cout << "Signal  : " << signal_strength << std::endl;
    std::cout << "Action  : " << direction << " " << quantite << " @ " << prix << std::endl;
    std::cout << "Urgence : " << urgence << std::endl;

    // Position apres trade
    int new_position = (direction == "BUY")
                     ? position_actuelle + quantite
                     : position_actuelle - quantite;

    std::cout << "Position: " << position_actuelle << " -> " << new_position << std::endl;
    std::cout << "Statut  : " << ((new_position > 0) ? "LONG" : "FLAT/SHORT") << std::endl;

    return 0;
}
```

---

## Checkpoint 

1. **Reecris avec un ternaire : `int r; if (a > b) r = a; else r = b;`**
   > `int r = (a > b) ? a : b;`

2. **Quand faut-il eviter le ternaire ?**
   > Quand la condition ou les valeurs sont complexes, quand il y a plus d'un niveau d'imbrication, ou quand ca nuit a la lisibilite. En cas de doute, if/else.

3. **Pourquoi mettre des parentheses autour du ternaire dans `cout` ?**
   > Pour eviter l'ambiguite avec l'operateur `<<`. Sans parentheses, le compilateur peut interpreter l'expression differemment de ce qu'on veut.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret.
