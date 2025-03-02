#include <raylib.h>

#include "../header/graphics.hpp"
#include "../../BoostNetworking/header/game.hpp"
//#include "../../BoostNetworking/header/asset.hpp"

constexpr double GAME_STATE_RATE = 30.0;

namespace Graphics{

	double lastUpdateTime = 0.0;
	constexpr double updateRate = 1.0 / GAME_STATE_RATE;

	Game game;


	void Initialize() 
	{
		constexpr int screenWidth = 1000;
		constexpr int screenHeight = 600;

		SetConfigFlags(
			FLAG_WINDOW_RESIZABLE |
			FLAG_VSYNC_HINT |
			FLAG_MSAA_4X_HINT
		);
		InitWindow(screenWidth, screenHeight, "Bomberman!!!");

		SetRandomSeed(GetTime() * 1000000);

		//loadAssets();

		//game = std::make_shared<Game>();
		
	}

	bool CheckWindowOpen() 
	{
		return !WindowShouldClose();
	}

	void HandleChanges()
	{
		//game->HandleChanges();
	}

	void HandleInput()
	{
		//game->HandleInput();
	}

	void Draw()
	{
		//game->Draw();
	}


	bool CheckKeyInput(char key, InputType type) 
	{
		bool (*InputFunc) (int) {}; // Pointer to a function taking 1 int argument
		if (type == InputType::pressed)			InputFunc = IsKeyPressed;
		else if (type == InputType::released)	InputFunc = IsKeyReleased;
		else									return false;

		if (key == 'w') return InputFunc(KEY_W);
		if (key == 'a') return InputFunc(KEY_A);
		if (key == 's') return InputFunc(KEY_S);
		if (key == 'd') return InputFunc(KEY_D);
		return false;
	}

	bool UpdatedGameState()
	{
		double currentTime = GetTime();

		if (currentTime - lastUpdateTime >= updateRate) {
			lastUpdateTime = currentTime;

			return true;
		}
		return false;

	}



	void Begin() 
	{
		BeginDrawing();
			ClearBackground(Color{ 20, 160, 133, 255 });

	}

	void End() 
	{
			DrawFPS(10, 110);

		EndDrawing();
	}

	void Deinitialize() 
	{

		//unloadAssets();

		CloseWindow();
	}
}


