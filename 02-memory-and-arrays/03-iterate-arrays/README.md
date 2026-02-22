# Parcourir les Arrays - Boucles index et while

## Pourquoi c'est important HFT/Offensive

En **HFT**, tu parcours des milliers de prix par seconde. La facon dont tu iteres
impacte directement la latence : une boucle `for` avec acces sequentiel est
**cache-friendly** (le prefetcher du CPU anticipe les acces suivants). Un parcours
dans le desordre detruit cette optimisation.

Cote **Red Team**, parcourir un buffer octet par octet est la base pour chercher
des patterns (signatures de fichiers, magic bytes, shellcode) dans un dump memoire.

## Concept en 5 minutes

Trois facons classiques de parcourir un array :

```cpp
int data[5] = {10, 20, 30, 40, 50};
int size = 5;

// 1. Boucle for classique (la plus courante)
for (int i = 0; i < size; i++) {
    cout << data[i] << endl;
}

// 2. Boucle while (utile avec condition d'arret)
int i = 0;
while (i < size) {
    cout << data[i] << endl;
    i++;
}

// 3. Boucle do-while (execute au moins une fois)
int j = 0;
do {
    cout << data[j] << endl;
    j++;
} while (j < size);
```

**Regles cles :**
- Toujours verifier `i < size`, jamais `i <= size` (off-by-one !)
- Le `for` est prefere quand on connait le nombre d'iterations
- Le `while` est prefere quand la condition d'arret est dynamique
- Acces sequentiel = cache-friendly = performance maximale

## Schema ASCII : Parcours sequentiel en memoire

```
  Index:      0      1      2      3      4
            +------+------+------+------+------+
  data[] =  |  10  |  20  |  30  |  40  |  50  |
            +------+------+------+------+------+
               ^
               |  i=0  -> lit data[0] = 10
               |
                  ^
                  |  i=1  -> lit data[1] = 20
                  |
                     ^
                     |  i=2  -> lit data[2] = 30
                     |
                        ^
                        |  i=3  -> lit data[3] = 40
                        |
                           ^
                           |  i=4  -> lit data[4] = 50
                           |
                           STOP : i=5 >= size(5)

  Parcours sequentiel = le CPU prefetch les donnees suivantes
  en cache L1 AVANT qu'on en ait besoin -> ultra rapide
```

## Exemple commente

```cpp
#include <iostream>
using namespace std;

int main() {
    double prices[] = {100.5, 101.2, 99.8, 102.1, 100.9, 98.7, 103.0};
    int size = sizeof(prices) / sizeof(prices[0]);

    // Parcours classique : calculer la somme
    double somme = 0;
    for (int i = 0; i < size; i++) {
        somme += prices[i];
    }
    cout << "Somme: " << somme << endl;

    // Parcours inverse : afficher du dernier au premier
    for (int i = size - 1; i >= 0; i--) {
        cout << "prices[" << i << "] = " << prices[i] << endl;
    }

    // Parcours avec condition d'arret (while)
    // Trouver le premier prix sous 100
    int idx = 0;
    while (idx < size && prices[idx] >= 100.0) {
        idx++;
    }
    if (idx < size) {
        cout << "Premier prix < 100 a l'index " << idx << endl;
    }

    return 0;
}
```

## Checkpoint

Avant de passer a l'exercice, verifie que tu sais repondre :

- [ ] Quelle est la difference entre `i < size` et `i <= size` ?
- [ ] Quand utiliser `while` plutot que `for` ?
- [ ] Pourquoi un parcours sequentiel est plus rapide qu'un parcours aleatoire ?
- [ ] Comment parcourir un array en sens inverse ?
- [ ] Quelle est la complexite d'un parcours complet d'un array de N elements ?
