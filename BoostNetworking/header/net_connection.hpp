#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

#include "packet_deque.hpp"
#include "util.hpp"


template <typename PacketHeaderType>
class Connection
{
public:
	uint64_t id{};
	boost::asio::ip::tcp::socket m_socket;
	Packet<PacketHeaderType> tempPacket;
	std::shared_ptr<PacketDeque<PacketHeaderType>> tcpRecvDeque;

	Connection() = default;
	Connection(boost::asio::ip::tcp::socket&& socket, std::shared_ptr<PacketDeque<PacketHeaderType>> tcpRecvDeque)
		: m_socket(std::move(socket)), tcpRecvDeque(tcpRecvDeque) {}

	void send(Packet<PacketHeaderType>& packet)
	{
		packet.header.id = id;
		std::cout << packet;

		/*std::cout << "Size Sent: " <<std::dec<< sizeof(Packet<PacketHeaderType>) << "\n";
		std::cout << "Size Sent: " << sizeof(PacketHeaderType) << "\n";
		std::cout << "Size Sent: " << sizeof(PacketHeader) << "\n";
		std::cout << "Size Sent: " << sizeof(tempPacket.header) << "\n";
		std::cout << "Size Sent: " << sizeof(tempPacket.header.id) << "\n";
		std::cout << "Size Sent: " << sizeof(tempPacket.header.size) <<"\n";*/

		boost::asio::async_write(m_socket, boost::asio::buffer(&packet, (sizeof(PacketHeaderType) + packet.header.size)),
			[this](std::error_code ec, std::size_t length)
			{
				// asio has now sent the bytes - if there was a problem
				// an error would be available...
				if (!ec)
				{
					std::cout << "Sent Message\n";
				}
				else
				{
					// ...asio failed to write the message, we could analyse why but 
					// for now simply assume the connection has died by closing the
					// socket. When a future attempt to write to this client fails due
					// to the closed socket, it will be tidied up.
					std::cout << std::hex << "[" << id << "] Write Header Fail.\n";
					m_socket.close();
				}
			});
	}

	void readHeader();

	void readPayload();

	void ConnectToClient();

	void ConnectToServer(boost::asio::ip::tcp::resolver::results_type endpoints);

	void AddToIncomingMessageQueue();

	bool isConnected() const;

	bool disconnect();

	bool reset();

};

//#include "../header/net_connection.hpp"

template <typename PacketHeaderType>
void Connection<PacketHeaderType>::readHeader()
{
	tempPacket.clear();

	//std::cout << "Here: " << tempPacket;
	boost::asio::async_read(m_socket,
		boost::asio::buffer(&tempPacket.header, sizeof(PacketHeaderType)),
		[this](std::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				// A complete message header has been read, check if this message
				// has a body to follow...
				std::cout << std::hex << "[" << id << "] Received something.\n";

				std::cout << tempPacket;
				if (tempPacket.header.size > 0)
				{
					// ...it does, so allocate enough space in the messages' body
					// vector, and issue asio with the task to read the body.
					tempPacket.payload.resize(tempPacket.header.size);
					readPayload();
				}
				else
				{
					// it doesn't, so add this bodyless message to the connections
					// incoming message queue
					//std::cout << "No Payload\n";
					AddToIncomingMessageQueue();

				}
			}
			else
			{
				// Reading form the client went wrong, most likely a disconnect
				// has occurred. Close the socket and let the system tidy it up later.
				std::cout << std::hex << "[" << id << "] Read Header Fail.\n";
				m_socket.close();
			}
		}
	);
}

template <typename PacketHeaderType>
void Connection<PacketHeaderType>::readPayload()
{
	boost::asio::async_read(m_socket,
		boost::asio::buffer(tempPacket.payload.data(), tempPacket.payload.size()),
		[this](std::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				// ...and they have! The message is now complete, so add
						// the whole message to incoming queue
				AddToIncomingMessageQueue();
			}
			else
			{
				// As above!
				std::cout << std::hex << "[" << id << "] Read Body Fail.\n";
				m_socket.close();
			}
		}
	);
}

template <typename PacketHeaderType>
void Connection<PacketHeaderType>::ConnectToClient()
{
	if (isConnected())
		readHeader();
}

template <typename PacketHeaderType>
void Connection<PacketHeaderType>::ConnectToServer(
	boost::asio::ip::tcp::resolver::results_type endpoints
)
{
	boost::asio::async_connect(m_socket, endpoints,
		[this](std::error_code ec, boost::asio::ip::tcp::endpoint endpoint)
		{
			if (!ec)
			{
				std::cout << "[Client] Connected to server\n";
				readHeader();
			}
		});
}

template <typename PacketHeaderType>
void Connection<PacketHeaderType>::AddToIncomingMessageQueue()
{
	tcpRecvDeque->push_back(tempPacket);
	readHeader();
}

template <typename PacketHeaderType>
bool Connection<PacketHeaderType>::isConnected() const
{
	return m_socket.is_open();
}

template <typename PacketHeaderType>
bool Connection<PacketHeaderType>::disconnect()
{
	m_socket.close();
	return true;
}

template <typename PacketHeaderType>
bool Connection<PacketHeaderType>::reset()
{
	return true;
}


//template class Connection<PacketHeader>;
