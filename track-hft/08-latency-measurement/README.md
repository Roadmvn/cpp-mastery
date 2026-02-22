# Chapitre 08 - Mesure de Latence

## Pourquoi mesurer la latence en HFT

En HFT, "faire vite" ne suffit pas. Il faut **mesurer précisément** pour:
- Identifier les hot paths (code exécuté millions de fois/seconde)
- Comparer des implémentations alternatives
- Détecter les régressions de performance
- Comprendre la distribution (p50, p99, p99.9 sont plus importants que la moyenne)

```
Distribution de latence typique (opération lookup):

  Occurrences
      │
  ████│
  ████│
  ████│████
  ████│████████
  ████│████████████
  ████│████████████████████
  ████│████████████████████████████
  ────┼────────────────────────────────────
  0   10  20  30  40  50  60  70  80  90 ns

  p50  =  15 ns   médiane: 50% des ops sont sous ce seuil
  p99  =  45 ns   99% des ops sont sous ce seuil
  p99.9=  80 ns   1 op sur 1000 dépasse ce seuil
  mean =  18 ns   la moyenne cache les outliers

  En HFT: on optimise p99 et p99.9, pas seulement la moyenne!
  Un outlier à 1ms peut coûter plus cher qu'un million d'ops à 20ns.
```

## std::chrono - Outils de mesure

```
┌─────────────────────────────────────────────────────────────────┐
│  std::chrono::high_resolution_clock                             │
│                                                                  │
│  Résolution: typiquement 1 ns sur Linux (TSC), ~100 ns macOS    │
│                                                                  │
│  auto t0 = Clock::now();                                         │
│  // ... opération à mesurer ...                                  │
│  auto t1 = Clock::now();                                         │
│  auto ns = duration_cast<nanoseconds>(t1 - t0).count();         │
│                                                                  │
│  Attention: overhead de Clock::now() lui-même = ~20-50 ns       │
│   Pour des opérations < 50 ns, répéter N fois et diviser       │
└─────────────────────────────────────────────────────────────────┘

  Pattern correct pour mesurer une opération rapide:

  constexpr int N = 1'000'000;
  auto t0 = Clock::now();
  for (int i = 0; i < N; i++) {
      do_operation();
  }
  auto t1 = Clock::now();
  double avg_ns = duration_cast<nanoseconds>(t1 - t0).count() / (double)N;
```

## Calcul des percentiles

```
  Données brutes (ns): [15, 12, 18, 11, 45, 14, 16, 13, 80, 17, ...]

  1. Trier: [11, 12, 13, 14, 15, 16, 17, 18, 45, 80, ...]

  2. Calculer les indices:
     p50   index = 0.50 * N
     p90   index = 0.90 * N
     p99   index = 0.99 * N
     p99.9 index = 0.999 * N

  ┌────────────────────────────────────────────────────────────────┐
  │  sorted[0]    sorted[N/2]   sorted[N*0.99]  sorted[N-1]       │
  │    min           p50            p99             max            │
  │     │             │              │               │             │
  │  ───┼─────────────┼──────────────┼───────────────┼───         │
  │     11            15             45              80             │
  └────────────────────────────────────────────────────────────────┘
```

## Benchmark: vector vs map vs unordered_map

```
Scénario: 1M lookups de prix dans une structure de données

  std::vector (non trié):
  ┌──────┬──────┬──────┬──────┬──────┬──────
  │100.10│ 99.8 │100.5 │100.2 │ 99.9 │ ...
  └──────┴──────┴──────┴──────┴──────┴──────
  Recherche: O(N) scan linéaire = ~50,000 ns pour N=1000

  std::map (arbre rouge-noir):
  Recherche: O(log N) = ~7 comparaisons pour N=128 = ~50-100 ns
  Cache: mauvais (noeuds alloués dynamiquement, éparpillés en mémoire)

  std::unordered_map (table de hachage):
  Recherche: O(1) amortie = ~50-200 ns (variable selon collisions)
  Cache: mieux si load factor raisonnable

  ┌────────────────────────────┬──────────────┬──────────────────┐
  │  Structure                 │  Lookup N=100│  Lookup N=10000  │
  ├────────────────────────────┼──────────────┼──────────────────┤
  │  vector<pair> (non trié)   │   ~200 ns    │    ~20000 ns     │
  │  vector<pair> (trié+bsrch) │    ~50 ns    │      ~120 ns     │
  │  std::map                  │    ~80 ns    │      ~200 ns     │
  │  std::unordered_map        │    ~60 ns    │       ~60 ns     │
  └────────────────────────────┴──────────────┴──────────────────┘
```

## Pièges de mesure

```
1. Compiler sans optimisation  mesures fausses (trop lentes)
    Toujours -O2 ou -O3 pour les benchmarks

2. Le compilateur peut ÉLIMINER du code si le résultat n'est pas utilisé
    Utiliser volatile ou __asm__ volatile("" : "+r"(val)) pour éviter ça

3. Variance due au scheduling OS, TLB miss, interruptions
    Répéter l'opération, garder le minimum ou la médiane, pas juste la moyenne

4. Warm-up du cache obligatoire avant de mesurer
    Faire 1000 opérations de "warm-up" avant de commencer la mesure

5. Clock resolution sur macOS: high_resolution_clock ≈ 40 ns résolution
    Pour mesures très fines: répéter 1M fois et diviser
```

## Checkpoint

Avant de passer au chapitre suivant, tu dois savoir :
- [ ] Utiliser std::chrono::high_resolution_clock correctement
- [ ] Mesurer une opération rapide (< 100 ns) sans biais
- [ ] Calculer p50, p99, p99.9 à partir d'un vecteur de mesures
- [ ] Comparer les performances de vector/map/unordered_map pour du lookup
- [ ] Éviter les pièges classiques (élimination compilateur, variance OS)

---
Compilation : `g++ -std=c++17 -O2 -o exercise exercise.cpp && ./exercise`
