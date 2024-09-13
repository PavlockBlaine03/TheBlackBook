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
		std::cout << "BIRD SPAWNED" << std::endl;
		break;
	case EnemyTypes::BIRD:
		this->activeEnemies.push_back(new Bird(enemy_spawner_tile, textures["BIRD1_SHEET"], x_pos, y_pos, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		std::cout << "RAT SPAWNED" << std::endl;
		break;
	case EnemyTypes::SCORPION:
		this->activeEnemies.push_back(new Scorpion(enemy_spawner_tile, textures["SCORPION1_SHEET"], x_pos, y_pos, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		std::cout << "SCORPION SPAWNED" << std::endl;
		break;
	case EnemyTypes::BLOB1:
		this->activeEnemies.push_back(new Blob(enemy_spawner_tile, textures["BLOB1_SHEET"], x_pos, y_pos, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		std::cout << "BLOB SPAWNED" << std::endl;
		break;
	default:
		std::cerr << "ERROR::ENEMY_SYSTEM::CREATE_ENEMY_FUNCTION::INVALID_TYPE" << std::endl;
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
