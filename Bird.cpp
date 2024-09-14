#include "stdafx.h"
#include "Bird.h"

void Bird::initVariables()
{

}

void Bird::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 2, 0, 61, 57);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 0, 2, 0, 61, 57);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 1, 2, 1, 61, 57);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 2, 2, 2, 61, 57);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 3, 2, 3, 61, 57);
	//this->animationComponent->addAnimation("ATTACK", 6.f, 0, 2, 3, 2, 60, 64);
}

void Bird::initGui()
{
	std::stringstream ss;
	ss << this->attributeComponent->level;

	this->headerText.setFont(this->font);
	this->headerText.setString("BIRD LVL: " + ss.str());
	this->headerText.setCharacterSize(8.f);
	this->headerText.setFillColor(sf::Color::Yellow );
	this->headerText.setPosition(sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y));

	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(75.f, 5.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x - 5.f, this->sprite.getPosition().y + 75.f));
}

Bird::Bird(EnemySpawnerTile& enemy_spawner_tile, sf::Texture& texture_sheet, float x, float y, Entity& player)
	: Enemy(enemy_spawner_tile)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 16.f, 16.f, 30.f, 30.f);
	this->createMovementComponent(70.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(rand() % 6 + 5);

	this->generateAttributes(this->attributeComponent->level, enemy_spawner_tile.getEnemyType());

	this->setPosition(x, y);
	this->initAnimations();
	this->initGui();
	this->follow = new AIFollow(*this, player);
	this->roam = new AIRoam(*this, player);
}

Bird::~Bird()
{
}

void Bird::playDeath(SoundManager& sound_manager)
{
	sound_manager.setSoundVolume("ENEMY_DEATH", 12.f);

	sound_manager.playSound("ENEMY_DEATH");
}

void Bird::playHurt(SoundManager& sound_manager)
{
	sound_manager.setSoundVolume("ENEMY_HURT", 12.f);
	sound_manager.playSound("ENEMY_HURT");
}

void Bird::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}

	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}

	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
	{
		this->sprite.setColor(sf::Color::Red);
	}
	else
		this->sprite.setColor(sf::Color::White);

}

void Bird::update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view)
{
	Enemy::update(dt, mos_pos_view, view);

	this->movementComponent->update(dt);

	// Update Gui Test
	this->hpBar.setSize(sf::Vector2f(75.f * (static_cast<float>(this->attributeComponent->hp) / static_cast<float>(this->attributeComponent->hpMax)), 5.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x - 5.f, this->sprite.getPosition().y + 75.f));
	this->headerText.setPosition(sf::Vector2f(this->sprite.getPosition().x + 8.f, this->sprite.getPosition().y - 5.f));
	this->updateAnimation(dt);
	this->hitboxComponent->update();

	this->follow->update(dt);
	//this->roam->update(dt);
}

void Bird::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);

		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}

	target.draw(this->hpBar);
	target.draw(this->headerText);

	if (show_hitbox)
		hitboxComponent->render(target);
}
