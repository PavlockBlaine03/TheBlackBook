#pragma once

#include "Tile.h"

class Tile;
class Entity;
class Enemy;
class EnemySpawnerTile : public Tile
{
private:

	bool spawned;
	int enemyType;
	int enemyAmount;
	sf::Int32 enemyTimeToSpawn;
	float enemyMaxDistance;

	// Spawn Timer
	sf::Clock enemySpawnTimer;

public:
	EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect, int enemy_type, 
		int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawnerTile();


	// Functions
	const bool canSpawn() const;
	const bool& getSpawned() const;
	void setSpawned(const bool spawned);
	virtual const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());
};

