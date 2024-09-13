#include "stdafx.h"
#include "Blob.h"

void Blob::initVariables()
{

}

void Blob::initAnimations()
{
			//  start_frame_x, start_frame_y , frames_x, frames_y
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 2, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 0, 2, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 1, 2, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 2, 2, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 3, 2, 3, 60, 64);
	//this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);
}

void Blob::initAttributes()
{

}

void Blob::initGui()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(75.f, 5.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x - 5.f, this->sprite.getPosition().y + 75.f));
}

void Blob::initAI(Entity& player)
{
	this->follow = new AIFollow(*this, player);
	this->roam = new AIRoam(*this, player);
}

Blob::Blob(EnemySpawnerTile& enemy_spawner_tile, sf::Texture& texture_sheet, float x, float y, Entity& player)
	: Enemy(enemy_spawner_tile), player(player)
{
	this->initVariables();
	this->initGui();
	this->createHitboxComponent(this->sprite, 15.f, 39.f, 30.f, 30.f);
	this->createMovementComponent(80.f, 1400.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(rand() % 6 + 1);
	this->generateAttributes(this->attributeComponent->level, enemy_spawner_tile.getEnemyType());

	this->initAttributes();

	this->setPosition(x, y);
	this->initAnimations();

	this->initAI(player);
}

Blob::~Blob()
{
	delete this->follow;
	delete this->roam;
}

void Blob::playDeath(SoundManager& sound_manager)
{
	sound_manager.setSoundVolume("ENEMY_DEATH", 12.f);
	sound_manager.playSound("ENEMY_DEATH");
}

void Blob::playHurt(SoundManager& sound_manager)
{
	sound_manager.setSoundVolume("ENEMY_HURT", 12.f);
	sound_manager.playSound("ENEMY_HURT");
}

void Blob::updateAnimation(const float& dt)
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

void Blob::update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view)
{
	Enemy::update(dt, mos_pos_view, view);

	this->movementComponent->update(dt);
	this->attributeComponent->update();

	// Update Gui Test
	this->hpBar.setSize(sf::Vector2f(75.f * (static_cast<float>(this->attributeComponent->hp) / static_cast<float>(this->attributeComponent->hpMax)), 5.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x - 5.f, this->sprite.getPosition().y + 75.f));
	this->updateAnimation(dt);
	this->hitboxComponent->update();

	this->follow->update(dt);
	//this->roam->update(dt);
}

void Blob::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
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

	if (show_hitbox)
		hitboxComponent->render(target);
}
