# Thread-Safe Queue — Queue generique multi-producteur / multi-consommateur

## Mutex vs Lock-Free : quand choisir quoi ?

### Mutex + condition_variable

Avantages :
- Simple a implementer et a raisonner
- Correct par construction (le compilateur et l'OS gerent l'ordering)
- Faible consommation CPU quand la queue est vide (le consommateur dort)
- Supporte N producteurs et M consommateurs sans contrainte

Inconvenients :
- Latence impredictible : appel systeme possible (futex), context switch
- Jitter eleve sous forte charge (p99 souvent 10x a 100x le p50)
- Le "thundering herd" peut degrader les perfs avec beaucoup de threads

### Lock-Free (CAS, atomics)

Avantages :
- Latence faible et predictible sur le chemin non contente
- Pas de deadlock possible
- Meilleur debit si les threads sont tres nombreux

Inconvenients :
- Complexite de mise en oeuvre elevee (ABA problem, memory ordering)
- Consomme du CPU meme quand la queue est vide (busy-wait)
- La garantie "lock-free" ne signifie pas "plus rapide" sous forte contention

### Regle pratique HFT

| Scenario                           | Recommandation          |
|------------------------------------|-------------------------|
| 1 prod / 1 cons, latence critique  | SPSC lock-free          |
| N prod / M cons, latence critique  | MPMC lock-free (Disruptor-style) |
| N prod / M cons, latence toleree   | Mutex + cond_var (ce projet) |
| Thread de logging / IO             | Mutex + cond_var        |

## Architecture

```
  Producteurs (N threads)         Consommateurs (M threads)
  +-----------+                   +-----------+
  | prod 1    |--+             +--| cons 1    |
  | prod 2    |--+--> [ mutex ]-+-| cons 2    |
  | prod 3    |--+   [ deque  ] +-| cons 3    |
  +-----------+       [ cv    ]   +-----------+
                         |
                   Notify sur push
                   Wait sur pop si vide
```

## Interface

```cpp
ThreadSafeQueue<T> q;

q.push(item);           // Bloquant si capacite atteinte (non implemente ici : illimite)
q.pop();                // Bloquant jusqu'a disponibilite -> retourne T
q.try_pop();            // Non-bloquant -> retourne std::optional<T>
q.size();               // Approximatif
q.empty();              // Approximatif
q.close();              // Signale aux consommateurs que plus rien n'arrivera
```

## Compilation

```bash
g++ -std=c++17 -O2 -pthread -o benchmark main.cpp
./benchmark
```
