#pragma once

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;

class DefaultEditorMode :
    public EditorMode
{
private:
	sf::Text cursorText;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	sf::RectangleShape sideBar;
	gui::TextureSelector* texureSelector;
	int layer;
	bool collision;
	bool tileAddLock;
	short type;

	// init functions
	void initVariables();
	void initGui();

public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~DefaultEditorMode();

	// Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

