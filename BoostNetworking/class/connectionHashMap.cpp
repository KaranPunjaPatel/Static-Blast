#include "../header/connectionHashMap.hpp"
#include "../header/util.hpp"

template<typename PacketHeaderType>
uint64_t ConnectionHashMap<PacketHeaderType>::getUniqueId()
{
	uint64_t id;
	while (exist(id = getRandomNumber<uint64_t>(0, UINT64_MAX)));

	return id;
}

template<typename PacketHeaderType>
bool ConnectionHashMap<PacketHeaderType>::exist(uint64_t id)
{
	std::lock_guard<std::mutex> lock(readMutex);
	return (connections.find(id) != connections.end());
}

template<typename PacketHeaderType>
void ConnectionHashMap<PacketHeaderType>::addConnection(std::shared_ptr<Connection<PacketHeaderType>> conn)
{
	std::lock_guard<std::mutex> lock(writeMutex);

	conn->id = getUniqueId(); // Get an unique identification number

	std::cout << "[Server] Added Connection with id: " << std::hex << conn->id << "\n";

	conn->tcpRecvDeque = tcpRecvDeque;
	connections.insert(std::make_pair(conn->id, conn));

	//auto packet = std::make_shared < Packet<PacketHeaderType>>();
	conn->ConnectToClient();
}

template<typename PacketHeaderType>
void ConnectionHashMap<PacketHeaderType>::removeConnection(uint64_t id)
{
	std::lock_guard<std::mutex> lock(writeMutex);
	if(exist(id)) connections.erase(id);
}

template<typename PacketHeaderType>
void ConnectionHashMap<PacketHeaderType>::sendMessage(uint64_t id, Packet<PacketHeaderType>& packet)
{
	std::lock_guard<std::mutex> lock(writeMutex);
	//std::scoped_lock(writeMutex);

	if (exist(id))
	{
		std::shared_ptr<Connection<PacketHeaderType>> conn = connections.at(id);
		if (conn->isConnected())
		{
			conn->send(packet);

		}
		else
		{
			// TODO: Client disconnected
			// maybe perform a retry on the socket
			if (conn->reset())
			{

			}
			else {
				conn->disconnect();
			}
		}
	}
}

template class ConnectionHashMap<PacketHeader>;

