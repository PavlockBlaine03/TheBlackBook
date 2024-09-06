#include "stdafx.h"
#include "EnemyEditorMode.h"

void EnemyEditorMode::initVariables()
{

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
	ss <<"\nCollision: " <<
		"\n" << "Type: " <<
		"\n" << "Tiles: " <<
		"\n" << "Tile Lock: ";
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
	target.draw(sideBar);
	target.draw(cursorText);
}

void EnemyEditorMode::render(sf::RenderTarget& target)
{
	renderGui(target);
}
