#pragma once

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
	sf::Sprite& sprite;
	sf::Vector2f velocity;

	float maxVelocity;
	float acceleration;
	float deceleration;

	// init functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	// getters
	const sf::Vector2f& getVelocity() const;
	const float& getMaxVelocity() const;

	// Functions
	const bool getState(const short unsigned state) const;

	void move(const float x, const float y, const float dt);
	void update(const float& dt);
};

