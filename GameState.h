#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "Tilemap.h"
#include "PlayerGUI.h"
#include "TextTagSystem.h"
#include "Sword.h"
#include "Bow.h"

class GameState : public State
{
private:

	// Systems
	SoundManager& soundManager;
	TextureManager* textureManager;
	TextTagSystem* textTagSystem;

	sf::Text debugText;

	sf::Text gameOverText;

	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	std::map<std::string, sf::Font> fonts;

	std::vector<Enemy*> activeEnemies;

	EnemySystem* enemySystem;

	Player* player;
	PlayerGUI* playerGUI;
	PauseMenu* pmenu;
	
	TileMap* tileMap;

	bool isGameOver;

	sf::Shader coreShader;

	// init functions
	void initDebugText();
	void initGameMusic();
	void initGameSound();
	void initDeferredRender();
	void initTextureManager();
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
	void initTextTagSystem();

public:
	GameState(StateData* state_data, SoundManager* soundManager);
	virtual ~GameState();

	// Functions
	void gameOver();
	void updateInput(const float& dt);
	void updateView(const float& dt);
	void updateTileMap(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePlayer(const float& dt);
	void updateCombatAndEnemies(const float& dt);
	void updateCombat(Enemy* enemy, const int index, const float& dt);
	void update(const float& dt);
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void updateDebugText(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

