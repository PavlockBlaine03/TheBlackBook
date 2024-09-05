#pragma once

#include "Tile.h"

class Tile;
class Entity;
class Enemy;
class EnemySpawner : public Tile
{
private:

	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	float enemyMaxDistance;

public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect,
		float grid_size, int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawner();


	// Functions
	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f player_position = sf::Vector2f());
};

