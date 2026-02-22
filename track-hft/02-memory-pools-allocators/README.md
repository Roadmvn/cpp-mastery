# Chapitre 02 - Memory Pools & Allocators 🏊

## Pourquoi c'est critique en HFT 

`new` et `delete` appellent `malloc`/`free` qui prennent des **locks globaux**,
fragmentent la memoire, et font potentiellement des **syscalls** (`mmap`/`brk`).
En HFT, une allocation peut prendre **100-1000 ns** - c'est une eternite.

La solution : **pre-allouer** la memoire au demarrage, puis distribuer des blocs
depuis un pool. Zero syscall, zero lock, zero fragmentation. Latence: **~5 ns**.

## Le probleme de new/delete 🐌

```
ALLOCATION STANDARD (new/malloc):
                                                        Latence
  Code           Appel          OS                     estimee
  ─────          ─────          ──                     ───────
  new Order() ── malloc() ── lock(global_heap)       ~50 ns
                     │         cherche bloc libre       ~100 ns (fragmente)
                     │         potentiel mmap()         ~1000 ns !!
                     │         unlock()
                     ▼
              Adresse aleatoire en memoire
              (mauvaise localite spatiale)

PROBLEMES:
  1. Lock global = contention multi-thread
  2. Fragmentation = cache misses
  3. Syscall possible = latence imprevisible (tail latency)
  4. Localite terrible = objets eparpilles en memoire
```

## Memory Pool - Le concept 

```
INITIALISATION (au demarrage, UNE SEULE fois):
┌──────────────────────────────────────────────────────────┐
│  Pool: allocation d'un gros bloc contigu                  │
│                                                           │
│  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐      │
│  │ Slot │ Slot │ Slot │ Slot │ Slot │ Slot │ Slot │ ...  │
│  │  0   │  1   │  2   │  3   │  4   │  5   │  6   │      │
│  └──┬───┴──┬───┴──┬───┴──┬───┴──┬───┴──┬───┴──┬───┘      │
│     │      │      │      │      │      │      │           │
│     ▼      ▼      ▼      ▼      ▼      ▼      ▼           │
│  Free List: 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null     │
│  next_free ─┘                                             │
└──────────────────────────────────────────────────────────┘

ALLOCATION (allocate()):               LIBERATION (deallocate()):
┌──────┬──────┬──────┬──────┐         ┌──────┬──────┬──────┬──────┐
│ USED │ Free │ Free │ Free │         │ USED │ Free │ Free │ Free │
└──────┴──┬───┴──────┴──────┘         └──┬───┴──────┴──────┴──────┘
          │                              │
next_free─┘                              └── retourne en tete de free list
                                              next_free ──┘
Temps: O(1) - juste un pointeur!        Temps: O(1) - juste un pointeur!
```

## Arena Allocator - Encore plus simple 🏟

```
ARENA: alloue lineairement, libere TOUT d'un coup

  ┌─────────────────────────────────────────────────┐
  │  Arena Buffer (1 MB pre-alloue)                  │
  │                                                  │
  │  ████████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░   │
  │  ^              ^                           ^    │
  │  │              │                           │    │
  │  start      current_ptr                    end   │
  │                                                  │
  │  allocate(N):                                    │
  │    ptr = current_ptr                             │
  │    current_ptr += N                              │
  │    return ptr     // C'est TOUT. ~2 ns.          │
  │                                                  │
  │  reset():                                        │
  │    current_ptr = start  // Libere tout. ~1 ns.   │
  └─────────────────────────────────────────────────┘

  Ideal pour: traitement de messages batch,
  ou toutes les allocations d'une "frame" sont liberees ensemble
```

## Comparaison des approches 

```
┌───────────────────┬───────────┬───────────┬───────────────┐
│                   │ new/delete│ Pool      │ Arena         │
├───────────────────┼───────────┼───────────┼───────────────┤
│ Allocation        │ ~100 ns   │ ~5 ns     │ ~2 ns         │
│ Liberation        │ ~80 ns    │ ~5 ns     │ ~1 ns (reset) │
│ Thread-safe       │ Oui (lock)│ Possible  │ Non (1 thread)│
│ Fragmentation     │ Oui       │ Non       │ Non           │
│ Cache locality    │ Mauvaise  │ Bonne     │ Excellente    │
│ Flexibilite       │ Totale    │ Taille fixe│ Lineaire     │
│ Usage HFT         │ JAMAIS    │ Orders    │ Messages      │
│                   │ (hot path)│           │               │
└───────────────────┴───────────┴───────────┴───────────────┘
```

## Exemple concret - Pool Allocator 

```cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>

template<typename T, size_t PoolSize = 65536>
class PoolAllocator {
    union Slot {
        T object;
        Slot* next;
        Slot() {}
        ~Slot() {}
    };

    std::vector<Slot> pool_;
    Slot* free_list_ = nullptr;

public:
    PoolAllocator() : pool_(PoolSize) {
        // Chainer tous les slots dans la free list
        for (size_t i = 0; i < PoolSize - 1; i++) {
            pool_[i].next = &pool_[i + 1];
        }
        pool_[PoolSize - 1].next = nullptr;
        free_list_ = &pool_[0];
    }

    T* allocate() {
        if (!free_list_) return nullptr;
        Slot* slot = free_list_;
        free_list_ = free_list_->next;
        return reinterpret_cast<T*>(slot);
    }

    void deallocate(T* ptr) {
        Slot* slot = reinterpret_cast<Slot*>(ptr);
        slot->next = free_list_;
        free_list_ = slot;
    }
};

struct Order {
    double price;
    int quantity;
    int id;
    char side;
};

int main() {
    constexpr int N = 50000;
    PoolAllocator<Order> pool;

    // Benchmark pool vs new
    std::vector<Order*> ptrs(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) ptrs[i] = pool.allocate();
    for (int i = 0; i < N; i++) pool.deallocate(ptrs[i]);
    auto end = std::chrono::high_resolution_clock::now();
    auto pool_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) ptrs[i] = new Order();
    for (int i = 0; i < N; i++) delete ptrs[i];
    end = std::chrono::high_resolution_clock::now();
    auto new_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Pool:       " << pool_ns / N << " ns/op\n";
    std::cout << "new/delete: " << new_ns / N  << " ns/op\n";
    std::cout << "Speedup:    " << (double)new_ns / pool_ns << "x\n";
}
```

## Checkpoint 

Avant de passer au chapitre suivant, tu dois savoir :
- [ ] Pourquoi `new`/`delete` est interdit sur le hot path en HFT
- [ ] Comment fonctionne un pool allocator (free list chainee)
- [ ] La difference entre pool allocator et arena allocator
- [ ] Pourquoi la localite spatiale des pools ameliore le cache
- [ ] Comment pre-allouer la memoire au demarrage pour eviter les syscalls

---
Compilation : `g++ -std=c++17 -O2 -o pool exercise.cpp && ./pool`
