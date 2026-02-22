# Operateurs Logiques 🧠

## Pourquoi c'est important

En HFT, chaque decision de trading combine plusieurs conditions : prix dans la fourchette
ET volume suffisant ET risque acceptable ET marche ouvert. Rater un `&&` ou confondre
avec `||` et tu trades quand tu devrais pas. En offensive, c'est pareil : cible accessible
ET port ouvert ET service vulnerable ET pas de WAF. Les operateurs logiques sont le
ciment de toute logique conditionnelle.

---

## Les 3 operateurs logiques

```
  Operateur   Nom     Description
 ┌───────────┬───────┬─────────────────────────────────┐
 │    &&     │  ET   │ Vrai si les DEUX sont vrais     │
 │    ||     │  OU   │ Vrai si AU MOINS UN est vrai    │
 │    !      │  NON  │ Inverse la valeur (vrai <-> faux)│
 └───────────┴───────┴─────────────────────────────────┘
```

---

## && (ET logique)

Les deux conditions doivent etre vraies.

```
  A       B       A && B
 ┌───────┬───────┬────────┐
 │ true  │ true  │ true   │
 │ true  │ false │ false  │
 │ false │ true  │ false  │
 │ false │ false │ false  │
 └───────┴───────┴────────┘
```

```cpp
double prix = 150.0;
int volume = 20000;

if (prix > 100.0 && volume > 10000) {
    std::cout << "Conditions reunies pour trader" << std::endl;
}
```

---

## || (OU logique)

Au moins une condition doit etre vraie.

```
  A       B       A || B
 ┌───────┬───────┬────────┐
 │ true  │ true  │ true   │
 │ true  │ false │ true   │
 │ false │ true  │ true   │
 │ false │ false │ false  │
 └───────┴───────┴────────┘
```

```cpp
int port = 443;

if (port == 80 || port == 443) {
    std::cout << "Port web detecte" << std::endl;
}
```

---

## ! (NON logique)

Inverse la valeur booleenne.

```cpp
bool marche_ouvert = false;

if (!marche_ouvert) {
    std::cout << "Marche ferme, pas de trading" << std::endl;
}
```

---

## Court-circuit (short-circuit evaluation)

C'est un concept crucial pour la performance et la securite.

```
  &&  : Si la premiere condition est false, la deuxieme
        n'est PAS evaluee (le resultat est forcement false)

  ||  : Si la premiere condition est true, la deuxieme
        n'est PAS evaluee (le resultat est forcement true)
```

```
  a && b
  ┌─────┐
  │  a  │──false──> resultat = false (b jamais evalue)
  └──┬──┘
     │ true
     ▼
  ┌─────┐
  │  b  │──> resultat = b
  └─────┘

  a || b
  ┌─────┐
  │  a  │──true───> resultat = true (b jamais evalue)
  └──┬──┘
     │ false
     ▼
  ┌─────┐
  │  b  │──> resultat = b
  └─────┘
```

Le court-circuit est utile pour eviter des operations couteuses ou dangereuses :

```cpp
// Si diviseur est 0, la division n'est JAMAIS executee
if (diviseur != 0 && (nombre / diviseur) > 10) {
    std::cout << "Ratio superieur a 10" << std::endl;
}

// Si le pointeur est nul, on ne deference pas (securite)
// (apercu, on verra les pointeurs plus tard)
// if (ptr != nullptr && ptr->value > 0) { ... }
```

---

## Ordre d'evaluation et priorite

```
  Priorite (haute -> basse)
 ┌────────────────────────────┐
 │  1. !      (NON)           │
 │  2. &&     (ET)            │
 │  3. ||     (OU)            │
 └────────────────────────────┘

  Attention :
  a || b && c  est evalue comme  a || (b && c)
  PAS comme  (a || b) && c
```

En cas de doute, **mets des parentheses**. C'est toujours plus clair.

```cpp
bool a = true, b = false, c = true;

// Sans parentheses : a || (b && c) = true || false = true
bool r1 = a || b && c;

// Avec parentheses : (a || b) && c = true && true = true
bool r2 = (a || b) && c;

// Ici les deux donnent true, mais ce n'est pas toujours le cas
```

---

## Exemple complet commente

```cpp
#include <iostream>
#include <string>

int main() {
    // Parametres de trading
    double prix = 148.50;
    double prix_min = 140.0;
    double prix_max = 160.0;
    int volume = 25000;
    int volume_min = 10000;
    bool marche_ouvert = true;
    double risque_actuel = 0.03;  // 3%
    double risque_max = 0.05;     // 5%

    std::cout << "=== Validation Pre-Trade ===" << std::endl;

    // Condition 1 : prix dans la fourchette
    bool prix_ok = (prix >= prix_min) && (prix <= prix_max);
    std::cout << "Prix dans la fourchette : " << (prix_ok ? "OUI" : "NON") << std::endl;

    // Condition 2 : volume suffisant
    bool volume_ok = volume >= volume_min;
    std::cout << "Volume suffisant       : " << (volume_ok ? "OUI" : "NON") << std::endl;

    // Condition 3 : risque acceptable
    bool risque_ok = risque_actuel < risque_max;
    std::cout << "Risque acceptable      : " << (risque_ok ? "OUI" : "NON") << std::endl;

    // Condition 4 : marche ouvert
    std::cout << "Marche ouvert          : " << (marche_ouvert ? "OUI" : "NON") << std::endl;

    // Decision finale : TOUTES les conditions doivent etre vraies
    bool peut_trader = prix_ok && volume_ok && risque_ok && marche_ouvert;

    std::cout << "\nDecision : "
              << (peut_trader ? "TRADE AUTORISE" : "TRADE BLOQUE")
              << std::endl;

    // Raison du blocage (si bloque)
    if (!peut_trader) {
        std::cout << "Raison(s) : ";
        if (!prix_ok) std::cout << "[PRIX HORS FOURCHETTE] ";
        if (!volume_ok) std::cout << "[VOLUME INSUFFISANT] ";
        if (!risque_ok) std::cout << "[RISQUE DEPASSE] ";
        if (!marche_ouvert) std::cout << "[MARCHE FERME] ";
        std::cout << std::endl;
    }

    return 0;
}
```

---

## Checkpoint ✅

1. **Que vaut `true && false || true` ?**
   > `true`. Le `&&` est evalue en premier : `(true && false) || true` = `false || true` = `true`.

2. **Qu'est-ce que le court-circuit et pourquoi c'est utile ?**
   > Si le resultat est deja determine par la premiere operande, la deuxieme n'est pas evaluee. Utile pour eviter les divisions par zero, les dereferences de pointeurs nuls, ou les appels couteux.

3. **Quelle est la difference entre `!a && b` et `!(a && b)` ?**
   > `!a && b` : inverse d'abord `a`, puis fait le ET avec `b`. `!(a && b)` : fait d'abord le ET, puis inverse le resultat. Avec `a=true, b=true` : `!a && b = false`, `!(a && b) = false`. Avec `a=true, b=false` : `!a && b = false`, `!(a && b) = true`.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret.
