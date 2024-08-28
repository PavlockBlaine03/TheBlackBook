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
	lvlBarText.setPosition(lvlBarBack.getPosition().x + gui::p2pX(0.4f, vm), lvlBarBack.getPosition().y + gui::p2pY(0.34f, vm));
}

void PlayerGUI::initHpBar()
{
	float width = gui::p2pX(11.7f, vm);
	float height = gui::p2pY(2.8f, vm);
	float x = gui::p2pX(0.8f, vm);
	float y = gui::p2pY(4.2f, vm);

	hpBarMaxWidth = width;
	hpBarBack.setSize(sf::Vector2f(width, height));
	hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	hpBarBack.setPosition(sf::Vector2f(x, y));

	hpBarInner.setSize(sf::Vector2f(width, height));
	hpBarInner.setFillColor(sf::Color(250, 20, 20, 190));
	hpBarInner.setPosition(hpBarBack.getPosition());

	hpBarText.setFont(font);
	hpBarText.setCharacterSize(gui::calcCharSize(vm, 155));
	hpBarText.setPosition(hpBarInner.getPosition().x + gui::p2pX(0.4f, vm), hpBarInner.getPosition().y + gui::p2pY(0.34f, vm));
}

void PlayerGUI::initExpBar()
{
	float width = gui::p2pX(9.8f, vm);
	float height = gui::p2pY(2.1f, vm);
	float x = gui::p2pX(0.8f, vm);
	float y = gui::p2pY(8.3f, vm);

	expBarMaxWidth = width;
	expBarBack.setSize(sf::Vector2f(width, height));
	expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	expBarBack.setPosition(sf::Vector2f(x, y));

	expBarInner.setSize(sf::Vector2f(width, height));
	expBarInner.setFillColor(sf::Color(225, 200, 20, 200));
	expBarInner.setPosition(expBarBack.getPosition());


	expBarText.setFont(font);
	expBarText.setCharacterSize(gui::calcCharSize(vm, 200));
	expBarText.setPosition(expBarInner.getPosition().x + gui::p2pX(0.4f, vm), expBarInner.getPosition().y + gui::p2pY(0.34f, vm));
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	: vm(vm)
{
	initFont();
	initHpBar();
	initExpBar();
	initLevelBar();

	this->player = player;
}

PlayerGUI::~PlayerGUI()
{

}

// Functions

void PlayerGUI::updateHpBar()
{
	float percent = static_cast<float>(player->getAttributeComponent()->hp) / static_cast<float>(player->getAttributeComponent()->hpMax);

	hpBarInner.setSize(sf::Vector2f(std::floor(hpBarMaxWidth * percent), hpBarInner.getSize().y));

	hpBarString = "HP: " + std::to_string(player->getAttributeComponent()->hp) + " / " + std::to_string(player->getAttributeComponent()->hpMax);
	hpBarText.setString(hpBarString);

}

void PlayerGUI::updateExpBar()
{
	float percent = static_cast<float>(player->getAttributeComponent()->exp) / static_cast<float>(player->getAttributeComponent()->expNext);

	expBarInner.setSize(sf::Vector2f(std::floor(expBarMaxWidth * percent), expBarInner.getSize().y));

	expBarString = "EXP: " + std::to_string(player->getAttributeComponent()->exp) + " / " + std::to_string(player->getAttributeComponent()->expNext);
	expBarText.setString(expBarString);
}

void PlayerGUI::updateLevelBar()
{
	lvlBarString = "LVL: " + std::to_string(player->getAttributeComponent()->level);
	lvlBarText.setString(lvlBarString);
}

void PlayerGUI::update(const float& dt)
{
	updateHpBar();
	updateExpBar();
	updateLevelBar();
}

void PlayerGUI::renderHpbar(sf::RenderTarget& target)
{
	target.draw(hpBarBack);
	target.draw(hpBarInner);
	target.draw(hpBarText);
}

void PlayerGUI::renderExpbar(sf::RenderTarget& target)
{
	target.draw(expBarBack);
	target.draw(expBarInner);
	target.draw(expBarText);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(lvlBarBack);
	target.draw(lvlBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	renderHpbar(target);
	renderExpbar(target);
	renderLevelBar(target);
}
