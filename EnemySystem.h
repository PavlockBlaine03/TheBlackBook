#pragma once

#include "EnemySpawnerTile.h"
#include "Rat.h"
#include "Bird.h"
#include "Scorpion.h"
#include "Blob.h"
#include "Orc.h"
#include "Spider.h"
#include "OrcMinion.h"

enum EnemyTypes {RAT = 0, BIRD, SCORPION, BLOB1, ORC1, ORC_MINION1, ORC_MINION2, SPIDER1};

class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;
	Entity& player;

public:
	EnemySystem(std::vector<Enemy*>& active_enemies, std::map<std::string, sf::Texture>& textures, Entity& player);
	virtual ~EnemySystem();

	// Accessors
	

	// Modifiers


	// Functions
	void createEnemy(const short type, const float x_pos, const float y_pos, EnemySpawnerTile& enemy_spawner_tile);
	void removeEnemy(const int index);
	void update(const float& dt);
	void render(sf::RenderTarget* target);

};

