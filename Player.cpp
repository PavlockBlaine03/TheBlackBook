#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->mainAttack = false;
}

void Player::initComponents()
{
	
}

Player::Player(sf::Texture& texture_sheet, float x, float y)
{
	this->initVariables();
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 10.f, 5.f, 44.f, 54.f);
	this->createMovementComponent(200.f, 1500.f, 900.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 8.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 8.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 8.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 8.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 6.f, 0, 2, 3, 2, 64, 64);
}

Player::~Player()
{

}

void Player::updateAnimation(const float& dt)
{
	if (this->mainAttack)
	{
		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->mainAttack = false;
		}
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}

	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
	
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}

}

AttributeComponent* Player::getAttributeComponent()
{
	return attributeComponent;
}

void Player::loseHP(const int hp)
{
	attributeComponent->hp -= hp;

	if (attributeComponent->hp < 0)
	{
		attributeComponent->hp = 0;
	}
}

void Player::loseEXP(const int exp)
{
	attributeComponent->exp -= exp;

	if (attributeComponent->exp < 0)
	{
		attributeComponent->exp = 0;
	}
}

void Player::gainHP(const int hp)
{
	attributeComponent->hp += hp;

	if (attributeComponent->hp > attributeComponent->hpMax)
	{
		attributeComponent->hp = attributeComponent->hpMax;
	}
}

void Player::gainEXP(const int exp)
{
	attributeComponent->gainExp(exp);
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//this->mainAttack = true;
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->updateAttack();
	//this->updateSprint();
	this->updateAnimation(dt);
	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", getCenter());

		target.draw(this->sprite, shader);
	}
	else
		target.draw(this->sprite);

	if(show_hitbox)
		hitboxComponent->render(target);
}
