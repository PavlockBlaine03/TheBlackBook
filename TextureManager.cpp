#include "stdafx.h"
#include "TextureManager.h"

void TextureManager::initTextures()
{
	this->textures["PLAYER"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Player/PLAYER_SHEET2.png";
	this->textures["RAT1"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Enemy/rat1_60x64.png";
	this->textures["ORC1"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Enemy/orc1_64x64.png";
	this->textures["BIRD1"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Enemy/bird1_61x57.png";
	this->textures["SCORPION1"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Enemy/scorpion1_60x64.png";
	this->textures["BLOB1"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Enemy/blob1_60x64.png";
	this->textures["SWORD"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Player/sword.png";
	this->textures["BOW"] = "C:/VisualCodeProjects/TheBlackBook/resources/images/Sprites/Player/bow.png";
}

TextureManager::TextureManager()
{
	this->initTextures();
}

TextureManager::~TextureManager()
{
}

const std::map<std::string, std::string>& TextureManager::getTextures() const
{
	return this->textures;
}
