#include "stdafx.h"
#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect, int enemy_type,
	int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance)
	: Tile(TileTypes::ENEMYSPAWNER, grid_x, grid_y, gridSizeF, tile_texture_sheet, tex_rect, false)
{
	this->enemySpawnTimer.restart();
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->firstSpawn = true;
}

EnemySpawnerTile::~EnemySpawnerTile()
{

}

void EnemySpawnerTile::increaseEnemyCounter()
{
	if (this->enemyCounter < this->enemyAmount)
		++this->enemyCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter()
{
	if (this->enemyCounter > 0)
		--this->enemyCounter;
}

const std::string EnemySpawnerTile::getAsString() const
{
	std::stringstream ss;

	/*
	* x, y, z (done in tilemap save function)
	* Type
	* rect X, rect Y
	* enemy type
	* enemy amount
	* enemy time to spawn
	* enemy max distance
	*/

	ss << this->type <<
		" " << this->shape.getTextureRect().left <<
		" " << this->shape.getTextureRect().top <<
		" " << this->enemyType << 
		" " << this->enemyAmount << 
		" " << this->enemyTimeToSpawn <<
		" " << this->enemyMaxDistance;

	return ss.str();
}

const int& EnemySpawnerTile::getEnemyCounter() const
{
	return this->enemyCounter;
}

const int& EnemySpawnerTile::getEnemyAmount() const
{
	return this->enemyAmount;
}

const bool EnemySpawnerTile::getSpawnTimer()
{
	if (this->enemySpawnTimer.getElapsedTime().asSeconds() >= this->enemyTimeToSpawn || this->firstSpawn)
	{
		this->enemySpawnTimer.restart();
		this->firstSpawn = false;
		return true;
	}

	return false;
}

const int& EnemySpawnerTile::getEnemyType() const
{
	return this->enemyType;
}

const float& EnemySpawnerTile::getEnemymaxDistance() const
{
	return this->enemyMaxDistance;
}

// Functions
void EnemySpawnerTile::update()
{
	
}

void EnemySpawnerTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}
