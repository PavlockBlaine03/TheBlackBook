#pragma once

#include "Gui.h"

class Tile
{
private:


protected:
	sf::RectangleShape shape;

public:
	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect);
	virtual ~Tile();

	// Functions
	void update();
	void render(sf::RenderTarget& target);
};

