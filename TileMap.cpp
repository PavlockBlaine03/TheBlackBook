#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	if (!this->map.empty())
	{
		for (int x = 0; x < this->map.size(); x++)
		{
			for (int y = 0; y < this->map[x].size(); y++)
			{
				for (int z = 0; z < this->map[x][y].size(); z++)
				{
					for (int k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = NULL;
					}

					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}

		this->map.clear();
	}
}

TileMap::TileMap(float grid_size, int width, int height, std::string texture_file)
{
	this->gridSizeF = grid_size;
	this->gridSizeI = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorld.x = static_cast<float>(width) * grid_size;
	this->maxSizeWorld.y = static_cast<float>(height) * grid_size;
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}
	
	if (!this->tileSheet.loadFromFile(texture_file))
	{
		std::cerr << "ERROR::TILEMAP::FAILED TO LOAD TEXTURE SHEET::FILENAME: " << texture_file << std::endl;
		exit(EXIT_FAILURE);
	}

	this->collisionBox.setSize(sf::Vector2f(grid_size, grid_size));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::TileMap(const std::string file_name)
{
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	loadFromFile(file_name);

	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->clear();
}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x 
		&& y >= 0 && y < this->maxSizeWorldGrid.y 
		&& z >= 0 && z < this->layers)
	{
		return this->map[x][y][z].empty();
	}
	return false;
}

// Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return static_cast<int>(this->map[x][y][layer].size());
			}
		}
	}
	return -1;
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const
{
	return maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::getMaxSizeF() const
{
	return maxSizeWorld;
}

// Functions
void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& tex_rect, const bool collision, const short type)
{
	/* Take three indices from mouse position in grid and add tile to that position if internal tile map array allows it */
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		/* ok to add tile*/
		this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, tex_rect, collision, type));

		std::cout << "DEBUG: ADDED A TILE" << std::endl;
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	/* Take three indices from mouse position in grid and remove tile at that position if internal tile map array allows it */
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			/* ok to remove tile*/
			delete this->map[x][y][z][this->map[x][y][z].size() - 1];
			this->map[x][y][z].pop_back();
			std::cout << "DEBUG: REMOVED A TILE" << std::endl;
		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/* Saves the tile map to a text-file
	Format:
	Basic:
	Size x y
	gridSize
	layers
	texture file

	All tiles:
	gridPos x y layer
	TextureRect rect x y
	collision
	type

	*/

	std::ofstream out_file;
	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (int k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " << this->map[x][y][z][k]->getAsString() << " ";	// Make sure last space is not saved!!!
						}
					}
				}
			}
		}
	}
	else
	{
		std::cerr << "ERROR::TILEMAP::SAVE_TO_FILE::COULD NOT SAVE TO FILE::FILENAME: " << file_name << std::endl;
		exit(EXIT_FAILURE);
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;
	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		int gridSize = 0;
		int layers = 0;
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type;
		std::string texture_file = "";

		// Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		// Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorld.x = static_cast<float>(size.x * gridSize);
		this->maxSizeWorld.y = static_cast<float>(size.y * gridSize);
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
		{
			std::cerr << "ERROR::TILEMAP::FAILED TO LOAD TEXTURE SHEET::FILENAME: " << texture_file << std::endl;
			exit(EXIT_FAILURE);
		}

		// load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type) 
		{
			this->map[x][y][z].push_back(
				new Tile(
					x, y, 
					this->gridSizeF, 
					this->tileSheet, 
					sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), 
					collision, 
					type
				)
			);
		}
	}
	else
	{
		std::cerr << "ERROR::TILEMAP::LOAD_FROM_FILE::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << std::endl;
		exit(EXIT_FAILURE);
	}

	in_file.close();
}

void TileMap::update(Entity* entity, const float& dt)
{

	// World Bounds
	if (entity->getPosition().x < 0.f)
	{
		entity->stopVelocityX();
		entity->setPosition(0.f, entity->getPosition().y);
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorld.x)
	{
		entity->stopVelocityX();
		entity->setPosition(this->maxSizeWorld.x - entity->getGlobalBounds().width, entity->getPosition().y);
	}
	if (entity->getPosition().y < 0.f )
	{
		entity->stopVelocityY();
		entity->setPosition(entity->getPosition().x, 0.f);
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorld.y)
	{
		entity->stopVelocityY();
		entity->setPosition(entity->getPosition().x, this->maxSizeWorld.y - entity->getGlobalBounds().height);
	}

	// Tiles
	this->layer = 0;

	// CULLING
	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;
	

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (int k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				this->map[x][y][this->layer][k]->update();

				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (this->map[x][y][this->layer][k]->getCollision() &&
					this->map[x][y][this->layer][k]->intersects(nextPositionBounds))
				{
					//Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}

					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}

					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
		}
	}
}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i &gridPosition, sf::Shader* shader, const sf::Vector2f playerPosition, const bool show_collision)
{

	this->layer = 0;

	// Left
	this->fromX = gridPosition.x - 20;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	// Right
	this->toX = gridPosition.x + 21;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	// Top
	this->fromY = gridPosition.y - 11;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	// Bottom
	this->toY = gridPosition.y + 12;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (int k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::RENDERTOP)
				{
					this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
				}
				else
				{
					if(shader)
						this->map[x][y][this->layer][k]->render(target, shader, playerPosition);
					else
						this->map[x][y][this->layer][k]->render(target);
				}

				// debug
				if (show_collision)
				{
					if (this->map[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition)
{
	while (!this->deferredRenderStack.empty()) 
	{
		if(shader)
			deferredRenderStack.top()->render(target, shader, playerPosition);
		else
			deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}

