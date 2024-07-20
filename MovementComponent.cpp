#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{

}

// getters
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

// Functions
void MovementComponent::update(const float& dt)
{
	if (this->velocity.x > 0.f)
	{
		// Max Velocity check x positive
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		// Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;

	}
	else if(this->velocity.x < 0.f)
	{
		// Max velocity check x negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		// Deceleration x negative
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	if (this->velocity.y > 0.f)
	{
		// Max Velocity check y positive
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		// Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;

	}
	else if (this->velocity.y < 0.f)
	{
		// Max velocity check y negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		// Deceleration y negative
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}


	// Final move
	this->sprite.move(this->velocity * dt);
}



const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:

		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;

		break;
	case MOVING:

		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;

		break;
	case MOVING_LEFT:

		if (this->velocity.x < 0.f)
			return true;

		break;
	case MOVING_RIGHT:

		if (this->velocity.x > 0.f)
			return true;

		break;
	case MOVING_UP:

		if (this->velocity.y < 0.f)
			return true;

		break;
	case MOVING_DOWN:

		if (this->velocity.y > 0.f)
			return true;

		break;
	case SPRINT_LEFT:
		if (this->velocity.x < 0.f)
			return true;

		break;
	case SPRINT_RIGHT:

		if (this->velocity.x > 0.f)
			return true;

		break;
	case SPRINT_UP:

		if (this->velocity.y < 0.f)
			return true;

		break;
	case SPRINT_DOWN:

		if (this->velocity.y > 0.f)
			return true;

		break;
	}
	return false;
}

void MovementComponent::setVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

void MovementComponent::setMaxVelocity(const float& max_velocity)
{
	this->maxVelocity = max_velocity;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float dt)
{
	// Acceleration
	this->velocity.x += this->acceleration * dir_x;	
	this->velocity.y += this->acceleration * dir_y;
}
