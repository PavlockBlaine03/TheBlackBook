#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->initAttack = false;
	this->attacking = false;
	//this->weapon = new Bow(WeaponType::WEAPON_BOW, 1, 3, 7, 2000 , 20, this->textureManager->getTextures().at("BOW"));
	this->weapon = new Sword(WeaponType::WEAPON_SWORD, 1, 3, 7, 65 , 20, this->textureManager->getTextures().at("SWORD"));
	this->weapon->generate(3, 1);
	this->damageTimerMax = 1000.f;
}

void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

void Player::initInventory()
{
	this->inventory = new Inventory(100);
	this->inventory->add(this->weapon);
}

Player::Player(sf::Texture& texture_sheet, TextureManager* texture_manager, float x, float y)
	: Entity()
{
	this->textureManager = texture_manager;
	this->initVariables();

	this->createHitboxComponent(this->sprite, 16.f, 26.f, 32.f, 38.f);
	this->createMovementComponent(150.f, 1300.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();
	
	this->setPosition(x, y);
	this->initAnimations();
	this->initInventory();

}

Player::~Player()
{
	delete this->weapon;
	delete this->inventory;
}

void Player::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}

	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play(
			"WALK_RIGHT",
			dt,
			this->movementComponent->getVelocity().y,
			this->movementComponent->getMaxVelocity()
		);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play(
			"WALK_LEFT",
			dt,
			this->movementComponent->getVelocity().y,
			this->movementComponent->getMaxVelocity()
		);
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play(
			"WALK_UP",
			dt,
			this->movementComponent->getVelocity().y,
			this->movementComponent->getMaxVelocity()
		);
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play(
			"WALK_DOWN",
			dt, 
			this->movementComponent->getVelocity().y, 
			this->movementComponent->getMaxVelocity()
		);
	}

}

AttributeComponent* Player::getAttributeComponent()
{
	return attributeComponent;
}

Weapon* Player::getWeapon() const
{
	return this->weapon;
}

const std::string Player::toStringCharacterTab() const
{
	std::stringstream ss;
	AttributeComponent* ac = this->attributeComponent;
	Weapon* w = this->weapon;
	ss << "Level: " << ac->level << "\n"
		<< "Exp: " << ac->exp << "\n"
		<< "Exp next: " << ac->expNext - ac->exp << "\n"
		<< "Attribute Points: " << ac->attributePoints << "\n"
		<< "Accuracy: " << ac->accuracy << "\n"
		<< "Agility: " << ac->agility << "\n"
		<< "Dexterity: " << ac->dexterity << "\n"
		<< "Defense: " << ac->defense << "\n"
		<< "Strength: " << ac->strength << "\n"
		<< "Intelligence: " << ac->intelligence << "\n"
		<< "Vitality: " << ac->vitality << "\n"
		<< "Luck: " << ac->luck << "\n"
		<< "Max HP: " << ac->hpMax << "\n\n\n"

		<< "Weapon Level: " << w->getLevel() << "\n"
		<< "Weapon Value: " << w->getValue() << "\n"
		<< "Weapon Damage Min: " << w->getDamageMin() + ac->dmgMin << "(" << ac->dmgMin << ")" << "\n"
		<< "Weapon Damage Max: " << w->getDamageMax() + ac->dmgMax << "(" << ac->dmgMax << ")" << "\n"
		<< "Weapon Range: " << w->getRange() << "\n"
		<< "Weapon Type: " << w->getType() << "\n";

	return ss.str();
}

const bool& Player::getInitAttack() const
{
	return this->initAttack;
}

const unsigned Player::getDamage() const
{
	return rand() % (
		(this->attributeComponent->dmgMax + this->weapon->getDamageMax()) - 
		(this->attributeComponent->dmgMin + this->weapon->getDamageMin() + 1)) + 
		(this->attributeComponent->dmgMin + this->weapon->getDamageMin());
}

Inventory* Player::getInventory() const
{
	return this->inventory;
}

void Player::setInitAttack(const bool init_attack)
{
	this->initAttack = init_attack;
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

void Player::update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view)
{
	this->movementComponent->update(dt);
	this->updateAnimation(dt);
	this->hitboxComponent->update();
	this->weapon->update(mos_pos_view, sf::Vector2f(getSpriteCenter().x, getSpriteCenter().y + 10.f));
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader,
	const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);

		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		this->weapon->render(target, shader);
	}
	else
	{
		target.draw(this->sprite);
		this->weapon->render(target);
	}

	if(show_hitbox)
		hitboxComponent->render(target);
}
