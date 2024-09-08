#pragma once

#include "EnemySpawnerTile.h"
#include "Rat.h"

enum EnemyTypes {RAT = 0};

class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;

public:
	EnemySystem(std::vector<Enemy*>& active_enemies, std::map<std::string, sf::Texture>& textures);
	virtual ~EnemySystem();

	// Accessors
	

	// Modifiers


	// Functions
	void createEnemy(const short type, const float x_pos, const float y_pos);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

};

