#include "stdafx.h"
#include "AIFollow.h"

AIFollow::AIFollow(Entity& self, Entity& entity)
	: AIOption(self, entity)
{

}

AIFollow::~AIFollow()
{
	
}

void AIFollow::update(const float& dt)
{
	sf::Vector2f moveVec;
	moveVec.x = this->entity.getPosition().x - this->self.getPosition().x;
	moveVec.y = this->entity.getPosition().y - this->self.getPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if (this->self.getPosition().x != this->entity.getPosition().x && std::abs(vecLength) < 500.f)
	{
		this->self.move(moveVec.x, moveVec.y, dt);
	}
}
