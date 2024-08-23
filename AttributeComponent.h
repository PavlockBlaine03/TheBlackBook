#pragma once


class AttributeComponent
{
private:


public:

	// Leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;

	// Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	// Stats
	/* Vitality */
	int hp;
	int hpMax;

	/* Strength */
	int dmgMin;
	int dmgMax;

	/* Dexterity */
	int accuracy;
	int defense;

	/* Intelligence */
	int luck;


	// Contructors/Destructors
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	// Functions
	void gainExp(const unsigned exp);
	void updateStats(const bool reset);
	void updateLevel();
	void update();

	std::string debugPrint();

};

