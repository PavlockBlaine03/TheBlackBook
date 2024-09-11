#pragma once



class SoundManager
{
private:
	std::unique_ptr<sf::SoundBuffer> buffer;
	std::unique_ptr<sf::Sound> sound;

	std::unique_ptr<sf::Music> music;

	std::map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
	std::map<std::string, std::unique_ptr<sf::Sound>> sounds;
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

	void setSoundVolume(const std::string& name, float volume);
	void setMusicVolume(const std::string& name, float volume);
};

