# Arrays Multidimensionnels - Matrices et memoire row-major

## Pourquoi c'est important HFT/Offensive

En **HFT**, les matrices de correlation entre actifs, les grilles de prix
(prix x temps), et les matrices de covariance sont partout dans les modeles
quantitatifs. Comprendre le layout row-major est crucial pour les performances :
parcourir une matrice ligne par ligne est cache-friendly, colonne par colonne
tue le cache.

Cote **Red Team**, une matrice d'adjacence represente un reseau : quels noeuds
sont connectes, quels ports sont ouverts, quelles machines communiquent entre elles.
C'est la base du network mapping.

## Concept en 5 minutes

Un array 2D est un tableau de tableaux. En C++, il est stocke en memoire
de facon **row-major** : les lignes sont contiguees.

```cpp
// Declaration : 3 lignes x 4 colonnes
int matrix[3][4] = {
    {1, 2, 3, 4},      // Ligne 0
    {5, 6, 7, 8},      // Ligne 1
    {9, 10, 11, 12}    // Ligne 2
};

// Acces : matrix[ligne][colonne]
int val = matrix[1][2]; // Ligne 1, colonne 2 -> 7

// Parcours standard : ligne par ligne (cache-friendly)
for (int i = 0; i < 3; i++) {       // Lignes
    for (int j = 0; j < 4; j++) {   // Colonnes
        cout << matrix[i][j] << " ";
    }
    cout << endl;
}
```

**Regles cles :**
- `matrix[i][j]` : i = ligne, j = colonne
- Stockage row-major : les colonnes d'une meme ligne sont contiguees
- Parcourir par ligne = rapide, par colonne = lent (cache misses)
- Taille totale = lignes * colonnes * sizeof(type)

## Schema ASCII : Layout row-major en memoire

```
  Matrice 3x4 logique :

       Col 0  Col 1  Col 2  Col 3
  Lig 0 [  1  |  2  |  3  |  4  ]
  Lig 1 [  5  |  6  |  7  |  8  ]
  Lig 2 [  9  | 10  | 11  | 12  ]

  En memoire (ROW-MAJOR = ligne par ligne) :

  Adresse : 0x00  0x04  0x08  0x0C  0x10  0x14  0x18  0x1C  0x20  0x24  0x28  0x2C
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | 10  | 11  | 12  |
            +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
            |------ Ligne 0 --------|------ Ligne 1 --------|------ Ligne 2 --------|

  Acces a matrix[i][j] = adresse_base + (i * nb_colonnes + j) * sizeof(int)
  Exemple : matrix[1][2] = base + (1*4 + 2)*4 = base + 24 = 0x18 -> valeur 7

  PARCOURS RAPIDE (cache-friendly) :       PARCOURS LENT (cache misses) :
  for (i) for (j) -> sequentiel            for (j) for (i) -> sauts en memoire
  [1][2][3][4][5][6][7][8][9]...           [1][5][9][2][6][10][3][7][11]...
  ^^^^^^^^^^^^^^^^^^^^^^^^                  ^     ^     ^  sauts de 16 octets !
  Contigu en memoire !
```

## Exemple commente

```cpp
#include <iostream>
using namespace std;

int main() {
    const int ROWS = 3;
    const int COLS = 4;

    int matrix[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // Affichage formatee
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    // Somme de chaque ligne
    for (int i = 0; i < ROWS; i++) {
        int sum = 0;
        for (int j = 0; j < COLS; j++) {
            sum += matrix[i][j];
        }
        cout << "Somme ligne " << i << " : " << sum << endl;
    }

    // Somme de chaque colonne
    for (int j = 0; j < COLS; j++) {
        int sum = 0;
        for (int i = 0; i < ROWS; i++) {
            sum += matrix[i][j];
        }
        cout << "Somme colonne " << j << " : " << sum << endl;
    }

    return 0;
}
```

## Checkpoint

Avant de passer a l'exercice, verifie que tu sais repondre :

- [ ] Comment declarer un array 2D de 5 lignes et 3 colonnes ?
- [ ] Qu'est-ce que le layout row-major ?
- [ ] Pourquoi parcourir par ligne est plus rapide que par colonne ?
- [ ] Comment acceder a l'element en ligne 2, colonne 3 ?
- [ ] Quelle est la taille en memoire d'un `int matrix[4][5]` ?
