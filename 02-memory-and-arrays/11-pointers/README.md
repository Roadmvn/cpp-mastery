# Chapitre 11 : Pointeurs 🎯

## Ce que tu vas apprendre 🎯

- Declarer un pointeur avec `*`
- Obtenir l'adresse avec `&` et dereferencier avec `*`
- L'arithmetique des pointeurs
- La relation pointeurs / arrays
- Pourquoi les pointeurs sont la base de tout en C++ (et en securite offensive)

---

## C'est quoi un pointeur ? 🔍

Un pointeur est une variable qui **stocke une adresse memoire**. Au lieu de contenir une valeur directement, il contient l'adresse ou se trouve cette valeur.

```
    Variable normale          Pointeur
    ┌──────────┐              ┌──────────┐         ┌──────────┐
    │ age = 25 │              │ ptr =    │────────► │ age = 25 │
    │ @0x7FF04 │              │ 0x7FF04  │         │ @0x7FF04 │
    └──────────┘              └──────────┘         └──────────┘
                               @0x7FF10

    ptr contient l'ADRESSE de age, pas sa valeur.
    *ptr (dereferencement) = 25 (la valeur a cette adresse)
```

---

## Declaration et utilisation 📝

```cpp
int age = 25;
int* ptr = &age;    // ptr pointe vers age

cout << age << endl;    // 25 (valeur directe)
cout << &age << endl;   // 0x7FF04 (adresse de age)
cout << ptr << endl;    // 0x7FF04 (adresse stockee dans ptr)
cout << *ptr << endl;   // 25 (dereferencement : valeur A l'adresse)
```

**Synthese des operateurs :**

| Syntaxe   | Signification                          | Exemple              |
|-----------|----------------------------------------|----------------------|
| `int* p`  | Declare un pointeur vers un int        | `int* ptr;`          |
| `&var`    | Adresse de la variable                 | `ptr = &age;`        |
| `*ptr`    | Dereferencement (valeur a l'adresse)   | `cout << *ptr;`      |

---

## Schema detaille : pointeur vers donnee 🗺️

```
    STACK
    ┌─────────────────────────────────────────┐
    │                                         │
    │   age          ptr                      │
    │   ┌───────┐    ┌───────────┐            │
    │   │  25   │◄───│ 0x7FF004  │            │
    │   └───────┘    └───────────┘            │
    │   @0x7FF004    @0x7FF010                │
    │                                         │
    │   Taille: 4B   Taille: 8B (64-bit)     │
    │                                         │
    └─────────────────────────────────────────┘

    &age  = 0x7FF004    (adresse de age)
    ptr   = 0x7FF004    (valeur du pointeur = adresse de age)
    *ptr  = 25          (valeur a l'adresse 0x7FF004)
    &ptr  = 0x7FF010    (adresse du pointeur lui-meme)
```

---

## Modifier une valeur via un pointeur ✏️

```cpp
int score = 100;
int* p = &score;

*p = 200;           // modifie score a travers le pointeur

cout << score << endl;  // 200 (modifie!)
cout << *p << endl;     // 200
```

C'est comme ca que les fonctions modifient des variables via des pointeurs (style C).

---

## Arithmetique des pointeurs 🔢

L'arithmetique de pointeurs ne travaille pas en octets mais en **elements du type pointe**.

```
    int arr[5] = {10, 20, 30, 40, 50};
    int* p = arr;  // p pointe vers arr[0]

    Adresses (sizeof(int) = 4) :
    ┌────────┬────────┬────────┬────────┬────────┐
    │   10   │   20   │   30   │   40   │   50   │
    └────────┴────────┴────────┴────────┴────────┘
    0x100    0x104    0x108    0x10C    0x110
    p        p+1     p+2      p+3      p+4

    p       → adresse 0x100, *p     = 10
    p + 1   → adresse 0x104, *(p+1) = 20
    p + 2   → adresse 0x108, *(p+2) = 30
    p + 3   → adresse 0x10C, *(p+3) = 40
```

**p + n** avance de **n * sizeof(type)** octets.

```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* p = arr;

for (int i = 0; i < 5; i++) {
    cout << "*(p+" << i << ") = " << *(p + i) << endl;
}
```

---

## Pointeurs et arrays : la relation secrete 🤝

Le nom d'un array est en fait un **pointeur vers son premier element**.

```cpp
int arr[5] = {10, 20, 30, 40, 50};

// Ces deux lignes sont equivalentes :
cout << arr[2] << endl;       // 30
cout << *(arr + 2) << endl;   // 30

// arr[i] est du sucre syntaxique pour *(arr + i)
```

```
    arr[i]  ≡  *(arr + i)
    &arr[i] ≡  arr + i
```

---

## Pointeur comme parametre de fonction 📮

Style C classique (avant les references) :

```cpp
void doubler(int* p) {
    *p = *p * 2;
}

int main() {
    int n = 21;
    doubler(&n);        // passe l'adresse
    cout << n << endl;  // 42
}
```

En C++ moderne, on prefere les references (`&`), mais les pointeurs sont essentiels pour :
- Les APIs C
- L'allocation dynamique
- Les structures de donnees (listes chainees, arbres)
- La securite offensive (manipulation memoire directe)

---

## Points cles a retenir 🔑

1. **`int* p`** declare un pointeur vers un int
2. **`&var`** donne l'adresse d'une variable
3. **`*p`** dereference : donne la valeur a l'adresse stockee
4. **`p + n`** avance de n elements (pas n octets)
5. **`arr[i]`** est equivalent a **`*(arr + i)`**
6. Un pointeur sur un systeme 64 bits fait toujours **8 octets**

---

## Compilation 🔧

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
```
