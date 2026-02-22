# Chapitre 09 : Adresses Memoire 🧠

## Ce que tu vas apprendre 🎯

- Comment fonctionne la RAM (memoire vive)
- L'operateur `&` pour obtenir l'adresse d'une variable
- Les adresses hexadecimales
- La difference entre stack et heap
- La localite spatiale (critical pour la performance HFT)

---

## La RAM : comment ca marche vraiment 🔍

Ton programme tourne en RAM. Chaque variable que tu crees occupe un emplacement memoire avec une **adresse unique** (comme une adresse postale).

```
         RAM (Memoire vive)
    ┌─────────────────────────────┐
    │  Adresse      Contenu       │
    │  ────────     ─────────     │
    │  0x7FFF0000   ...           │  ← Adresses hautes (Stack)
    │  0x7FFF0004   42            │  ← int age = 42;
    │  0x7FFF0008   3.14          │  ← double pi = 3.14;
    │  0x7FFF0010   'A'           │  ← char grade = 'A';
    │  ...          ...           │
    │  ...          ...           │
    │  0x00400000   instructions  │  ← Code du programme
    │  ...          ...           │
    │  0x00200000   donnees heap  │  ← Adresses basses (Heap)
    └─────────────────────────────┘
```

Chaque adresse est un **nombre hexadecimal** (base 16) qui identifie un octet en memoire.

---

## L'operateur & (adresse-de) 📍

L'operateur `&` place devant une variable retourne son **adresse en memoire**.

```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 25;
    double salaire = 55000.0;
    char grade = 'A';

    cout << "Valeur de age     : " << age << endl;
    cout << "Adresse de age    : " << &age << endl;

    cout << "Valeur de salaire : " << salaire << endl;
    cout << "Adresse de salaire: " << &salaire << endl;

    cout << "Valeur de grade   : " << grade << endl;
    // Pour char, il faut caster pour voir l'adresse
    cout << "Adresse de grade  : " << (void*)&grade << endl;

    return 0;
}
```

**Sortie possible :**
```
Valeur de age     : 25
Adresse de age    : 0x7ffeeb3c
Valeur de salaire : 55000
Adresse de salaire: 0x7ffeeb30
Valeur de grade   : A
Adresse de grade  : 0x7ffeeb2f
```

Les adresses changent a chaque execution (ASLR — Address Space Layout Randomization).

---

## Stack vs Heap : les deux zones memoire 🏗️

```
    MEMOIRE DU PROGRAMME
    ┌────────────────────────────────────┐  Adresses hautes
    │            STACK  ↓                │  0x7FFF...
    │  ┌──────────────────────────────┐  │
    │  │  Variables locales           │  │
    │  │  Parametres de fonctions     │  │
    │  │  Adresses de retour          │  │
    │  │  Automatiquement geree       │  │
    │  │  LIFO (Last In, First Out)   │  │
    │  └──────────────────────────────┘  │
    │             ↓ grandit vers le bas   │
    │                                    │
    │         espace libre               │
    │                                    │
    │             ↑ grandit vers le haut  │
    │  ┌──────────────────────────────┐  │
    │  │  Allocation dynamique        │  │
    │  │  new / malloc                │  │
    │  │  Manuellement geree         │  │
    │  │  Fragmentable               │  │
    │  └──────────────────────────────┘  │
    │            HEAP  ↑                 │  0x0040...
    ├────────────────────────────────────┤
    │       Donnees globales/static      │
    ├────────────────────────────────────┤
    │       Code du programme (Text)     │  Adresses basses
    └────────────────────────────────────┘  0x0000...
```

| Propriete          | Stack                        | Heap                          |
|--------------------|------------------------------|-------------------------------|
| Allocation         | Automatique                  | Manuelle (new/delete)         |
| Vitesse            | Tres rapide (un mov)         | Plus lent (syscall possible)  |
| Taille             | Limitee (~1-8 MB)            | Limitee par la RAM            |
| Liberation         | Automatique (fin de scope)   | Manuelle (delete)             |
| Fragmentation      | Aucune                       | Possible                      |
| Acces cache        | Excellent (localite)         | Variable                      |

---

## Taille des types et disposition memoire 📐

Les variables occupent un nombre fixe d'octets selon leur type :

```
    int age = 42;     // 4 octets
    ┌────┬────┬────┬────┐
    │ 00 │ 00 │ 00 │ 2A │  Adresse: 0x7FFF0004
    └────┴────┴────┴────┘
    byte0 byte1 byte2 byte3

    double pi = 3.14; // 8 octets
    ┌────┬────┬────┬────┬────┬────┬────┬────┐
    │ 1F │ 85 │ EB │ 51 │ B8 │ 1E │ 09 │ 40 │  Adresse: 0x7FFF0008
    └────┴────┴────┴────┴────┴────┴────┴────┘

    char c = 'A';     // 1 octet
    ┌────┐
    │ 41 │  Adresse: 0x7FFF0010
    └────┘
```

---

## Localite spatiale : pourquoi ca compte en HFT 🏎️

Le processeur ne lit pas la RAM octet par octet. Il charge des **lignes de cache** (64 octets typiquement). Si tes donnees sont proches en memoire, elles arrivent dans le cache ensemble = **acces ultra rapide**.

```
    Cache Line (64 bytes)
    ┌──────────────────────────────────────────────────────┐
    │ arr[0] │ arr[1] │ arr[2] │ arr[3] │ ... │ arr[15]   │
    └──────────────────────────────────────────────────────┘
    Un seul chargement = 16 int accessibles !

    vs. Donnees dispersees en heap :
    ┌───┐          ┌───┐                    ┌───┐
    │ A │          │ B │                    │ C │
    └───┘          └───┘                    └───┘
    0x1000         0x5000                   0x9000
    3 chargements differents = 3x plus lent (cache misses)
```

C'est pour ca que les arrays sont ultra performants : **localite spatiale**.

---

## Afficher les adresses d'un array 📊

```cpp
#include <iostream>
using namespace std;

int main() {
    int tableau[5] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 5; i++) {
        cout << "tableau[" << i << "] = " << tableau[i]
             << "  adresse: " << &tableau[i] << endl;
    }

    return 0;
}
```

**Sortie :**
```
tableau[0] = 10  adresse: 0x7ffeeb30
tableau[1] = 20  adresse: 0x7ffeeb34    ← +4 octets (sizeof(int))
tableau[2] = 30  adresse: 0x7ffeeb38    ← +4 octets
tableau[3] = 40  adresse: 0x7ffeeb3c    ← +4 octets
tableau[4] = 50  adresse: 0x7ffeeb40    ← +4 octets
```

Les adresses sont **contigues** ! C'est ca la localite spatiale.

---

## Points cles a retenir 🔑

1. **`&variable`** donne l'adresse memoire d'une variable
2. Les adresses sont en **hexadecimal** (base 16)
3. La **stack** est rapide et automatique, le **heap** est flexible mais manuel
4. Les variables locales vivent sur la **stack**
5. Les elements d'un array sont **contigus en memoire** = excellent pour le cache
6. La **localite spatiale** est un concept fondamental en performance

---

## Compilation 🔧

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
```
