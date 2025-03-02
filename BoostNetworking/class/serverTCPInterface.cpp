#include "../header/serverTCPInterface.hpp"

template <typename PacketHeaderType>
ServerTCPInterface<PacketHeaderType>::ServerTCPInterface(
    boost::asio::io_context& context,
    const boost::asio::ip::port_type port, 
    std::shared_ptr<ConnectionHashMap<PacketHeaderType>> connections
)
	: context_(context), 
        socket(context), 
        acceptor(context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
        connections_(connections)
{
    readBuffer = std::make_shared<boost::asio::streambuf>();
}

template <typename PacketHeaderType>
bool ServerTCPInterface<PacketHeaderType>::Start()
{
    try
    {
        WaitForClientConnnections();
    }
    catch (std::exception& e)
    {
        // Error during listening
        std::cerr << "[Server] Exception " << e.what() << "\n";
        return false;
    }

    std::cout << "[Server] TCP Iface started\n";
    return true;
}

template <typename PacketHeaderType>
bool ServerTCPInterface<PacketHeaderType>::Stop()
{
    return true;
}

template <typename PacketHeaderType>
void ServerTCPInterface<PacketHeaderType>::WaitForClientConnnections()
{
    acceptor.async_accept(
        [this](std::error_code ec, boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                std::cout << "[Server] New Connection: " << socket.remote_endpoint() << "\n";
                auto conn = std::make_shared<Connection<PacketHeaderType>>(std::move(socket), nullptr);
                connections_->addConnection(conn);
                Packet<PacketHeaderType> packet{};
                SendMessageToConnection(conn->id, packet);
            }
            else
            {
                std::cout << "[Server] New Connection Error: " << ec.message() << "\n";
            }

            WaitForClientConnnections();
        }
    );
}

template <typename PacketHeaderType>
void ServerTCPInterface<PacketHeaderType>::SendMessageToConnection(uint64_t id, Packet<PacketHeaderType>& packet)
{
    connections_->sendMessage(id,packet);
}

template class ServerTCPInterface<PacketHeader>;

/*
void ServerTCPInterface::startAccept()
{
    std::cout << "Waiting for incoming connections..." << std::endl;
    acceptor.async_accept(socket, 
        [this](const boost::system::error_code& error)
        {
            handleAccept(error);
        });
}

void ServerTCPInterface::handleAccept(const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "Connection accepted from: " << socket.remote_endpoint() << std::endl;
        startRecv();
    }
    else
    {
        std::cerr << "Error accepting connection: " << error.message() << std::endl;
    }
}

void ServerTCPInterface::startRecv()
{
    std::cout << "Ready to receive data..." << std::endl;
    boost::asio::async_read(socket, *readBuffer, boost::asio::transfer_at_least(1),
        [this](const boost::system::error_code& error, size_t bytes_transferred)
        {
            handleRecv(error, bytes_transferred);
        });
}

void ServerTCPInterface::handleRecv(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Received " << bytes_transferred << " bytes of data" << std::endl;

        // Here you can parse the received data into packets and push it into the deque
        // Example: recvMessageDeque.push_back(Packet<PacketHeader>(readBuffer));

        // After receiving, continue receiving
        startRecv();
    }
    else
    {
        std::cerr << "Error receiving data: " << error.message() << std::endl;
    }
}

void ServerTCPInterface::startWrite(const std::string& message)
{
    std::cout << "Sending message: " << message << std::endl;

    // Example: Convert message to a Packet<PacketHeader> and enqueue it to sendMessageDeque

    // Assuming the message can be converted to the correct packet structure:
    // sendMessageDeque.push_back(Packet<PacketHeader>(message));

    // Convert the message to a buffer for sending
    auto buffer = std::make_shared<std::string>(message);
    boost::asio::async_write(socket, boost::asio::buffer(*buffer),
        [this, buffer](const boost::system::error_code& error, size_t bytes_transferred)
        {
            handleWrite(error, bytes_transferred);
        });
}

void ServerTCPInterface::handleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Successfully sent " << bytes_transferred << " bytes of data" << std::endl;
    }
    else
    {
        std::cerr << "Error sending data: " << error.message() << std::endl;
    }
}

void ServerTCPInterface::listen()
{
    startAccept();  // Begin accepting connections
    context_.run(); // Start the IO context to begin asynchronous operations
}

*/