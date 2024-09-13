#pragma once

#include "Entity.h"
#include "Items.h"
#include "Inventory.h"
#include "TextureManager.h"

class Sword;
class Entity;
class Player final : public Entity
{
private:
	// variables
	Inventory* inventory;
	TextureManager* textureManager;

	bool initAttack;
	bool attacking;

	Weapon* weapon;

	// init functions
	void initVariables();
	void initAnimations();
	void initInventory();

public:
	Player(sf::Texture& texture_sheet, TextureManager* texture_manager, float x, float y);
	virtual ~Player();

	// Functions
	AttributeComponent* getAttributeComponent();
	Weapon* getWeapon() const;
	const std::string toStringCharacterTab() const;
	const bool& getInitAttack() const;
	const unsigned getDamage() const;
	Inventory* getInventory() const;

	void setInitAttack(const bool init_attack);

	void loseHP(const int hp);
	void loseEXP(const int exp);
	void gainHP(const int hp);
	void gainEXP(const int exp);

	void updateAnimation(const float& dt);
	virtual void update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

