# Passer un array a une fonction - Decay en pointeur

## Pourquoi c'est important HFT/Offensive

En **HFT**, tu ne copies jamais un array de 10 000 prix pour le passer a une
fonction d'analyse. Tu passes un pointeur (8 octets) + la taille. C'est la base
du zero-copy : pas de copie = pas de latence inutile. Tes fonctions `normalize()`,
`scale()`, `analyze()` operent directement sur les donnees en memoire.

Cote **Red Team**, comprendre le decay array->pointeur est essentiel : c'est
exactement ce mecanisme qui rend les buffer overflows possibles. La fonction recoit
un pointeur brut sans aucune info sur la taille reelle du buffer.

## Concept en 5 minutes

Quand tu passes un array a une fonction, il **decay** (se degrade) en pointeur
vers son premier element. La taille est perdue.

```cpp
// Ces 3 signatures sont IDENTIQUES
void print(int arr[], int size);
void print(int arr[10], int size);  // Le 10 est IGNORE !
void print(int* arr, int size);

// Tu dois TOUJOURS passer la taille separement
```

**Regles cles :**
- Un array passe a une fonction devient un `pointeur`
- `sizeof(arr)` dans la fonction = taille du pointeur (8), pas de l'array !
- Toujours passer la taille comme parametre additionnel
- La fonction peut modifier l'array original (c'est un pointeur)

## Schema ASCII : Stack frame et decay

```
  APPELANT (main) :
  +----------------------------------+
  |  int data[5] = {10,20,30,40,50}  |   <- Array sur la stack de main
  |  Adresse : 0x7FF0                |
  |  sizeof(data) = 20 octets        |
  +----------------------------------+
             |
             | Appel: process(data, 5)
             | data "decay" en pointeur vers data[0]
             v
  FONCTION (process) :
  +----------------------------------+
  |  int* arr = 0x7FF0               |   <- Pointeur (8 octets), pas l'array !
  |  int size = 5                    |   <- Taille passee manuellement
  |  sizeof(arr) = 8 (pointeur !)   |
  +----------------------------------+
             |
             | arr[2] = 99;  // Modifie data[2] dans main !
             v
  MEMOIRE :
  +------+------+------+------+------+
  |  10  |  20  |  99  |  40  |  50  |   <- Modifie directement !
  +------+------+------+------+------+
  0x7FF0  ...                  0x7FFC

  arr pointe vers la MEME zone memoire que data
  -> Pas de copie, modification directe
```

## Exemple commente

```cpp
#include <iostream>
using namespace std;

// Le parametre 'arr' est en realite un int*
// On doit passer la taille separement
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Modifier l'array directement (pas de copie)
void doubleValues(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

// Calculer une valeur sans modifier l'array
double average(const int arr[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

int main() {
    int data[] = {10, 20, 30, 40, 50};
    int size = sizeof(data) / sizeof(data[0]);

    printArray(data, size);          // 10 20 30 40 50
    cout << "Moyenne: " << average(data, size) << endl;

    doubleValues(data, size);        // Modifie data directement
    printArray(data, size);          // 20 40 60 80 100

    return 0;
}
```

## Checkpoint

Avant de passer a l'exercice, verifie que tu sais repondre :

- [ ] Que signifie "decay" pour un array passe a une fonction ?
- [ ] Pourquoi sizeof ne fonctionne pas sur un array recu en parametre ?
- [ ] Comment empecher une fonction de modifier l'array ? (const)
- [ ] Pourquoi doit-on passer la taille comme parametre separe ?
- [ ] La fonction recoit-elle une copie de l'array ou un pointeur vers l'original ?
