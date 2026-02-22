# Boucles Imbriquees 🔲

## Pourquoi c'est important

Les boucles imbriquees permettent de travailler en 2D : matrices, grilles, combinaisons.
En HFT, tu parcours un order book (lignes = niveaux de prix, colonnes = ordres).
En Red Team, tu generes des combinaisons de caracteres pour du brute-force.

---

## Principe

Une boucle dans une boucle. La boucle interne s'execute completement pour chaque iteration de la boucle externe.

```cpp
for (int i = 0; i < 3; i++) {         // Boucle externe
    for (int j = 0; j < 4; j++) {     // Boucle interne
        cout << "(" << i << "," << j << ") ";
    }
    cout << endl;
}
```

```
  Sortie :
  (0,0) (0,1) (0,2) (0,3)
  (1,0) (1,1) (1,2) (1,3)
  (2,0) (2,1) (2,2) (2,3)

  Nombre total d'iterations = 3 x 4 = 12
```

---

## Complexite ⚠️

Les boucles imbriquees multiplient le nombre d'operations :

```
  1 boucle  : O(n)      -- lineaire
  2 boucles : O(n^2)    -- quadratique
  3 boucles : O(n^3)    -- cubique

  n = 1000 :
  O(n)   = 1 000 operations
  O(n^2) = 1 000 000 operations
  O(n^3) = 1 000 000 000 operations  <-- lent !
```

En HFT, on evite les O(n^2) autant que possible. Chaque microseconde compte.

---

## Patterns classiques

### Triangle d'etoiles

```cpp
for (int i = 1; i <= 5; i++) {
    for (int j = 0; j < i; j++) {
        cout << "* ";
    }
    cout << endl;
}
// *
// * *
// * * *
// * * * *
// * * * * *
```

### Matrice

```cpp
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        cout << matrix[i][j] << " ";
    }
    cout << endl;
}
```

### Toutes les paires

```cpp
string items[] = {"A", "B", "C", "D"};

for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {  // j = i+1 evite les doublons
        cout << items[i] << "-" << items[j] << " ";
    }
}
// A-B A-C A-D B-C B-D C-D
```

---

## Break dans des boucles imbriquees

`break` ne sort que de la boucle la plus interne :

```cpp
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (j == 1) break;  // Sort seulement du for(j)
        cout << i << "," << j << endl;
    }
    // Le for(i) continue
}
// 0,0
// 1,0
// 2,0
```

Pour sortir des deux boucles, utilise un flag ou un `goto` (rarement recommande).

---

## Checkpoint ✅

1. **Combien d'iterations pour 2 boucles imbriquees de 10 ?**
   > 10 x 10 = 100 iterations.

2. **Comment eviter les paires en double (A-B et B-A) ?**
   > Commencer la boucle interne a `j = i + 1`.

3. **Un break dans la boucle interne sort-il de la boucle externe ?**
   > Non, il sort uniquement de la boucle interne.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 👊
