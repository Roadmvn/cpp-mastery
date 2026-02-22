# Matching Engine - Projet HFT

## Description

Un matching engine simplifié qui implémente:
- Ordres limites BID et ASK
- Priorité prix-temps (price-time priority)
- Affichage du book après chaque opération
- Génération et affichage des trades

## Architecture

```
┌──────────────────────────────────────────────────────────────────┐
│                     MATCHING ENGINE                              │
│                                                                  │
│  ┌─────────────────┐       ┌──────────────────────────────────┐  │
│  │   OrderBook     │       │   MatchingEngine                 │  │
│  │                 │       │                                  │  │
│  │  bids (map)     │◄──────│  submit_order(Order)             │  │
│  │  asks (map)     │       │  → match contre côté opposé      │  │
│  │                 │       │  → génère Trade list             │  │
│  │  add_order()    │       │  → remaining → add_order()       │  │
│  │  cancel_order() │       │                                  │  │
│  │  get_best_*()   │       │  cancel_order(id)                │  │
│  │  print()        │       │  get_book_snapshot()             │  │
│  └─────────────────┘       └──────────────────────────────────┘  │
│                                       │                          │
│                              ┌────────▼────────┐                 │
│                              │   Trade Log     │                 │
│                              │                 │                 │
│                              │ - trade_id      │                 │
│                              │ - buy_order_id  │                 │
│                              │ - sell_order_id │                 │
│                              │ - price         │                 │
│                              │ - quantity      │                 │
│                              │ - timestamp     │                 │
│                              └─────────────────┘                 │
└──────────────────────────────────────────────────────────────────┘
```

## Flux d'un ordre

```
Nouvel ordre BUY limit 100.30 qty=5000

  1. MatchingEngine::submit_order(BUY, 100.30, 5000)
        │
        ▼
  2. Chercher dans asks tous les niveaux ≤ 100.30
        │
  asks: [100.20→5000][100.25→2000][100.30→3000][100.40→8000]
         ↑ matché     ↑ matché     ↑ matché     ✗ trop cher
        │
        ▼
  3. FIFO matching par niveau:
     - 100.20: trade 5000 → buy qty reste = 0  (partiellement rempli selon volume)
     - ...

  4. Si qty restante > 0: add_order(resting BUY @ 100.30, qty_remaining)
  5. Afficher le book après chaque trade
```

## Fichiers

- `order_book.h`      : OrderBook (bids/asks maps, add/cancel/print)
- `matching_engine.h` : MatchingEngine (submit_order, trade log)
- `main.cpp`          : scénarios de test, affichage

## Compilation

```bash
g++ -std=c++17 -O2 -o matching_engine main.cpp && ./matching_engine
```
