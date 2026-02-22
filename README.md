# Full C++ : De Zero a Hero

**Maîtrise C++ de A à Z — LeetCode, HFT, Red Team.**

Un repo structuré, progressif et sans bullshit pour apprendre C++ en partant de zéro et devenir dangereux dans 3 domaines : algorithmes compétitifs, trading haute fréquence et sécurité offensive.

---

## Pour qui ?

- Tu n'as **jamais codé** ou tu viens d'un autre langage
- Tu veux **grind LeetCode** en C++ (le langage le plus rapide sur les judges)
- Tu vises un poste en **HFT / low-latency** (Jane Street, Citadel, Jump Trading...)
- Tu veux faire du **Red Team / Maldev** avec un langage qui tourne sans runtime
- Tu veux simplement **comprendre comment la machine fonctionne vraiment**

Pas besoin de diplôme. Pas besoin d'expérience. Juste un PC et de la ténacité.

---

## Prérequis

### Ce qu'il te faut

- Un ordinateur (Linux, Mac ou Windows)
- Un terminal
- Un éditeur de code (VS Code recommandé)
- `g++` installé

### Installer g++

**Linux (Ubuntu/Debian) :**
```bash
sudo apt update && sudo apt install g++ build-essential -y
g++ --version
```

**Mac :**
```bash
xcode-select --install
g++ --version
```

**Windows :**
```
1. Installer MSYS2  https://www.msys2.org
2. Dans le terminal MSYS2 : pacman -S mingw-w64-x86_64-gcc
3. Ajouter C:\msys64\mingw64\bin au PATH
4. Ouvrir un nouveau terminal : g++ --version
```

Si `g++ --version` affiche un numéro de version, t'es bon. Let's go.

---

## Roadmap

```
                    FULL C++ : ZERO TO HERO
  ============================================================

  Semaines 1-3        Semaines 4-5        Semaines 6-7
  +----------------+  +----------------+  +----------------+
  |  FOUNDATIONS   |  |  MEMORY &      |  |     OOP        |
  |                |--|  ARRAYS        |--|                |
  | Variables      |  | Pointeurs      |  | Classes        |
  | Boucles        |  | new/delete     |  | Heritage       |
  | Fonctions      |  | References     |  | Polymorphisme  |
  | Conditions     |  | Recursion      |  | Smart Ptrs     |
  +----------------+  +----------------+  +--------+-------+
                                                   |
                      +----------------------------+
                      |
                      v
  Semaines 8-9        Semaines 10-14
  +----------------+  +----------------+
  |  STL MASTERY   |  |  DSA &         |
  |                |--|  LEETCODE      |
  | Vectors        |  |               |
  | Maps/Sets      |  | Two Pointers  |
  | Queues         |  | Binary Search |
  | Algorithmes    |  | Trees/Graphs  |
  | Lambdas        |  | DP & Greedy   |
  +----------------+  +-------+--------+
                              |
              +---------------+---------------+
              |                               |
              v                               v
  +-------------------+       +-------------------+
  |    TRACK HFT      |       |  TRACK OFFENSIVE  |
  |                   |       |                   |
  | Cache Lines       |       | Win32 API         |
  | Lock-Free         |       | Process Injection |
  | SIMD              |       | Shellcode         |
  | Networking        |       | Evasion           |
  | Matching Engine   |       | C2 Implants       |
  +-------------------+       +-------------------+
```

---

## Comment utiliser ce repo

Chaque chapitre suit le même format :

```
XX-nom-du-chapitre/
├── README.md          # Théorie complète avec exemples
├── exercise.cpp       # Exercices guidés (à compléter)
├── solution.cpp       # Solutions commentées
└── challenge.cpp      # Défi bonus pour aller plus loin
```

### La méthode

1. **Lis le README.md** du chapitre — comprends la théorie
2. **Code `exercise.cpp`** — mets en pratique immédiatement
3. **Compare avec `solution.cpp`** — seulement après avoir essayé
4. **Attaque `challenge.cpp`** — pousse tes limites

### Compiler et exécuter

```bash
g++ -std=c++17 -o programme fichier.cpp
./programme
```

Ajoute `-Wall -Wextra` pour activer les warnings (recommandé) :
```bash
g++ -std=c++17 -Wall -Wextra -o programme fichier.cpp
```

---

## Table des matieres

### Fondations (Semaines 1-3)
| # | Chapitre | Description |
|---|----------|-------------|
| 01 | [Setup & Hello World](01-foundations/01-setup-hello-world) | Premier programme, compilation, exécution |
| 02 | [Variables & Types](01-foundations/02-variables-types) | int, float, double, char, bool, string |
| 03 | [Const](01-foundations/03-const) | Constantes et immutabilité |
| 04 | [Namespaces](01-foundations/04-namespaces) | Organisation du code, std:: |
| 05 | [Typedef & Aliases](01-foundations/05-typedef-aliases) | using, typedef, alias de types |

### Memory & Arrays (Semaines 4-5)
| # | Chapitre | Description |
|---|----------|-------------|
| 01 | [Arrays](02-memory-and-arrays/01-arrays) | Tableaux statiques, déclaration, accès |
| 02 | [Sizeof](02-memory-and-arrays/02-sizeof-operator) | Taille des types en mémoire |
| 03 | [Itérer sur un array](02-memory-and-arrays/03-iterate-arrays) | Boucles for, while sur tableaux |
| 04 | [Foreach](02-memory-and-arrays/04-foreach-loop) | Range-based for loop |
| 05 | [Passer un array](02-memory-and-arrays/05-pass-array-to-function) | Arrays en paramètres de fonctions |
| 06 | [Recherche](02-memory-and-arrays/06-search-array) | Recherche linéaire et binaire |
| 07 | [Tri](02-memory-and-arrays/07-sort-array) | Bubble sort, selection sort |
| 08 | [Arrays 2D](02-memory-and-arrays/08-multidimensional-arrays) | Matrices et tableaux multidimensionnels |
| 09 | [Adresses mémoire](02-memory-and-arrays/09-memory-addresses) | &variable, comprendre la RAM |
| 10 | [Valeur vs Référence](02-memory-and-arrays/10-pass-by-value-vs-reference) | Passage par copie vs par référence |
| 11 | [Pointeurs](02-memory-and-arrays/11-pointers) | *, &, arithmétique de pointeurs |
| 12 | [Null Pointers](02-memory-and-arrays/12-null-pointers) | nullptr, vérifications |
| 13 | [Mémoire dynamique](02-memory-and-arrays/13-dynamic-memory-new-delete) | new, delete, heap vs stack |
| 14 | [Récursion](02-memory-and-arrays/14-recursion) | Fonctions récursives, call stack |
| 15 | [Templates](02-memory-and-arrays/15-function-templates) | Fonctions génériques |

### OOP (Semaines 6-7)
| # | Chapitre | Description |
|---|----------|-------------|
| 01 | [Structs](03-oop/01-structs) | Structures de données custom |
| 02 | [Enums](03-oop/02-enums) | Énumérations, enum class |
| 03 | [Classes & Objets](03-oop/03-classes-objects) | Encapsulation, attributs, méthodes |
| 04 | [Constructeurs](03-oop/04-constructors) | Initialisation d'objets |
| 05 | [Surcharge constructeurs](03-oop/05-constructor-overloading) | Constructeurs multiples |
| 06 | [Getters & Setters](03-oop/06-getters-setters) | Accès contrôlé aux données |
| 07 | [Héritage](03-oop/07-inheritance) | Classes dérivées, réutilisation |
| 08 | [Polymorphisme](03-oop/08-polymorphism-virtual) | virtual, override, vtable |
| 09 | [Classes abstraites](03-oop/09-abstract-classes) | Interfaces, pure virtual |
| 10 | [Smart Pointers](03-oop/10-smart-pointers) | unique_ptr, shared_ptr, weak_ptr |
| 11 | [Move Semantics & RAII](03-oop/11-move-semantics-raii) | std::move, gestion des ressources |

### STL Mastery (Semaines 8-9)
| # | Chapitre | Description |
|---|----------|-------------|
| 01 | [Vectors](04-stl-mastery/01-vectors) | Le tableau dynamique de la STL |
| 02 | [Strings avancé](04-stl-mastery/02-strings-advanced) | Manipulation de chaînes |
| 03 | [Pairs & Tuples](04-stl-mastery/03-pairs-tuples) | Conteneurs légers |
| 04 | [Stack](04-stl-mastery/04-stack) | Pile LIFO |
| 05 | [Queue & Deque](04-stl-mastery/05-queue-deque) | File FIFO, double-ended |
| 06 | [Priority Queue](04-stl-mastery/06-priority-queue-heap) | Heap, min/max priority |
| 07 | [Unordered Map](04-stl-mastery/07-unordered-map) | Hash map O(1) |
| 08 | [Unordered Set](04-stl-mastery/08-unordered-set) | Hash set O(1) |
| 09 | [Map & Set ordonnés](04-stl-mastery/09-map-set-ordered) | Red-black tree, O(log n) |
| 10 | [Iterators](04-stl-mastery/10-iterators) | Parcours générique |
| 11 | [Algorithmes STL](04-stl-mastery/11-algorithms-sort-find) | sort, find, transform... |
| 12 | [Lambdas](04-stl-mastery/12-lambda-functions) | Fonctions anonymes, captures |

### DSA & LeetCode (Semaines 10-14)
| # | Chapitre | Description |
|---|----------|-------------|
| 00 | [Big O](05-dsa-leetcode/00-big-o-complexity) | Complexité temporelle et spatiale |
| 01 | [Two Pointers](05-dsa-leetcode/01-two-pointers) | Technique à deux pointeurs |
| 02 | [Sliding Window](05-dsa-leetcode/02-sliding-window) | Fenêtre glissante |
| 03 | [Binary Search](05-dsa-leetcode/03-binary-search) | Recherche dichotomique |
| 04 | [Linked Lists](05-dsa-leetcode/04-linked-lists) | Listes chaînées |
| 05 | [Stacks & Queues](05-dsa-leetcode/05-stacks-queues-problems) | Problèmes classiques |
| 06 | [Hash Maps](05-dsa-leetcode/06-hash-maps-problems) | Problèmes de hash |
| 07 | [Trees](05-dsa-leetcode/07-trees-binary-tree) | Arbres binaires |
| 08 | [BST](05-dsa-leetcode/08-bst) | Arbres binaires de recherche |
| 09 | [BFS & DFS](05-dsa-leetcode/09-bfs-dfs) | Parcours en largeur et profondeur |
| 10 | [Graphs](05-dsa-leetcode/10-graphs) | Graphes, adjacency list/matrix |
| 11 | [Dynamic Programming](05-dsa-leetcode/11-dynamic-programming) | Mémoïsation, tabulation |
| 12 | [Backtracking](05-dsa-leetcode/12-backtracking) | Exploration exhaustive |
| 13 | [Greedy](05-dsa-leetcode/13-greedy) | Algorithmes gloutons |
| 14 | [Heap Problems](05-dsa-leetcode/14-heap-problems) | Top K, médiane, merge |
| 15 | [Tries](05-dsa-leetcode/15-tries) | Arbres préfixés |

### Tracks de spécialisation
| Track | Description | Lien |
|-------|-------------|------|
| HFT Low-Latency  | Cache, lock-free, SIMD, networking, matching engine | [track-hft/](track-hft/) |
| Offensive / Red Team  | Win32 API, injection, shellcode, evasion, C2 | [track-offensive/](track-offensive/) |

### Projets finaux
| Projet | Description |
|--------|-------------|
| [HFT Order Book Simulator](projects/hft-orderbook-simulator) | Simulateur d'order book complet |
| [C2 Implant](projects/c2-implant-cpp) | Implant C2 custom en C++ |

---

## Structure du repo

```
full-c++/
│
├── README.md
│
├── 01-foundations/              # Semaines 1-3
│   ├── 01-setup-hello-world/
│   ├── 02-variables-types/
│   ├── 03-const/
│   ├── 04-namespaces/
│   ├── 05-typedef-aliases/
│   └── mini-projects/
│
├── 02-memory-and-arrays/       # Semaines 4-5
│   ├── 01-arrays/
│   ├── ...
│   ├── 15-function-templates/
│   └── mini-projects/
│
├── 03-oop/                     # Semaines 6-7
│   ├── 01-structs/
│   ├── ...
│   ├── 11-move-semantics-raii/
│   └── mini-projects/
│
├── 04-stl-mastery/             # Semaines 8-9
│   ├── 01-vectors/
│   ├── ...
│   └── 12-lambda-functions/
│
├── 05-dsa-leetcode/            # Semaines 10-14
│   ├── 00-big-o-complexity/
│   ├── ...
│   ├── 15-tries/
│   └── leetcode-solutions/
│
├── track-hft/                  # Spécialisation HFT
│   ├── 01-cache-optimization/
│   ├── ...
│   ├── 08-latency-measurement/
│   └── projects/matching-engine/
│
├── track-offensive/            # Spécialisation Red Team
│   ├── 01-win32-api-basics/
│   ├── ...
│   ├── 08-persistence-mechanisms/
│   └── projects/custom-implant/
│
└── projects/                   # Projets intégrateurs
    ├── hft-orderbook-simulator/
    └── c2-implant-cpp/
```

---

## Let's go

Commence par [01-foundations/01-setup-hello-world](01-foundations/01-setup-hello-world) et avance chapitre par chapitre. Pas de raccourcis. Chaque concept s'appuie sur le précédent.

La différence entre toi et quelqu'un qui maîtrise C++, c'est juste du temps et de la discipline. Le repo est là. Le chemin est tracé. A toi de marcher.

```
g++ -o start 01-foundations/01-setup-hello-world/exercise.cpp && ./start
```
