#pragma once


class AttributeComponent
{
private:


public:

	// Leveling
	int level;
	int exp;
	int expNext;
	int attributePoints;

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
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	// Functions
	const bool isDead() const;

	void loseHP(const int hp);
	void loseEXP(const int exp);
	void gainHP(const int hp);
	void gainExp(const int exp);
	void updateStats(const bool reset);
	void updateLevel();
	void update();

	std::string debugPrint();

};

