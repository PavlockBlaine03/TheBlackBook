#include "stdafx.h"
#include "Orc.h"

void Orc::initVariables()
{

}

void Orc::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 30.f, 0, 0, 5, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 15.f, 0, 0, 5, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 15.f, 0, 1, 5, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 15.f, 0, 2, 5, 2, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 15.f, 0, 3, 5, 3, 64, 64);
	//this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

void Orc::initGui()
{
	std::stringstream ss;
	ss << this->attributeComponent->level;

	this->headerText.setFont(this->font);
	this->headerText.setString("ORC LVL: " + ss.str());
	this->headerText.setCharacterSize(12.f);
	this->headerText.setFillColor(sf::Color::Red);
	this->headerText.setPosition(sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y));

	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(100.f, 10.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x - 5.f, this->sprite.getPosition().y + 200.f));
}

void Orc::initAI(Entity& player)
{
	this->follow = new AIFollow(*this, player);
	this->roam = new AIRoam(*this, player);
}

Orc::Orc(EnemySpawnerTile& enemy_spawner_tile, sf::Texture& texture_sheet, float x, float y, Entity& player)
	: Enemy(enemy_spawner_tile)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 36.f, 36.f, 50.f, 50.f);
	this->createMovementComponent(50.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(rand() % 14 + 8);

	this->sprite.setScale(sf::Vector2f(2.f, 2.f));

	this->generateAttributes(this->attributeComponent->level, enemy_spawner_tile.getEnemyType());

	this->setPosition(x, y);
	this->initAnimations();
	this->initGui();
	this->initAI(player);
}

Orc::~Orc()
{
}

void Orc::playDeath(SoundManager& sound_manager)
{
	sound_manager.playSound("ORC_DEATH");
}

void Orc::playHurt(SoundManager& sound_manager)
{
	sound_manager.playSound("ORC_HURT");
}

void Orc::updateAnimation(const float& dt)
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

void Orc::update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view)
{
	Enemy::update(dt, mos_pos_view, view);

	this->movementComponent->update(dt);
	this->attributeComponent->update();

	// Update Gui Test
	this->hpBar.setSize(sf::Vector2f(75.f * (static_cast<float>(this->attributeComponent->hp) / static_cast<float>(this->attributeComponent->hpMax)), 5.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x + 24.f, this->sprite.getPosition().y + 100.f));

	this->headerText.setPosition(sf::Vector2f(this->sprite.getPosition().x + 35.f, this->sprite.getPosition().y));

	this->updateAnimation(dt);
	this->hitboxComponent->update();

	this->follow->update(dt);
	//this->roam->update(dt);
}

void Orc::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
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
