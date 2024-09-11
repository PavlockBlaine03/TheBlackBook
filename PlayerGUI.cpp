#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	if (!font.loadFromFile("C:/VisualCodeProjects/TheBlackBook/fonts/Folker.ttf"))
	{
		std::cerr << "ERROR::PLAYER_GUI::COULD_NOT_LOAD_FONT";
		exit(EXIT_FAILURE);
	}
}

void PlayerGUI::initLevelBar()
{
	float width = gui::p2pX(4.7f, vm);
	float height = gui::p2pY(2.1f, vm);
	float x = gui::p2pX(0.8f, vm);
	float y = gui::p2pY(1.4f, vm);

	lvlBarBack.setSize(sf::Vector2f(width, height));
	lvlBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	lvlBarBack.setPosition(sf::Vector2f(x, y));

	lvlBarText.setFont(font);
	lvlBarText.setCharacterSize(gui::calcCharSize(vm, 200));

	lvlBarText.setPosition(
		lvlBarBack.getPosition().x + gui::p2pX(0.4f, vm), 
		lvlBarBack.getPosition().y + gui::p2pY(0.34f, vm)
	);
}

void PlayerGUI::initHpBar()
{
	hpBar = new gui::ProgressBar(
		0.8f, 4.2f, 11.7f, 2.8f, 
		this->player->getAttributeComponent()->hpMax, 
		vm, 
		sf::Color(250, 20, 20, 190), 
		155, &font
	);
}

void PlayerGUI::initExpBar()
{
	expBar = new gui::ProgressBar(
		0.8f, 8.3f, 9.8f, 2.1f, 
		player->getAttributeComponent()->expNext, 
		vm, 
		sf::Color(200, 20, 200, 190), 
		180, &font
	);
}

void PlayerGUI::initTabMenu()
{

}

void PlayerGUI::initCharacterTab()
{
	// Background
	this->characterTabBack.setFillColor(sf::Color(20, 20, 20, 200));

	this->characterTabBack.setSize(
		sf::Vector2f(
			gui::p2pX(25.f, this->vm),
			static_cast<float>(this->vm.height)
		)
	);

	// Text
	this->characterInfoText.setFont(this->font);
	this->characterInfoText.setCharacterSize(gui::calcCharSize(this->vm, 200));
	this->characterInfoText.setFillColor(sf::Color::White);
	this->characterInfoText.setPosition(
		this->characterTabBack.getPosition().x + gui::p2pX(1.f, this->vm),
		this->characterTabBack.getPosition().y + gui::p2pY(1.f, this->vm)
	);

}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	: vm(vm)
{
	this->player = player;
	initFont();
	initHpBar();
	initExpBar();
	initLevelBar();
	initTabMenu();
	initCharacterTab();

}

PlayerGUI::~PlayerGUI()
{
	delete hpBar;
	delete expBar;
}

// Functions
void PlayerGUI::updateHpBar()
{
	hpBar->update("HP:", player->getAttributeComponent()->hp, player->getAttributeComponent()->hpMax);
}

void PlayerGUI::updateExpBar()
{
	expBar->update("EXP:", player->getAttributeComponent()->exp, player->getAttributeComponent()->expNext);
}

void PlayerGUI::updateLevelBar()
{
	lvlBarString = "LVL: " + std::to_string(player->getAttributeComponent()->level);
	lvlBarText.setString(lvlBarString);
}

void PlayerGUI::updateCharacterTab()
{
	this->characterInfoText.setString("TESTING");
}

void PlayerGUI::update(const float& dt)
{
	updateHpBar();
	updateExpBar();
	updateLevelBar();
	updateCharacterTab();
}

void PlayerGUI::renderHpbar(sf::RenderTarget& target)
{
	hpBar->render(target);
}

void PlayerGUI::renderExpbar(sf::RenderTarget& target)
{
	expBar->render(target);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(lvlBarBack);
	target.draw(lvlBarText);
}

void PlayerGUI::renderCharacterTab(sf::RenderTarget& target)
{
	target.draw(this->characterTabBack);
	target.draw(this->characterInfoText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	renderHpbar(target);
	renderExpbar(target);
	renderLevelBar(target);

	// Tabs
	renderCharacterTab(target);
}
