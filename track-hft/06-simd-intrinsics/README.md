# Chapitre 06 - SIMD et Vectorisation

## Pourquoi SIMD en HFT

SIMD (Single Instruction Multiple Data) permet d'appliquer **une instruction CPU sur plusieurs données en même temps**.
En HFT, on traite des flux de prices, de volumes, des arrays de doubles en continu.
Chaque nanoseconde compte. Vectoriser une boucle, c'est diviser son coût par 4 à 16.

```
SCALAIRE (sans SIMD):          SIMD (avec AVX2 - 4x double):

  for each float:                Un seul cycle CPU:
    result = a * b + c            ┌─────────────────────────────────┐
                                  │  a[0]  a[1]  a[2]  a[3]        │  ← registre YMM (256 bits)
    4 iterations × N ns           │   ×     ×     ×     ×          │
    = 4N ns                       │  b[0]  b[1]  b[2]  b[3]        │
                                  │   +     +     +     +          │
                                  │  c[0]  c[1]  c[2]  c[3]        │
                                  │   ↓     ↓     ↓     ↓          │
                                  │ r[0]  r[1]  r[2]  r[3]        │
                                  └─────────────────────────────────┘
                                    1 instruction = N ns
                                    Speedup: 4x (SSE) ou 8x (AVX2)
```

## Architecture des registres SIMD

```
Évolution des extensions SIMD Intel/AMD:

  MMX  (1997):  64 bits   = 2x int32  ou 8x int8
  SSE  (1999): 128 bits   = 4x float  ou 2x double    ← registres XMM
  SSE2 (2001): 128 bits   = 4x double
  AVX  (2011): 256 bits   = 8x float  ou 4x double    ← registres YMM
  AVX2 (2013): 256 bits   + instructions entières
  AVX-512(2017):512 bits  = 16x float ou 8x double    ← registres ZMM

  ┌──────────────────────────────────────────────────────────────────┐
  │  Registre YMM0 (AVX, 256 bits = 4 doubles de 64 bits chacun)   │
  │                                                                  │
  │  ┌──────────┬──────────┬──────────┬──────────┐                  │
  │  │  double  │  double  │  double  │  double  │                  │
  │  │  [63:0]  │ [127:64] │[191:128] │[255:192] │                  │
  │  │  = 8 B   │  = 8 B   │  = 8 B   │  = 8 B   │                  │
  │  └──────────┴──────────┴──────────┴──────────┘                  │
  │                                                                  │
  │  Une seule instruction VMULPD traite les 4 doubles!             │
  └──────────────────────────────────────────────────────────────────┘
```

## Concept de vectorisation auto par le compilateur

```
Code C++ standard:                Code C++ avec hint de vectorisation:

  for (int i = 0; i < N; i++) {     // Le compilateur peut auto-vectoriser
      c[i] = a[i] * b[i];           // si les arrays sont alignés (alignas)
  }                                  // et si pas d'alias entre a, b, c

  Le compilateur (gcc -O2) analyse:
  ┌──────────────────────────────────────────────────────────────────┐
  │  - Indépendance des itérations? → OUI (c[i] ne dépend pas de   │
  │    c[i-1])                                                        │
  │  - Aliasing possible? → NON si __restrict__ ou noalias           │
  │  - Alignement? → OUI si alignas(32) sur les tableaux             │
  │  - Taille connue? → Mieux si multiple de 4 (ou padding)          │
  │  → VECTORISATION AUTOMATIQUE (on voit "ymm" dans l'assembleur)   │
  └──────────────────────────────────────────────────────────────────┘
```

## Calcul vectorisé : min/max/moyenne sur array de prix

```
Problème: sur 1 million de prix, calculer min, max, mean.

APPROCHE SCALAIRE:
  min = prices[0]
  for i in [1..N]: if prices[i] < min → min = prices[i]
  Coût: N comparaisons séquentielles

APPROCHE SIMD (conceptuelle avec 4 doubles en parallèle):

  prices = [100.1, 99.8, 100.5, 99.9, 100.2, 100.0, 99.7, 100.3, ...]
            ├─────────────────┤  ├─────────────────┤
              Chunk 0 (4 val)       Chunk 1 (4 val)

  Chunk 0: min_vec = min(100.1, 99.8, 100.5, 99.9) → en 1 instruction
  Chunk 1: min_vec = min(100.2, 100.0, 99.7, 100.3) → en 1 instruction
  ...
  Réduction finale: min(min_vec[0], min_vec[1], min_vec[2], min_vec[3])

  Speedup théorique: 4x (double/AVX) ou 8x (float/AVX)
```

## Règles d'or pour la vectorisation

```
╔══════════════════════════════════════════════════════════════════╗
║  CE QUI PERMET LA VECTORISATION:                                 ║
║                                                                  ║
║  1. Tableaux alignés: alignas(32) double prices[N]              ║
║  2. Accès séquentiel: prices[i], pas prices[index[i]]           ║
║  3. Pas de dépendance inter-itération: c[i] ≠ f(c[i-1])        ║
║  4. Pas de branchement complexe dans la boucle                  ║
║  5. -O2 ou -O3 + -march=native (active AVX2 sur modern CPUs)   ║
║                                                                  ║
║  CE QUI BLOQUE LA VECTORISATION:                                 ║
║                                                                  ║
║  1. Aliasing: a et b pointent peut-être sur la même zone        ║
║  2. Exception possible: throw dans la boucle                    ║
║  3. Appel de fonction non-inline                                 ║
║  4. Branchement data-dépendant imprévisible                     ║
╚══════════════════════════════════════════════════════════════════╝
```

## Mesure de l'impact en HFT

```
Opération: calculer VWAP sur 100,000 prix

  Version scalaire     :  ~800 µs
  Version auto-vect.   :  ~200 µs  (-O3 -march=native)
  Version SSE manuel   :  ~200 µs  (même résultat, mais garanti)
  Version AVX2 manuel  :  ~100 µs

  → La vectorisation auto est souvent suffisante si le code est propre.
  → Les intrinsics manuels servent quand le compilateur ne peut pas deviner.
```

## Checkpoint

Avant de passer au chapitre suivant, tu dois savoir :
- [ ] Ce que fait une instruction SIMD sur plusieurs données simultanément
- [ ] La différence entre SSE (128 bits) et AVX2 (256 bits)
- [ ] Pourquoi l'alignement mémoire est critique pour la vectorisation
- [ ] Comment écrire une boucle que le compilateur peut vectoriser
- [ ] Calculer min/max/mean sur un grand array de façon optimisée

---
Compilation : `g++ -std=c++17 -O3 -march=native -o exercise exercise.cpp && ./exercise`
