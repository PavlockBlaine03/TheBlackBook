#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->scale = sf::Vector2f(3.f, 3.f);
	this->mainAttack = false;
	this->powerAttack = false;
}

void Player::initComponents()
{
	
}

Player::Player(sf::Texture& texture_sheet, float x, float y)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 35.5f, 70.f, 86.5f, 185.f);
	this->createMovementComponent(350.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	this->setScale(scale);

	this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 3, 0, 67, 86);
	this->animationComponent->addAnimation("WALK", 8.f, 0, 1, 7, 1, 67, 86);
	this->animationComponent->addAnimation("MAIN_ATTACK", 12.f, 0, 2, 3, 2, 67 * 1.6f, 86);
	this->animationComponent->addAnimation("POWER_ATTACK", 16.f, 0, 3, 4, 3, 67 * 1.27f, 86);
}

Player::~Player()
{

}

void Player::updateAnimation(const float& dt)
{
	if (this->mainAttack)
	{
		if (this->animationComponent->play("MAIN_ATTACK", dt, true))
		{
			this->mainAttack = false;
		}
	}
	if (this->powerAttack)
	{
		if (this->animationComponent->play("POWER_ATTACK", dt, true))
		{
			this->powerAttack = false;
		}
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(3.f, 3.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(53.f, 0.f);
			this->sprite.setScale(-3.f, 3.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->mainAttack = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->powerAttack = true;
	}
}


void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->updateAttack();
	this->updateAnimation(dt);
	this->hitboxComponent->update();
}
