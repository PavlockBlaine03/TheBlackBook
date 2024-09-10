#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(unsigned damage_min, unsigned damage_max, unsigned range, 
	unsigned value, std::string texture_file)
	: Weapon(damage_min, damage_max, range, value, texture_file)
{
	this->type = ItemTypes::IT_MELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon()
{

}
