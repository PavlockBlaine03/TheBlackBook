#include "stdafx.h"
#include "Game.h"

// Static functions

// init functions

void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	this->gridSize = 100.f;
}

void Game::initGraphicSettings()
{
	this->gfxSettings.loadFromFile("C:/VisualCodeProjects/TheBlackBook/config/graphics.ini");
}

void Game::InitStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initWindow()
{
	if(this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);
	else
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.vsync);
}

void Game::initKeys()
{
	std::ifstream ifs("C:/VisualCodeProjects/TheBlackBook/config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key;
		int keyValue = 0;
		while (ifs >> key >> keyValue)
		{
			this->supportedKeys[key] = keyValue;
		}
	}

	ifs.close();

	//// debug print
	//for (auto i : this->supportedKeys)
	//{
	//	std::cout << i.first << " " << i.second << "\n";
	//}
}


void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

// Constructor/Destructor
Game::Game()
{
	this->initVariables();
	this->initGraphicSettings();
	this->initWindow();
	this->initKeys();
	this->InitStateData();
	this->initStates();
}
Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

// Functions
void Game::endApplication()
{
	std::cout << "Ending application";
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed) this->window->close();
	}
}

void Game::updateDt()
{
	/*Update deltaTime variable for each time it takes for frame*/
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::update()
{
	this->updateSFMLEvents();
	if (!this->states.empty() && this->window->hasFocus())
	{
		this->states.top()->update(this->dt);
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else // Application end, no states
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	// Render objects
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
