#pragma once
#include<SFML/Audio.hpp>
class Sound{
	public:
	Sound();
	float time_till_end;
	sf::SoundBuffer jump_buffer;
	sf::SoundBuffer igloo_buffer;
	sf::SoundBuffer walk_buffer;
	sf::SoundBuffer hit_buffer;
	sf::SoundBuffer death_buffer;

	sf::Sound jumpSound;
	sf::Sound iglooSound;
	sf::Sound walkSound;
	sf::Sound hitSound;
	sf::Sound deathSound;

	void loadSounds();

	void insertSounds();

	void playSound(const char* sound);

	void stopSound(const char* sound);
	~Sound();
};