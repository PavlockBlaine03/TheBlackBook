#pragma once

#include "Enemy.h"
#include "AIFollow.h"
#include "AIRoam.h"

class Bird :
    public Enemy
{
private:
    // Init functions
    virtual void initVariables();
    virtual void initAnimations();
    virtual void initGui();

    sf::RectangleShape hpBar;

    AIRoam* roam;
    AIFollow* follow;

public:
    Bird(EnemySpawnerTile& enemy_spawner_tile, sf::Texture& texture_sheet, float x, float y, Entity& player);
    virtual ~Bird();

    // Functions
    void playDeath(SoundManager& sound_manager);
    void playHurt(SoundManager& sound_manager);
    virtual void updateAnimation(const float& dt);
    virtual void update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = true);
};

