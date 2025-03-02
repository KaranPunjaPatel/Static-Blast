#pragma once

#include <boost/asio.hpp>
//#include "../../BoostNetworking/header/packet_deque.hpp"
//#include "../../BoostNetworking/header/util.hpp"
#include "clientTCPInterface.hpp"

class Client
{
public:
	Client();
	~Client();

	bool Start(const std::string host, const uint16_t port);
	void Stop();

	void ProcessTcpPackets();

protected:
	boost::asio::io_context context;
	std::unique_ptr<boost::asio::io_context::work> idleWork;

	std::shared_ptr<PacketDeque<PacketHeader>> tcpRecvMessageDeque;
	
	ClientTCPInterface<PacketHeader> tcpIface;


	std::thread threadContext;

};