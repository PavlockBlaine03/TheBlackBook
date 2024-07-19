#pragma once
#include "MainMenuState.h"

class Game
{
private:
	// variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	sf::Clock dtClock;

	GraphicSettings gfxSettings;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	float dt;

	// init
	void initVariables();
	void initGraphicSettings();
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

