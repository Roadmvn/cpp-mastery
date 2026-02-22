# Switch / Case 🔀

## Pourquoi c'est important

En HFT, le type d'ordre (MARKET, LIMIT, STOP) determine le traitement. Un `switch` sur
un enum est plus rapide qu'une chaine de `if/else` car le compilateur peut generer une
table de saut (jump table). En offensive, les menus d'outils, le parsing de protocoles,
le dispatch de commandes -- tout ca c'est du switch. Chaque byte d'un protocole peut
etre route avec un switch ultra-rapide.

---

## Syntaxe de base

```cpp
switch (expression) {
    case valeur1:
        // Code si expression == valeur1
        break;
    case valeur2:
        // Code si expression == valeur2
        break;
    default:
        // Code si aucun case ne matche
        break;
}
```

```
  expression
     │
     ▼
  ┌──────────────────────────────────┐
  │ case 1 ? ──> bloc 1 ──> break ──┼──> suite
  │ case 2 ? ──> bloc 2 ──> break ──┼──> suite
  │ case 3 ? ──> bloc 3 ──> break ──┼──> suite
  │ default  ──> bloc def ─> break ──┼──> suite
  └──────────────────────────────────┘
```

**Important** : `expression` doit etre un type integral (`int`, `char`, `enum`).
Les `string` et `double` ne sont PAS supportes dans un switch.

---

## Le piege du break oublie (fall-through)

Sans `break`, l'execution "tombe" dans le case suivant. C'est rarement ce qu'on veut.

```cpp
int x = 2;
switch (x) {
    case 1:
        std::cout << "Un" << std::endl;
        // Pas de break -> tombe dans case 2
    case 2:
        std::cout << "Deux" << std::endl;
        // Pas de break -> tombe dans case 3
    case 3:
        std::cout << "Trois" << std::endl;
        break;
}
// Affiche : "Deux" puis "Trois" (fall-through)
```

Parfois le fall-through est voulu (grouper des cases) :

```cpp
char grade = 'B';
switch (grade) {
    case 'A':
    case 'B':  // A et B partagent le meme traitement
        std::cout << "Bon" << std::endl;
        break;
    case 'C':
        std::cout << "Moyen" << std::endl;
        break;
    default:
        std::cout << "Insuffisant" << std::endl;
        break;
}
```

---

## switch vs if-else -- Quand utiliser quoi ?

```
  Utilise switch quand :              Utilise if-else quand :
 ┌────────────────────────────┐     ┌─────────────────────────────┐
 │ Valeurs discretes connues  │     │ Plages de valeurs (> < >=)  │
 │ Type int, char, enum       │     │ Conditions complexes        │
 │ Beaucoup de cas (> 3-4)    │     │ Types string, double        │
 │ Comparaison d'egalite      │     │ Combinaisons logiques       │
 └────────────────────────────┘     └─────────────────────────────┘
```

---

## Exemple complet commente

```cpp
#include <iostream>
#include <string>

int main() {
    // Type d'ordre de trading (simule par un int)
    // 1 = MARKET, 2 = LIMIT, 3 = STOP, 4 = STOP_LIMIT
    int order_type = 2;
    double prix = 150.00;

    std::cout << "=== Traitement d'Ordre ===" << std::endl;

    switch (order_type) {
        case 1:
            std::cout << "MARKET ORDER" << std::endl;
            std::cout << "Execution immediate au meilleur prix" << std::endl;
            break;

        case 2:
            std::cout << "LIMIT ORDER @ " << prix << std::endl;
            std::cout << "Execute seulement si prix <= " << prix << std::endl;
            break;

        case 3:
            std::cout << "STOP ORDER @ " << prix << std::endl;
            std::cout << "Declenche un market order si prix atteint " << prix << std::endl;
            break;

        case 4:
            std::cout << "STOP LIMIT ORDER @ " << prix << std::endl;
            std::cout << "Declenche un limit order si prix atteint " << prix << std::endl;
            break;

        default:
            std::cout << "TYPE INCONNU (" << order_type << ")" << std::endl;
            std::cout << "Ordre rejete" << std::endl;
            break;
    }

    return 0;
}
```

---

## Checkpoint 

1. **Que se passe-t-il si tu oublies un `break` dans un case ?**
   > L'execution "tombe" (fall-through) dans le case suivant et execute son code aussi, jusqu'au prochain `break` ou la fin du switch.

2. **Peut-on utiliser un `string` dans un switch ?**
   > Non. Le switch ne supporte que les types integraux : `int`, `char`, `enum`, `bool`. Pour les strings, il faut utiliser des `if/else if`.

3. **Quand preferer un switch a une chaine de if/else ?**
   > Quand on compare une seule variable a plusieurs valeurs discretes connues (entiers, caracteres, enums). Le switch est plus lisible et potentiellement plus performant (jump table).

---

Passe aux exercices dans `exercise.cpp` quand t'es pret.
