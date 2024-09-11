#pragma once
#include "Player.h"
#include "Gui.h"
#include "GraphicSettings.h"
#include "SoundManager.h"

class Player;
class Gui;
class GraphicSettings;
class State;

class StateData
{
public:
	StateData() {};

	// Variables
	float gridSize = 0.f;
	sf::RenderWindow* window = NULL;
	GraphicSettings* gfxSettings = NULL;
	std::map<std::string, int>* supportedKeys = NULL;
	std::stack<State*>* states = NULL;
};

class State
{
private:

protected:

	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	std::map<std::string, sf::Texture> textures;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	virtual void initKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();

	// Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

