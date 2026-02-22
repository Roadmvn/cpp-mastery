# Chapitre 10 - Smart Pointers

## Pourquoi les smart pointers

Les raw pointers (`int* p = new int(42)`) sont dangereux : oublis de `delete`, double-free, dangling pointers. Les smart pointers encapsulent un raw pointer et gerent sa duree de vie automatiquement.

**Regle d'or :** Ne jamais utiliser `new`/`delete` directement en C++ moderne. Toujours utiliser `make_unique` ou `make_shared`.

## Les trois smart pointers

### unique_ptr : proprietaire unique

```cpp
#include <memory>

auto p = std::make_unique<int>(42);  // Alloue, p est proprietaire
// p2 = p;                            // ERREUR : pas de copie
auto p2 = std::move(p);             // OK : transfert de propriete
// p est maintenant nullptr
```

### shared_ptr : propriete partagee

```cpp
auto s1 = std::make_shared<int>(42);
auto s2 = s1;                        // OK : compteur de references += 1
// s1 et s2 pointent sur le meme objet
// Libere quand le compteur atteint 0
cout << s1.use_count();              // 2
```

### weak_ptr : reference non-proprietaire

```cpp
auto s = std::make_shared<int>(42);
std::weak_ptr<int> w = s;           // Pas de copropriete
// w.use_count() n'incremente pas le compteur
auto locked = w.lock();             // Essaie d'obtenir un shared_ptr
if (locked) { cout << *locked; }    // Verifie que l'objet existe encore
```

## Schema ASCII : Ownership

```
unique_ptr :

  stack          heap
  +--------+     +-------+
  | uptr   |---->| objet |
  +--------+     +-------+
  (1 proprietaire, ownership non-partageable)
  A la destruction de uptr -> delete automatique

  uptr          uptr2
  +--------+    +--------+    +-------+
  | uptr   |--->| uptr2  |--->| objet |
  +--------+    +--------+    +-------+
  move()  ~~~~>
  uptr devient nullptr, uptr2 devient proprietaire


shared_ptr :

  stack          heap
  +--------+     +-------+
  | sptr1  |---->| objet |<----| sptr2 |
  +--------+     +-------+     +--------+
       \           /
        \         /
        +----------+
        | refcount |  <- 2
        +----------+
  Chaque copie incremente refcount.
  Delete quand refcount == 0.


weak_ptr :

  stack          heap
  +--------+     +-------+
  | sptr   |---->| objet |
  +--------+     +-------+
  +--------+          ^
  | wptr   |~~~~~~~~~~|   (observation, pas de propriete)
  +--------+
  wptr.lock() -> shared_ptr si objet existe, nullptr sinon
  Brise les cycles de reference.
```

## Cas d'usage

| Smart pointer | Quand l'utiliser                              |
|---------------|-----------------------------------------------|
| `unique_ptr`  | Propriete exclusive (la plupart des cas)      |
| `shared_ptr`  | Ressource partagee entre plusieurs ownerss    |
| `weak_ptr`    | Observer sans posseder / briser les cycles    |

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
```
