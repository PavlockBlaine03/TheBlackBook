#include "stdafx.h"
#include "EnemyEditorMode.h"

void EnemyEditorMode::initVariables()
{
	type = 0;
	amount = 1;
	timeToSpawn = 60;
	maxDistance = 1000.f;
}

void EnemyEditorMode::initGui()
{
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y);

	this->sideBar.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width),
		80.f
	)
	);
	this->sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sideBar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sideBar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
}

EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: EditorMode(state_data, tile_map, editor_state_data)
{
	initVariables();
	initGui();
}

EnemyEditorMode::~EnemyEditorMode()
{

}

void EnemyEditorMode::updateInput(const float& dt)
{
	// Add a tile to tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			this->tileMap->addTile(
				this->editorStateData->mousePosGrid->x, 
				this->editorStateData->mousePosGrid->y, 
				0, 
				this->textureRect, false, TileTypes::ENEMYSPAWNER);
		}
	}
	// remove a tile from tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, TileTypes::ENEMYSPAWNER);
		}
	}
}

void EnemyEditorMode::updateGui(const float& dt)
{
	this->selectorRect.setPosition(
		this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
		this->editorStateData->mousePosGrid->y * this->stateData->gridSize);

	this->cursorText.setPosition(
		this->editorStateData->mousePosView->x - 50.f, 
		this->editorStateData->mousePosView->y - 50.f);

	std::stringstream ss;
	ss <<
		"\n" << "Enemy type: " << this->type <<
		"\n" << "Enemy amount: " << this->amount <<
		"\n" << "Enemy max distance: " << this->maxDistance <<
		"\n" << "Time to spawn: " << this->timeToSpawn;
	this->cursorText.setString(ss.str());
}

void EnemyEditorMode::update(const float& dt)
{
	updateInput(dt);
	updateGui(dt);
}

void EnemyEditorMode::renderGui(sf::RenderTarget& target)
{
	target.setView(*this->editorStateData->view);
	target.draw(selectorRect);
	target.draw(cursorText);

	target.setView(target.getDefaultView());
	target.draw(sideBar);
}

void EnemyEditorMode::render(sf::RenderTarget& target)
{
	renderGui(target);
}
