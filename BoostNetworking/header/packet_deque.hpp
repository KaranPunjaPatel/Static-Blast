#ifndef PACKET_DEQUE_H
#define PACKET_DEQUE_H

#include <deque>
#include <mutex>
#include <iostream>
#include <condition_variable>

template <typename T>
struct Packet;

template <typename PacketHeaderType>
class PacketDeque {
public:
    PacketDeque() = default;
    PacketDeque(const PacketDeque<Packet<PacketHeaderType>>&) = delete;
    virtual ~PacketDeque() { clear(); }

    const Packet<PacketHeaderType>& front() {
        std::lock_guard<std::mutex> lg(muxQueue);
        return deqQueue.front();
    }

    const Packet<PacketHeaderType>& back() {
        std::lock_guard<std::mutex> lg(muxQueue);
        return deqQueue.back();
    }

    Packet<PacketHeaderType> pop_front() {
        std::lock_guard<std::mutex> lg(muxQueue);
        Packet item = std::move(deqQueue.front());
        deqQueue.pop_front();
        return item;
    }

    Packet<PacketHeaderType> pop_back() {
        std::lock_guard<std::mutex> lg(muxQueue);
        Packet item = std::move(deqQueue.back());
        deqQueue.pop_back();
        return item;
    }

    void push_back(const Packet<PacketHeaderType>& item) {
        {
            std::cout << "Insert: " << item << "\n";
            std::lock_guard<std::mutex> lg(muxQueue);
            deqQueue.push_back(item);
        }
        cvBlocking.notify_one();
    }

    void push_front(const Packet<PacketHeaderType>& item) {
        {
            std::lock_guard<std::mutex> lg(muxQueue);
            deqQueue.push_front(item);
        }
        cvBlocking.notify_one();
    }

    bool empty() {
        std::lock_guard<std::mutex> lg(muxQueue);
        return deqQueue.empty();
    }

    size_t count() {
        std::lock_guard<std::mutex> lg(muxQueue);
        return deqQueue.size();
    }

    void clear() {
        std::lock_guard<std::mutex> lg(muxQueue);
        deqQueue.clear();
    }

    void wait() {
        std::unique_lock<std::mutex> ul(muxQueue);
        cvBlocking.wait(ul, [this] { return !deqQueue.empty(); });
    }

protected:
    std::mutex muxQueue;
    std::deque<Packet<PacketHeaderType>> deqQueue;
    std::condition_variable cvBlocking;
};

#endif // PACKET_DEQUE_H
