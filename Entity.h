#pragma once
#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	// Component functions
	sf::Sprite getSprite() const { return sprite; }
	void setTexture(sf::Texture& texture);
	void setScale(sf::Vector2f& scale);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);

	// Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float dt);

	virtual void update(const float dt);
	virtual void render(sf::RenderTarget& target);
};

