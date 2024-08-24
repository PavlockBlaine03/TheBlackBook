#include "stdafx.h"
#include "SettingsState.h"

// Init functions
void SettingsState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("C:/VisualCodeProjects/TheBlackBook/resources/images/backgrounds/bg1.png"))
	{
		std::cerr << "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_BACKGROUND_IMAGE_FILE";
		exit(EXIT_FAILURE);
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("C:/VisualCodeProjects/TheBlackBook/fonts/Folker.ttf"))
	{
		std::cerr << "ERROR::MAIN_STATE::COULD_NOT_LOAD_FONT";
		exit(EXIT_FAILURE);
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("C:/VisualCodeProjects/TheBlackBook/config/settings_keybinds.ini");

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
	this->buttons["BACK"] = new gui::Button(
		p2pX(90.f), p2pY(90.2f), p2pX(6.f), p2pY(3.5f),
		&this->font, "Back", calcCharSize(),
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),	
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0
		)
	);

	this->buttons["APPLY"] = new gui::Button(
		p2pX(82.f), p2pY(90.2f), p2pX(6.f), p2pY(3.5f),
		&this->font, "Apply", calcCharSize(),
		sf::Color(125, 125, 125, 200), sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0
		)
	);

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(p2pX(75.3f), p2pY(27.8f), p2pX(7.8f), p2pY(3.5f), font, modes_str.data(), static_cast<unsigned>(modes_str.size()));
	
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(p2pX(62.5f), p2pY(29.5f)));
	this->optionsText.setCharacterSize(20);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString("Resolution \n\n\nFullscreen \n\n\nVsync \n\n\nAntialiasing \n\n\n");
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
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
		it.second->update(this->mousePosWindow);
	}

	// Quit game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	// Apply settings
	if (this->buttons["APPLY"]->isPressed())
	{	
		// Test remove later
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementID()];
		this->window->close();

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}

	// Update Dropdownlists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
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

	target->draw(this->optionsText);
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
