#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
	exp = 0;
	expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	attributePoints = 2;

	vitality = 1;
	strength = 1;
	dexterity = 1;
	agility = 1;
	intelligence = 1;

	updateLevel();

	updateStats(true);
}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void AttributeComponent::loseEXP(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
	{
		this->exp = 0;
	}
}

void AttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::gainExp(const int exp)
{
	this->exp += exp;
	updateLevel();
}

void AttributeComponent::updateStats(const bool reset)
{
	hpMax		= vitality * 5 + vitality + strength / 2 + intelligence / 5;
	dmgMax		= strength * 2 + strength / 2 + intelligence / 5;
	dmgMin		= strength * 2 + strength / 4 + intelligence / 5;
	accuracy	= dexterity * 4 + dexterity / 3 + intelligence / 5;
	defense		= agility * 2 + agility / 4 + intelligence / 5;
	luck		= intelligence * 2 + intelligence / 5;


	if (reset)
	{
		hp = hpMax;
	}
}

void AttributeComponent::updateLevel()
{
	while (this->exp >= this->expNext) 
	{
		++level;
		exp -= expNext;
		expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
		++attributePoints;
	}
}

void AttributeComponent::update()
{
	updateLevel();
}

std::string AttributeComponent::debugPrint()
{
	std::stringstream ss;

	ss << "Level: " << level << "\n"
		<< "Exp: " << exp << "\n"
		<< "Exp Next: " << expNext << "\n"
		<< "Attribute Points: " << attributePoints << "\n";

	return ss.str();
}
