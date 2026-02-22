# Trier un Array - Bubble sort, selection sort et std::sort

## Pourquoi c'est important HFT/Offensive

En **HFT**, l'order book est une structure triee par prix. Les ordres d'achat (bids)
sont tries du plus haut au plus bas, les ordres de vente (asks) du plus bas au
plus haut. Maintenir ce tri a chaque nouvel ordre est critique. `std::sort` avec
un comparateur custom est l'outil standard pour ca.

Cote **Red Team**, trier des donnees est utile pour identifier les anomalies : trier
des connexions par frequence, des processus par consommation memoire, ou des IPs
par nombre de tentatives de connexion.

## Concept en 5 minutes

**Bubble Sort O(n^2)** : compare chaque paire adjacente et echange si necessaire.
Simple mais lent. Utile pedagogiquement.

**Selection Sort O(n^2)** : trouve le minimum restant et le place en bonne position.
Aussi lent, mais fait moins d'echanges.

**std::sort O(n log n)** : algorithme optimise (introsort). Toujours utiliser en prod.

```cpp
#include <algorithm> // Pour std::sort

int data[] = {5, 2, 8, 1, 9};
int size = 5;

// Tri croissant (defaut)
std::sort(data, data + size);

// Tri decroissant avec comparateur
std::sort(data, data + size, [](int a, int b) { return a > b; });
```

## Schema ASCII : Bubble sort pas a pas

```
  Array initial : [5, 3, 8, 1, 4]

  PASSE 1 (i=0) : comparer chaque paire adjacente
  [5, 3, 8, 1, 4]  5>3 ? swap -> [3, 5, 8, 1, 4]
  [3, 5, 8, 1, 4]  5>8 ? non  -> [3, 5, 8, 1, 4]
  [3, 5, 8, 1, 4]  8>1 ? swap -> [3, 5, 1, 8, 4]
  [3, 5, 1, 8, 4]  8>4 ? swap -> [3, 5, 1, 4, 8]
                                                ^^ 8 est en place

  PASSE 2 (i=1) :
  [3, 5, 1, 4, 8]  3>5 ? non  -> [3, 5, 1, 4, 8]
  [3, 5, 1, 4, 8]  5>1 ? swap -> [3, 1, 5, 4, 8]
  [3, 1, 5, 4, 8]  5>4 ? swap -> [3, 1, 4, 5, 8]
                                          ^^ 5 en place

  PASSE 3 (i=2) :
  [3, 1, 4, 5, 8]  3>1 ? swap -> [1, 3, 4, 5, 8]
  [1, 3, 4, 5, 8]  3>4 ? non  -> [1, 3, 4, 5, 8]
                                    ^^ 4 en place

  PASSE 4 (i=3) :
  [1, 3, 4, 5, 8]  1>3 ? non  -> [1, 3, 4, 5, 8]

  Resultat : [1, 3, 4, 5, 8] -- TRIE !
```

## Exemple commente

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }
}

int main() {
    int data[] = {64, 25, 12, 22, 11};
    int size = 5;

    bubbleSort(data, size);
    for (int i = 0; i < size; i++) cout << data[i] << " ";
    cout << endl; // 11 12 22 25 64

    // std::sort avec comparateur decroissant
    sort(data, data + size, [](int a, int b) { return a > b; });
    for (int i = 0; i < size; i++) cout << data[i] << " ";
    cout << endl; // 64 25 22 12 11

    return 0;
}
```

## Checkpoint

Avant de passer a l'exercice, verifie que tu sais repondre :

- [ ] Quelle est la complexite de bubble sort et selection sort ?
- [ ] Quelle est la complexite de std::sort ?
- [ ] Comment trier en ordre decroissant avec std::sort ?
- [ ] Qu'est-ce qu'un tri "stable" vs "instable" ?
- [ ] Pourquoi ne jamais utiliser bubble sort en production ?
