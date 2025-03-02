#pragma once

#ifndef GAME_H
#define GAME_H

#include <raylib.h> 
#include <vector> 
#include <thread>
#include <atomic>
#include <mutex>
#include <memory>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
//#include "structure.hpp"

//#include "level.hpp"
#include "map1vs1.hpp"
#include "player.hpp"
//#include "bomb.hpp"

#include "button.hpp"
#include "level.hpp"

class Game
{
private:

public:
	int prevScreenWidth;
	int prevScreenHeight;

	std::shared_ptr<Map> map;

	Texture2D textureTitle;

	int page;

	Button startButton;
	Button oneVsOneButton;
	Button onlineButton;

	Button returnButton;

	std::vector<LevelButton> lvlBtnArr;

	float bgOffsetX;   // Horizontal offset for movement
	float speed;     // Speed in pixels per second
	Texture2D background;


//public:
	Game();
	~Game();

	void LoadMap(int index);
	void Draw();
	void MoveBg();
	void DrawBg() const;

	void HandleChanges();

	void HandleInput();

	void DrawStartingPage();
	void HandleStartingInput();

	void LoadLevelChoosingPage();
	void DrawLevelChoosingPage();
	void HandleLevelChoosingInput();

};
#endif // GAME_H
