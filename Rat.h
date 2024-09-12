#pragma once

#include "Enemy.h"
#include "AIFollow.h"
#include "AIRoam.h"

class Enemy;

class Rat :
    public Enemy
{
private:


    // Init functions
    virtual void initVariables();
    virtual void initAnimations();
    virtual void initGui();
    void initAI();

    sf::RectangleShape hpBar;

    AIFollow* follow;
    AIRoam* roam;

public:
    Rat(EnemySpawnerTile& enemy_spawner_tile, sf::Texture& texture_sheet, float x, float y, Entity& player);
    virtual ~Rat();

    // Functions

    virtual void updateAnimation(const float& dt);
    virtual void update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

