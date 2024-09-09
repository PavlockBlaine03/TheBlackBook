#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
	this->range = 50;
	this->damageMin = 1;
	this->damageMax = 2;
}

void Weapon::initCoolDown()
{
	this->cooldown = 0.f;
	this->cooldownMax = 10.f;
	this->cooldownIteration = 1.f;
}

Weapon::Weapon(unsigned value, std::string texture_file)
	: Item(value)
{
	initVariables();
	initCoolDown();

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

const unsigned& Weapon::getDamageMin() const
{
	return this->damageMin;
}

const unsigned& Weapon::getDamageMax() const
{
	return this->damageMax;
}

const unsigned& Weapon::getRange() const
{
	return this->range;
}
