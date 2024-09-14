#include "stdafx.h"
#include "OrcMinion.h"

void OrcMinion::initVariables()
{

}

void OrcMinion::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 30.f, 0, 0, 5, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 15.f, 0, 0, 5, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 15.f, 0, 1, 5, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 15.f, 0, 2, 5, 2, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 15.f, 0, 3, 5, 3, 64, 64);
	//this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

void OrcMinion::initGui()
{
	std::stringstream ss;
	ss << this->attributeComponent->level;

	this->headerText.setFont(this->font);
	this->headerText.setString("ORC MINION LVL: " + ss.str());
	this->headerText.setCharacterSize(8.f);
	this->headerText.setFillColor(sf::Color::Yellow);
	this->headerText.setPosition(sf::Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y));

	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(75.f, 5.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x - 5.f, this->sprite.getPosition().y + 75.f));

	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(75.f, 5.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x - 5.f, this->sprite.getPosition().y + 75.f));
}

void OrcMinion::initAI(Entity& player)
{
	this->follow = new AIFollow(*this, player);
	this->roam = new AIRoam(*this, player);
}

OrcMinion::OrcMinion(EnemySpawnerTile& enemy_spawner_tile, sf::Texture& texture_sheet, float x, float y, Entity& player)
	: Enemy(enemy_spawner_tile)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 16.f, 16.f, 30.f, 30.f);
	this->createMovementComponent(90.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(rand() % 5 + 8);


	this->generateAttributes(this->attributeComponent->level, enemy_spawner_tile.getEnemyType());

	this->setPosition(x, y);
	this->initAnimations();
	this->initGui();
	this->initAI(player);
}

OrcMinion::~OrcMinion()
{

}

void OrcMinion::playDeath(SoundManager& sound_manager)
{
	sound_manager.playSound("ORC_DEATH");
}

void OrcMinion::playHurt(SoundManager& sound_manager)
{
	sound_manager.playSound("ORC_HURT");
}

void OrcMinion::updateAnimation(const float& dt)
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

void OrcMinion::update(const float& dt, sf::Vector2f& mos_pos_view, const sf::View& view)
{
	Enemy::update(dt, mos_pos_view, view);

	this->movementComponent->update(dt);
	this->attributeComponent->update();

	// Update Gui Test
	this->hpBar.setSize(sf::Vector2f(75.f * (static_cast<float>(this->attributeComponent->hp) / static_cast<float>(this->attributeComponent->hpMax)), 5.f));
	this->hpBar.setPosition(sf::Vector2f(this->sprite.getPosition().x - 5.f, this->sprite.getPosition().y + 50.f));
	this->headerText.setPosition(sf::Vector2f(this->sprite.getPosition().x - 12.f, this->sprite.getPosition().y - 8.f));
	this->updateAnimation(dt);
	this->hitboxComponent->update();

	this->follow->update(dt);
	//this->roam->update(dt);
}

void OrcMinion::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position, const bool show_hitbox)
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
