#pragma once

#include "Entity.h"
#include "Items.h"
#include "Inventory.h"

class Sword;
class Entity;
class Player : public Entity
{
private:
	// variables
	Inventory* inventory;

	bool mainAttack;

	Sword* sword;

	// init functions
	void initVariables();
	void initAnimations();
	void initInventory();

public:
	Player(sf::Texture& texture_sheet, float x, float y);
	virtual ~Player();

	// Functions
	AttributeComponent* getAttributeComponent();

	void loseHP(const int hp);
	void loseEXP(const int exp);
	void gainHP(const int hp);
	void gainEXP(const int exp);

	void updateAttack();
	void updateAnimation(const float& dt);
	virtual void update(const float& dt, sf::Vector2f& mos_pos_view);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

