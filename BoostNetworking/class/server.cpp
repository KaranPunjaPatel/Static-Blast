#include "../header/server.hpp"

Server::Server() 
	: idleWork(std::make_unique<boost::asio::io_context::work>(context)),
		tcpRecvMessageDeque(std::make_shared<PacketDeque<PacketHeader>>()),
		connections(std::make_shared<ConnectionHashMap<PacketHeader>>(tcpRecvMessageDeque)),
		tcpIface( context, PORT, connections )
{
	//boost::asio::io_context::work idlework(context);
	threadContext = std::thread([this]() { context.run(); });
}

bool Server::Start()
{
	if (!tcpIface.Start())
	{
		std::cerr << "[Server] Failed to start one or both of the ifaces\n";
	}
	return true;
}

void Server::Stop()
{
	context.stop();

	if (threadContext.joinable()) threadContext.join();

	std::cout << "[Server] Stopped\n";
}

void Server::Update()
{

}

Server::~Server()
{
	Stop();
}
