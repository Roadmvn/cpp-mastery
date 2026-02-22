# Chapitre 02 - Les Enumerations (enum) en C++ 🔢

## Concept fondamental 

Une **enumeration** definit un type avec un ensemble fini de valeurs nommees. C'est le moyen propre de representer des constantes liees entre elles.

## Enum classique (C-style) 📜

```cpp
enum Couleur { ROUGE, VERT, BLEU };  // 0, 1, 2

Couleur c = ROUGE;
int val = VERT;   // Conversion implicite vers int - DANGER
```

Problemes de l'enum classique :
- Les valeurs polluent le scope global
- Conversion implicite vers int (pas type-safe)
- Risque de collision de noms

## Enum class (C++11) - La bonne pratique 

```cpp
enum class Direction { NORD, SUD, EST, OUEST };

Direction d = Direction::NORD;
// int val = d;                    // ERREUR : pas de conversion implicite
int val = static_cast<int>(d);    // Conversion explicite : OK
```

## Comparaison visuelle 

```
enum classique           enum class (C++11)
+------------------+     +------------------+
| ROUGE = 0        |     | Couleur::ROUGE   |
| VERT  = 1        |     | Couleur::VERT    |
| BLEU  = 2        |     | Couleur::BLEU    |
+------------------+     +------------------+
  Scope: GLOBAL            Scope: Couleur::
  Conversion: implicite    Conversion: explicite
  Type-safe: NON           Type-safe: OUI
```

## Underlying type (type sous-jacent) 

```cpp
// Par defaut : int (4 bytes)
enum class Status : uint8_t {   // Force 1 byte
    OK = 0,
    ERROR = 1,
    PENDING = 2
};

// Utile en HFT : economiser de la memoire dans les structs
sizeof(Status);  // 1 byte au lieu de 4
```

## Valeurs personnalisees 

```cpp
enum class HttpCode : uint16_t {
    OK          = 200,
    NOT_FOUND   = 404,
    INTERNAL    = 500,
    BAD_GATEWAY = 502
};
```

## Pattern : enum vers string 

```cpp
enum class Niveau { DEBUTANT, INTERMEDIAIRE, AVANCE };

std::string to_string(Niveau n) {
    switch (n) {
        case Niveau::DEBUTANT:       return "Debutant";
        case Niveau::INTERMEDIAIRE:  return "Intermediaire";
        case Niveau::AVANCE:         return "Avance";
    }
    return "Inconnu";
}
```

## Utilisation avec switch 

```cpp
enum class Action { ACHETER, VENDRE, ANNULER };

void executer(Action a) {
    switch (a) {
        case Action::ACHETER:  /* ... */ break;
        case Action::VENDRE:   /* ... */ break;
        case Action::ANNULER:  /* ... */ break;
    }
    // Le compilateur previent si un cas est oublie avec -Wall
}
```

## Bonnes pratiques 

1. **Toujours** utiliser `enum class` (jamais `enum` seul)
2. Specifier le type sous-jacent si la taille compte
3. Fournir une fonction `to_string()` pour l'affichage
4. Utiliser `-Wall` pour que le compilateur detecte les switch incomplets

## Compilation 🔨

```bash
g++ -std=c++17 -Wall -Wextra -o exercise exercise.cpp
g++ -std=c++17 -Wall -Wextra -o solution solution.cpp
g++ -std=c++17 -Wall -Wextra -o challenge challenge.cpp
```
