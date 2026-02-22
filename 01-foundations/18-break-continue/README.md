# Break & Continue ⏭

## Pourquoi c'est important

`break` et `continue` te donnent un controle fin sur le flux d'une boucle.
En HFT, tu arretes de traiter des ordres quand un seuil de risque est atteint.
En Red Team, tu sautes les cibles non pertinentes et tu stoppes quand tu as trouve ta vulnerabilite.

---

## break -- Sortir de la boucle

`break` termine immediatement la boucle en cours :

```cpp
for (int i = 0; i < 1000; i++) {
    if (i == 5) {
        break;  // Sort de la boucle quand i vaut 5
    }
    cout << i << " ";
}
// Affiche : 0 1 2 3 4
```

```
  Boucle
  ┌─────────────────────────┐
  │  i = 0, 1, 2, 3, 4     │
  │  ...                    │
  │  if (i == 5) break; ────┼──> Sort immediatement
  │  i = 6, 7, 8...        │    (jamais execute)
  └─────────────────────────┘
```

---

## continue -- Sauter une iteration

`continue` saute le reste du bloc et passe a l'iteration suivante :

```cpp
for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
        continue;  // Saute les nombres pairs
    }
    cout << i << " ";
}
// Affiche : 1 3 5 7 9
```

```
  Boucle
  ┌─────────────────────────┐
  │  i = 0 -> continue (skip)│
  │  i = 1 -> cout 1        │
  │  i = 2 -> continue (skip)│
  │  i = 3 -> cout 3        │
  │  ...                    │
  └─────────────────────────┘
```

---

## Combinaison break + continue

```cpp
for (int i = 0; i < 100; i++) {
    if (i % 3 != 0) continue;  // Saute les non-multiples de 3
    if (i > 30) break;          // Arrete apres 30
    cout << i << " ";
}
// Affiche : 0 3 6 9 12 15 18 21 24 27 30
```

---

## break dans un switch vs dans une boucle

Attention : `break` dans un switch sort du switch, pas de la boucle englobante :

```cpp
for (int i = 0; i < 5; i++) {
    switch (i) {
        case 3:
            break;  // Sort du SWITCH, pas du FOR
    }
    // Le for continue normalement
}
```

Pour sortir de la boucle depuis un switch, utilise un flag :

```cpp
bool stop = false;
for (int i = 0; i < 100 && !stop; i++) {
    switch (i) {
        case 42:
            stop = true;
            break;  // Sort du switch, le flag arrete le for
    }
}
```

---

## Bonnes pratiques 

```
  Utilise break quand :
  ├── Tu as trouve ce que tu cherchais
  ├── Un seuil critique est atteint
  └── Continuer n'a plus de sens

  Utilise continue quand :
  ├── L'element courant ne t'interesse pas
  ├── Tu filtres des donnees
  └── Tu veux eviter un if profondement imbrique
```

---

## Checkpoint 

1. **Que fait `break` dans une boucle ?**
   > Termine immediatement la boucle en cours et reprend apres.

2. **Que fait `continue` dans une boucle ?**
   > Saute le reste du bloc de la boucle et passe a l'iteration suivante.

3. **Un `break` dans un switch sort-il de la boucle englobante ?**
   > Non, il sort uniquement du switch. Pour sortir de la boucle, utilise un flag.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 
