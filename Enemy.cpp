#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	this->gainExp = 10;
}

void Enemy::initAnimations()
{

}

Enemy::Enemy(EnemySpawnerTile& enemy_spawner_tile)
	:enemySpawnerTile(enemy_spawner_tile)
{
	this->initVariables();
	this->initAnimations();
}

Enemy::~Enemy()
{

}

const unsigned& Enemy::getGainExp() const
{
	return this->gainExp;
}

EnemySpawnerTile& Enemy::getEnemySpawnerTile()
{
	return this->enemySpawnerTile;
}

void Enemy::generateAttributes(const unsigned level)
{
	if (this->attributeComponent)
	{
		this->gainExp = level * (rand() % 5 + 1);
	}
}

void Enemy::loseHP(const int hp)
{
	if(this->attributeComponent)
		this->attributeComponent->loseHP(hp);
}

const bool Enemy::isDead() const
{
	if(this->attributeComponent)
		return this->attributeComponent->isDead();
	else
	{
		std::cerr << "ERROR::ENEMY::IS_DEAD::NO_ATTRIBUTE_COMPONENT" << std::endl;
		exit(EXIT_FAILURE);
	}
}

const AttributeComponent* Enemy::getAttributeComponent() const
{
	if (this->attributeComponent)
		return this->attributeComponent;
	else
	{
		std::cerr << "ERROR::ENEMY::GET_ATTRIBUTE_COMPONENT::NO_ATTRIBUTE_COMPONENT" << std::endl;
		exit(EXIT_FAILURE);
	}
}
