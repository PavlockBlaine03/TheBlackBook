#pragma once

#include "Entity.h"
#include "EnemySpawner.h"

class EnemySpawner;
class Entity;
class Enemy :
    public Entity
{
private:
    // Variables
    EnemySpawner& enemySpawner;

    // Init functions
    void initVariables();
    void initAnimations();

public:
    Enemy(EnemySpawner& enemy_spawner, sf::Texture& texture_sheet, float x, float y);
    virtual ~Enemy();

    // Functions
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mos_pos_view);
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

