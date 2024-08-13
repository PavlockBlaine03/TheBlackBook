#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->scale = sf::Vector2f(2.f, 2.f);
	this->mainAttack = false;
	this->powerAttack = false;
	this->isSprinting = false;
}

void Player::initComponents()
{
	
}

Player::Player(sf::Texture& texture_sheet, float x, float y)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 10.f, 45.f, 86.5f, 125.f);
	this->createMovementComponent(350.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->setScale(scale);

	this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 3, 0, 67, 86);
	this->animationComponent->addAnimation("WALK", 8.f, 0, 1, 7, 1, 67, 86);
	this->animationComponent->addAnimation("MAIN_ATTACK", 12.f, 0, 2, 3, 2, 67 * 1.6f, 86);
	this->animationComponent->addAnimation("POWER_ATTACK", 16.f, 0, 3, 4, 3, 67 * 1.27f, 86);
	this->animationComponent->addAnimation("SPRINT", 8.f, 0, 4, 6, 4, 67 + 2, 86);
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
		if (this->isSprinting)
		{
			if (this->animationComponent->play("SPRINT", dt, true))
			{
				this->movementComponent->addAcceleration();
				this->movementComponent->setMaxVelocity(600.f);
				this->isSprinting = false;
			}
			if (this->sprite.getScale().x < 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
				this->sprite.setScale(2.f, 2.f);
			}
		}
		else
		{
			this->movementComponent->setMaxVelocity(350.f);
			this->movementComponent->setAcceleration();

			if (this->sprite.getScale().x < 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
				this->sprite.setScale(2.f, 2.f);
			}

			this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
		}
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->isSprinting)
		{
			if (this->animationComponent->play("SPRINT", dt, true))
			{
				this->movementComponent->addAcceleration();
				this->movementComponent->setMaxVelocity(600.f);
				this->isSprinting = false;
			}
			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(53.f, 0.f);
				this->sprite.setScale(-2.f, 2.f);
			}
		}
		else
		{
			this->movementComponent->setAcceleration();
			this->movementComponent->setMaxVelocity(350.f);

			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(53.f, 0.f);
				this->sprite.setScale(-2.f, 2.f);
			}

			this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
		}
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		if (this->isSprinting)
		{
			if (this->animationComponent->play("SPRINT", dt, true))
			{
				this->movementComponent->addAcceleration();
				this->movementComponent->setMaxVelocity(600.f);
				this->isSprinting = false;
			}
		}
		else
		{
			this->movementComponent->setAcceleration();
			this->movementComponent->setMaxVelocity(350.f);
			this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
		}
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		if (this->isSprinting)
		{
			if (this->animationComponent->play("SPRINT", dt, true))
			{
				this->movementComponent->addAcceleration();
				this->movementComponent->setMaxVelocity(600.f);
				this->isSprinting = false;
			}
		}
		else
		{
			this->movementComponent->setAcceleration();
			this->movementComponent->setMaxVelocity(350.f);
			this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
		}
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

void Player::updateSprint()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		this->isSprinting = true;
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->updateAttack();
	this->updateSprint();
	this->updateAnimation(dt);
	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	hitboxComponent->render(target);
}
