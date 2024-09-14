#pragma once

#include "Entity.h"
#include "EnemySpawnerTile.h"

class Enemy :
    public Entity
{
protected:
    // Variables
    EnemySpawnerTile& enemySpawnerTile;
    unsigned gainExp;
    sf::Clock despawnTimer;
    sf::Int32 despawnTimerMax;

    sf::Font font;
    sf::Text headerText;

    // Init functions
    virtual void initVariables() = 0;
    virtual void initAnimations() = 0;

public:
    Enemy(EnemySpawnerTile& enemy_spawner_tile);
    virtual ~Enemy();

    // Accessors
    const unsigned& getGainExp() const;
    EnemySpawnerTile& getEnemySpawnerTile();
    const bool getDespawnTimerDone() const;

    // Functions

    virtual void playDeath(SoundManager& sound_manager) = 0;
    virtual void playHurt(SoundManager& sound_manager) = 0;
    virtual void generateAttributes(const unsigned level, const int type);
    virtual void loseHP(const int hp);
    virtual const bool isDead() const; 

    virtual void updateAnimation(const float& dt) = 0;
    virtual void update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};

