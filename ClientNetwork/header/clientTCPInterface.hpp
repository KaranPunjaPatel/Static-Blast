#pragma once
#include <boost/asio.hpp>
#include <memory>
#include "../../BoostNetworking/header/net_connection.hpp"
//#include "../../BoostNetworking/header/packet_deque.hpp"

template <typename PacketHeaderType>
class ClientTCPInterface
{
public:
	ClientTCPInterface(
		boost::asio::io_context& context,
		std::shared_ptr<PacketDeque<PacketHeaderType>> tcpRecvDeque
	);

	//bool Connect(const std::string& host, const boost::asio::ip::port_type port);
	bool Connect(const std::string host, const uint16_t port);
	bool Stop();


protected:
	boost::asio::io_context& context_;
	std::shared_ptr<PacketDeque<PacketHeaderType>> tcpRecvDeque;
	std::unique_ptr<Connection<PacketHeaderType>> connection;
};