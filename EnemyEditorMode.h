#pragma once

#include "EditorMode.h"
#include "EnemySpawner.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;
class Enemy;
class EnemySpawner;

class EnemyEditorMode :
    public EditorMode
{
private:
	sf::Text cursorText;
	sf::RectangleShape sideBar;
	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;

	int type;
	int amount;
	int timeToSpawn;
	float maxDistance;

	// init Functions
	void initVariables();
	void initGui();

public:
    EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EnemyEditorMode();

	// Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

