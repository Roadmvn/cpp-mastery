# SPSC Queue — Single Producer Single Consumer Lock-Free Queue

## Concept

Une SPSC queue est une file d'attente conçue pour un seul thread producteur et un seul thread consommateur.
L'absence de contention entre deux producteurs ou deux consommateurs permet d'éliminer totalement les mutex
et d'utiliser uniquement des opérations atomiques avec des memory orders soigneusement choisis.

## Pourquoi lock-free en HFT ?

Un mutex implique potentiellement un appel système (futex) et un context switch — coût typique : 1 000 à 10 000 ns.
En trading haute fréquence, la latence cible est de l'ordre de la centaine de nanosecondes.
Une SPSC lock-free atteint des latences de 20 à 100 ns sur matériel moderne, soit un gain d'un ordre de grandeur.

Avantages concrets :
- Aucun blocage possible (wait-free du côté producteur et consommateur en cas de capacité suffisante)
- Prévisibilité de la latence (pas de jitter dû à la contention)
- Adapté aux pipelines de données en temps réel : tick data, order flow, signaux de trading

## Cas d'usage HFT

- Transmission de market data (ticks) depuis le thread de réception réseau vers le thread de stratégie
- Pipeline de signaux : calcul d'indicateurs -> moteur d'ordres
- Logging asynchrone : thread principal -> thread I/O sans bloquer le chemin critique

## Structure interne : Circular Buffer

```
                        capacity = 8
  index :   0     1     2     3     4     5     6     7
          +-----+-----+-----+-----+-----+-----+-----+-----+
  buffer: |  A  |  B  |  C  |     |     |     |     |     |
          +-----+-----+-----+-----+-----+-----+-----+-----+
                              ^                 ^
                           tail=3             head=6
                        (prochain pop)      (prochain push)

  head avance lors d'un push (producteur)
  tail avance lors d'un pop  (consommateur)

  File vide  : head == tail
  File pleine: (head + 1) % capacity == tail
```

## Cache Line Padding

Le head et le tail sont placés sur des cache lines séparées (alignas(64)) pour éviter le "false sharing".
Sans ce padding, la mise à jour du head par le producteur invaliderait la cache line du consommateur
contenant le tail, causant des miss L1 inutiles.

```
  Cache line 0 (64 bytes)          Cache line 1 (64 bytes)
  +--------------------------------+ +--------------------------------+
  | head (8B) | padding (56B)      | | tail (8B) | padding (56B)      |
  +--------------------------------+ +--------------------------------+
        |                                   |
   thread prod                         thread cons
  (écrit head)                         (écrit tail)
```

## Compilation

```bash
g++ -std=c++17 -O2 -pthread -o benchmark main.cpp
./benchmark
```

## Memory Orders utilisés

| Opération         | Order       | Raison                                               |
|-------------------|-------------|------------------------------------------------------|
| load(head) prod   | relaxed     | seul le producteur écrit head                        |
| load(tail) prod   | acquire     | synchronise avec la release du consommateur          |
| store(head) prod  | release     | publie les données écrites dans le buffer            |
| load(tail) cons   | relaxed     | seul le consommateur écrit tail                      |
| load(head) cons   | acquire     | synchronise avec la release du producteur            |
| store(tail) cons  | release     | signale au producteur que la slot est libérée        |
