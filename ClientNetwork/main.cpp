#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include <boost/asio.hpp>
#include <iostream>

//#include "../BoostNetworking/header/packet_deque.hpp"
//#include "../BoostNetworking/header/util.hpp"

#include "header/graphics.hpp"
#include "header/client.hpp"

constexpr uint16_t PORT = 12345;

struct KeyInput {
	uint32_t timestamp;
	// Bitmask of pressed keys (e.g., WASD = 00001111)
	uint16_t keyPressedState; 
	uint16_t keyReleasedState; 
};

int main()
{
	Graphics::Initialize();

	Client client;
	client.Start("127.0.0.1", PORT);

	std::vector<KeyInput> keyinputs{};
	while (Graphics::CheckWindowOpen()) {

		uint16_t bitmask{};
		// 1. Update variables
		if (Graphics::CheckKeyInput('a', InputType::pressed)) {
			bitmask |= 1 << 2;
			std::cout << "Key A pressed!!!\n";
		}
		if (Graphics::CheckKeyInput('a', InputType::released)) {
			std::cout << "Key A released!!!\n";
		}
		if (Graphics::CheckKeyInput('d', InputType::pressed)) {
			bitmask |= 1;
			std::cout << "Key D pressed!!!\n";
		}
		if (Graphics::CheckKeyInput('d', InputType::released)) {
			std::cout << "Key D released!!!\n";
		}

		Graphics::HandleChanges();

		Graphics::HandleInput();
		
		// 2. Game State change
		//std::

		// 3. Send Game State change packet to server
		
		if (Graphics::UpdatedGameState()) {

		}

		// 4. Draw
		Graphics::Begin();
			
			Graphics::Draw();
			
		Graphics::End();


	}
	std::cout << "Client \n";


	Graphics::Deinitialize();

	return 0;
}