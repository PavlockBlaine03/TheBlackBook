#include "stdafx.h"
#include "AIRoam.h"

void AIRoam::switchDirection()
{
	// Randomly pick a new direction
	int randDir = std::rand() % 4;  // 0: Up, 1: Down, 2: Left, 3: Right
	switch (randDir) 
	{
	case 0: direction = sf::Vector2f(0.f, -1.f); break;  // Up
	case 1: direction = sf::Vector2f(0.f, 1.f); break;   // Down
	case 2: direction = sf::Vector2f(-1.f, 0.f); break;  // Left
	case 3: direction = sf::Vector2f(1.f, 0.f); break;   // Right
	}
}

AIRoam::AIRoam(Entity& self, Entity& entity)
	: AIOption(self, entity)

{
	speed = 1000.f;
	timer = 0.f;
	switchTime = 2.f;
	direction = sf::Vector2f(0.f, 0.f);
	std::srand(static_cast<unsigned>(std::time(0)));
}

AIRoam::~AIRoam()
{

}

void AIRoam::update(const float& dt)
{
	timer += dt;
	if (timer >= switchTime)
	{
		timer = 0.f;
		switchDirection();
	}

	sf::Vector2f movement = direction * speed * dt;
	self.move(movement.x, movement.y, dt);
}
