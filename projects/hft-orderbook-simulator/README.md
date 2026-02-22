# HFT Order Book Simulator

## Description

Simulateur complet qui:
1. Génère un flux d'ordres aléatoires (marche aléatoire sur le prix)
2. Injecte les ordres dans un order book avec matching price-time priority
3. Calcule et affiche les statistiques: trades, spread moyen, latence

## Architecture

```
┌────────────────────────────────────────────────────────────────────┐
│                    HFT ORDER BOOK SIMULATOR                        │
│                                                                    │
│  ┌──────────────────┐    ┌─────────────────┐   ┌───────────────┐  │
│  │  Order Generator │    │   Order Book    │   │  Stats Engine │  │
│  │                  │    │                 │   │               │  │
│  │  marche aléat.   │───│  PriceLevels    │──│  trades/s     │  │
│  │  + spread        │    │  FIFO matching  │   │  spread moyen │  │
│  │  + volume dist.  │    │  price-time     │   │  VWAP         │  │
│  │                  │    │  priority       │   │  p50/p99 lat. │  │
│  └──────────────────┘    └─────────────────┘   └───────────────┘  │
│                                                                    │
│  Paramètres:                                                       │
│    N_ORDERS  = 10,000 ordres                                       │
│    INIT_PRICE = 100.00                                             │
│    SIGMA      = 0.05 (volatilité par tick)                         │
│    SPREAD     = 0.10 (spread initial)                              │
│    TICK_SIZE  = 0.01                                               │
└────────────────────────────────────────────────────────────────────┘
```

## Compilation

```bash
g++ -std=c++17 -O2 -o simulator main.cpp && ./simulator
```

## Exemple de sortie

```
=== HFT Order Book Simulator ===
Génération de 10000 ordres...

Snapshots du book:
  [après ordre 1000]  bid=99.85  ask=99.95  spread=0.10
  [après ordre 2000]  bid=100.12 ask=100.22 spread=0.10
  ...

=== Stats finales ===
  Ordres traités    : 10000
  Trades générés    : 3421
  Volume total      : 17,432,500
  VWAP              : 100.0312
  Spread moyen      : 0.0987
  Prix final        : 100.23
  Latence p50       : 120 ns
  Latence p99       : 580 ns
```
