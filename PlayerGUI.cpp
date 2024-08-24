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
	float width = 120.f;
	float height = 30.f;
	float x = 20.f;
	float y = 20.f;

	lvlBarBack.setSize(sf::Vector2f(width, height));
	lvlBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	lvlBarBack.setPosition(sf::Vector2f(x, y));

	lvlBarText.setFont(font);
	lvlBarText.setCharacterSize(18);
	lvlBarText.setPosition(lvlBarBack.getPosition().x + 10.f, lvlBarBack.getPosition().y + 5.f);
}

void PlayerGUI::initHpBar()
{
	float width = 300.f;
	float height = 40.f;
	float x = 20.f;
	float y = 60.f;

	hpBarMaxWidth = width;
	hpBarBack.setSize(sf::Vector2f(width, height));
	hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	hpBarBack.setPosition(sf::Vector2f(x, y));

	hpBarInner.setSize(sf::Vector2f(width, height));
	hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	hpBarInner.setPosition(hpBarBack.getPosition());

	hpBarText.setFont(font);
	hpBarText.setCharacterSize(18);
	hpBarText.setPosition(hpBarInner.getPosition().x + 10.f, hpBarInner.getPosition().y + 5.f);
}

void PlayerGUI::initExpBar()
{
	float width = 250.f;
	float height = 30.f;
	float x = 20.f;
	float y = 120.f;

	expBarMaxWidth = width;
	expBarBack.setSize(sf::Vector2f(width, height));
	expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	expBarBack.setPosition(sf::Vector2f(x, y));

	expBarInner.setSize(sf::Vector2f(width, height));
	expBarInner.setFillColor(sf::Color(225, 200, 20, 200));
	expBarInner.setPosition(expBarBack.getPosition());


	expBarText.setFont(font);
	expBarText.setCharacterSize(14);
	expBarText.setPosition(expBarInner.getPosition().x + 10.f, expBarInner.getPosition().y + 5.f);
}

PlayerGUI::PlayerGUI(Player* player)
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
