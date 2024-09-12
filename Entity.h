#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	SkillComponent* skillcomponent;
	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;

public:
	Entity();
	virtual ~Entity();

	// Component functions
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);
	void createAttributeComponent(const int level);
	void createSkillComponent();
	void createAIComponent();

	// Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();


	sf::Sprite getSprite() const { return sprite; }
	void setTexture(sf::Texture& texture);
	void setScale(sf::Vector2f& scale);
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2i getGridPosition(const int grid_size_i) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	virtual const sf::Vector2f& getVelocity() const { return this->movementComponent->getVelocity(); }
	virtual const float getDistance(const Entity& entity) const;

	virtual void update(const float& dt, sf::Vector2f& mos_pos_view) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox = false) = 0;
};

