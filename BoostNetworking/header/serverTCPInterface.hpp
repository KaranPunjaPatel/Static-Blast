#pragma once

#include "connectionHashMap.hpp"
#include "packet_deque.hpp"
#include "util.hpp"
#include <boost/asio.hpp>

template <typename PacketHeaderType>
class ServerTCPInterface
{
public:
	ServerTCPInterface(boost::asio::io_context& context,
				const boost::asio::ip::port_type port, 
				std::shared_ptr<ConnectionHashMap<PacketHeaderType>> connections);
	/*void startAccept();
	void startRecv();
	void startWrite(const std::string& message);
	void listen();*/

	bool Start();
	bool Stop();
	void Update(size_t nMaxMessages = -1); 

	void WaitForClientConnnections();
	void SendMessageToConnection(uint64_t id, Packet<PacketHeaderType>& packet);

protected:


	boost::asio::io_context& context_;
	boost::asio::ip::tcp::socket socket;
	boost::asio::ip::tcp::acceptor acceptor;
	std::shared_ptr<ConnectionHashMap<PacketHeaderType>> connections_;

	std::shared_ptr<boost::asio::streambuf> readBuffer;

};

