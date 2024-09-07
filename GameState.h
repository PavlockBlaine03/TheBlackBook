#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "Tilemap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Bow.h"
#include "Enemies.h"

class Enemy;
class Rat;
class Sword;
class Bow;
class RangedWeapon;
class MeleeWeapon;
class Item;
class PlayerGUI;
class PauseMenu;
class Player;
class TileMap;
class State;
class sf::View;
class sf::RenderTexture;
class sf::Font;
class sf::Shader;

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

public:
	GameState(StateData* state_data, sf::Music* menu_music);
	virtual ~GameState();

	// Functions
	void restartMenuMusic();
	void updateInput(const float& dt);
	void updateView(const float& dt);
	void updateTileMap(const float& dt);
	void updatePlayerGUI(const float& dt);
	void update(const float& dt);
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

