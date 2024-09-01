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

	this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 54.f);
	this->createMovementComponent(200.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 6.f, 0, 2, 3, 2, 64, 64);

	// Visual Weapon
	if (!weaponTexture.loadFromFile("C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Player/sword.png"))
	{
		std::cerr << "ERROR::PLAYER.CPP::COULD_NOT_LOAD_WEAPON_TEXTURE";
		exit(EXIT_FAILURE);
	}
	weaponSprite.setTexture(weaponTexture);

	weaponSprite.setOrigin
	(
		weaponSprite.getGlobalBounds().width / 2.f, 
		weaponSprite.getGlobalBounds().height
	);

}

Player::~Player()
{

}

void Player::updateAnimation(const float& dt)
{
	if (this->mainAttack)
	{
		
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
	attributeComponent->loseHP(hp);
}

void Player::loseEXP(const int exp)
{
	attributeComponent->loseEXP(exp);
}

void Player::gainHP(const int hp)
{
	attributeComponent->gainHP(hp);
}

void Player::gainEXP(const int exp)
{
	attributeComponent->gainExp(exp);
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->mainAttack = true;
	}
}

void Player::update(const float& dt, sf::Vector2f& mos_pos_view)
{
	this->movementComponent->update(dt);
	this->updateAttack();
	this->updateAnimation(dt);
	this->hitboxComponent->update();

	// update visual weapon
	weaponSprite.setPosition(getCenter());

	float dx = mos_pos_view.x - weaponSprite.getPosition().x;
	float dy = mos_pos_view.y - weaponSprite.getPosition().y;

	const float PI = 3.14159265;
	float deg = atan2(dy, dx) * 180 / PI;

	weaponSprite.setRotation(deg + 90.f);
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", getCenter());

		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", getCenter());
		target.draw(weaponSprite, shader);
	}
	else
	{
		target.draw(this->sprite);
		target.draw(weaponSprite);
	}

	if(show_hitbox)
		hitboxComponent->render(target);
}
