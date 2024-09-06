#include "stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->layer = 0;
	this->tileAddLock = false;
}

void DefaultEditorMode::initGui()
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
	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->texureSelector = new gui::TextureSelector(
		1700.f, 90.f, 800.f, 700.f, 
		this->stateData->gridSize, 
		this->tileMap->getTileSheet(), *this->editorStateData->font, "TS");
}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: EditorMode(state_data, tile_map, editor_state_data)
{
	initVariables();
	initGui();
}

DefaultEditorMode::~DefaultEditorMode()
{
	delete this->texureSelector;
}

// Functions
void DefaultEditorMode::updateInput(const float& dt)
{
	// Add a tile to tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			if (!this->texureSelector->getActive())
			{
				if (this->tileAddLock)
				{
					if (this->tileMap->tileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0))
					{
						this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
					}
				}
				else
				{
					this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);

				}
			}
			else
			{
				this->textureRect = this->texureSelector->getTextureRect();
			}
		}
	}
	// remove a tile from tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			if (!this->texureSelector->getActive())
			{
				this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);
			}
		}
	}

	// Toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TOGGLE_COLLISION"))) && this->getKeytime())
	{
		this->collision = !collision;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TYPE_INC"))) && this->getKeytime())
	{
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TYPE_DEC"))) && this->getKeytime())
	{
		if (this->type > 0)
			--this->type;
	}

	// Set Lock on / off
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TOGGLE_TILE_LOCK"))) && this->getKeytime())
	{
		this->tileAddLock = !tileAddLock;
	}
}

void DefaultEditorMode::updateGui(const float& dt)
{
	this->texureSelector->update(*this->editorStateData->mousePosWindow, dt);

	if (!this->texureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(
			this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
			this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
	}

	/*****************debug remove later************************/
	this->cursorText.setPosition(this->editorStateData->mousePosView->x - 50.f, this->editorStateData->mousePosView->y - 50.f);

	std::stringstream ss;
	ss << this->editorStateData->mousePosView->x << " " << this->editorStateData->mousePosView->y <<
		"\n" << this->editorStateData->mousePosGrid->x << " " << this->editorStateData->mousePosGrid->y <<
		"\n" << this->textureRect.left << " " << this->textureRect.top <<
		"\nCollision: " << this->collision <<
		"\n" << "Type: " << this->type <<
		"\n" << "Tiles: " << this->tileMap->getLayerSize(
			this->editorStateData->mousePosGrid->x,
			this->editorStateData->mousePosGrid->y,
			this->layer) <<
		"\n" << "Tile Lock: " << this->tileAddLock;
	this->cursorText.setString(ss.str());
}

void DefaultEditorMode::update(const float& dt)
{
	this->updateInput(dt);
	this->updateGui(dt);
}

void DefaultEditorMode::renderGui(sf::RenderTarget& target)
{
	if (!this->texureSelector->getActive())
	{
		target.setView(*this->editorStateData->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->stateData->window->getDefaultView());
	this->texureSelector->render(target);
	target.draw(this->sideBar);

	target.setView(*this->editorStateData->view);
	target.draw(this->cursorText);
}

void DefaultEditorMode::render(sf::RenderTarget& target)
{
	this->renderGui(target);
}
