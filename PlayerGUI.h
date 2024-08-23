#pragma once
#include "Player.h"

class Player;
class sf::RectangleShape;
class PlayerGUI
{
private:

	sf::Font font;
	Player* player;
	
	// EXP bar


	// Health Bar
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	void initFont();
	void initHpBar();

public:
	PlayerGUI(Player* player);
	virtual ~PlayerGUI();

	// Functions

	void updateHpBar();
	void update(const float& dt);

	void renderHpbar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

