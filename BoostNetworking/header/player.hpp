
#pragma once 
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>
#include <memory>
#include <iostream>
#include <cmath>

#include "human.hpp"
#include "map.hpp"

//class Map;
//class Human;

class Player : public Human
{
private:
	int rotateSpeed = 10;

public:
	Player(std::shared_ptr<Map> map, int id, size_t row, size_t column);
	~Player() = default;

	int lifeCount;

	void HandleInput();
	void HandleInput2();
	void Draw();
	void Draw3d();

	virtual void Dies();

	// Texture2D grass;

	int animCount = 0;
	int animFrame = 0;
	int rotationAngle = 180;

	std::shared_ptr<Model> model;
	ModelAnimation* animation;
};

#endif // PLAYER_HPP