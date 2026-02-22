# Setup & Hello World 

## Pourquoi c'est important

Avant de hacker quoi que ce soit ou de coder un trading bot, faut savoir compiler du C++.
C'est la base absolue. Pas de raccourci, pas de triche. On commence ici.

---

## C'est quoi C++ ?

C++ est un langage de programmation **compilé** et **performant**. Il te donne un controle total sur la machine :

- **Performance brute** -- Utilise en HFT (High Frequency Trading) ou chaque nanoseconde compte
- **Controle memoire** -- Tu decides ce qui va en memoire et quand ca sort
- **Systeme et bas niveau** -- OS, drivers, moteurs de jeux, outils de securite... tout ca c'est du C++
- **Maldev & Red Team** -- Les outils offensifs serieux sont souvent ecrits en C/C++

---

## C'est quoi un compilateur ?

Ton code C++ est du **texte lisible par un humain**. La machine, elle, ne comprend que le **binaire**.
Le compilateur fait la traduction.

```
  Code source (.cpp)          Compilateur (g++)         Binaire executable        Execution
 ┌──────────────────┐       ┌───────────────────┐       ┌──────────────────┐     ┌──────────┐
 │                  │       │                   │       │                  │     │          │
 │  #include <...>  │──────>│  Analyse le code  │──────>│  01101001...     │────>│  Output  │
 │  int main() {    │       │  Verifie les      │       │  Programme       │     │  sur le  │
 │    cout << ...   │       │  erreurs          │       │  machine natif   │     │  terminal│
 │  }               │       │  Genere le binaire│       │                  │     │          │
 └──────────────────┘       └───────────────────┘       └──────────────────┘     └──────────┘
     hello.cpp                     g++                       ./hello               "Hello!"
```

---

## Installation de g++

### Linux (Ubuntu/Debian)
```bash
sudo apt update && sudo apt install g++ -y
```

### Mac (avec Homebrew)
```bash
xcode-select --install
# ou
brew install gcc
```

### Windows
Installe **MSYS2** depuis https://www.msys2.org/ puis :
```bash
pacman -S mingw-w64-x86_64-gcc
```

### Verifier l'installation
```bash
g++ --version
```
Tu dois voir quelque chose comme `g++ (Ubuntu 13.x.x)` ou `Apple clang version 16.x.x`.

---

## Ton premier programme

Cree un fichier `hello.cpp` :

```cpp
#include <iostream>    // Inclut la bibliotheque d'entree/sortie (Input/Output Stream)
using namespace std;   // Permet d'utiliser cout/cin sans ecrire std:: devant

int main() {           // Point d'entree du programme -- TOUJOURS la
    cout << "Hello, World!" << endl;  // Affiche du texte dans le terminal
    return 0;          // Dit au systeme : "tout s'est bien passe" (code 0)
}
```

### Explication ligne par ligne

| Ligne | Role |
|---|---|
| `#include <iostream>` | Charge la bibliotheque standard pour afficher/lire du texte |
| `using namespace std;` | Raccourci pour ne pas ecrire `std::cout` a chaque fois |
| `int main()` | Fonction principale. C'est ici que le programme demarre |
| `cout << "..."` | Envoie du texte vers la sortie standard (ton terminal) |
| `<< endl` | Retour a la ligne et vide le buffer de sortie |
| `return 0;` | Retourne 0 au systeme = pas d'erreur |

### Compiler et executer

```bash
g++ -o hello hello.cpp    # Compile hello.cpp en un executable nomme "hello"
./hello                    # Execute le programme
```

Tu dois voir :
```
Hello, World!
```

C'est fait. Tu viens de compiler ton premier programme C++. 

---

## Checkpoint 

Avant de passer a la suite, assure-toi de savoir repondre :

1. **Qu'est-ce qu'un compilateur ?**
   > C'est un programme qui transforme ton code source (texte) en binaire executable par la machine.

2. **Quelle commande pour compiler un fichier C++ ?**
   > `g++ -o nom_executable fichier.cpp`

3. **Que fait `#include <iostream>` ?**
   > Ca inclut la bibliotheque standard d'entree/sortie, qui donne acces a `cout` et `cin`.

---

Passe aux exercices dans `exercise.cpp` quand t'es pret. 
