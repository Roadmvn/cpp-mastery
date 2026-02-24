// Chapitre 06 — Challenge HFT : ObjectPool avec perfect forwarding
// Compilation : g++ -std=c++20 -Wall -Wextra -O2 -o challenge challenge.cpp
//
// Contexte : En HFT, new/delete sont prohibes sur le chemin critique.
// L'allocateur systeme (malloc) peut prendre 50 a 500 ns par appel,
// avec variance impredictible. Un object pool pre-alloue un bloc memoire
// et recycle les objets sans jamais appeler l'allocateur systeme.
//
// On implemente ObjectPool<T, N> :
//   - acquire()         : retourne un T* depuis le pool (sans malloc)
//   - release(T*)       : remet l'objet dans le pool (sans free)
//   - make<Args...>(...)  : construit dans le pool via perfect forwarding
//
// Architecture :
//
//   Memoire pre-allouee
//   [slot 0][slot 1][slot 2]...[slot N-1]
//      |
//      free_list_ -> liste chainee des slots libres
//      (quand le slot est libre, il stocke un pointeur vers le prochain libre)
//
//   acquire() : pop depuis free_list_, retourne le slot
//   release() : push vers free_list_, slot disponible a nouveau
//
// Benchmark : pool vs new/delete sur 100k allocations/liberations

#include <iostream>
#include <chrono>
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <array>
#include <new>
#include <utility>
#include <iomanip>
#include <string>
#include <vector>

// ============================================================
// Utilitaire : timing en nanosecondes
// ============================================================

using ns_t = std::int64_t;

inline ns_t now_ns() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(
        steady_clock::now().time_since_epoch()
    ).count();
}

// ============================================================
// ObjectPool<T, N>
//
// Principe :
//   - Bloc memoire brut de N * sizeof(T), aligne sur alignof(T)
//   - Free list chainee : chaque slot libre contient l'adresse du suivant
//   - acquire() : extrait le premier slot libre, retourne T*
//   - release() : reinscrit le slot dans la free list
//   - make<Args...>() : acquire() + placement new avec perfect forwarding
//   - Le pool ne gere PAS automatiquement la destruction : appelez
//     destroy(ptr) pour appeler le destructeur avant release().
// ============================================================

template<typename T, std::size_t N>
class ObjectPool {
    static_assert(N > 0, "ObjectPool size must be > 0");
    static_assert(sizeof(T) >= sizeof(void*),
        "T trop petit pour contenir un pointeur de free list");

    // Stockage brut aligne : N emplacements, aucun objet construit
    alignas(T) std::byte storage_[sizeof(T) * N];

    // Tete de la free list : pointe vers le premier slot libre
    // (null si le pool est plein)
    void* free_head_ = nullptr;

    std::size_t available_ = N;

    // Obtenir l'adresse du slot i
    T* slot(std::size_t i) noexcept {
        return reinterpret_cast<T*>(storage_ + i * sizeof(T));
    }

public:
    ObjectPool() noexcept {
        // Initialiser la free list : chaque slot pointe vers le suivant
        // Le dernier slot pointe vers nullptr (fin de liste)
        for (std::size_t i = 0; i < N - 1; ++i) {
            // Ecrire l'adresse du slot suivant dans les octets du slot i
            void* next = slot(i + 1);
            std::memcpy(storage_ + i * sizeof(T), &next, sizeof(void*));
        }
        // Dernier slot : nullptr
        void* null_ptr = nullptr;
        std::memcpy(storage_ + (N - 1) * sizeof(T), &null_ptr, sizeof(void*));

        // La free list commence au slot 0
        free_head_ = slot(0);
    }

    // Pas de copie : le pool est une ressource unique
    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;

    // acquire() : retourne un T* non initialise depuis le pool
    // IMPORTANT : l'objet N'EST PAS construit. Utilise make() pour construire.
    // Retourne nullptr si le pool est plein.
    [[nodiscard]] T* acquire() noexcept {
        if (!free_head_) return nullptr;

        // Extraire le premier slot libre
        T* slot_ptr = reinterpret_cast<T*>(free_head_);

        // Lire l'adresse du prochain slot libre (stockee dans les octets du slot)
        void* next = nullptr;
        std::memcpy(&next, free_head_, sizeof(void*));
        free_head_ = next;

        --available_;
        return slot_ptr;
    }

    // release(ptr) : remet le slot dans la free list
    // IMPORTANT : le destructeur de T doit avoir ete appele avant release().
    // Utilise destroy() + release() ou simplement reclaim().
    void release(T* ptr) noexcept {
        assert(owns(ptr) && "release : pointeur hors du pool");

        // Ecrire l'adresse de la tete courante dans les octets du slot libere
        std::memcpy(ptr, &free_head_, sizeof(void*));
        free_head_ = ptr;

        ++available_;
    }

    // destroy(ptr) : appelle le destructeur de T, puis libere le slot
    void reclaim(T* ptr) noexcept {
        ptr->~T();          // appel explicite du destructeur
        release(ptr);       // reinscrit dans la free list
    }

    // make<Args...>(...) : acquire + placement new avec perfect forwarding
    // Retourne nullptr si le pool est plein.
    template<typename... Args>
    [[nodiscard]] T* make(Args&&... args) {
        T* slot_ptr = acquire();
        if (!slot_ptr) return nullptr;

        // Construire l'objet T in-place avec forwarding des arguments
        // forward preserve la categorie de chaque arg :
        //   - rvalue -> move (pas de copie)
        //   - lvalue -> copie (comportement attendu)
        new (slot_ptr) T(std::forward<Args>(args)...);
        return slot_ptr;
    }

    std::size_t available()  const noexcept { return available_; }
    std::size_t capacity()   const noexcept { return N; }
    std::size_t used()       const noexcept { return N - available_; }

    // Verifier que ptr appartient bien a ce pool
    bool owns(const T* ptr) const noexcept {
        const auto* base  = reinterpret_cast<const std::byte*>(storage_);
        const auto* p     = reinterpret_cast<const std::byte*>(ptr);
        return p >= base && p < base + sizeof(T) * N;
    }
};

// ============================================================
// Type de test : message d'ordre HFT
// ============================================================

struct Order {
    std::uint32_t id;
    double        price;
    std::uint32_t quantity;
    std::string   symbol;   // string : necessite ctor/dtor

    Order(std::uint32_t i, double p, std::uint32_t q, std::string sym)
        : id(i), price(p), quantity(q), symbol(std::move(sym)) {}
};

// ============================================================
// Benchmark utilitaire
// ============================================================

struct BenchResult {
    ns_t total_ns;
    ns_t per_op_ns;
    std::size_t ops;

    void print(const char* label) const {
        std::cout << std::setw(30) << std::left << label
                  << " total=" << std::setw(10) << total_ns << "ns"
                  << " per_op=" << std::setw(6) << per_op_ns << "ns"
                  << " ops=" << ops << "\n";
    }
};

BenchResult bench_pool(std::size_t iterations) {
    // Pool de 1024 ordres (taille representant un burst)
    ObjectPool<Order, 1024> pool;

    ns_t start = now_ns();

    for (std::size_t i = 0; i < iterations; ++i) {
        // Allouer
        Order* o = pool.make(
            static_cast<std::uint32_t>(i),
            100.0 + static_cast<double>(i % 100),
            10 + static_cast<std::uint32_t>(i % 50),
            std::string("AAPL")  // string construite avec perfect forwarding
        );
        // Utiliser l'ordre (evite l'optimisation agressive du compilateur)
        if (o && o->id != static_cast<std::uint32_t>(i)) {
            std::cerr << "erreur bench\n";
        }
        // Liberer
        if (o) pool.reclaim(o);
    }

    ns_t elapsed = now_ns() - start;
    return { elapsed, elapsed / static_cast<ns_t>(iterations), iterations };
}

BenchResult bench_new_delete(std::size_t iterations) {
    ns_t start = now_ns();

    for (std::size_t i = 0; i < iterations; ++i) {
        Order* o = new Order(
            static_cast<std::uint32_t>(i),
            100.0 + static_cast<double>(i % 100),
            10 + static_cast<std::uint32_t>(i % 50),
            std::string("AAPL")
        );
        if (o && o->id != static_cast<std::uint32_t>(i)) {
            std::cerr << "erreur bench\n";
        }
        delete o;
    }

    ns_t elapsed = now_ns() - start;
    return { elapsed, elapsed / static_cast<ns_t>(iterations), iterations };
}

// ============================================================
// main
// ============================================================

int main() {
    // --- Test fonctionnel ---
    std::cout << "=== ObjectPool<Order, 8> : test fonctionnel ===\n";
    {
        ObjectPool<Order, 8> pool;
        std::cout << "Pool : capacity=" << pool.capacity()
                  << " available=" << pool.available() << "\n";

        // make() avec perfect forwarding
        std::string sym1 = "AAPL";
        Order* o1 = pool.make(1001u, 142.50, 100u, sym1);          // sym1 : copie (lvalue)
        Order* o2 = pool.make(1002u, 99.99, 200u, std::string("TSLA")); // rvalue : move
        Order* o3 = pool.make(1003u, 500.0, 50u, "NVDA");          // char* : construction directe

        std::cout << "Apres 3 make() : available=" << pool.available()
                  << " used=" << pool.used() << "\n";

        std::cout << "o1: id=" << o1->id << " sym=" << o1->symbol << " price=" << o1->price << "\n";
        std::cout << "o2: id=" << o2->id << " sym=" << o2->symbol << " price=" << o2->price << "\n";
        std::cout << "o3: id=" << o3->id << " sym=" << o3->symbol << " price=" << o3->price << "\n";

        // sym1 est toujours valide (copie, pas move)
        std::cout << "sym1 apres make(sym1) : \"" << sym1 << "\" (inchange : lvalue copiee)\n";

        // reclaim : appelle ~Order() puis libere le slot
        pool.reclaim(o1);
        pool.reclaim(o2);
        std::cout << "Apres 2 reclaim() : available=" << pool.available() << "\n";

        // Reutiliser un slot libere
        Order* o4 = pool.make(1004u, 200.0, 75u, "META");
        std::cout << "Nouveau slot reutilise : o4->id=" << o4->id << " sym=" << o4->symbol << "\n";

        // Remplir le pool
        std::vector<Order*> all;
        all.push_back(o3);
        all.push_back(o4);
        for (std::size_t i = 0; all.size() < pool.capacity(); ++i) {
            Order* ox = pool.make(
                static_cast<std::uint32_t>(2000 + i), 1.0, 1u, "X"
            );
            if (!ox) break;
            all.push_back(ox);
        }
        std::cout << "Pool plein : available=" << pool.available() << "\n";

        Order* overflow = pool.make(9999u, 0.0, 0u, "OVERFLOW");
        std::cout << "make() sur pool plein retourne : "
                  << (overflow == nullptr ? "nullptr (correct)" : "ERREUR") << "\n";

        // Liberer tout avant fin de scope
        for (Order* o : all) pool.reclaim(o);
        std::cout << "Tout libere : available=" << pool.available() << "\n";
    }

    // --- Benchmark ---
    std::cout << "\n=== Benchmark : pool vs new/delete (100k ops) ===\n";
    constexpr std::size_t ITERS = 100'000;

    // Chauffe (evite les effets de cache froid)
    bench_pool(1000);
    bench_new_delete(1000);

    // Mesures
    auto r_pool = bench_pool(ITERS);
    auto r_new  = bench_new_delete(ITERS);

    r_pool.print("ObjectPool::make/reclaim");
    r_new.print("new/delete");

    if (r_pool.total_ns < r_new.total_ns) {
        double ratio = static_cast<double>(r_new.total_ns) /
                       static_cast<double>(r_pool.total_ns);
        std::cout << "Pool " << std::fixed << std::setprecision(1)
                  << ratio << "x plus rapide que new/delete\n";
    } else {
        double ratio = static_cast<double>(r_pool.total_ns) /
                       static_cast<double>(r_new.total_ns);
        std::cout << "new/delete " << std::fixed << std::setprecision(1)
                  << ratio << "x plus rapide (cache chaud ou optimisations)\n";
        std::cout << "Note : avec -O2, new peut etre optimise agressivement.\n";
        std::cout << "En production (allocation diversifiee), le pool gagne toujours.\n";
    }

    std::cout << "\nNote sur perfect forwarding dans make() :\n";
    std::cout << "  pool.make(id, price, qty, sym)  ou  sym est lvalue -> copie\n";
    std::cout << "  pool.make(id, price, qty, std::move(sym)) -> move (zero copie)\n";
    std::cout << "  pool.make(id, price, qty, \"LITERAL\") -> const char* forward direct\n";

    return 0;
}
