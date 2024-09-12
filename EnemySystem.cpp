#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& active_enemies,
	std::map<std::string, sf::Texture>& textures, Entity& player)
	: textures(textures), activeEnemies(active_enemies), player(player)
{
	
}

EnemySystem::~EnemySystem()
{

}

void EnemySystem::createEnemy(const short type, const float x_pos, const float y_pos, EnemySpawnerTile& enemy_spawner_tile)
{
	switch (type)
	{
	case EnemyTypes::RAT:
		this->activeEnemies.push_back(new Rat(enemy_spawner_tile, textures["RAT1_SHEET"], x_pos, y_pos, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTypes::BIRD:
		this->activeEnemies.push_back(new Bird(enemy_spawner_tile, textures["BIRD1_SHEET"], x_pos, y_pos));
		enemy_spawner_tile.increaseEnemyCounter();
	default:
		std::cerr << "ERROR::ENEMY_SYSTEM::CREATE_ENEMY_FUNCTION::INVALID_TYPE";
		exit(EXIT_FAILURE);
		break;
	}
}

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(
		this->activeEnemies.begin() + index
	);
}

void EnemySystem::update(const float& dt)
{

}

void EnemySystem::render(sf::RenderTarget* target)
{

}
