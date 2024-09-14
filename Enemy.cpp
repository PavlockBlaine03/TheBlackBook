#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	if (!this->font.loadFromFile("C:/VisualCodeProjects/TheBlackBook/fonts/KOMIKAX_.ttf"))
	{
		std::cerr << "ERROR::ENEMY_HEADER_FONT::COULD_NOT_LOAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->gainExp = 10;
	this->damageTimerMax = 500.f;
	this->despawnTimerMax = 1000.f;
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

const bool Enemy::getDespawnTimerDone() const
{
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}

void Enemy::generateAttributes(const unsigned level, const int type)
{
	/*
	* Types:
	* 0 = RAT
	* 1 = BIRD
	* 2 = SCORPION
	* 3 = BLOB
	* 4 = ORC
	* 5 = ORC_MINION1
	* 6 = ORC_MINION2
	* 7 = SPIDER
	*/

	switch (type)
	{
	case 0:	// RAT
		if (this->attributeComponent)
		{
			this->gainExp = level * (rand() % 5 + level + 1);
		}
		break;
	case 1:	// BIRD
		if (this->attributeComponent)
		{
			this->attributeComponent->hpMax += (level * rand() % 4 + 2) + (level + gainExp / 3);
			this->attributeComponent->hp = this->attributeComponent->hpMax;

			this->attributeComponent->dmgMax += (rand() % 3 + 2) + this->attributeComponent->strength;
			this->attributeComponent->dmgMin = this->attributeComponent->dmgMax - (this->attributeComponent->dmgMax / 4);

			this->gainExp = level * (rand() % 6 + 3) + level;
		}
		break;
	case 2:	// SCORPION
		if (this->attributeComponent)
		{
			this->attributeComponent->hpMax += (level * rand() % 3 + 1) + (level + gainExp / 5);
			this->attributeComponent->hp = this->attributeComponent->hpMax;

			this->attributeComponent->dmgMax += (rand() % 3 + 2);
			this->attributeComponent->dmgMin = this->attributeComponent->dmgMax - (this->attributeComponent->dmgMax / 4);

			this->gainExp = level * (rand() % 5 + level + 2);
		}
		break;
	case 3:	// BLOB
		if (this->attributeComponent)
		{
			this->attributeComponent->hpMax += (level + rand() % 3 + 1) + (level * 2);
			this->attributeComponent->hp = this->attributeComponent->hpMax;

			this->gainExp = level * (rand() % 4 + level + 2);
		}
		break;
	case 4:	// ORC
		if (this->attributeComponent)
		{
			this->attributeComponent->hpMax += (level * rand() % 10 + 5) * (std::pow(level, 2) / 2);
			this->attributeComponent->hp = this->attributeComponent->hpMax;

			this->attributeComponent->dmgMax += level;
			this->attributeComponent->dmgMin += level - 4;

			this->gainExp = pow(level + 1, 2) * (rand() % level + (level * 2)) + 6;
		}
		break;
	case 5: // ORC_MINION1
		if (this->attributeComponent)
		{
			this->attributeComponent->hpMax += (level * rand() % 4 + 2) + (level + gainExp / 3);
			this->attributeComponent->hp = this->attributeComponent->hpMax;

			this->attributeComponent->dmgMax += (rand() % 3 + 2) + this->attributeComponent->strength;
			this->attributeComponent->dmgMin = this->attributeComponent->dmgMax - (this->attributeComponent->dmgMax / 4);

			this->gainExp = level * (rand() % 6 + 3) + level;
		}
		break;
	case 6: // ORC_MINION 2
		if (this->attributeComponent)
		{
			this->attributeComponent->hpMax += (level * rand() % 4 + 2) + (level + gainExp / 3);
			this->attributeComponent->hp = this->attributeComponent->hpMax;

			this->attributeComponent->dmgMax += (rand() % 3 + 2) + this->attributeComponent->strength;
			this->attributeComponent->dmgMin = this->attributeComponent->dmgMax - (this->attributeComponent->dmgMax / 4);

			this->gainExp = level * (rand() % 6 + 3) + level;
		}
		break;
	case 7: // SPIDER
		if (this->attributeComponent)
		{
			this->gainExp = level * (rand() % 5 + 2) + level;
		}
		break;
	default:
		std::cerr << "ERROR::GENERATE_ATTRIBUTES::ENEMY::WRONG_TYPE" << std::endl;
		exit(EXIT_FAILURE);
		break;
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

void Enemy::update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view)
{
	if (vec::vectorDistance(this->getPosition(), view.getCenter()) < 1250.f)
		this->despawnTimer.restart();
}