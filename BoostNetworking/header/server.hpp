#pragma once
#include "util.hpp"
#include <boost/asio.hpp>

#include <unordered_map>

#include "serverTCPInterface.hpp"
#include "connectionHashMap.hpp"

constexpr boost::asio::ip::port_type PORT = 12345;

class Server
{
public:
	Server();
	~Server();

	bool Start();
	void Stop();
	void Update();


protected:
	boost::asio::io_context context;
	std::unique_ptr<boost::asio::io_context::work> idleWork;

	std::shared_ptr<PacketDeque<PacketHeader>> tcpRecvMessageDeque;
	std::shared_ptr<ConnectionHashMap<PacketHeader>> connections;

	ServerTCPInterface<PacketHeader> tcpIface;


	std::thread threadContext;


	
};

