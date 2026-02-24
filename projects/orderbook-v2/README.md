# Order Book v2 — Price Ladder avec allocation fixe

## Pourquoi Price Ladder plutot que std::map ?

### std::map (order book v1)
- Arbre rouge-noir : chaque acces = O(log N) avec des sauts memoire non-lineaires
- Chaque noeud est alloue dynamiquement : mauvaise localite cache
- Insertion/suppression de niveau de prix = reequilibrage possible
- Latence typique pour 1000 niveaux : ~500 ns a ~2 us

### Price Ladder (order book v2)
- Tableau de taille fixe indexe directement par le prix (en ticks)
- Acces a un niveau de prix : O(1), un simple acces tableau
- Toute la structure tient en memoire contigue -> prefetcher CPU efficace
- Latence typique : ~20 a ~100 ns

### Contrainte : plage de prix fixe
La price ladder suppose que les prix restent dans une plage connue a l'avance.
En HFT, le sous-jacent ne bouge que de quelques pourcents dans une session.
On alloue une fenetre centree sur le prix mid et on la recale si necessaire.

```
  Prix en ticks : 9990 ... 10010
  Index tableau :   0  ...   20   (offset = 9990)

  +-------+-------+-------+-------+-------+
  | 9990  | 9991  | ...   | 10000 | ...   |  <- prix (bid side)
  | 100   |  50   |  ...  | 500   |  ...  |  <- quantite totale
  | [ord] | [ord] |  ...  | [ord] |  ...  |  <- liste FIFO d'ordres
  +-------+-------+-------+-------+-------+
                              ^
                           best bid
```

## Architecture

```
  OrderBook v2
  +-----------------------------------------+
  |  PriceLadder bids_  (BUYS)              |
  |  +----+----+----+----+----+             |
  |  | .. | Q  | Q  | Q  | .. |  <- qty    |
  |  | .. |FIFO|FIFO|FIFO| .. |  <- orders |
  |  +----+----+----+----+----+             |
  |       ^                                 |
  |    best_bid                             |
  |                                         |
  |  PriceLadder asks_  (SELLS)             |
  |  +----+----+----+----+----+             |
  |  | .. | Q  | Q  | Q  | .. |             |
  |  | .. |FIFO|FIFO|FIFO| .. |             |
  |  +----+----+----+----+----+             |
  |            ^                            |
  |         best_ask                        |
  +-----------------------------------------+

  Matching : best_bid >= best_ask -> trade
  FIFO par niveau : premier arrive, premier servi
```

## FIFO par niveau de prix

Au sein d'un meme niveau de prix, les ordres sont executes dans l'ordre
d'arrivee (First In First Out). C'est la priorite temporelle, standard
sur la plupart des exchanges electroniques.

## Stats de matching

L'OrderBook v2 collecte :
- Nombre de trades executes
- Quantite totale echangee
- Latence de matching par ordre (time to fill)

## Compilation

```bash
g++ -std=c++17 -O2 -o benchmark main.cpp
./benchmark
```

Note : pas de -pthread necessaire, le benchmark est monothreade.
