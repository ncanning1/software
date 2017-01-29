#pragma once
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Audio {
public:
	Audio();
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music *music;
	char *memblock; //for music storage
	std::streampos size;
	bool isEffect; //true = effect, false = music
};