
#pragma once
#include <raylib.h>
#include <memory>

//#include "human.hpp"
#include "human.hpp"
#include "map.hpp"
//class Map;
//class Human;

class Enemy : public Human
{
private:
	int rotateSpeed = 10;


public:
	Enemy(std::shared_ptr<Map> map, int id, size_t row, size_t column);
	~Enemy() = default;

	void Draw();
	void Draw3d();

	void Move();
	void ChangeDirection();
	virtual void Dies();

	int animCount = 0;
	int animFrame = 0;
	float rotationAngle = 90.0f;

	//Model model;
	std::shared_ptr<Model> model1;
	ModelAnimation* animation;

};
