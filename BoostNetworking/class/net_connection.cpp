//#include "../header/net_connection.hpp"
//
//template <typename PacketHeaderType>
//void Connection<PacketHeaderType>::readHeader()
//{
//	boost::asio::async_read(m_socket,
//		boost::asio::buffer(&tempPacket.header, sizeof(PacketHeaderType)),
//		[this](std::error_code ec, std::size_t length)
//		{
//			if (!ec)
//			{
//				// A complete message header has been read, check if this message
//				// has a body to follow...
//				std::cout << "[" << id << "] Received something.\n";
//
//				if (tempPacket.header.size > 0)
//				{
//					// ...it does, so allocate enough space in the messages' body
//					// vector, and issue asio with the task to read the body.
//					tempPacket.payload.resize(tempPacket.header.size);
//					readPayload();
//				}
//				else
//				{
//					// it doesn't, so add this bodyless message to the connections
//					// incoming message queue
//					AddToIncomingMessageQueue();
//
//				}
//			}
//			else
//			{
//				// Reading form the client went wrong, most likely a disconnect
//				// has occurred. Close the socket and let the system tidy it up later.
//				std::cout << "[" << id << "] Read Header Fail.\n";
//				m_socket.close();
//			}
//		}
//	);
//}
//
//template <typename PacketHeaderType>
//void Connection<PacketHeaderType>::readPayload()
//{
//	boost::asio::async_read(m_socket,
//		boost::asio::buffer(tempPacket.payload.data(), tempPacket.payload.size()),
//		[this](std::error_code ec, std::size_t length)
//		{
//			if (!ec)
//			{
//				// ...and they have! The message is now complete, so add
//						// the whole message to incoming queue
//				AddToIncomingMessageQueue();
//			}
//			else
//			{
//				// As above!
//				std::cout << "[" << id << "] Read Body Fail.\n";
//				m_socket.close();
//			}
//		}
//	);
//}
//
//template <typename PacketHeaderType>
//void Connection<PacketHeaderType>::ConnectToClient()
//{
//	if(isConnected())
//		readHeader();
//}
//
//template <typename PacketHeaderType>
//void Connection<PacketHeaderType>::ConnectToServer(
//	boost::asio::ip::tcp::resolver::results_type endpoints
//)
//{
//	boost::asio::async_connect(m_socket, endpoints,
//		[this](std::error_code ec, boost::asio::ip::tcp::endpoint endpoint)
//		{
//			if (!ec)
//			{
//				readHeader();
//			}
//		});
//}
//
//template <typename PacketHeaderType>
//void Connection<PacketHeaderType>::AddToIncomingMessageQueue()
//{
//
//	tcpRecvDeque->push_back(tempPacket);
//
//	readHeader();
//}
//
//template <typename PacketHeaderType>
//bool Connection<PacketHeaderType>::isConnected() const
//{
//	return m_socket.is_open();
//}
//
//template <typename PacketHeaderType>
//bool Connection<PacketHeaderType>::disconnect()
//{
//	m_socket.close();
//	return true;
//}
//
//template <typename PacketHeaderType>
//bool Connection<PacketHeaderType>::reset()
//{
//	return true;
//}
//
//
//template class Connection<PacketHeader>;
