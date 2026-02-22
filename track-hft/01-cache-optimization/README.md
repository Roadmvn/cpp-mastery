# Chapitre 01 - Cache Optimization 🔥

## Pourquoi c'est critique en HFT ⚡

En HFT, chaque **nanoseconde** compte. La difference entre lire depuis le cache L1 et la RAM,
c'est un facteur **~100x**. Un code qui provoque des **cache misses** perd la course avant meme
de commencer. Les meilleurs systemes HFT sont designes autour du cache, pas autour de la logique.

## Hierarchie memoire - Latences reelles 📊

```
┌─────────────────────────────────────────────────────────────┐
│                    CPU Core                                  │
│  ┌─────────────────────────────┐                            │
│  │  Registres   ~ 0.3 ns       │  ◄── Acces instantane     │
│  └──────────┬──────────────────┘                            │
│             ▼                                                │
│  ┌─────────────────────────────┐                            │
│  │  Cache L1   32-64 KB        │  ◄── ~1 ns    (4 cycles)  │
│  │  (par core, split I/D)      │                            │
│  └──────────┬──────────────────┘                            │
│             ▼                                                │
│  ┌─────────────────────────────┐                            │
│  │  Cache L2   256 KB - 1 MB   │  ◄── ~4 ns   (12 cycles)  │
│  │  (par core)                 │                            │
│  └──────────┬──────────────────┘                            │
│             ▼                                                │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────────────────────┐                            │
│  │  Cache L3   8-64 MB         │  ◄── ~12 ns  (36 cycles)  │
│  │  (partage entre cores)      │                            │
│  └──────────┬──────────────────┘                            │
│             ▼                                                │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────────────────────┐                            │
│  │  RAM (DRAM)  16-256 GB      │  ◄── ~100 ns (300 cycles) │
│  └─────────────────────────────┘                            │
└─────────────────────────────────────────────────────────────┘
```

## Cache Line - L'unite fondamentale 📦

Le CPU ne lit **jamais** un seul octet. Il charge toujours une **cache line** de **64 octets**.

```
Adresse memoire:  0x1000  0x1040  0x1080  0x10C0
                    │       │       │       │
                    ▼       ▼       ▼       ▼
                 ┌──────┬──────┬──────┬──────┐
    RAM:         │ 64 B │ 64 B │ 64 B │ 64 B │  ...
                 └──┬───┴──────┴──────┴──────┘
                    │
          Tu demandes 1 int a 0x1004?
          Le CPU charge TOUTE la ligne 0x1000-0x103F
                    │
                    ▼
                 ┌──────┐
    Cache L1:    │ 64 B │  ◄── Cache line complete
                 └──────┘
```

## Data Locality - Sequentiel vs Random 🎯

```
ACCES SEQUENTIEL (cache-friendly) ✅          ACCES RANDOM (cache-hostile) ❌
┌───┬───┬───┬───┬───┬───┬───┬───┐           ┌───┬───┬───┬───┬───┬───┬───┬───┐
│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │           │   │   │ 3 │   │   │ 1 │   │ 2 │
└─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘           └───┴───┴─┬─┴───┴───┴─┬─┴───┴─┬─┘
  │   │   │   │   │   │   │   │                         │           │       │
  ▼   ▼   ▼   ▼   ▼   ▼   ▼   ▼                         ▼           ▼       ▼
  1 cache line = 8 ints charges             Chaque acces = potentiel cache miss
  7 hits gratuits apres 1 miss!             Latence x100 a chaque saut
```

## Struct Padding & Alignment 🧱

Le compilateur ajoute du **padding** pour aligner les membres. Ca gaspille de la memoire
et ca peut causer des cache misses supplementaires.

```
MAUVAIS (24 octets avec padding):           BON (16 octets, compact):
struct Bad {                                struct Good {
  char  a;    // 1 byte                      double y;  // 8 bytes
  // 7 bytes PADDING !!                      int    x;  // 4 bytes
  double y;   // 8 bytes                     char   a;  // 1 byte
  int    x;   // 4 bytes                     char   b;  // 1 byte
  char   b;   // 1 byte                      // 2 bytes padding
  // 3 bytes PADDING !!                    };  // Total: 16 bytes
};  // Total: 24 bytes

Layout memoire:                             Layout memoire:
[a|.|.|.|.|.|.|.][y y y y y y y y]          [y y y y y y y y][x x x x|a|b|.|.]
[x x x x|b|.|.|.]
     3 lignes potentielles                       2 lignes max = plus compact
```

## alignas - Forcer l'alignement 🔧

```cpp
// Force la struct a etre alignee sur une cache line
struct alignas(64) MarketData {
    double price;      // 8
    int    quantity;    // 4
    int    order_id;   // 4
    char   side;       // 1
    // padding auto    // 43 bytes
};  // Total: exactement 64 bytes = 1 cache line

// Empeche le false sharing entre threads
struct alignas(64) PerThreadCounter {
    std::atomic<long> count{0};
    // Chaque thread a sa propre cache line
};
```

## Prefetching 🚀

Dire au CPU de charger une donnee en cache **avant** d'en avoir besoin.

```cpp
// Le CPU charge data[i+16] pendant qu'on traite data[i]
for (int i = 0; i < N; i++) {
    __builtin_prefetch(&data[i + 16], 0, 3);  // read, haute localite
    process(data[i]);
}
```

## Exemple concret - Impact mesurable 📈

```cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>

struct alignas(64) CacheFriendlyOrder {
    double price;
    int quantity;
    int id;
};

struct CacheHostileOrder {
    char padding1[60];  // pousse au-dela de la cache line
    double price;
    char padding2[60];
    int quantity;
    char padding3[60];
    int id;
};

int main() {
    constexpr int N = 1'000'000;

    // Test cache-friendly
    std::vector<CacheFriendlyOrder> good(N);
    for (int i = 0; i < N; i++) good[i] = {100.0 + i, i, i};

    auto start = std::chrono::high_resolution_clock::now();
    double sum = 0;
    for (int i = 0; i < N; i++) sum += good[i].price;
    auto end = std::chrono::high_resolution_clock::now();
    auto good_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Test cache-hostile
    std::vector<CacheHostileOrder> bad(N);
    for (int i = 0; i < N; i++) bad[i] = {{}, 100.0 + i, {}, i, {}, i};

    start = std::chrono::high_resolution_clock::now();
    sum = 0;
    for (int i = 0; i < N; i++) sum += bad[i].price;
    end = std::chrono::high_resolution_clock::now();
    auto bad_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Cache-friendly: " << good_time << " us\n";
    std::cout << "Cache-hostile:  " << bad_time  << " us\n";
    std::cout << "Ratio:          " << (double)bad_time / good_time << "x plus lent\n";
}
```

## Checkpoint ✅

Avant de passer au chapitre suivant, tu dois savoir :
- [ ] Pourquoi le CPU charge des cache lines de 64 bytes et pas des bytes individuels
- [ ] La difference de latence entre L1, L2, L3 et RAM
- [ ] Comment organiser une struct pour minimiser le padding
- [ ] Ce que fait `alignas(64)` et pourquoi c'est utile en HFT
- [ ] Pourquoi l'acces sequentiel est 10-100x plus rapide que l'acces random

---
Compilation : `g++ -std=c++17 -O2 -o cache exercise.cpp && ./cache`
