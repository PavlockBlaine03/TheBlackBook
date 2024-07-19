#pragma once

#include "Gui.h"

class Tile
{
private:


protected:
	sf::RectangleShape shape;

public:
	Tile();
	Tile(float x, float y, float gridSizeF);
	virtual ~Tile();

	// Functions
	void update();
	void render(sf::RenderTarget& target);
};

