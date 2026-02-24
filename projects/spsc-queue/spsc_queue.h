#pragma once

#include <atomic>
#include <array>
#include <optional>
#include <cstddef>

// Single Producer Single Consumer lock-free circular queue.
// Template parameters:
//   T    : type des elements stockes (doit etre movable)
//   Size : capacite maximale (nombre d'elements, doit etre une puissance de 2)
//
// Contrainte : un seul thread appelle push(), un seul thread appelle pop().
// Violation de cette contrainte = comportement indefini.
template<typename T, std::size_t Size>
class SPSCQueue {
    static_assert((Size & (Size - 1)) == 0, "Size must be a power of 2");
    static_assert(Size >= 2, "Size must be at least 2");

    static constexpr std::size_t MASK = Size - 1;

public:
    SPSCQueue() = default;

    // Non-copiable, non-deplacable (les atomiques ne le sont pas)
    SPSCQueue(const SPSCQueue&) = delete;
    SPSCQueue& operator=(const SPSCQueue&) = delete;

    // Tente d'inserer un element. Retourne false si la queue est pleine.
    // Appele uniquement depuis le thread producteur.
    bool push(T item) noexcept {
        const std::size_t h = head_.load(std::memory_order_relaxed);
        const std::size_t next_head = (h + 1) & MASK;

        // Acquire : synchronise avec le store(release) du consommateur sur tail_
        // afin de voir les slots liberees par les pops precedents.
        if (next_head == tail_.load(std::memory_order_acquire)) {
            return false; // queue pleine
        }

        buffer_[h] = std::move(item);

        // Release : rend l'element visible au consommateur.
        head_.store(next_head, std::memory_order_release);
        return true;
    }

    // Tente de retirer un element. Retourne std::nullopt si la queue est vide.
    // Appele uniquement depuis le thread consommateur.
    std::optional<T> pop() noexcept {
        const std::size_t t = tail_.load(std::memory_order_relaxed);

        // Acquire : synchronise avec le store(release) du producteur sur head_
        // afin de voir les elements ecrits dans le buffer.
        if (t == head_.load(std::memory_order_acquire)) {
            return std::nullopt; // queue vide
        }

        T item = std::move(buffer_[t]);
        const std::size_t next_tail = (t + 1) & MASK;

        // Release : signale au producteur que la slot est libre.
        tail_.store(next_tail, std::memory_order_release);
        return item;
    }

    // Retourne vrai si la queue est vide (approximatif hors thread proprietaire).
    bool empty() const noexcept {
        return head_.load(std::memory_order_acquire) ==
               tail_.load(std::memory_order_acquire);
    }

    // Retourne le nombre d'elements presents (approximatif).
    std::size_t size() const noexcept {
        const std::size_t h = head_.load(std::memory_order_acquire);
        const std::size_t t = tail_.load(std::memory_order_acquire);
        return (h - t + Size) & MASK;
    }

    static constexpr std::size_t capacity() noexcept { return Size - 1; }

private:
    // head_ : index de la prochaine ecriture (producteur)
    // Padding pour isoler head_ sur sa propre cache line et eviter le false sharing.
    alignas(64) std::atomic<std::size_t> head_{0};
    char pad0_[64 - sizeof(std::atomic<std::size_t>)];

    // tail_ : index de la prochaine lecture (consommateur)
    alignas(64) std::atomic<std::size_t> tail_{0};
    char pad1_[64 - sizeof(std::atomic<std::size_t>)];

    // Le buffer est place apres les indexes pour ne pas partager leur cache line.
    std::array<T, Size> buffer_;
};
