#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
	this->range = 55;
	this->damageMin = 1;
	this->damageMax = 2;

	// Timer
	this->attackTimer.restart();
	this->attackTimerMax = 250;
}


Weapon::Weapon(unsigned level, unsigned value, std::string texture_file)
	: Item(level, value)
{
	initVariables();

	if (!weaponTexture.loadFromFile(texture_file))
	{
		std::cerr << "ERROR::PLAYER.CPP::COULD_NOT_LOAD_WEAPON_TEXTURE::" << texture_file << std::endl;
		exit(EXIT_FAILURE);
	}
	weaponSprite.setTexture(weaponTexture);
}

Weapon::Weapon(const short type, unsigned level, unsigned damage_min, unsigned damage_max, unsigned range, unsigned value, std::string texture_file)
	: Item(level, value)
{
	initVariables();
	this->weaponType = type;
	this->damageMin = damage_min;
	this->damageMax = damage_max;
	this->range = range;

	if (!weaponTexture.loadFromFile(texture_file))
	{
		std::cerr << "ERROR::PLAYER.CPP::COULD_NOT_LOAD_WEAPON_TEXTURE::" << texture_file << std::endl;
		exit(EXIT_FAILURE);
	}
	weaponSprite.setTexture(weaponTexture);
}

Weapon::~Weapon()
{

}

const short Weapon::getWeaponType() const
{
	return this->weaponType;
}

const unsigned& Weapon::getDamageMin() const
{
	return this->damageMin;
}

const unsigned& Weapon::getDamageMax() const
{
	return this->damageMax;
}

const unsigned Weapon::getDamage() const
{
	return rand() % (this->damageMax - this->damageMin + 1) + (this->damageMin);
}

const unsigned& Weapon::getRange() const
{
	return this->range;
}

const bool Weapon::getAttackTimer()
{
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}
	return false;
}

const sf::Sprite& Weapon::getSprite() const
{
	return this->weaponSprite;
}
