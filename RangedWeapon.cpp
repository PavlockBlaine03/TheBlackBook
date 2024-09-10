#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned level, unsigned damage_min, unsigned damage_max, unsigned range,
	unsigned value, std::string texture_file)
	: Weapon(level, damage_min, damage_max, range, value, texture_file)
{
	this->type = ItemTypes::IT_RANGEDWEAPON;
}

RangedWeapon::~RangedWeapon()
{

}

void RangedWeapon::generate(const unsigned levelMax, const unsigned levelMin)
{

}
