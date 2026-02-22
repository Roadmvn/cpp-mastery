# Chapitre 12 : Null Pointers et Dangling Pointers ⚠️

## Ce que tu vas apprendre 🎯

- `nullptr` (C++11) vs `NULL` vs `0`
- Verifier si un pointeur est null avant de l'utiliser
- Les dangling pointers et pourquoi c'est dangereux
- Gestion robuste des pointeurs (defensive programming)

---

## nullptr : le pointeur vers rien 🚫

Un pointeur qui ne pointe vers aucune donnee valide doit etre mis a `nullptr`.

```cpp
int* ptr = nullptr;   // C++11 : la bonne facon
int* old1 = NULL;     // C : macro qui vaut 0
int* old2 = 0;        // Aussi valide mais ambigu
```

**Toujours utiliser `nullptr`** en C++ moderne. C'est type-safe.

```
    Pointeur valide              Pointeur null
    ┌──────────┐    ┌───────┐   ┌──────────┐
    │ ptr =    │───►│ 42    │   │ ptr =    │───► RIEN (nullptr)
    │ 0x7FF04  │    └───────┘   │ nullptr  │
    └──────────┘                └──────────┘

    *ptr = 42  ✓                 *ptr = CRASH ! ✗
                                 (segmentation fault)
```

---

## Pourquoi verifier null ? 💀

Dereferencier un pointeur null = **segmentation fault** = crash du programme.

```cpp
int* ptr = nullptr;
cout << *ptr << endl;  // CRASH ! Segfault !
```

Toujours verifier avant d'utiliser :

```cpp
int* ptr = nullptr;

if (ptr != nullptr) {
    cout << *ptr << endl;
} else {
    cout << "Pointeur null, pas de donnee" << endl;
}

// Version courte (un pointeur null est "falsy") :
if (ptr) {
    cout << *ptr << endl;
}
```

---

## Dangling pointer : le piege mortel 🪤

Un **dangling pointer** pointe vers une zone memoire qui a ete liberee ou qui n'existe plus. C'est le bug le plus dangereux en C/C++.

```
    AVANT                          APRES delete
    ┌──────────┐    ┌───────┐     ┌──────────┐    ┌───────┐
    │ ptr =    │───►│ 42    │     │ ptr =    │───►│ ???   │
    │ 0x7FF04  │    │ VALID │     │ 0x7FF04  │    │ FREED │
    └──────────┘    └───────┘     └──────────┘    └───────┘

    ptr pointe toujours vers 0x7FF04...
    mais la memoire a ete liberee !
    Lire *ptr = comportement indefini (UB)
```

### Cas 1 : Apres delete

```cpp
int* p = new int(42);
delete p;
// p pointe toujours vers l'ancienne adresse !
cout << *p << endl;  // UNDEFINED BEHAVIOR !

// Solution : mettre a nullptr apres delete
delete p;
p = nullptr;
```

### Cas 2 : Pointeur vers variable locale

```cpp
int* getNumber() {
    int local = 42;
    return &local;  // DANGER : local est detruit a la fin de la fonction !
}

int main() {
    int* p = getNumber();
    cout << *p << endl;  // UNDEFINED BEHAVIOR !
}
```

```
    PENDANT getNumber()          APRES getNumber()
    ┌───────────────────┐        ┌───────────────────┐
    │ Stack: getNumber  │        │ Stack: (libere)    │
    │ ┌───────────────┐ │        │ ┌───────────────┐  │
    │ │ local = 42    │ │        │ │ ??? (garbage)  │  │
    │ │ @0x7FF100     │ │        │ │ @0x7FF100      │  │
    │ └───────────────┘ │        │ └───────────────┘  │
    ├───────────────────┤        ├───────────────────┤
    │ Stack: main       │        │ Stack: main       │
    │ ┌───────────────┐ │        │ ┌───────────────┐  │
    │ │ p = 0x7FF100  │─┼────►   │ │ p = 0x7FF100  │──┼── DANGLING !
    │ └───────────────┘ │        │ └───────────────┘  │
    └───────────────────┘        └───────────────────┘
```

### Cas 3 : Apres reallocation

```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* p = &arr[2];   // p pointe vers arr[2]
// Si arr est realloue/detruit, p devient dangling
```

---

## Les regles d'or des pointeurs 📏

| Regle                                          | Exemple                        |
|------------------------------------------------|--------------------------------|
| Initialise TOUJOURS un pointeur                | `int* p = nullptr;`           |
| Verifie null AVANT dereferencement             | `if (p) { *p; }`             |
| Mets a nullptr APRES delete                    | `delete p; p = nullptr;`     |
| Ne retourne JAMAIS l'adresse d'une var locale  | Utilise `new` ou `static`    |
| Un pointeur = une responsabilite               | Qui alloue doit liberer      |

---

## Comparaison : NULL vs nullptr vs 0 🔍

```cpp
void foo(int x)    { cout << "int" << endl; }
void foo(int* p)   { cout << "pointer" << endl; }

foo(0);        // Appelle foo(int) — ambigu !
foo(NULL);     // Depend du compilateur — ambigu !
foo(nullptr);  // Appelle foo(int*) — sans ambiguite !
```

`nullptr` est de type `std::nullptr_t`, pas `int`. Pas d'ambiguite possible.

---

## Points cles a retenir 🔑

1. **`nullptr`** = pointeur null, toujours l'utiliser (pas NULL ni 0)
2. Dereferencier un null = **crash** (segfault)
3. **Dangling pointer** = pointe vers memoire liberee = **undefined behavior**
4. Toujours **verifier null** avant d'utiliser un pointeur
5. Toujours **mettre a nullptr** apres un delete
6. Ne **jamais retourner** l'adresse d'une variable locale

---

## Compilation 🔧

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
```
