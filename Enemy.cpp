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
    case 0: // RAT (Non-aggressive, low stats)
        if (this->attributeComponent)
        {
            this->attributeComponent->hp = 12;
            this->gainExp = level * (rand() % 4 + level + 2);  // Low EXP
        }
        break;
    case 1: // BIRD (Tier 1 Enemy, easy to kill)
        if (this->attributeComponent)
        {
            this->attributeComponent->hpMax += (level * rand() % 4 + 3);  // Light HP scaling
            this->attributeComponent->hp = this->attributeComponent->hpMax;

            this->attributeComponent->dmgMax += (rand() % 3 + 2) + this->attributeComponent->strength;  // Lower damage
            this->attributeComponent->dmgMin = this->attributeComponent->dmgMax - (this->attributeComponent->dmgMax / 4);

            this->gainExp = (rand() % 11 + 20) + level;  // EXP range 20-30
        }
        break;
    case 2: // SCORPION (Tier 1 Enemy, moderate difficulty)
        if (this->attributeComponent)
        {
            this->attributeComponent->hpMax += (level * rand() % 3 + 5);  // Moderate HP scaling
            this->attributeComponent->hp = this->attributeComponent->hpMax;

            this->attributeComponent->dmgMax += (rand() % 4 + 3);  // Moderate damage
            this->attributeComponent->dmgMin = this->attributeComponent->dmgMax - (this->attributeComponent->dmgMax / 4);

            this->gainExp = (rand() % 11 + 25) + level;  // EXP range 25-35
        }
        break;
    case 3: // BLOB (Tier 1 Enemy, easy to kill)
        if (this->attributeComponent)
        {
            this->attributeComponent->hpMax += (level * rand() % 2 + 4);  // Lower HP scaling
            this->attributeComponent->hp = this->attributeComponent->hpMax;

            this->gainExp = (rand() % 11 + 20) + level;  // EXP range 20-30
        }
        break;
    case 4: // ORC (First area boss, difficult)
        if (this->attributeComponent)
        {
            this->attributeComponent->hpMax += (level * rand() % 20 + 100);  // High HP scaling, large base HP
            this->attributeComponent->hp = this->attributeComponent->hpMax;

            this->attributeComponent->dmgMax += level + (rand() % 5 + 20);  // Higher damage scaling
            this->attributeComponent->dmgMin += level;

            std::cout << this->attributeComponent->dmgMax << std::endl;
            std::cout << this->attributeComponent->hp << std::endl;

            this->gainExp = level * (rand() % 6 + 50);  // Higher EXP reward
        }
        break;
    case 5: // ORC_MINION1 (Tier 2 Enemy, moderate difficulty)
        if (this->attributeComponent)
        {
            this->attributeComponent->hpMax += (level * rand() % 6 + 25);
            this->attributeComponent->hp = this->attributeComponent->hpMax;

            this->attributeComponent->dmgMax += (rand() % 4 + 4) + this->attributeComponent->strength;  // Moderate damage
            this->attributeComponent->dmgMin = this->attributeComponent->dmgMax - (this->attributeComponent->dmgMax / 4);

            this->gainExp = (rand() % 16 + 40) + level;  // EXP range 40-55
        }
        break;
    case 6: // ORC_MINION2 (Tier 2 Enemy, moderate difficulty)
        if (this->attributeComponent)
        {
            this->attributeComponent->hpMax += (level * rand() % 6 + 25); 
            this->attributeComponent->hp = this->attributeComponent->hpMax;

            this->attributeComponent->dmgMax += (rand() % 4 + 4) + this->attributeComponent->strength;  // Moderate damage
            this->attributeComponent->dmgMin = this->attributeComponent->dmgMax - (this->attributeComponent->dmgMax / 4);

            this->gainExp = (rand() % 16 + 40) + level;  // EXP range 40-55
        }
        break;
    case 7: // SPIDER (Tier 2 Enemy, moderate difficulty)
        if (this->attributeComponent)
        {
            this->gainExp = (rand() % 11 + 35) + level;  // EXP range 35-45
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