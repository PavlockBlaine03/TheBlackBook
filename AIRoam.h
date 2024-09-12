#pragma once

#include "AIOption.h"

class AIRoam : public AIOption
{
private:
	sf::Vector2f direction;
	float timer;
	float switchTime;
	float speed;
	void switchDirection();

public:
	AIRoam(Entity& self, Entity& entity);
	virtual ~AIRoam();

	void update(const float& dt);
};

