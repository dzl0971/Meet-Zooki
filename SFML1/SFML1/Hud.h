#pragma once
#include <SFML/Graphics.hpp>
#include "Zooki.h"

class Hud
{
public:
	Hud();
	Hud(sf::Clock* time, Zooki* zooki_ptr);
	
	~Hud();

	sf::Sprite getIceCreamSprite();
	std::vector<sf::Sprite> getLives();
	sf::Text getLivesText();
	sf::Text getTimeText();
	sf::Text getIceCreamText();



	void Update();

private:
	int conesCollected;
	sf::Clock* clock;
	sf::Font font;
	sf::Text livesText;
	sf::Text timeText;
	sf::Text iceCreamCountText;
	
	sf::Sprite penguin;
	sf::Sprite iceCream;
	sf::Texture iceCreamTex;


	std::vector<sf::Sprite> lives;

	Zooki* zooki;

	void setLives();
};

