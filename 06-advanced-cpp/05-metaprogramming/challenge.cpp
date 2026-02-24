// Chapitre 05 — Challenge HFT : TypeList, type_at et dispatcher de protocole
// Compilation : g++ -std=c++20 -Wall -Wextra -O2 -o challenge challenge.cpp
//
// Contexte : En HFT, les protocoles réseau (ITCH, OUCH, FIX Binary) definissent
// un ensemble fini de types de messages connus a la compilation. L'objectif est
// de construire un dispatcher zero-overhead : le bon handler est selectionne a
// la compilation, sans branchement dynamique ni vtable.
//
// Ce que l'on implemente :
//   1. TypeList<Types...>  : liste de types manipulable a la compilation
//   2. type_at<N, List>    : acces au N-ieme type dans une TypeList
//   3. index_of<T, List>   : trouver l'indice d'un type dans la liste
//   4. contains<T, List>   : detecter si un type est present
//   5. MessageDispatcher   : appelle la bonne surcharge selon le tag compile-time
//
// Architecture du dispatcher :
//
//   enum class MsgTag { NewOrder, Cancel, Fill, Heartbeat };
//
//   TypeList<NewOrder, Cancel, Fill, Heartbeat>
//        |
//        v
//   Dispatcher::dispatch<MsgTag::NewOrder>(data)
//        |
//        v
//   Handler::handle(NewOrder&)   <- resolu a la compilation, zero branchement

#include <iostream>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <string_view>
#include <array>

// ============================================================
// 1. TypeList : conteneur de types a la compilation
// ============================================================

// Type vide sentinel (fin de liste)
struct NullType {};

// TypeList variadic : TypeList<int, double, char>
template<typename... Types>
struct TypeList {
    static constexpr std::size_t size = sizeof...(Types);
};

// Specialisation vide
template<>
struct TypeList<> {
    static constexpr std::size_t size = 0;
};

// ============================================================
// 2. type_at<N, TypeList> : acces au N-ieme type
//
//    type_at<0, TypeList<int, double, char>>::type  =>  int
//    type_at<2, TypeList<int, double, char>>::type  =>  char
// ============================================================

// Declaration primaire : N = index, List = TypeList
template<std::size_t N, typename List>
struct type_at;

// Cas de base : N == 0, on prend le premier type
template<typename Head, typename... Tail>
struct type_at<0, TypeList<Head, Tail...>> {
    using type = Head;
};

// Cas recursif : decrementer N et passer au reste de la liste
template<std::size_t N, typename Head, typename... Tail>
struct type_at<N, TypeList<Head, Tail...>> {
    static_assert(N < sizeof...(Tail) + 1, "type_at: index hors limites");
    using type = typename type_at<N - 1, TypeList<Tail...>>::type;
};

// Alias pratique
template<std::size_t N, typename List>
using type_at_t = typename type_at<N, List>::type;

// ============================================================
// 3. index_of<T, TypeList> : retrouver l'indice d'un type
//
//    index_of<double, TypeList<int, double, char>>::value  =>  1
// ============================================================

template<typename T, typename List, std::size_t I = 0>
struct index_of;

// T correspond a Head : on a trouve l'indice
template<typename T, typename... Tail, std::size_t I>
struct index_of<T, TypeList<T, Tail...>, I> {
    static constexpr std::size_t value = I;
};

// T ne correspond pas : continuer avec le reste
template<typename T, typename Head, typename... Tail, std::size_t I>
struct index_of<T, TypeList<Head, Tail...>, I> {
    static constexpr std::size_t value = index_of<T, TypeList<Tail...>, I + 1>::value;
};

// Pas trouve : valeur sentinelle
template<typename T, std::size_t I>
struct index_of<T, TypeList<>, I> {
    static constexpr std::size_t value = static_cast<std::size_t>(-1);
};

// ============================================================
// 4. contains<T, TypeList> : detecter la presence d'un type
// ============================================================

template<typename T, typename List>
struct contains {
    static constexpr bool value = (index_of<T, List>::value != static_cast<std::size_t>(-1));
};

template<typename T, typename List>
constexpr bool contains_v = contains<T, List>::value;

// ============================================================
// Static assertions : validation de l'infrastructure
// ============================================================

using TestList = TypeList<int, double, char, float>;

static_assert(TestList::size == 4);
static_assert(std::is_same_v<type_at_t<0, TestList>, int>);
static_assert(std::is_same_v<type_at_t<1, TestList>, double>);
static_assert(std::is_same_v<type_at_t<2, TestList>, char>);
static_assert(std::is_same_v<type_at_t<3, TestList>, float>);
static_assert(index_of<double, TestList>::value == 1);
static_assert(index_of<float,  TestList>::value == 3);
static_assert(contains_v<char,  TestList> == true);
static_assert(contains_v<short, TestList> == false);

// ============================================================
// 5. Messages de protocole HFT (style ITCH/OUCH simplifie)
//
//    Chaque message est un struct POD avec un tag identifiant son type.
// ============================================================

// Tag de message : identifiant compile-time
enum class MsgTag : std::uint8_t {
    NewOrder    = 0,
    CancelOrder = 1,
    Fill        = 2,
    Heartbeat   = 3
};

struct NewOrder {
    static constexpr MsgTag tag = MsgTag::NewOrder;
    std::uint32_t order_id;
    double        price;
    std::uint32_t quantity;
    bool          is_buy;
};

struct CancelOrder {
    static constexpr MsgTag tag = MsgTag::CancelOrder;
    std::uint32_t order_id;
};

struct Fill {
    static constexpr MsgTag tag = MsgTag::Fill;
    std::uint32_t order_id;
    std::uint32_t filled_qty;
    double        fill_price;
};

struct Heartbeat {
    static constexpr MsgTag tag = MsgTag::Heartbeat;
    std::uint64_t timestamp_ns;
};

// La TypeList complete des messages du protocole
using ProtocolMessages = TypeList<NewOrder, CancelOrder, Fill, Heartbeat>;

static_assert(ProtocolMessages::size == 4);
static_assert(std::is_same_v<type_at_t<0, ProtocolMessages>, NewOrder>);
static_assert(std::is_same_v<type_at_t<3, ProtocolMessages>, Heartbeat>);

// ============================================================
// 6. Handler de messages : un overload par type
// ============================================================

struct MarketDataHandler {
    int new_orders    = 0;
    int cancellations = 0;
    int fills         = 0;
    int heartbeats    = 0;

    void handle(const NewOrder& msg) {
        ++new_orders;
        std::cout << "  NewOrder  id=" << msg.order_id
                  << " price=" << msg.price
                  << " qty=" << msg.quantity
                  << " side=" << (msg.is_buy ? "BUY" : "SELL") << "\n";
    }

    void handle(const CancelOrder& msg) {
        ++cancellations;
        std::cout << "  Cancel    id=" << msg.order_id << "\n";
    }

    void handle(const Fill& msg) {
        ++fills;
        std::cout << "  Fill      id=" << msg.order_id
                  << " qty=" << msg.filled_qty
                  << " price=" << msg.fill_price << "\n";
    }

    void handle(const Heartbeat& msg) {
        ++heartbeats;
        std::cout << "  Heartbeat ts=" << msg.timestamp_ns << "ns\n";
    }
};

// ============================================================
// 7. MessageDispatcher : dispatch compile-time
//
//    dispatch<MsgTag::NewOrder>(handler, raw_data) :
//      - reinterpret_cast<const NewOrder*>(raw_data)
//      - appelle handler.handle(msg)
//
//    Pas de switch, pas de virtual : branchement statique.
// ============================================================

// Helper : dispatcher pour un tag specifique
// Le type est deduit depuis la TypeList via type_at
template<MsgTag Tag, typename Handler>
void dispatch_single(Handler& handler, const void* raw) {
    // Trouver l'indice correspondant au tag dans la liste
    // On utilise le tag directement comme indice (design simplifie coherent)
    constexpr std::size_t idx = static_cast<std::size_t>(Tag);
    using MsgType = type_at_t<idx, ProtocolMessages>;

    // Verification que le mapping tag -> type est coherent
    static_assert(MsgType::tag == Tag,
        "Incoherence entre MsgTag et position dans ProtocolMessages");

    const MsgType* msg = reinterpret_cast<const MsgType*>(raw);
    handler.handle(*msg);
}

// Dispatcher principal : resout le tag au runtime, puis appelle le
// bon handler avec typage static. En production, le compilateur peut
// transformer ce switch en table de pointeurs de fonctions inlinees.
template<typename Handler>
void dispatch(Handler& handler, MsgTag tag, const void* raw) {
    switch (tag) {
        case MsgTag::NewOrder:
            dispatch_single<MsgTag::NewOrder>(handler, raw);
            break;
        case MsgTag::CancelOrder:
            dispatch_single<MsgTag::CancelOrder>(handler, raw);
            break;
        case MsgTag::Fill:
            dispatch_single<MsgTag::Fill>(handler, raw);
            break;
        case MsgTag::Heartbeat:
            dispatch_single<MsgTag::Heartbeat>(handler, raw);
            break;
    }
}

// ============================================================
// 8. Dispatcher entierement compile-time (sans switch runtime)
//
//    Quand le tag est une constante template, le dispatch est
//    resolu a zero cout : pas de branchement, pas de table.
// ============================================================

// expand_dispatch : genere un tableau de fonctions statiques (une par message)
// Appele avec dispatch_table[tag_index](handler, raw)

template<typename Handler, typename List, std::size_t... Is>
void dispatch_table_impl(Handler& handler, std::size_t tag_idx,
                         const void* raw, std::index_sequence<Is...>) {
    // Tableau de pointeurs vers les fonctions dispatch specialisees
    using DispatchFn = void(*)(Handler&, const void*);
    constexpr DispatchFn table[] = {
        [](Handler& h, const void* p) {
            const type_at_t<Is, List>* msg =
                reinterpret_cast<const type_at_t<Is, List>*>(p);
            h.handle(*msg);
        }...
    };
    if (tag_idx < sizeof...(Is)) {
        table[tag_idx](handler, raw);
    }
}

// Surcharge propre utilisant index_sequence
template<typename Handler>
void dispatch_static(Handler& handler, std::size_t tag_idx, const void* raw) {
    dispatch_table_impl<Handler, ProtocolMessages>(
        handler, tag_idx, raw,
        std::make_index_sequence<ProtocolMessages::size>{}
    );
}

// ============================================================
// main
// ============================================================

int main() {
    std::cout << "=== TypeList inspection ===\n";
    std::cout << "ProtocolMessages::size = " << ProtocolMessages::size << "\n";
    std::cout << "index_of<Fill>         = " << index_of<Fill, ProtocolMessages>::value << "\n";
    std::cout << "contains<Heartbeat>    = " << contains_v<Heartbeat, ProtocolMessages> << "\n";
    std::cout << "contains<int>          = " << contains_v<int, ProtocolMessages> << "\n";

    // Simulation : messages arrives depuis le reseau sous forme de bytes
    std::cout << "\n=== Dispatch via switch (runtime tag) ===\n";
    MarketDataHandler handler1;

    NewOrder    no{1001, 142.50, 100, true};
    CancelOrder co{1001};
    Fill        fi{1001, 100, 142.50};
    Heartbeat   hb{1708704000000000000ULL};

    dispatch(handler1, MsgTag::NewOrder,    &no);
    dispatch(handler1, MsgTag::CancelOrder, &co);
    dispatch(handler1, MsgTag::Fill,        &fi);
    dispatch(handler1, MsgTag::Heartbeat,   &hb);

    std::cout << "  -> new_orders="    << handler1.new_orders
              << " cancels="           << handler1.cancellations
              << " fills="             << handler1.fills
              << " heartbeats="        << handler1.heartbeats << "\n";

    // Dispatch entierement statique via table de fonctions
    std::cout << "\n=== Dispatch via table statique (index_sequence) ===\n";
    MarketDataHandler handler2;

    NewOrder    no2{2001, 99.99, 200, false};
    Fill        fi2{2001, 200, 99.99};

    dispatch_static(handler2, static_cast<std::size_t>(MsgTag::NewOrder), &no2);
    dispatch_static(handler2, static_cast<std::size_t>(MsgTag::Fill),     &fi2);
    dispatch_static(handler2, static_cast<std::size_t>(MsgTag::Heartbeat),&hb);

    std::cout << "  -> new_orders="    << handler2.new_orders
              << " fills="             << handler2.fills
              << " heartbeats="        << handler2.heartbeats << "\n";

    // Dispatch entierement a la compilation : le tag est une constante template
    std::cout << "\n=== Dispatch compile-time pur (template tag) ===\n";
    MarketDataHandler handler3;
    NewOrder no3{3001, 200.00, 50, true};

    // Appel direct : resolu sans branchement, type deduit depuis ProtocolMessages
    dispatch_single<MsgTag::NewOrder>(handler3, &no3);
    dispatch_single<MsgTag::Fill>(handler3, &fi);
    std::cout << "  -> new_orders=" << handler3.new_orders
              << " fills="          << handler3.fills << "\n";

    // Verification compile-time des proprietes TypeList
    std::cout << "\n=== Static assertions passees ===\n";
    std::cout << "  type_at<0> = NewOrder     : "
              << std::is_same_v<type_at_t<0, ProtocolMessages>, NewOrder> << "\n";
    std::cout << "  type_at<2> = Fill          : "
              << std::is_same_v<type_at_t<2, ProtocolMessages>, Fill> << "\n";
    std::cout << "  index_of<CancelOrder> = 1  : "
              << (index_of<CancelOrder, ProtocolMessages>::value == 1) << "\n";

    return 0;
}
