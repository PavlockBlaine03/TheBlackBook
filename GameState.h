#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "Tilemap.h"


class GameState : public State
{
private:
	sf::Font font;

	Player* player;
	PauseMenu* pmenu;

	TileMap map;

	void initKeybinds();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initFonts();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	// Functions
	void updateInput(const float& dt);
	void update(const float& dt);
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

