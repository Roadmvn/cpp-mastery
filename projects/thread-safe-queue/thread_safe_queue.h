#pragma once

#include <deque>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <cstddef>
#include <stdexcept>

// Queue thread-safe generique : N producteurs, M consommateurs.
// Utilise un mutex + condition_variable.
// Pas de capacite maximale (illimitee) — voir bounded variant si necessaire.
template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;

    // Non-copiable
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    // Insere un element. Reveille un consommateur en attente.
    // Thread-safe, peut etre appele depuis n'importe quel thread.
    void push(T item) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (closed_) {
                throw std::runtime_error("push on closed queue");
            }
            queue_.push_back(std::move(item));
        }
        cv_.notify_one();
    }

    // Retire et retourne un element.
    // Bloque si la queue est vide. Retourne std::nullopt si la queue est fermee et vide.
    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !queue_.empty() || closed_; });

        if (queue_.empty()) {
            return std::nullopt; // queue fermee et vide
        }

        T item = std::move(queue_.front());
        queue_.pop_front();
        return item;
    }

    // Tente de retirer un element sans bloquer.
    // Retourne std::nullopt si la queue est vide.
    std::optional<T> try_pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return std::nullopt;
        }
        T item = std::move(queue_.front());
        queue_.pop_front();
        return item;
    }

    // Ferme la queue : les consommateurs bloques seront reveilles et recevront nullopt.
    // Apres close(), push() lance une exception.
    void close() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            closed_ = true;
        }
        cv_.notify_all();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    std::size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    bool is_closed() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return closed_;
    }

private:
    mutable std::mutex      mutex_;
    std::condition_variable cv_;
    std::deque<T>           queue_;
    bool                    closed_{false};
};
