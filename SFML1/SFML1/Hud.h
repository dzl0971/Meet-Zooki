#pragma once
#include <SFML/Graphics.hpp>
#include "Zooki.h"
#include "Tile.h"

class Hud
{
public:
	Hud();
	Hud(sf::Clock* time, Zooki* zooki_ptr, std::vector<Tile>* tiles);
	sf::Sprite iceCream;
	~Hud();

	std::vector<sf::Sprite> getLives();
	void Update();

private:
	int size_X;
	int size_Y;
	sf::Clock* clock;
	sf::Sprite penguin;
	
	sf::Texture iceCreamTex;
	std::vector<sf::Sprite> lives;

	Zooki* zooki;

	void setLives();
};

