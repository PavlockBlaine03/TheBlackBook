#pragma once
#include "MainMenuState.h"


class MainMenuState;

class Game
{
private:
	// variables
	SoundManager soundManager;
	sf::RenderWindow *window;
	StateData stateData;
	sf::Event sfEvent;
	sf::Clock dtClock;

	GraphicSettings gfxSettings;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	float dt;
	float gridSize;

	// init
	void initVariables();
	void initSoundManager();
	void initGraphicSettings();
	void InitStateData();
	void initWindow();
	void initStates();
	void initKeys();

public:
	// Constructor/Destructor
	Game();
	virtual ~Game();

	// functions
	void endApplication();

	// update
	void updateSFMLEvents();
	void updateDt();
	void update();

	// render
	void render();

	// Core
	void run();
};

