
#include "../header/client.hpp"

Client::Client()
	: idleWork(std::make_unique<boost::asio::io_context::work>(context)),
		tcpRecvMessageDeque(std::make_shared<PacketDeque<PacketHeader>>()),
		tcpIface(context, tcpRecvMessageDeque)
{

}

Client::~Client()
{
	Stop();
}

bool Client::Start(
	const std::string host,
	const uint16_t port
)
{
	threadContext = std::thread([this]() { context.run(); });
	if (!tcpIface.Connect(host,port))
	{
		std::cerr << "[Client] Failed to start one or both of the ifaces\n";
	}
	return true;
}

void Client::Stop()
{
	context.stop();

	if (threadContext.joinable()) threadContext.join();

	std::cout << "[Client] Stopped\n";
}

void Client::ProcessTcpPackets()
{

}
