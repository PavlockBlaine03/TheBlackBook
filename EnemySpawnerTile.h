#pragma once

#include "Tile.h"

class EnemySpawnerTile : public Tile
{
private:

	bool firstSpawn;
	int enemyType;
	int enemyAmount;
	int enemyCounter;
	sf::Int32 enemyTimeToSpawn;
	float enemyMaxDistance;

	// Spawn Timer
	sf::Clock enemySpawnTimer;

public:
	EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect, int enemy_type, 
		int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawnerTile();


	// Accessors
	virtual const std::string getAsString() const;
	const int& getEnemyCounter() const;
	const int& getEnemyAmount() const;
	const bool getSpawnTimer();
	const int& getEnemyType() const;
	const float& getEnemymaxDistance() const;

	// Modifiers

	// Functions
	void increaseEnemyCounter();
	void decreaseEnemyCounter();

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());
};

