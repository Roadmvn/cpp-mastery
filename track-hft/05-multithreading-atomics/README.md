# Chapitre 05 - Multithreading & Atomics 🧵

## Pourquoi c'est critique en HFT ⚡

Un systeme HFT typique a **3-5 threads dedies**, chacun pin a un core CPU specifique.
Pas de thread pool, pas de task queue generique. Chaque thread a un role precis
et tourne en **busy-loop** (jamais de sleep, jamais de yield).

Le threading en HFT, c'est de l'horlogerie: chaque thread est une piece du mecanisme,
et la communication inter-thread doit etre **lock-free** et **zero-allocation**.

## Architecture multi-thread HFT 🏗️

```
┌─────────────────────────────────────────────────────────────────┐
│                    CPU avec 6+ cores                             │
│                                                                  │
│  Core 0 (isole)         Core 1 (isole)        Core 2 (isole)   │
│  ┌───────────────┐      ┌───────────────┐     ┌───────────────┐ │
│  │  Network      │      │  Strategy     │     │  Order        │ │
│  │  Thread       │      │  Thread       │     │  Thread       │ │
│  │               │      │               │     │               │ │
│  │  - recv UDP   │      │  - analyse    │     │  - send TCP   │ │
│  │  - parse msg  │ ───► │  - decide     │ ──► │  - manage     │ │
│  │  - normalize  │ SPSC │  - signal     │SPSC │  - confirm    │ │
│  │               │Queue │               │Queue│               │ │
│  │  BUSY LOOP    │      │  BUSY LOOP    │     │  BUSY LOOP    │ │
│  └───────────────┘      └───────────────┘     └───────────────┘ │
│                                                                  │
│  Core 3                 Core 4-5                                │
│  ┌───────────────┐      ┌───────────────┐                       │
│  │  Logging      │      │  OS / autres  │                       │
│  │  Thread       │      │  processes    │                       │
│  └───────────────┘      └───────────────┘                       │
│                                                                  │
│  Regles:                                                        │
│  - Cores 0-2: isoles (isolcpus), dedies au trading              │
│  - Pas de context switch, pas d'interruption                    │
│  - Communication: SPSC queues lock-free uniquement              │
│  - Jamais de mutex sur le hot path                              │
└─────────────────────────────────────────────────────────────────┘
```

## std::thread - Les bases 📋

```
Creation et gestion de threads:

  ┌──────────────┐     std::thread t(func)    ┌──────────────┐
  │  Main Thread │ ──────────────────────────► │  New Thread  │
  │              │                             │  func()      │
  │  continue... │                             │  running...  │
  │              │     t.join()                │              │
  │  BLOQUE ici  │ ◄─────────────────────────  │  return      │
  │  until done  │                             └──────────────┘
  └──────────────┘

  t.join()    → attend la fin du thread (bloquant)
  t.detach()  → laisse tourner independamment (dangereux en HFT)
  t.joinable() → verifie si le thread est encore actif
```

## std::atomic - Operations thread-safe sans lock 🔒

```
SANS atomic (DATA RACE - UB):          AVEC atomic (SAFE):
  int counter = 0;                       std::atomic<int> counter{0};

  Thread A:   Thread B:                  Thread A:      Thread B:
  counter++   counter++                  counter++      counter++
     │           │                          │              │
     ▼           ▼                          ▼              ▼
  LOAD 0      LOAD 0                    atomic LOAD    WAIT (bus lock)
  ADD 1       ADD 1                     atomic ADD     atomic LOAD
  STORE 1     STORE 1                   atomic STORE   atomic ADD
                                                       atomic STORE
  Resultat: 1 (FAUX!)                   Resultat: 2 (CORRECT)
```

## std::mutex vs std::atomic en HFT ⚖️

```
┌──────────────────────┬───────────────┬────────────────┐
│                      │  std::mutex   │  std::atomic   │
├──────────────────────┼───────────────┼────────────────┤
│ Latence (no contest) │  ~25 ns       │  ~5 ns         │
│ Latence (conteste)   │  ~1000+ ns    │  ~50 ns (CAS)  │
│ Peut bloquer?        │  OUI ❌       │  NON ✅        │
│ Priority inversion?  │  OUI ❌       │  NON ✅        │
│ Usage HFT            │  Init/logging │  Hot path      │
│ Complexite           │  Simple       │  Expert        │
└──────────────────────┴───────────────┴────────────────┘
```

## Thread Affinity - Pinning 📌

```
SANS affinity:                      AVEC affinity:
  Thread A saute entre cores         Thread A fixe sur Core 0
  ┌──────┐ ┌──────┐ ┌──────┐       ┌──────┐ ┌──────┐ ┌──────┐
  │Core 0│ │Core 1│ │Core 2│       │Core 0│ │Core 1│ │Core 2│
  │ t=0  │ │      │ │      │       │Thread│ │Thread│ │Thread│
  │Thread│ │      │ │      │       │  A   │ │  B   │ │  C   │
  │  A   │ │      │ │      │       │      │ │      │ │      │
  │ t=1  │ │ t=1  │ │      │       │JAMAIS│ │JAMAIS│ │JAMAIS│
  │      │ │Thread│ │      │       │migre │ │migre │ │migre │
  │      │ │  A   │ │      │       └──────┘ └──────┘ └──────┘
  │ t=2  │ │      │ │ t=2  │
  │      │ │      │ │Thread│       Cache L1/L2 toujours chaud
  │      │ │      │ │  A   │       Pas de migration = pas de flush
  └──────┘ └──────┘ └──────┘       Latence stable et previsible
  Cache froid a chaque migration
```

## condition_variable - Notification 📣

```
Pattern: un thread attend une condition, un autre le reveille

  Producer                            Consumer
     │                                   │
     │  prepare data                     │  unique_lock(mutex)
     │                                   │  cv.wait(lock, pred)
     │                                   │  DORT 💤
     │  lock(mutex)                      │
     │  data_ready = true                │
     │  unlock(mutex)                    │
     │  cv.notify_one() ─────────────►   │  REVEILLE! 🔔
     │                                   │  verifie pred → true
     │                                   │  traite data
     │                                   │

  NOTE: En HFT, on prefere le busy-wait avec atomic
  car cv.wait() implique un syscall (futex) trop lent
```

## Checkpoint ✅

Avant de passer au chapitre suivant, tu dois savoir :
- [ ] Pourquoi chaque thread HFT est pin a un core dedie
- [ ] La difference entre std::mutex et std::atomic en termes de latence
- [ ] Comment fonctionne le pattern producer-consumer avec SPSC queue
- [ ] Pourquoi le busy-wait est prefere a condition_variable en HFT
- [ ] Ce qu'est le thread affinity et pourquoi ca maintient le cache chaud

---
Compilation : `g++ -std=c++17 -O2 -pthread -o mt exercise.cpp && ./mt`
