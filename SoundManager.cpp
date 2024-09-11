#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

const bool SoundManager::loadSound(const std::string& name, const std::string file_name)
{
	if (!this->buffer.loadFromFile(file_name))
	{
		std::cerr << "ERROR::SOUND_MANAGER::COULD_NOT_LOAD_SOUND_FILE " << file_name << std::endl;
		exit(EXIT_FAILURE);
	}
	this->soundBuffers[name] = buffer;
	this->sound.setBuffer(this->buffer);
	this->sounds[name] = sound;
	return true;
}

const bool SoundManager::loadMusic(const std::string& name, const std::string file_name)
{
	this->music = std::make_unique<sf::Music>();
	if (!this->music->openFromFile(file_name))
	{
		std::cerr << "ERROR::SOUND_MANAGER::COULD_NOT_OPEN_MUSIC_FILE " << file_name << std::endl;
		exit(EXIT_FAILURE);
	}
	musicTracks[name] = std::move(music);
	std::cout << "Music Loaded" << std::endl;
	return true;
}

void SoundManager::playSound(const std::string& name)
{
	if (sounds.find(name) != sounds.end())
	{
		sounds[name].play();
	}
	else
	{
		std::cerr << "ERROR::SOUNDMANAGER::SOUND_NOT_FOUND";
		exit(EXIT_FAILURE);
	}
}

void SoundManager::playMusic(const std::string& name, bool loop)
{
	if (musicTracks.find(name) != musicTracks.end())
	{
		std::cout << "Music Played" << std::endl;
		musicTracks[name]->setLoop(loop);
		musicTracks[name]->play();
	}
	else
	{
		std::cerr << "ERROR::SOUNDMANAGER::MUSIC_NOT_FOUND";
		exit(EXIT_FAILURE);
	}
}

void SoundManager::pauseSound(const std::string& name)
{
	if (sounds.find(name) != sounds.end())
	{
		sounds[name].pause();
	}
}

void SoundManager::pauseMusic(const std::string& name)
{
	if (musicTracks.find(name) != musicTracks.end())
	{
		musicTracks[name]->pause();
	}
}

void SoundManager::stopSound(const std::string& name)
{
	if (sounds.find(name) != sounds.end())
	{
		sounds[name].stop();
	}
}

void SoundManager::stopMusic(const std::string& name)
{
	if (musicTracks.find(name) != musicTracks.end())
	{
		std::cout << "Music stopped" << std::endl;
		musicTracks[name]->stop();
	}
}
