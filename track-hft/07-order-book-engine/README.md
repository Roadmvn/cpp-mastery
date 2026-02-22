# Chapitre 07 - Order Book Engine

## Qu'est-ce qu'un Order Book

L'order book (carnet d'ordres) est la structure centrale de tout exchange financier.
Il maintient en temps réel tous les ordres d'achat (bids) et de vente (asks) non exécutés,
triés par prix et par priorité temps (FIFO).

```
                     ORDER BOOK - AAPL
    ┌───────────────────────────────────────────────┐
    │                                               │
    │  ASKS (vendeurs) - ordres de vente            │
    │  Prix croissant vers le haut                  │
    │                                               │
    │  Prix     │ Volume │ Ordres                   │
    │  ─────────┼────────┼──────────────────────── │
    │  100.50   │  3000  │ [500@t3][1500@t1][1000@t4] │   best ask
    │  100.40   │  2000  │ [2000@t2]                │
    │  100.30   │  5000  │ [2000@t1][3000@t5]       │
    │                                               │
    │  ─────── SPREAD = 100.30 - 100.20 = 0.10 ─── │
    │                                               │
    │  100.20   │  4000  │ [4000@t1]                │   best bid
    │  100.10   │  1500  │ [500@t2][1000@t3]        │
    │  100.00   │  8000  │ [3000@t1][5000@t4]       │
    │                                               │
    │  BIDS (acheteurs) - ordres d'achat            │
    │  Prix décroissant vers le bas                 │
    │                                               │
    └───────────────────────────────────────────────┘
```

## Structure de données

```
Order Book:
┌─────────────────────────────────────────────────────────────────┐
│  bids: std::map<double, PriceLevel, std::greater<double>>       │
│  asks: std::map<double, PriceLevel, std::less<double>>          │
│                                                                  │
│  PriceLevel:                                                     │
│  ┌────────────────────────────────────┐                          │
│  │  total_volume: int                 │                          │
│  │  orders: std::deque<Order>         │   FIFO par niveau      │
│  └────────────────────────────────────┘                          │
│                                                                  │
│  Order:                                                          │
│  ┌────────────────────────────────────┐                          │
│  │  id:        uint64_t               │                          │
│  │  side:      BID | ASK              │                          │
│  │  price:     double                 │                          │
│  │  quantity:  int                    │                          │
│  │  timestamp: nanoseconds            │                          │
│  └────────────────────────────────────┘                          │
└─────────────────────────────────────────────────────────────────┘
```

## Priorité prix-temps (Price-Time Priority)

```
Matching engine: quand un ordre arrive, on le matche contre le book opposé.

  Nouvel ordre BUY  100.30  qty=3000

  ASKS disponibles:
  ┌──────────────────────────────────────────────┐
  │ 100.30  [1000@t1][500@t2][2000@t3]          │  meilleur ask ≤ 100.30
  │ 100.40  [2000@t4]                           │
  └──────────────────────────────────────────────┘

  Matching:
  1. ask 100.30, ordre t1: qty=1000  trade 1000 @ 100.30  (reste: 2000)
  2. ask 100.30, ordre t2: qty=500   trade  500 @ 100.30  (reste: 1500)
  3. ask 100.30, ordre t3: qty=2000  trade 1500 @ 100.30  (ordre partiellement rempli)
      order t3 reste dans le book avec qty=500

  FIFO = premier entré, premier servi POUR UN MÊME PRIX.
```

## Complexité des opérations

```
┌──────────────────────────────────────┬──────────────────────────────┐
│  Opération                           │  Complexité                  │
├──────────────────────────────────────┼──────────────────────────────┤
│  add_order(price, qty, side)         │  O(log N) - insert map       │
│  cancel_order(id)                    │  O(log N) - lookup + erase   │
│  get_best_bid()                      │  O(1) - begin() du map       │
│  get_best_ask()                      │  O(1) - begin() du map       │
│  match(order)                        │  O(K log N) - K=trades       │
│  get_level_volume(price)             │  O(log N) - find dans map    │
└──────────────────────────────────────┴──────────────────────────────┘

  N = nombre de niveaux de prix distincts
  En HFT réel: on utilise souvent une array-based price ladder
  pour obtenir O(1) sur les opérations les plus fréquentes.
```

## Price Ladder vs std::map

```
std::map (arbre équilibré):           Price Ladder (array):

  Accès: O(log N) ~50-100 ns           Accès: O(1) ~5 ns
  Mémoire: ~40 bytes/noeud             Mémoire: fixe, contigu
  Cache: mauvais (pointers)            Cache: excellent (array)
  Flexibilité: prix quelconque         Limité: prix entiers tick-grid

  ┌─────┐                              price_min = 99.00
  │root │                              tick_size = 0.01
  │99.5 │                              index = (price - price_min) / tick
  ├──┬──┤
  │  │  │                              Array: [0][1][2]...[200]
  99.0 100.0                                                 
   └──┘  └──┘                             99.00             101.00

  En production HFT: price ladder pour les 20 meilleurs niveaux,
  std::map pour les niveaux lointains (rare).
```

## Checkpoint

Avant de passer au chapitre suivant, tu dois savoir :
- [ ] Comment structurer bids et asks avec std::map et les bons comparateurs
- [ ] Implémenter add_order, cancel_order avec FIFO par niveau de prix
- [ ] Implémenter get_best_bid / get_best_ask en O(1)
- [ ] Comprendre le spread et son importance pour la liquidité
- [ ] Afficher un order book de façon lisible

---
Compilation : `g++ -std=c++17 -O2 -o exercise exercise.cpp && ./exercise`
