#pragma once
#include "MainMenuState.h"

class Game
{
private:
	
	// variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	sf::Clock dtClock;

	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	float dt;
	bool fullscreen;

	// init
	void initVariables();
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

