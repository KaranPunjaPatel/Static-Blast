#pragma once

#include <boost/asio.hpp>

#include <unordered_map>
#include <mutex>

#include "util.hpp"
#include "packet_deque.hpp"

#include "net_connection.hpp"

//template <typename T>
//struct Packet;



template<typename PacketHeaderType>
class ConnectionHashMap
{
public:
	ConnectionHashMap(std::shared_ptr<PacketDeque<PacketHeaderType>> tcpRecvDeque)
		: tcpRecvDeque(tcpRecvDeque) {}
	~ConnectionHashMap() = default;

	uint64_t getUniqueId();
	bool exist(uint64_t id);
	void addConnection(std::shared_ptr<Connection<PacketHeaderType>> conn);
	void removeConnection(uint64_t id);

	void sendMessage(uint64_t id, Packet<PacketHeaderType>& packet);

//protected: 
	std::unordered_map<
			uint64_t, 
			std::shared_ptr<Connection<PacketHeaderType>>
		> connections;

	std::shared_ptr<PacketDeque<PacketHeaderType>> tcpRecvDeque;

	std::mutex readMutex;
	std::mutex writeMutex;
};

