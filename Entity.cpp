#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
	this->skillcomponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
	delete this->skillcomponent;
}

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::setScale(sf::Vector2f& scale)
{
	this->sprite.setScale(scale);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createAttributeComponent(const int level)
{
	this->attributeComponent = new AttributeComponent(level);
}

void Entity::createSkillComponent()
{
	this->skillcomponent = new SkillComponent();
}

void Entity::createAIComponent()
{

}

void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);	// sets velocity
	}

	if (this->skillcomponent)
	{
		this->skillcomponent->gainExp(SKILLS::ENDURANCE, 1);
		//std::cout << this->skillcomponent->getSkill(SKILLS::ENDURANCE) << std::endl;
	}
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

MovementComponent* Entity::getMovementComponent()
{
	if (this->movementComponent)
		return this->movementComponent;
	else
	{
		std::cerr << "ERROR::ENTITY::NO_MOVEMENT_COMPONENT" << std::endl;
		exit(EXIT_FAILURE);
	}
}

AttributeComponent* Entity::getAttributeComponent()
{
	if(this->attributeComponent)
		return this->attributeComponent;
	else
	{
		std::cerr << "ERROR::ENTITY::NO_ATTRIBUTE_COMPONENT" << std::endl;
		exit(EXIT_FAILURE);
	}
}

AnimationComponent* Entity::getAnimationComponent()
{
	if(this->animationComponent)
		return this->animationComponent;
	else
	{
		std::cerr << "ERROR::ENTITY::NO_ANIMATION_COMPONENT" << std::endl;
		exit(EXIT_FAILURE);
	}
}

SkillComponent* Entity::getSkillComponent()
{
	if(this->skillcomponent)
		return this->skillcomponent;
	else
	{
		std::cerr << "ERROR::ENTITY::NO_SKILL_COMPONENT" << std::endl;
		exit(EXIT_FAILURE);
	}
}

const bool Entity::getDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}
	return false;
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2f& Entity::getSpritePosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition() + sf::Vector2f(hitboxComponent->getGlobalBounds().width / 2.f, hitboxComponent->getGlobalBounds().height / 2.f);

	return this->sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
}

const sf::Vector2f Entity::getSpriteCenter() const
{
	return this->sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
}

const sf::Vector2i Entity::getGridPosition(const int grid_size_i) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / grid_size_i,
			static_cast<int>(this->hitboxComponent->getPosition().y) / grid_size_i);

	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / grid_size_i,
		static_cast<int>(this->sprite.getPosition().y) / grid_size_i);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
	{
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

const float Entity::getDistance(const Entity& entity) const
{
	return static_cast<float>(sqrt(pow(this->getCenter().x - entity.getCenter().x, 2) + pow(this->getCenter().y - entity.getCenter().y, 2)));
}

const float Entity::getSpriteDistance(const Entity& entity) const
{
	return static_cast<float>(sqrt(pow(this->getSpriteCenter().x - entity.getSpriteCenter().x, 2) + pow(this->getSpriteCenter().y - entity.getSpriteCenter().y, 2)));
}
