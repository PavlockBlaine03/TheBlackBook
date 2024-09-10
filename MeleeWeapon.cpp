#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(unsigned level, unsigned damage_min, unsigned damage_max, unsigned range,
	unsigned value, std::string texture_file)
	: Weapon(level, damage_min, damage_max, range, value, texture_file)
{
	this->type = ItemTypes::IT_MELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon()
{

}

void MeleeWeapon::generate(const unsigned levelMax, const unsigned levelMin)
{
	this->level = rand() % (levelMax - levelMin + 1) + levelMin;
	this->damageMin = this->level * (rand() % 2 + 1);
	this->damageMax = this->level * (rand() % 2 + 1) + this->damageMin;

	this->range = this->level + rand() % 10 + 50;

	this->value = this->level + this->damageMin + this->damageMax + this->range + (rand() % level * 10);
}
