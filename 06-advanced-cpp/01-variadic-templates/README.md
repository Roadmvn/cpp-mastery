# Chapitre 01 — Variadic Templates

## Concept

Un template variadique accepte un nombre arbitraire de paramètres de type. C'est la base
de nombreux composants de la bibliothèque standard : `std::tuple`, `std::make_unique`,
`std::printf` type-safe, etc.

```cpp
template<typename... Args>   // "Args" est un parameter pack
void print(Args... args);    // "args" est un argument pack
```

---

## sizeof...

`sizeof...(args)` retourne le nombre d'éléments dans le pack, à la compilation.

```cpp
template<typename... Args>
void show_count(Args... args) {
    std::cout << sizeof...(args) << "\n";  // nombre d'arguments
}

show_count(1, 2.0, "hello");  // affiche 3
```

---

## Pack expansion

Le pack s'étend avec `...` après l'expression qui le contient :

```cpp
template<typename... Args>
void print_all(Args... args) {
    // Fold expression (C++17) — voir ci-dessous
    (std::cout << ... << args);
}

// Expansion dans un initializer list (C++11/14)
template<typename... Args>
void print_all_legacy(Args... args) {
    int dummy[] = { (std::cout << args << " ", 0)... };
    (void)dummy;
}
```

---

## Fold expressions (C++17)

Syntaxe compacte pour appliquer un opérateur sur tout le pack :

```
Unary fold gauche  :  (... op pack)      =>  ((a op b) op c)
Unary fold droite  :  (pack op ...)      =>  (a op (b op c))
Binary fold gauche :  (init op ... op pack)
Binary fold droite :  (pack op ... op init)
```

Exemples :

```cpp
template<typename... Ts>
auto sum(Ts... args) {
    return (... + args);          // fold gauche sur +
}

template<typename... Ts>
bool all_positive(Ts... args) {
    return (... && (args > 0));   // fold gauche sur &&
}

template<typename... Ts>
void print(Ts... args) {
    (std::cout << ... << args);   // fold gauche sur <<
}
```

---

## Récursion (technique C++11/14 avant fold)

Avant les fold expressions, on récurse explicitement :

```cpp
// Cas de base
void print() {}

// Cas récursif
template<typename First, typename... Rest>
void print(First first, Rest... rest) {
    std::cout << first << " ";
    print(rest...);   // récursion sur le reste du pack
}
```

---

## Diagramme : expansion du pack

```
Appel : print(1, 2.5, "ok")
                |
    template<First=int, Rest={double, const char*}>
                |
    cout << 1      print(2.5, "ok")
                        |
            template<First=double, Rest={const char*}>
                        |
            cout << 2.5    print("ok")
                                |
                    template<First=const char*, Rest={}>
                                |
                    cout << "ok"   print()   <-- cas de base
```

---

## Fichiers

| Fichier | Description |
|---------|-------------|
| `exercise.cpp` | Implémenter sum(), print(), et un tuple simplifié |
| `solution.cpp` | Solution complète avec commentaires |
| `challenge.cpp` | Logger variadique formaté pour HFT |
