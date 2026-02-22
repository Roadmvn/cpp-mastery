# Chapitre 11 - Move Semantics et RAII

## Le probleme de la copie

Quand tu passes un objet par valeur, C++ le **copie**. Copier un `vector` de 10 millions d'elements = allouer 10M cases et copier chaque element. C'est lent. Les move semantics resolvent ca.

## lvalue vs rvalue

```
lvalue : objet avec une adresse memoire, identifiable, peut etre a gauche de '='
rvalue : valeur temporaire, pas d'adresse stable, vit le temps d'une expression

int x = 42;        // x = lvalue  |  42 = rvalue
int y = x + 1;     // y = lvalue  |  x+1 = rvalue (temporaire)
string s = "hello";// s = lvalue  |  "hello" = rvalue litterale
string t = s;      // s = lvalue -> COPIE
string u = move(s);// move(s) = rvalue -> MOVE (s devient valide mais "vide")
```

## Move constructor et move assignment

```cpp
class Buffer {
    int* data;
    int  size;
public:
    // Copy constructor : alloue et copie (lent)
    Buffer(const Buffer& other)
        : data(new int[other.size]), size(other.size) {
        memcpy(data, other.data, size * sizeof(int));
    }

    // Move constructor : vole les ressources (rapide, O(1))
    Buffer(Buffer&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;  // L'original ne possede plus rien
        other.size = 0;
    }
};
```

## Schema ASCII : Copy vs Move

```
COPY (lent) :

  Avant :          source          copie
                 +--------+      +---------+
                 | data --+----> | 1 2 3 4 |
                 | size=4 |      +---------+
                 +--------+

  Apres Copy :   source          nouvel espace
                 +--------+      +---------+
                 | data --+----> | 1 2 3 4 |
                 | size=4 |      +---------+
                 +--------+
                                +---------+
  dest :         dest           | 1 2 3 4 |  <- allocation + copie
                 +--------+---> +---------+
                 | size=4 |
                 +--------+
  Cout : O(n) allocations + O(n) copies


MOVE (rapide) :

  Avant :         source
                 +--------+     +---------+
                 | data --+---> | 1 2 3 4 |
                 | size=4 |     +---------+
                 +--------+

  Apres Move :   source (invalide)    dest
                 +----------+        +--------+     +---------+
                 | data=null |        | data --+---> | 1 2 3 4 |
                 | size=0   |        | size=4 |     +---------+
                 +----------+        +--------+
  Cout : O(1) - juste des copies de pointeurs !
```

## RAII : Resource Acquisition Is Initialization

Le principe : **acquis dans le constructeur, libere dans le destructeur**. La duree de vie de la ressource est liee a la duree de vie de l'objet.

```cpp
class FileHandle {
    FILE* f;
public:
    explicit FileHandle(const char* path, const char* mode)
        : f(fopen(path, mode)) {
        if (!f) throw runtime_error("Cannot open file");
    }
    ~FileHandle() {
        if (f) fclose(f);  // Toujours libere, meme en cas d'exception
    }
    // Pas de copie
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
};
```

RAII = gestion automatique de la duree de vie. C'est ce que font `unique_ptr`, `lock_guard`, `ifstream`, etc.

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp && ./exercise
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp && ./solution
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp && ./challenge
```
