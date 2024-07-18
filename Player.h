#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	// variables
	sf::Vector2f scale;
	bool mainAttack;
	bool powerAttack;

	// init functions
	void initVariables();
	void initComponents();

public:
	Player(sf::Texture& texture_sheet, float x, float y);
	virtual ~Player();

	// Functions
	void updateAttack();
	void updateAnimation(const float& dt);
	virtual void update(const float& dt);
};

