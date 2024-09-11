#pragma once



class SoundManager
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::unique_ptr<sf::Music> music;

	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, std::unique_ptr<sf::Music>> musicTracks;

public:
	SoundManager();
	virtual ~SoundManager();

	// Functions
	const bool loadSound(const std::string& name, const std::string file_name);
	const bool loadMusic(const std::string& name, const std::string file_name);
	void playSound(const std::string& name);
	void playMusic(const std::string& name, bool loop = true);
	void pauseSound(const std::string& name);
	void pauseMusic(const std::string& name);
	void stopSound(const std::string& name);
	void stopMusic(const std::string & name);
};

