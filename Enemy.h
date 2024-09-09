#pragma once

#include "Entity.h"
#include "EnemySpawnerTile.h"

class EnemySpawnerTile;
class Entity;

class Enemy :
    public Entity
{
private:
    // Variables
    //EnemySpawner& enemySpawner;
    unsigned gainExp;


    // Init functions
    virtual void initVariables() = 0;
    virtual void initAnimations() = 0;

public:
    Enemy();
    virtual ~Enemy();

    // Accessors
    const unsigned& getGainExp() const;

    // Functions
    virtual void loseHP(const int hp);
    virtual  const bool isDead() const; 
    virtual const AttributeComponent* getAttributeComponent() const;

    virtual void updateAnimation(const float& dt) = 0;
    virtual void update(const float& dt, sf::Vector2f& mos_pos_view) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};

