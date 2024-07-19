#include "stdafx.h"
#include "GraphicSettings.h"

GraphicSettings::GraphicSettings()
{
	this->title = "None";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->frameRateLimit = 120;
	this->vsync = false;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->frameRateLimit;
		ofs << this->vsync;
		ofs << this->contextSettings.antialiasingLevel;
	}

	ofs.close();
}

void GraphicSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->frameRateLimit;
		ifs >> this->vsync;
		ifs >> this->contextSettings.antialiasingLevel;
	}

	ifs.close();
}