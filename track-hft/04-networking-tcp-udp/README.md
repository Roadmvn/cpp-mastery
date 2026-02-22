# Chapitre 04 - Networking TCP/UDP 

## Pourquoi c'est critique en HFT 

Le market data arrive par le **reseau**. Chaque microseconde de latence reseau
est une microseconde de retard sur le signal de trading. En HFT :
- **UDP multicast** pour le market data (fire-and-forget, minimal overhead)
- **TCP** pour l'envoi d'ordres (fiabilite obligatoire)
- **Kernel bypass** (DPDK, Solarflare) pour les ultras (on y reviendra)

## TCP vs UDP - Comparaison HFT 

```
┌─────────────────────────────────────────────────────────────────┐
│                    TCP (Transmission Control Protocol)           │
│                                                                  │
│  Client                              Server                     │
│    │                                   │                        │
│    ├── SYN ──────────────────────────│   3-way handshake     │
│    │◄────────────────────── SYN+ACK ──┤    AVANT d'envoyer     │
│    ├── ACK ──────────────────────────│    la moindre donnee   │
│    │                                   │    (~100 us RTT)       │
│    │                                   │                        │
│    ├── DATA ─────────────────────────│                        │
│    │◄────────────────────── ACK ──────┤   Chaque paquet      │
│    ├── DATA ─────────────────────────│    est acquitte        │
│    │◄────────────────────── ACK ──────┤                        │
│    │                                   │                        │
│    │  Retransmission si perte ↻       │   Fiable mais LENT   │
│    │  Controle de flux (window)       │                        │
│    │  Nagle algorithm (batching!)     │   Desactiver!        │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────┐
│                    UDP (User Datagram Protocol)                  │
│                                                                  │
│  Sender                              Receiver                   │
│    │                                   │                        │
│    ├── DATA ─────────────────────────│   Pas de handshake!  │
│    ├── DATA ─────────────────────────│    Fire and forget.    │
│    ├── DATA ──────────── X (perdu)    │    Pas d'ACK.          │
│    ├── DATA ─────────────────────────│    Pas de retransmit.  │
│    │                                   │                        │
│    │  Overhead minimal                │                        │
│    │  Header: 8 bytes (vs 20+ TCP)   │                        │
│    │  Latence: ~10 us (vs ~100 us)   │                        │
└─────────────────────────────────────────────────────────────────┘
```

## UDP Multicast - Market Data Distribution 

```
MULTICAST: 1 sender  N receivers simultanement

  Exchange Feed Handler
         │
         │  UDP Multicast (239.1.1.1:5000)
         │
         ├──────────────────┬──────────────────┐
         ▼                  ▼                  ▼
  ┌─────────────┐   ┌─────────────┐   ┌─────────────┐
  │  Firm A     │   │  Firm B     │   │  Firm C     │
  │  Strategy   │   │  Strategy   │   │  Strategy   │
  └─────────────┘   └─────────────┘   └─────────────┘

  Avantages:
  - UN paquet sert N clients (scalable)
  - Latence identique pour tous
  - Pas de connexion a maintenir
  - Switch reseau gere la duplication

  En HFT on ecoute le multicast feed DIRECTEMENT
  (pas de middleware, pas de message broker)
```

## Optimisations reseau HFT 

```
┌──────────────────────────────────────────────────┐
│  TCP_NODELAY = 1                                  │
│  Desactive l'algorithme de Nagle                  │
│  Sans: attend ~40ms pour battre les petits pkts  │
│  Avec: envoie IMMEDIATEMENT                      │
│                                                   │
│  SO_REUSEADDR = 1                                │
│  Permet de rebind rapidement apres un crash       │
│                                                   │
│  SO_RCVBUF / SO_SNDBUF = large                   │
│  Agrandit les buffers socket (evite les drops)    │
│                                                   │
│  Non-blocking sockets + epoll/kqueue              │
│  Jamais bloquer sur recv() !!                     │
│  Le thread doit rester reactif                    │
└──────────────────────────────────────────────────┘
```

## Architecture reseau typique HFT 

```
                    Exchange
                       │
              UDP Multicast Feed
                       │
          ┌────────────┼────────────┐
          ▼            ▼            ▼
   ┌────────────┐ ┌────────┐ ┌──────────┐
   │  Market    │ │ Market │ │  Market  │
   │  Data A    │ │ Data B │ │  Data C  │
   └─────┬──────┘ └───┬────┘ └────┬─────┘
         │            │           │
         └──────┬─────┘───────────┘
                │
         SPSC Queue (lock-free)
                │
         ┌──────▼──────┐
         │  Strategy   │   Decision en < 1 us
         │  Engine     │
         └──────┬──────┘
                │
         TCP Connection
                │
         ┌──────▼──────┐
         │  Exchange   │   Envoi d'ordre
         │  Gateway    │
         └─────────────┘
```

## Exemple concret - UDP Sender/Receiver 

```cpp
// Cote sender:
int sock = socket(AF_INET, SOCK_DGRAM, 0);
struct sockaddr_in addr{};
addr.sin_family = AF_INET;
addr.sin_port = htons(5000);
inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

MarketData data{100.50, 1000, 12345};
sendto(sock, &data, sizeof(data), 0,
       (struct sockaddr*)&addr, sizeof(addr));

// Cote receiver:
int sock = socket(AF_INET, SOCK_DGRAM, 0);
struct sockaddr_in addr{};
addr.sin_family = AF_INET;
addr.sin_port = htons(5000);
addr.sin_addr.s_addr = INADDR_ANY;
bind(sock, (struct sockaddr*)&addr, sizeof(addr));

MarketData data;
recvfrom(sock, &data, sizeof(data), 0, nullptr, nullptr);
```

## Checkpoint 

Avant de passer au chapitre suivant, tu dois savoir :
- [ ] Pourquoi UDP est prefere a TCP pour le market data en HFT
- [ ] Ce que fait TCP_NODELAY et pourquoi c'est obligatoire
- [ ] Comment fonctionne le multicast UDP (un sender, N receivers)
- [ ] La difference de latence entre TCP handshake et UDP fire-and-forget
- [ ] Pourquoi il ne faut JAMAIS bloquer sur recv() dans un systeme HFT

---
Compilation : `g++ -std=c++17 -O2 -o net exercise.cpp && ./net`
