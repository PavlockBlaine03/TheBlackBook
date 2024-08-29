#pragma once
#include "Entity.h"

class Entity;
class Player : public Entity
{
private:
	// variables
	sf::Vector2f scale;
	bool mainAttack;

	// init functions
	void initVariables();
	void initComponents();

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
	virtual void update(const float& dt);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
};

