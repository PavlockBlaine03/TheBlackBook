#include "SettingsState.h"

// Init functions
void SettingsState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("resources/images/backgrounds/bg1.png"))
	{
		std::cerr << "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_IMAGE_FILE";
		exit(EXIT_FAILURE);
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initVariables()
{

}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("fonts/Folker.ttf"))
	{
		std::cerr << "ERROR::MAIN_STATE::COULD_NOT_LOAD_FONT";
		exit(EXIT_FAILURE);
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("config/settings_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void SettingsState::initGui()
{
	this->buttons["EXIT_STATE"] = new gui::Button(2300.f, 1300.f, 250.f, 50.f, &this->font, "Back", 32,
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),				// Text Colors
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		// Button Colors

	std::string li[] = { "3840x2160", "2560x1440", "1920x1080", "1280x720"};
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(1800.f, 400.f, 200.f, 50.f, font, li, 4);
	
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	auto end = this->buttons.end();
	for (it; it != end; ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownLists.begin();
	auto end2 = this->dropDownLists.end();
	for (it2; it2 != end2; ++it2)
	{
		delete it2->second;
	}
}
// Accessors

// Functions
void SettingsState::updateInput(const float& dt)
{
	// update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void SettingsState::updateGui(const float& dt)
{
	// Updates all buttons
	// Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	// Quit game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}

	// Update Dropdownlists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateGui(dt);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderGui(*target);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}
