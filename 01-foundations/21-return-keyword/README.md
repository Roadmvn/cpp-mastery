# Le Mot-Cle Return ↩

## Pourquoi c'est important

`return` est le mecanisme par lequel une fonction renvoie une valeur a son appelant.
Maitriser les patterns de return (early return, multiple returns, void) rend ton code
plus lisible et plus performant. En HFT, un early return evite des calculs inutiles.

---

## Types de retour

### Retourner une valeur

```cpp
int add(int a, int b) {
    return a + b;  // Retourne un int
}

double pi() {
    return 3.14159265358979;  // Retourne un double
}

bool is_positive(int n) {
    return n > 0;  // Retourne un bool (true/false)
}

string greeting() {
    return "Hello!";  // Retourne un string
}
```

### void -- Pas de retour

```cpp
void print_info(string msg) {
    cout << msg << endl;
    // Pas de return necessaire
    // Le compilateur retourne implicitement
}
```

Tu peux utiliser `return;` (sans valeur) dans une fonction void pour sortir tot :

```cpp
void process(int x) {
    if (x < 0) {
        cout << "Valeur negative ignoree" << endl;
        return;  // Sort de la fonction ici
    }
    cout << "Traitement de " << x << endl;
}
```

---

## Early Return (retour anticipe) 

L'early return simplifie le code en traitant les cas d'erreur en premier :

```cpp
// SANS early return (pyramide de doom)
double calculate(double price, int qty) {
    if (price > 0) {
        if (qty > 0) {
            if (qty <= 10000) {
                return price * qty;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

// AVEC early return (propre et lisible)
double calculate(double price, int qty) {
    if (price <= 0) return -1;
    if (qty <= 0) return -1;
    if (qty > 10000) return -1;
    return price * qty;
}
```

L'early return c'est un pattern tres utilise dans le code pro. Ca evite l'indentation excessive.

---

## Retour multiple (via conditions)

```cpp
string classify_trade(double pnl) {
    if (pnl > 1000)  return "Big Win";
    if (pnl > 0)     return "Small Win";
    if (pnl == 0)    return "Flat";
    if (pnl > -1000) return "Small Loss";
    return "Big Loss";
}
```

Chaque `return` termine la fonction immediatement. Le code apres un `return` n'est jamais execute.

---

## Return dans main()

```cpp
int main() {
    // return 0 = succes (convention Unix)
    // return 1 = erreur generique
    // return 2+ = codes d'erreur specifiques

    if (/* erreur critique */) {
        return 1;  // Arrete le programme avec code d'erreur
    }

    return 0;  // Tout s'est bien passe
}
```

Le code de retour est utilisable dans le shell :

```bash
./programme
echo $?   # Affiche le code de retour (0 = ok, autre = erreur)
```

---

## Checkpoint 

1. **Peut-on avoir plusieurs return dans une fonction ?**
   > Oui, mais un seul sera execute (le premier atteint).

2. **Qu'est-ce que l'early return ?**
   > Traiter les cas d'erreur en debut de fonction avec des return pour eviter l'imbrication.

3. **Que se passe-t-il apres un return ?**
   > La fonction se termine immediatement. Le code suivant le return n'est jamais execute.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 
