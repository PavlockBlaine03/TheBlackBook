#pragma once
#include "Tile.h"

class TileMap
{
private:
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::vector<std::vector<std::vector<Tile>>> map;

public:
	TileMap();
	virtual ~TileMap();

};

