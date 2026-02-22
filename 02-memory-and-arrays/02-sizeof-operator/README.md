# L'operateur sizeof - Mesurer la memoire au bit pres

## Pourquoi c'est important HFT/Offensive

En **HFT**, chaque octet compte. Si ta structure `Order` fait 64 octets au lieu de 32,
tu divises par 2 le nombre d'ordres que tu peux stocker dans le cache L1 (typiquement 32 KB).
`sizeof` te permet de verifier que tes structures sont compactes et alignees.

Cote **Red Team**, `sizeof` est indispensable pour calculer les offsets dans un buffer
overflow, comprendre le padding des structs, et construire des payloads de la bonne taille.

## Concept en 5 minutes

`sizeof` est un operateur (pas une fonction) evalue a la **compilation**.
Il retourne la taille en octets d'un type ou d'une variable.

```cpp
sizeof(int)       // Taille du type int (generalement 4)
sizeof(variable)  // Taille de la variable
sizeof(array)     // Taille TOTALE de l'array en octets
```

**Regles cles :**
- `sizeof(char)` vaut **toujours** 1 (par definition)
- La taille des autres types depend de la plateforme (mais souvent standardisee)
- Sur un array, sizeof donne la taille totale, pas le nombre d'elements
- Sur un pointeur, sizeof donne la taille du pointeur (8 octets sur x64)

## Schema ASCII : Tailles des types en memoire

```
  Type          Taille typique (x86-64)    Representation memoire

  char          1 octet                    [X]
  short         2 octets                   [X][X]
  int           4 octets                   [X][X][X][X]
  long          8 octets                   [X][X][X][X][X][X][X][X]
  float         4 octets                   [X][X][X][X]
  double        8 octets                   [X][X][X][X][X][X][X][X]
  bool          1 octet                    [X]
  pointeur      8 octets (x64)             [X][X][X][X][X][X][X][X]

  Array int[5] = 5 * 4 = 20 octets :
  [X][X][X][X] [X][X][X][X] [X][X][X][X] [X][X][X][X] [X][X][X][X]
  |-- int 0 --||-- int 1 --||-- int 2 --||-- int 3 --||-- int 4 --|

  Struct avec PADDING :
  struct Example {
      char  a;    // 1 octet
      // 3 octets de PADDING (alignement de int)
      int   b;    // 4 octets
      char  c;    // 1 octet
      // 7 octets de PADDING (alignement de double)
      double d;   // 8 octets
  };
  // sizeof(Example) = 24 (pas 14 !)

  [a][.][.][.]  [b][b][b][b]  [c][.][.][.][.][.][.][.]  [d][d][d][d][d][d][d][d]
   1   3 pad       4 octets    1       7 padding              8 octets
  |---- 4 ----|  |---- 4 ----|  |---------- 8 ----------|  |-------- 8 ---------|
                                                            Total = 24 octets
```

## Exemple commente

```cpp
#include <iostream>
using namespace std;

struct Order {
    char side;       // 'B' ou 'S' (1 octet)
    int quantity;    // nombre d'actions (4 octets)
    double price;    // prix (8 octets)
};

int main() {
    // Tailles des types fondamentaux
    cout << "char   : " << sizeof(char)   << " octet(s)" << endl;
    cout << "int    : " << sizeof(int)    << " octet(s)" << endl;
    cout << "double : " << sizeof(double) << " octet(s)" << endl;

    // Taille d'un array vs nombre d'elements
    int data[10] = {};
    cout << "sizeof(data)    : " << sizeof(data) << " octets" << endl;
    cout << "Nb elements     : " << sizeof(data) / sizeof(data[0]) << endl;

    // Taille d'une struct (attention au padding !)
    cout << "sizeof(Order)   : " << sizeof(Order) << " octets" << endl;
    // Probablement 16, pas 13, a cause du padding

    return 0;
}
```

## Checkpoint

Avant de passer a l'exercice, verifie que tu sais repondre :

- [ ] sizeof est un operateur ou une fonction ?
- [ ] Quelle est toujours la valeur de sizeof(char) ?
- [ ] Pourquoi sizeof(struct) peut etre plus grand que la somme des membres ?
- [ ] Quelle est la difference entre sizeof sur un array et sizeof sur un pointeur ?
- [ ] Quand est-ce que sizeof est evalue (compilation ou execution) ?
