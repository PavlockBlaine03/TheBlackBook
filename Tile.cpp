#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(short type, int grid_x, int grid_y, float gridSizeF, const sf::Texture& tile_texture_sheet, const sf::IntRect& tex_rect, const bool collision)
{
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->shape.setTexture(tile_texture_sheet);
	this->shape.setTextureRect(tex_rect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{

}

const bool& Tile::getCollision() const
{
	return this->collision;
}

const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

// Functions
//const std::string Tile::getAsString() const
//{
//	std::stringstream ss;
//
//	ss << this->type <<  
//		" " << this->shape.getTextureRect().left <<
//		" " << this->shape.getTextureRect().top <<
//		" " << this->collision;
//
//	return ss.str();
//}

const short& Tile::getType() const
{
	return this->type;
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	/*if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);*/
}
