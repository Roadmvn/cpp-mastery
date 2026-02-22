# Les Arrays en C++ - Fondations de la memoire contigue

## Pourquoi c'est important HFT/Offensive

En **HFT**, chaque nanoseconde compte. Les arrays sont stockes en memoire **contigue** :
le CPU charge un bloc entier dans le cache L1, et acceder aux elements voisins est
quasi instantane. Un `std::vector` ou une liste chainee provoque des **cache misses**
qui tuent la latence. Les systemes de trading ultra-rapides utilisent des arrays
de taille fixe pour stocker les prix, les ordres, les timestamps.

Cote **Red Team**, comprendre comment un array est dispose en memoire est la base
pour exploiter les buffer overflows : savoir ou commence un array, ou il finit, et
ce qui se trouve juste apres en memoire.

## Concept en 5 minutes

Un array C++ est un bloc de memoire contigue contenant N elements du meme type.

```cpp
int prices[5];           // Declaration : 5 int non initialises
int prices[5] = {100, 101, 102, 103, 104}; // Declaration + initialisation
int prices[] = {100, 101, 102};             // Taille deduite : 3
```

**Regles cles :**
- La taille est **fixe** a la compilation (pas de resize)
- Les index vont de `0` a `N-1`
- Aucun bounds checking par defaut (danger !)
- Acces en O(1) par index

## Schema ASCII : Array en memoire contigue

```
  Adresse memoire (exemple)

  prices[0]   prices[1]   prices[2]   prices[3]   prices[4]
  +----------+----------+----------+----------+----------+
  |   100    |   101    |   102    |   103    |   104    |
  +----------+----------+----------+----------+----------+
  0x1000     0x1004     0x1008     0x100C     0x1010

  ^                                                       ^
  |__ debut du bloc                     fin du bloc ______|

  Chaque int = 4 octets (typiquement)
  Adresse de prices[i] = adresse_base + i * sizeof(int)

  MEMOIRE CONTIGUE = cache-friendly = RAPIDE

  Que se passe-t-il si on accede a prices[5] ?
  +----------+
  | ??????   |  <-- Zone inconnue ! Undefined Behavior !
  +----------+
  0x1014
```

## Exemple commente

```cpp
#include <iostream>
using namespace std;

int main() {
    // Declaration et initialisation d'un array de prix (en centimes)
    int prices[5] = {10023, 10045, 10012, 10078, 10056};

    // Acces par index : O(1), ultra rapide
    cout << "Premier prix : " << prices[0] << endl;
    cout << "Dernier prix : " << prices[4] << endl;

    // Modification d'un element
    prices[2] = 10099;

    // Taille totale vs taille d'un element
    cout << "Taille totale : " << sizeof(prices) << " octets" << endl;
    cout << "Nombre d'elements : " << sizeof(prices) / sizeof(prices[0]) << endl;

    // DANGER : pas de bounds checking
    // prices[5] = 999; // Compile, mais Undefined Behavior !

    return 0;
}
```

## Checkpoint

Avant de passer a l'exercice, verifie que tu sais repondre :

- [ ] Comment declarer un array de 10 doubles ?
- [ ] Quel est l'index du dernier element d'un array de taille N ?
- [ ] Pourquoi un array est plus rapide qu'une liste chainee pour l'acces par index ?
- [ ] Que se passe-t-il si on accede a un index hors limites ?
- [ ] Comment calculer le nombre d'elements d'un array avec sizeof ?
