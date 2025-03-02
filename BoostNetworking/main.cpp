
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif


#include <boost/asio.hpp>
#include <iostream>
#include "header/packet_deque.hpp"
#include "header/util.hpp"
#include "header/serverTCPInterface.hpp"
#include "header/server.hpp"

int main()
{
	/*PacketDeque<int> queue;
	queue.push_front(1);
	queue.push_front(2);
	queue.push_front(3);

	std::cout << queue.pop_front() << "\n";
	std::cout << queue.pop_front() << "\n";
	std::cout << queue.pop_front() << "\n";*/

	Server server;
	server.Start();
	
	while (1)
	{
		server.Update();
	}

	return 0;
}

