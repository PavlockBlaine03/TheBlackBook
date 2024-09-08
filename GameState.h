#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "Tilemap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Bow.h"

class GameState : public State
{
private:

	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	sf::Music* menuMusic;

	std::vector<Enemy*> activeEnemies;

	EnemySystem* enemySystem;

	Player* player;
	PlayerGUI* playerGUI;
	PauseMenu* pmenu;
	
	TileMap* tileMap;

	sf::Shader coreShader;

	// init functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initPlayers();
	void initPlayerGUI();
	void initFonts();
	void initTileMap();
	void initEnemySystem();

public:
	GameState(StateData* state_data, sf::Music* menu_music);
	virtual ~GameState();

	// Functions
	void restartMenuMusic();
	void updateInput(const float& dt);
	void updateView(const float& dt);
	void updateTileMap(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePlayer(const float& dt);
	void updateEnemies(const float& dt);
	void update(const float& dt);
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

