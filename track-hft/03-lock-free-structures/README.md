# Chapitre 03 - Lock-Free Structures 🔓

## Pourquoi c'est critique en HFT 

Un `std::mutex` coute **~25 ns** non-conteste, **~1000+ ns** sous contention. En HFT,
le market data feed et le trading engine communiquent via des queues partagees.
Si tu mets un lock la-dessus, tu perds la course.

Les structures **lock-free** utilisent des operations atomiques (CAS - Compare And Swap)
pour synchroniser sans jamais bloquer. Resultat: latence previsible et minimale.

## Le probleme des locks 🐌

```
AVEC MUTEX (blocking):
  Thread A (Market Data)         Thread B (Trading Engine)
       │                              │
       ├── lock(mutex)                │
       │   ┌───────────┐              │
       │   │ ECRIT     │              ├── lock(mutex)
       │   │ donnees   │              │   BLOQUE!! ⏳
       │   └───────────┘              │   attend...
       ├── unlock(mutex)              │   attend...
       │                              │   attend... (+500ns)
       │                              ├── acquiert le lock
       │                              │   ┌───────────┐
       │                              │   │ LIT       │
       │                              │   │ donnees   │
       │                              │   └───────────┘
       │                              ├── unlock(mutex)

  Problemes: priority inversion, contention, latence imprevisible

LOCK-FREE (non-blocking):
  Thread A (Producer)            Thread B (Consumer)
       │                              │
       ├── atomic_store(data)         │
       │   ~5 ns, JAMAIS bloque       ├── atomic_load(data)
       │                              │   ~5 ns, JAMAIS bloque
       │                              │
  Aucun thread ne bloque JAMAIS l'autre
```

## Compare-And-Swap (CAS) - L'operation fondamentale 

```
CAS = Compare And Swap (compare_exchange sur x86)

  compare_exchange_strong(expected, desired):

  ┌─────────────────────────────────────────────┐
  │                                             │
  │  Atomiquement (1 instruction CPU):          │
  │                                             │
  │  if (variable == expected) {                │
  │      variable = desired;   // swap!         │
  │      return true;          // succes      │
  │  } else {                                   │
  │      expected = variable;  // charge valeur │
  │      return false;         // echec       │
  │  }                                          │
  │                                             │
  └─────────────────────────────────────────────┘

  Exemple concret - Increment atomique sans lock:

  Thread A                Thread B
     │                       │
     │  val = 5               │  val = 5
     │  expected = 5          │  expected = 5
     │  CAS(5, 6)  true   │
     │  val = 6               │  CAS(5, 6)  false 
     │                       │  expected = 6 (mis a jour)
     │                       │  CAS(6, 7)  true  (retry)
     │                       │  val = 7
```

## Memory Ordering - Les garanties 

```
Ordres du plus faible au plus fort:

  memory_order_relaxed    Aucune garantie d'ordre. Le plus rapide.
         │                Bon pour: compteurs simples
         ▼
  memory_order_acquire    Les loads apres sont visibles APRES ce load.
  memory_order_release    Les stores avant sont visibles AVANT ce store.
         │                Bon pour: producer/consumer (le pattern HFT!)
         ▼
  memory_order_seq_cst    Ordre total global. Le plus lent.
                          Defaut de std::atomic. Souvent suffisant.

  Pattern Producer-Consumer optimal:
  ┌──────────────┐                    ┌──────────────┐
  │   Producer   │                    │   Consumer   │
  │              │                    │              │
  │ data = 42;  │     release        │              │
  │ flag.store  ├────────────────────│ flag.load    │
  │ (true,      │                    │ (acquire)    │
  │  release)   │     acquire        │ // data = 42 │
  │              │                    │ // garanti!  │
  └──────────────┘                    └──────────────┘
```

## SPSC Lock-Free Queue 

```
Single Producer Single Consumer - La structure HFT par excellence

  ┌─────────────────────────────────────────────────────┐
  │  Ring Buffer (taille fixe, puissance de 2)           │
  │                                                      │
  │  ┌────┬────┬────┬────┬────┬────┬────┬────┐          │
  │  │ D3 │ D4 │    │    │    │    │ D1 │ D2 │          │
  │  └────┴────┴────┴────┴────┴────┴────┴────┘          │
  │    ▲                              ▲                  │
  │    │                              │                  │
  │  write_pos                     read_pos              │
  │  (atomic, producer seul)       (atomic, consumer)    │
  │                                                      │
  │  push(item):                                         │
  │    if (write - read == SIZE) return false; // full   │
  │    buffer[write % SIZE] = item;                      │
  │    write.store(write+1, release);                    │
  │                                                      │
  │  pop(item):                                          │
  │    if (read == write) return false; // empty         │
  │    item = buffer[read % SIZE];                       │
  │    read.store(read+1, release);                      │
  │                                                      │
  │  ZERO lock. ZERO allocation. ZERO syscall.           │
  └─────────────────────────────────────────────────────┘

  Utilisation typique en HFT:
  ┌─────────┐    SPSC Queue    ┌─────────────┐
  │ Network │ ─────────────── │   Strategy  │
  │ Thread  │   market data    │   Thread    │
  └─────────┘                  └─────────────┘
```

## Exemple concret 

```cpp
#include <atomic>
#include <thread>
#include <iostream>

template<typename T, size_t Size = 1024>
class SPSCQueue {
    static_assert((Size & (Size - 1)) == 0, "Size must be power of 2");
    T buffer_[Size];
    alignas(64) std::atomic<size_t> write_pos_{0};
    alignas(64) std::atomic<size_t> read_pos_{0};

public:
    bool push(const T& item) {
        size_t w = write_pos_.load(std::memory_order_relaxed);
        if (w - read_pos_.load(std::memory_order_acquire) == Size) return false;
        buffer_[w & (Size - 1)] = item;
        write_pos_.store(w + 1, std::memory_order_release);
        return true;
    }

    bool pop(T& item) {
        size_t r = read_pos_.load(std::memory_order_relaxed);
        if (r == write_pos_.load(std::memory_order_acquire)) return false;
        item = buffer_[r & (Size - 1)];
        read_pos_.store(r + 1, std::memory_order_release);
        return true;
    }
};
```

## Checkpoint 

Avant de passer au chapitre suivant, tu dois savoir :
- [ ] Pourquoi les mutex sont problematiques en HFT (contention, latence imprevisible)
- [ ] Comment fonctionne Compare-And-Swap (CAS)
- [ ] La difference entre memory_order_relaxed, acquire, release et seq_cst
- [ ] Comment implementer une SPSC queue lock-free avec un ring buffer
- [ ] Pourquoi les write_pos et read_pos sont sur des cache lines separees (alignas(64))

---
Compilation : `g++ -std=c++17 -O2 -pthread -o lockfree exercise.cpp && ./lockfree`
