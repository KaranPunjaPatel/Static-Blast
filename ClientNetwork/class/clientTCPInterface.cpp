#include "../header/clientTCPInterface.hpp"

template <typename PacketHeaderType>
ClientTCPInterface<PacketHeaderType>::ClientTCPInterface(
	boost::asio::io_context& context,
	std::shared_ptr<PacketDeque<PacketHeaderType>> tcpRecvDeque
)
	:	context_(context),
		tcpRecvDeque(tcpRecvDeque)
{

}

template <typename PacketHeaderType>
bool ClientTCPInterface<PacketHeaderType>::Connect(
	const std::string host,
	const uint16_t port
)
{
	
	try
	{
		// Resolve hostname/ip-address into tangiable physical address
		boost::asio::ip::tcp::resolver resolver(context_);
		boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

		// Create connection
		connection = std::make_unique<Connection<PacketHeaderType>>(boost::asio::ip::tcp::socket(context_), tcpRecvDeque);

		// Tell the connection object to connect to server
		connection->ConnectToServer(endpoints);


	}
	catch (std::exception& e)
	{
		std::cerr << "Client Exception: " << e.what() << "\n";
		return false;
	}
	std::cout << "[Client] TCP Iface started\n";
	return true;
}


template <typename PacketHeaderType>
bool ClientTCPInterface<PacketHeaderType>::Stop()
{
	return true;
}


template class ClientTCPInterface<PacketHeader>;
