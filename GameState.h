#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "Tilemap.h"

class PauseMenu;
class Player;
class TileMap;
class State;
class sf::View;
class sf::RenderTexture;
class sf::Font;

class GameState : public State
{
private:

	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	sf::Music* menuMusic;

	Player* player;
	PauseMenu* pmenu;

	TileMap* tileMap;

	// init functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initFonts();
	void initTileMap();

public:
	GameState(StateData* state_data, sf::Music* menu_music);
	virtual ~GameState();

	// Functions
	void restartMenuMusic();
	void updateInput(const float& dt);
	void updateView(const float& dt);
	void updateTileMap(const float& dt);
	void update(const float& dt);
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

