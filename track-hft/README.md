# Track HFT : Low-Latency C++

**Deviens le dev qui fait tourner les marchés financiers.**

Le trading haute fréquence (HFT), c'est là où chaque **nanoseconde** compte. Les firmes comme Citadel, Jump Trading, Jane Street et Tower Research utilisent C++ parce qu'aucun autre langage ne donne ce niveau de contrôle sur le hardware. Pas de garbage collector, pas de runtime, pas de surprises. Juste toi, le CPU et la mémoire.

Dans ce track, tu vas apprendre à écrire du code C++ qui rivalise avec ce qui tourne en production dans les plus grosses firmes de trading du monde.

---

## Ce que tu vas maîtriser

- Optimisation cache L1/L2/L3 et data locality
- Allocation mémoire custom sans fragmentation
- Structures lock-free pour le multithreading sans mutex
- Networking TCP/UDP ultra-rapide
- Programmation SIMD (vectorisation CPU)
- Mesure et réduction de la latence au niveau nanoseconde
- Construction d'un matching engine complet

---

## Prérequis

Tu **dois** avoir complété ces sections avant de commencer :

| Section | Pourquoi |
|---------|----------|
| [01-foundations](../01-foundations) | Syntaxe C++ de base |
| [02-memory-and-arrays](../02-memory-and-arrays) | Pointeurs, mémoire dynamique, références |
| [03-oop](../03-oop) | Classes, héritage, smart pointers, RAII |
| [04-stl-mastery](../04-stl-mastery) | Containers STL, iterators, algorithmes |

Si tu n'as pas fait ces sections, retourne au [README principal](../README.md). Pas de raccourcis.

---

## Roadmap détaillée

### 01 — Cache Optimization
[`01-cache-optimization/`](01-cache-optimization/)

Ton CPU est rapide. Ta RAM est lente. Le cache est le pont entre les deux, et la plupart des devs l'ignorent complètement. Tu vas apprendre comment structurer tes données pour que le CPU les trouve **toujours** dans le cache.

**Concepts clés :**
- Hiérarchie mémoire : registres  L1  L2  L3  RAM
- Cache lines (64 bytes), cache hits vs cache misses
- Data locality : spatial et temporal
- Structure of Arrays (SoA) vs Array of Structures (AoS)
- False sharing et padding
- `__builtin_prefetch`, alignement mémoire

**Après ce chapitre :** Tu sauras organiser tes données pour des accès mémoire 10x plus rapides. Tu comprendras pourquoi un `vector<int>` écrase un `list<int>` en performance.

---

### 02 — Memory Pools & Allocators 🏊
[`02-memory-pools-allocators/`](02-memory-pools-allocators/)

`new` et `delete` sont trop lents pour le HFT. Chaque allocation passe par l'OS, et ça prend des **microsecondes**. En HFT, on pré-alloue tout. Tu vas construire tes propres allocateurs.

**Concepts clés :**
- Problème de `malloc`/`new` : fragmentation, syscalls, locks
- Pool allocators : pré-allocation de blocs fixes
- Arena allocators : allocation linéaire ultra-rapide
- Slab allocators : pools par taille d'objet
- `std::pmr` (Polymorphic Memory Resources)
- Placement new

**Après ce chapitre :** Tu sauras écrire un allocateur custom qui élimine les allocations dynamiques en hot path. Zéro appel à l'OS pendant l'exécution critique.

---

### 03 — Lock-Free Data Structures 🔓
[`03-lock-free-structures/`](03-lock-free-structures/)

Les mutex tuent la performance. Quand un thread attend un lock, il dort. En HFT, personne ne dort. Tu vas apprendre à écrire des structures de données qui fonctionnent sans aucun lock.

**Concepts clés :**
- Pourquoi les mutex sont interdits en hot path
- `std::atomic`, memory ordering (relaxed, acquire, release, seq_cst)
- Compare-And-Swap (CAS) : la brique de base du lock-free
- SPSC queue (Single Producer Single Consumer) lock-free
- MPSC queue (Multiple Producer Single Consumer)
- ABA problem et solutions
- Hazard pointers, epoch-based reclamation

**Après ce chapitre :** Tu sauras construire une queue lock-free SPSC avec une latence de quelques nanosecondes. C'est la structure la plus utilisée en HFT pour passer des messages entre threads.

---

### 04 — Networking : TCP & UDP
[`04-networking-tcp-udp/`](04-networking-tcp-udp/)

Les marchés envoient des données via le réseau. Tu dois les recevoir le plus vite possible. TCP pour les ordres (fiabilité), UDP multicast pour les market data (vitesse). Tu vas coder des deux côtés.

**Concepts clés :**
- Sockets POSIX : `socket()`, `bind()`, `listen()`, `accept()`
- TCP : connexion fiable, Nagle's algorithm (et pourquoi le désactiver)
- UDP : datagrams, multicast, broadcast
- `epoll` / `kqueue` : I/O multiplexing sans threads
- Kernel bypass : concepts de DPDK et Solarflare OpenOnload
- Sérialisation zero-copy avec `reinterpret_cast`

**Après ce chapitre :** Tu sauras écrire un serveur TCP et un récepteur UDP multicast optimisés. Tu comprendras comment les feeds de marché arrivent et comment les traiter avec une latence minimale.

---

### 05 — Multithreading & Atomics
[`05-multithreading-atomics/`](05-multithreading-atomics/)

Le HFT utilise le multithreading, mais pas comme une app web. Chaque thread est pinné à un core CPU. Pas de context switching, pas de migrations. Tu vas apprendre le threading de précision.

**Concepts clés :**
- `std::thread`, `std::jthread`
- Thread affinity : `pthread_setaffinity_np`, CPU pinning
- Spinlocks vs mutex : quand utiliser quoi
- Thread-local storage (`thread_local`)
- Busy-waiting : pourquoi c'est acceptable en HFT
- Isoler les cores CPU (`isolcpus`, `taskset`)
- Pipeline threading : chaque thread = une étape du pipeline

**Après ce chapitre :** Tu sauras architecturer une application multi-threadée où chaque thread est dédié à une tâche précise sur un core isolé, sans contention.

---

### 06 — SIMD & Intrinsics 🚄
[`06-simd-intrinsics/`](06-simd-intrinsics/)

Ton CPU peut traiter 4, 8 ou même 16 données en **une seule instruction**. C'est le SIMD (Single Instruction Multiple Data). Les firmes HFT l'utilisent pour parser les market data à la vitesse du hardware.

**Concepts clés :**
- SSE, SSE2, AVX, AVX2, AVX-512
- Types vectoriels : `__m128`, `__m256`, `__m512`
- Intrinsics : `_mm256_add_ps`, `_mm256_cmp_pd`, etc.
- Auto-vectorisation du compilateur et ses limites
- SIMD pour parser du texte (FIX protocol)
- SIMD pour les calculs de prix et risk

**Après ce chapitre :** Tu sauras utiliser les instructions SIMD pour traiter des données 4-8x plus vite qu'en code scalaire. Tu comprendras quand le compilateur vectorise automatiquement et quand il faut le faire à la main.

---

### 07 — Order Book Engine
[`07-order-book-engine/`](07-order-book-engine/)

L'order book, c'est le coeur de tout exchange. Buy orders d'un côté, sell orders de l'autre, et un matching engine au milieu qui croise les ordres. Tu vas en construire un de A à Z.

**Concepts clés :**
- Structure d'un order book : bids, asks, price levels
- Types d'ordres : limit, market, cancel, modify
- Matching algorithms : price-time priority (FIFO)
- Structures de données optimales : `std::map` vs intrusive lists
- Order indexing par ID pour cancel/modify en O(1)
- Message parsing (simulated FIX/ITCH)

**Après ce chapitre :** Tu auras un order book fonctionnel qui gère les ordres limit/market avec matching price-time priority. La base de ton projet final.

---

### 08 — Latency Measurement
[`08-latency-measurement/`](08-latency-measurement/)

"Ce qui ne se mesure pas ne s'améliore pas." En HFT, tu mesures tout en nanosecondes. Tu vas apprendre à profiler ton code avec une précision chirurgicale.

**Concepts clés :**
- `std::chrono::high_resolution_clock` et ses limites
- `rdtsc` / `rdtscp` : lire le compteur CPU directement
- Percentiles : p50, p99, p99.9 (la moyenne ment)
- Microbenchmarking avec Google Benchmark
- `perf stat`, `perf record`, flamegraphs
- Cache profiling : `perf` events (L1-dcache-load-misses)
- Jitter : sources et mitigation (NUMA, CPU freq, interrupts)

**Après ce chapitre :** Tu sauras mesurer la latence de n'importe quel code au nanoseconde près, identifier les bottlenecks et les éliminer systématiquement.

---

## Projet final : Matching Engine
[`projects/matching-engine/`](projects/matching-engine/)

Tout ce que tu as appris converge ici. Tu vas construire un **matching engine complet** avec :

- Order book multi-symboles
- Matching price-time priority
- Queue SPSC lock-free entre les composants
- Memory pool custom pour zero-allocation en hot path
- Réception des ordres via TCP
- Market data broadcast via UDP multicast
- Mesure de latence tick-to-trade < 10 microsecondes

---

## Architecture d'un système HFT

```
    ┌─────────────────────────────────────────────────────────────────┐
    │                    EXCHANGE / MARCHE                            │
    └───────────┬──────────────────────────────────┬──────────────────┘
                │ UDP Multicast                    ▲ TCP
                │ (Market Data)                    │ (Orders)
                ▼                                  │
    ┌───────────────────┐                          │
    │   FEED HANDLER    │                          │
    │                   │                          │
    │ Parse ITCH/FIX    │                          │
    │ Normalize data    │                          │
    │ SIMD parsing      │                          │
    └────────┬──────────┘                          │
             │ SPSC Queue                          │
             │ (lock-free)                         │
             ▼                                     │
    ┌───────────────────┐    ┌──────────────┐      │
    │   ORDER BOOK      │───>│   STRATEGY   │      │
    │                   │    │   ENGINE     │      │
    │ Update bids/asks  │    │              │      │
    │ Price levels      │    │ Signal gen   │      │
    │ BBO tracking      │    │ Alpha calc   │      │
    └───────────────────┘    └──────┬───────┘      │
                                    │              │
                                    ▼              │
                             ┌──────────────┐      │
                             │     RISK     │      │
                             │    CHECK     │      │
                             │              │      │
                             │ Position lim │      │
                             │ Order size   │      │
                             │ Rate limit   │      │
                             └──────┬───────┘      │
                                    │              │
                                    ▼              │
                             ┌──────────────┐      │
                             │  ORDER       │──────┘
                             │  GATEWAY     │
                             │              │
                             │ Serialize    │
                             │ Send to exch │
                             └──────────────┘

    ══════════════════════════════════════════════════
     Latence totale tick-to-trade : < 10 microsecondes
    ══════════════════════════════════════════════════
```

Chaque composant tourne sur son propre core CPU isolé, communique via des queues lock-free, et n'alloue **aucune mémoire** en hot path.

---

## Ressources recommandées 📚

### Livres
- **"C++ High Performance"** — Bjorn Andrist & Viktor Sehr — Optimisation moderne C++
- **"The Art of Writing Efficient Programs"** — Fedor Pikus — Performance-oriented C++
- **"Is Parallel Programming Hard, And, If So, What Can You Do About It?"** — Paul McKenney — Lock-free et concurrence (gratuit en PDF)
- **"Computer Systems: A Programmer's Perspective"** — Bryant & O'Hallaron — Comprendre le hardware

### Blogs et sites
- [Mechanical Sympathy](https://mechanical-sympathy.blogspot.com/) — Martin Thompson, légende du low-latency
- [Brendan Gregg's Blog](https://www.brendangregg.com/) — Profiling et performance systems
- [CppCon YouTube](https://www.youtube.com/user/CppCon) — Talks pointus sur la performance C++
- [Agner Fog's Manuals](https://www.agner.org/optimize/) — Bibles de l'optimisation x86

### Tools
- **perf** — Profiler Linux intégré au kernel
- **Google Benchmark** — Micro-benchmarking framework
- **Compiler Explorer (godbolt.org)** — Voir l'assembleur généré par ton code
- **Valgrind / Cachegrind** — Analyse cache et mémoire

---

## Let's trade

```
g++ -std=c++17 -O2 -march=native -o cache 01-cache-optimization/exercise.cpp && ./cache
```

Le flag `-O2` active les optimisations du compilateur. `-march=native` cible ton CPU exact. C'est comme ça qu'on compile en HFT.
