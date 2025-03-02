#pragma once
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

template <typename T>
T getRandomNumber(T min, T max) {
    static std::random_device rd;                   // Random device for seeding
    static std::mt19937_64 gen(rd());               // 64-bit Mersenne Twister generator

    if constexpr (std::is_integral<T>::value) {     // For integral types
        std::uniform_int_distribution<T> dist(min, max);
        return dist(gen);
    }
    else if constexpr (std::is_floating_point<T>::value) { // For floating-point types
        std::uniform_real_distribution<T> dist(min, max);
        return dist(gen);
    }
    else {
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    }
}

enum struct ConnectionState : uint8_t { None, Lobby, Game, Disconnected };

enum struct PacketType : uint8_t {
    ServerIdentification,
    ConnectionRequest,   // Request to connect to the server
    ConnectionResponse,  // Server's response to a connection request
    GameMove,            // A move made in the game
    StateUpdate,         // Game state update
    ChatMessage,         // Chat between players
    KeepAlive,           // Keep-alive signal
    Disconnect           // Notify disconnection
};

#pragma pack(push, 1)
struct PacketHeader {
    uint64_t id;            // Unique packet ID or sequence number
    uint32_t size;          // Size of entire packet including the header
    ConnectionState state;  // State of connection at send time
    PacketType type;        // Type of the packet (for routing and processing)

    void clear()
    {
        id = 0;
        size = 0;
    }

    friend std::ostream& operator << (std::ostream& os, const PacketHeader& msg)
    {
        os << "ID:" << msg.id << " Size:" << msg.size << "\n";
        return os;
    }
    

};
#pragma pack(pop)

template <typename Header>
struct Packet {
    Header header;                  // Packet header
    std::vector<uint8_t> payload;   // Variable-sized payload

    size_t size() const
    {
        return payload.size();
    }

    void clear()
    {
        header.clear();
        payload.clear();
        //std::cout << "Size: " << payload.capacity() << "\n";
        payload.resize(0);
    }

    friend std::ostream& operator << (std::ostream& os, const Packet<Header>& msg)
    {
        os << "ID:" << msg.header.id << " Size:" << msg.header.size << "\n";
        return os;
    }

    template<typename DataType>
    friend Packet<Header>& operator << (Packet<Header>& msg, const DataType& data)
    {
        // Check that the type of the data being pushed is trivially copyable
        static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

        // Cache current size of vector, as this will be the point we insert the data
        size_t i = msg.payload.size();

        // Resize the vector by the size of the data being pushed
        msg.payload.resize(msg.payload.size() + sizeof(DataType));

        // Physically copy the data into the newly allocated vector space
        std::memcpy(msg.payload.data() + i, &data, sizeof(DataType));

        // Recalculate the message size
        msg.header.size = msg.payload.size();

        // Return the target message so it can be "chained"
        return msg;
    }
};

