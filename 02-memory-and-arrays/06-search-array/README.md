# Recherche dans un Array - Lineaire et binaire

## Pourquoi c'est important HFT/Offensive

En **HFT**, chercher un ordre dans un order book de 100 000 entrees en O(n) est
inacceptable. La recherche binaire en O(log n) reduit ca a ~17 comparaisons.
Les order books sont maintenus tries par prix, donc la recherche binaire est
l'algorithme par defaut pour trouver un niveau de prix.

Cote **Red Team**, la recherche de patterns (signatures de malware, magic bytes,
opcodes) dans un dump memoire est une operation de base. La recherche lineaire
sur des buffers bruts est incontournable quand les donnees ne sont pas triees.

## Concept en 5 minutes

**Recherche lineaire O(n)** : parcourir chaque element un par un.
- Fonctionne sur n'importe quel array (trie ou non)
- Simple mais lent sur de gros arrays

**Recherche binaire O(log n)** : diviser le probleme en deux a chaque etape.
- Necessite un array **trie**
- Extremement rapide : 1 million d'elements -> ~20 comparaisons

```cpp
// Lineaire : O(n)
int linearSearch(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1; // Non trouve
}

// Binaire : O(log n) - array DOIT etre trie
int binarySearch(const int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; // Evite l'overflow
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
```

## Schema ASCII : Etapes de la recherche binaire

```
  Chercher 42 dans : [5, 12, 18, 25, 33, 42, 51, 67, 73, 89]

  Etape 1 :  low=0           mid=4            high=9
             [5, 12, 18, 25, 33, 42, 51, 67, 73, 89]
                              ^^
              arr[4]=33 < 42 -> chercher a DROITE -> low = 5

  Etape 2 :            low=5    mid=7    high=9
             [5, 12, 18, 25, 33, 42, 51, 67, 73, 89]
                                         ^^
              arr[7]=67 > 42 -> chercher a GAUCHE -> high = 6

  Etape 3 :            low=5 mid=5 high=6
             [5, 12, 18, 25, 33, 42, 51, 67, 73, 89]
                                  ^^
              arr[5]=42 == 42 -> TROUVE a l'index 5 !

  3 comparaisons au lieu de 6 (lineaire)

  Comparaison sur 1 000 000 elements :
  - Lineaire : jusqu'a 1 000 000 comparaisons
  - Binaire  : maximum 20 comparaisons (log2(1000000) ~ 20)
```

## Exemple commente

```cpp
#include <iostream>
using namespace std;

int linearSearch(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int binarySearch(const int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    int sorted[] = {5, 12, 18, 25, 33, 42, 51, 67, 73, 89};
    int size = 10;

    int idx = binarySearch(sorted, size, 42);
    if (idx != -1)
        cout << "42 trouve a l'index " << idx << endl;

    idx = linearSearch(sorted, size, 99);
    if (idx == -1)
        cout << "99 non trouve" << endl;

    return 0;
}
```

## Checkpoint

Avant de passer a l'exercice, verifie que tu sais repondre :

- [ ] Quelle est la complexite de la recherche lineaire ? Binaire ?
- [ ] Pourquoi la recherche binaire necessite un array trie ?
- [ ] Pourquoi utiliser `low + (high - low) / 2` au lieu de `(low + high) / 2` ?
- [ ] Combien de comparaisons max pour chercher dans 1 024 elements en binaire ?
- [ ] Que retourner si l'element n'est pas trouve ?
