# Chapitre 13 : Memoire Dynamique - new / delete 

## Ce que tu vas apprendre 

- `new` et `delete` pour allouer/liberer de la memoire
- `new[]` et `delete[]` pour les tableaux dynamiques
- La difference profonde entre stack et heap
- Les memory leaks et comment les eviter
- Pattern de base pour les buffers dynamiques

---

## Pourquoi la memoire dynamique ? 

La stack est limitee (~1-8 MB) et la taille doit etre connue a la compilation. Parfois tu as besoin de :

- Tableaux dont la taille depend de l'utilisateur
- Donnees qui survivent au scope de la fonction
- De gros volumes de donnees (images, buffers reseau...)

Solution : allouer sur le **heap** avec `new`.

---

## new et delete : allocation simple 

```cpp
// Allocation d'un seul element
int* p = new int;       // alloue un int sur le heap
*p = 42;                // ecrit dedans
cout << *p << endl;     // 42
delete p;               // libere la memoire
p = nullptr;            // bonne pratique

// Allocation avec initialisation
int* q = new int(100);  // alloue ET initialise a 100
cout << *q << endl;     // 100
delete q;
q = nullptr;
```

```
    STACK                          HEAP
    ┌──────────────────┐           ┌──────────────┐
    │ p = 0x55A000     │──────────│ 42           │
    │ (8 octets)       │           │ (4 octets)   │
    └──────────────────┘           └──────────────┘
    Automatiquement libere          Manuellement libere
    a la fin du scope               avec delete
```

---

## new[] et delete[] : tableaux dynamiques 

```cpp
int taille;
cout << "Combien d'elements ? ";
cin >> taille;

// Allocation d'un tableau dynamique
int* arr = new int[taille];

// Utilisation normale
for (int i = 0; i < taille; i++) {
    arr[i] = i * 10;
}

// TOUJOURS delete[] pour un tableau (pas delete)
delete[] arr;
arr = nullptr;
```

```
    new int[5] :

    STACK                          HEAP
    ┌──────────────┐               ┌─────┬─────┬─────┬─────┬─────┐
    │ arr = 0xA000 │──────────────│  0  │ 10  │ 20  │ 30  │ 40  │
    └──────────────┘               └─────┴─────┴─────┴─────┴─────┘
                                   0xA000 0xA004 0xA008 0xA00C 0xA010

    delete[] arr :

    STACK                          HEAP
    ┌──────────────┐               ┌─────┬─────┬─────┬─────┬─────┐
    │ arr = nullptr│               │ ??? │ ??? │ ??? │ ??? │ ??? │
    └──────────────┘               └─────┴─────┴─────┴─────┴─────┘
                                   Memoire rendue au systeme
```

---

## Memory Leak : le tueur silencieux 

Un **memory leak** arrive quand tu alloues de la memoire sans jamais la liberer. Le programme consomme de plus en plus de RAM jusqu'a crash.

```cpp
// FUITE MEMOIRE : p est perdu, impossible de liberer
void fuite() {
    int* p = new int(42);
    // oublie delete p  fuite !
}  // p est detruit (variable locale) mais la memoire heap reste allouee

// FUITE MEMOIRE : reassignation sans delete
int* p = new int(10);
p = new int(20);    // l'ancien int(10) est perdu ! Fuite !
delete p;           // ne libere que int(20)
```

```
    MEMORY LEAK
    ┌──────────────┐               ┌───────────┐
    │ p = 0xB000   │──────────────│ 20        │   Seul celui-ci sera libere
    └──────────────┘               └───────────┘

                                   ┌───────────┐
                                   │ 10        │   PERDU ! Pas de pointeur
                                   └───────────┘     vers cette memoire
                                   0xA000            = MEMORY LEAK
```

### Regles pour eviter les fuites

1. Chaque `new` doit avoir son `delete`
2. Chaque `new[]` doit avoir son `delete[]`
3. Ne reassigne pas un pointeur sans `delete` d'abord
4. Mets a `nullptr` apres `delete`
5. En production : utilise les **smart pointers** (chapitre OOP)

---

## delete vs delete[] : ne te trompe pas ! 

| Allocation      | Liberation correcte | Liberation incorrecte     |
|----------------|--------------------|-----------------------------|
| `new int`       | `delete p;`        | `delete[] p;`  UB         |
| `new int[10]`   | `delete[] p;`      | `delete p;`  UB           |

**UB** = Undefined Behavior = tout peut arriver (crash, corruption, rien du tout).

---

## Cycle de vie heap vs stack 

```
    STACK                              HEAP
    ┌──────────────────────────┐       ┌──────────────────────────┐
    │ int x = 5;               │       │ int* p = new int(5);     │
    │  Cree en entrant scope  │       │  Cree quand TU le dis   │
    │  Detruit en sortant     │       │  Detruit quand TU le dis│
    │  Taille fixe (compil)   │       │  Taille variable (exec) │
    │  Rapide                 │       │  Plus lent              │
    │  Pas de fuite possible  │       │  Fuite possible         │
    └──────────────────────────┘       └──────────────────────────┘
```

---

## Exemple complet : tableau dynamique 

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Nombre de notes : ";
    cin >> n;

    double* notes = new double[n];

    // Saisie
    for (int i = 0; i < n; i++) {
        cout << "Note " << i + 1 << " : ";
        cin >> notes[i];
    }

    // Calcul moyenne
    double total = 0;
    for (int i = 0; i < n; i++) {
        total += notes[i];
    }
    cout << "Moyenne : " << total / n << endl;

    // Liberation
    delete[] notes;
    notes = nullptr;

    return 0;
}
```

---

## Points cles a retenir 

1. **`new`** alloue sur le heap, retourne un pointeur
2. **`delete`** libere un element, **`delete[]`** libere un tableau
3. **Memory leak** = new sans delete = memoire perdue
4. Toujours `delete` avant de reassigner un pointeur
5. Toujours `nullptr` apres `delete`
6. Stack = automatique + rapide. Heap = flexible + manuel
7. En C++ moderne : prefere `std::vector` ou `std::unique_ptr`

---

## Compilation 

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
```
