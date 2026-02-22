# Fonctions 

## Pourquoi c'est important

Les fonctions sont le coeur de tout programme serieux. Elles permettent de decouper le code
en blocs reutilisables, testables et lisibles.
En HFT, chaque calcul (spread, VWAP, mid-price) est une fonction optimisee.
En Red Team, chaque action (encoder, scanner, exfiltrer) est encapsulee dans une fonction.

---

## Declaration, definition, appel

### Prototype (declaration)

Le prototype annonce la fonction au compilateur AVANT qu'elle soit definie :

```cpp
// Prototype : dit au compilateur "cette fonction existe"
double calculer_spread(double bid, double ask);

int main() {
    double s = calculer_spread(150.00, 150.05);  // Appel
    cout << "Spread : " << s << endl;
    return 0;
}

// Definition : le code reel de la fonction
double calculer_spread(double bid, double ask) {
    return ask - bid;
}
```

### Pourquoi un prototype ?

Le compilateur C++ lit le code de haut en bas. Sans prototype, il ne connait pas la fonction
quand tu l'appelles dans `main()`.

```
  ┌────────────────────────┐
  │  Prototype (declaration)│  <-- "ca existe"
  └────────────┬───────────┘
               │
  ┌────────────▼───────────┐
  │  main()                │  <-- utilise la fonction
  │    calculer_spread()   │
  └────────────┬───────────┘
               │
  ┌────────────▼───────────┐
  │  Definition             │  <-- "voila le code"
  │  double calculer_spread │
  │  (double bid, double ask)│
  └─────────────────────────┘
```

---

## Parametres et arguments

```cpp
//         parametres
//         vvvvvvvvvvvvvvvvv
int add(int a, int b) {
    return a + b;
}

int result = add(3, 7);  // 3 et 7 sont les arguments
//                ^  ^
//            arguments
```

### Passage par valeur (par defaut)

```cpp
void double_it(int x) {
    x *= 2;  // Modifie la COPIE locale
}

int n = 5;
double_it(n);
// n vaut toujours 5 -- la fonction a travaille sur une copie
```

### Parametres par defaut

```cpp
void log_trade(string symbol, int qty, double price, string exchange = "NYSE") {
    cout << exchange << " | " << symbol << " x" << qty << " @ $" << price << endl;
}

log_trade("AAPL", 100, 150.25);            // exchange = "NYSE" (defaut)
log_trade("TSLA", 50, 245.00, "NASDAQ");   // exchange = "NASDAQ"
```

Les parametres par defaut doivent etre a la FIN de la liste.

---

## Types de retour

```cpp
int add(int a, int b) {       // Retourne un int
    return a + b;
}

double ratio(int a, int b) {  // Retourne un double
    return (double)a / b;
}

bool is_valid(int x) {        // Retourne un bool
    return x > 0 && x < 100;
}

void print_info(string msg) { // Ne retourne rien
    cout << msg << endl;
    // Pas de return necessaire (ou return; sans valeur)
}
```

---

## Organisation du code 

```
  Fichier .cpp typique :

  ┌──────────────────────────┐
  │ #include <...>           │  Includes
  │ using namespace std;     │
  ├──────────────────────────┤
  │ // Prototypes            │  Declarations
  │ double spread(d, d);     │
  │ double vwap(d[], int);   │
  ├──────────────────────────┤
  │ int main() {             │  Point d'entree
  │   ...                    │
  │ }                        │
  ├──────────────────────────┤
  │ double spread(...) {     │  Definitions
  │   ...                    │
  │ }                        │
  │ double vwap(...) {       │
  │   ...                    │
  │ }                        │
  └──────────────────────────┘
```

---

## Checkpoint 

1. **Quelle est la difference entre declaration et definition ?**
   > La declaration (prototype) annonce la signature. La definition contient le code.

2. **Pourquoi utiliser des prototypes ?**
   > Pour que le compilateur connaisse la fonction avant de la rencontrer dans le code.

3. **Qu'est-ce que le passage par valeur ?**
   > La fonction recoit une copie de l'argument. Modifier le parametre ne change pas l'original.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 
