#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
	exp = 0;
	expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + 400 * this->level) / 3;
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

const bool AttributeComponent::isDead() const
{
	return this->hp <= 0;
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
	hpMax		= vitality * 5 + ((vitality + strength) / 2) + intelligence / 5 + (this->level * 2) + 4;
	dmgMax		= strength * 2 + strength / 2 + intelligence / 5;
	dmgMin		= strength * 2 + strength / 4 + intelligence / 5;
	accuracy	= dexterity * 4 + dexterity / 3 + intelligence / 5;
	defense		= agility * 2 + agility / 4 + intelligence / 5 + (this->level * 3);
	luck		= intelligence * 2 + intelligence / 5 + (this->level * 2);
	vitality	= vitality + ((vitality + strength) / 2);
	strength	= strength + 1;
	intelligence = this->level * this->level / 2;


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
		expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + 400 * this->level) / 3;
		++attributePoints;
		updateStats(true);
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
