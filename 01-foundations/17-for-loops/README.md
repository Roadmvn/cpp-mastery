# Boucles For 🔢

## Pourquoi c'est important

La boucle `for` est la boucle la plus utilisee en C++. Quand tu connais le nombre d'iterations
ou que tu dois iterer sur une plage, c'est `for` qu'il te faut.
En HFT : parcourir un order book, iterer sur des ticks de prix.
En Red Team : scanner des ports, tester des combinaisons.

---

## Syntaxe classique

```cpp
for (initialisation; condition; increment) {
    // Code execute a chaque iteration
}
```

```
  for (int i = 0; i < 5; i++)

  ┌─────────────────┐
  │ int i = 0       │  <-- Execute UNE fois au debut
  └────────┬────────┘
           │
           ▼
  ┌─────────────────┐     NON
  │ i < 5 ?         │──────────> Sortie
  └────────┬────────┘
           │ OUI
           ▼
  ┌─────────────────┐
  │ Bloc de code    │
  └────────┬────────┘
           │
           ▼
  ┌─────────────────┐
  │ i++             │──────────> Retour au test
  └─────────────────┘
```

---

## Exemples classiques

### Compteur simple

```cpp
for (int i = 0; i < 10; i++) {
    cout << i << " ";
}
// 0 1 2 3 4 5 6 7 8 9
```

### Decompte

```cpp
for (int i = 10; i > 0; i--) {
    cout << i << " ";
}
// 10 9 8 7 6 5 4 3 2 1
```

### Pas personnalise

```cpp
for (int i = 0; i <= 100; i += 10) {
    cout << i << " ";
}
// 0 10 20 30 40 50 60 70 80 90 100
```

---

## Range-based for (C++11) 🆕

Pour iterer sur une collection, le range-based for est plus propre :

```cpp
int prices[] = {150, 152, 148, 155, 160};

for (int p : prices) {
    cout << "Prix : $" << p << endl;
}
```

Avec `auto` pour laisser le compilateur deduire le type :

```cpp
string tickers[] = {"AAPL", "GOOG", "TSLA", "MSFT"};

for (auto& t : tickers) {  // & pour eviter la copie
    cout << "Ticker : " << t << endl;
}
```

---

## Compteurs multiples

Tu peux avoir plusieurs variables dans le `for` :

```cpp
for (int i = 0, j = 10; i < j; i++, j--) {
    cout << "i=" << i << " j=" << j << endl;
}
// i=0 j=10
// i=1 j=9
// ...
// i=4 j=6
```

C'est utile pour parcourir un tableau des deux bouts (ex: verifier si un mot est un palindrome).

---

## for vs while 

```
  Situation                    -->  Boucle
  ──────────────────────────────────────────
  Nombre d'iterations connu    -->  for
  Iterer sur une collection    -->  for (range-based)
  Condition dynamique          -->  while
  Au moins une execution       -->  do-while
```

---

## Checkpoint 

1. **Quels sont les 3 composants d'un for classique ?**
   > Initialisation, condition, increment -- separes par des points-virgules.

2. **Qu'est-ce que le range-based for ?**
   > Une syntaxe simplifiee `for (auto x : collection)` pour iterer directement sur les elements.

3. **Peut-on avoir plusieurs variables dans un for ?**
   > Oui, separees par des virgules dans l'initialisation et l'increment.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 
