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

void PlayerGUI::initHpBar()
{
	float width = 300.f;
	float height = 40.f;
	float x = 20.f;
	float y = 20.f;

	hpBarText.setFont(font);

	hpBarMaxWidth = width;
	hpBarBack.setSize(sf::Vector2f(width, height));
	hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	hpBarBack.setPosition(sf::Vector2f(x, y));

	hpBarInner.setSize(sf::Vector2f(width, height));
	hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	hpBarInner.setPosition(hpBarBack.getPosition());

	hpBarText.setPosition(hpBarInner.getPosition().x + 10.f, hpBarInner.getPosition().y + 5.f);
}

PlayerGUI::PlayerGUI(Player* player)
{
	initFont();
	initHpBar();

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

	hpBarString = std::to_string(player->getAttributeComponent()->hp) + " / " + std::to_string(player->getAttributeComponent()->hpMax);
	hpBarText.setString(hpBarString);
}

void PlayerGUI::update(const float& dt)
{
	updateHpBar();
}

void PlayerGUI::renderHpbar(sf::RenderTarget& target)
{
	target.draw(hpBarBack);
	target.draw(hpBarInner);
	target.draw(hpBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	renderHpbar(target);
}
