#pragma once
#include "Enemy.h"
class Bird :
    public Enemy
{
private:
    // Init functions
    virtual void initVariables();
    virtual void initAnimations();
    virtual void initGui();

    sf::RectangleShape hpBar;

public:
    Bird(EnemySpawnerTile& enemy_spawner_tile, sf::Texture& texture_sheet, float x, float y);
    virtual ~Bird();

    // Functions
    virtual void updateAnimation(const float& dt);
    virtual void update(const float& dt, sf::Vector2f& mos_pos_view);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = true);
};

