#include "Hud.h"


Hud::Hud()
{
}

Hud::Hud(sf::Clock* time, Zooki* zooki_ptr, std::vector<Tile> *tiles)
{
	zooki = zooki_ptr;
	clock = time;

	iceCreamTex.loadFromFile("Data/cone.png");

	iceCream.setTexture(iceCreamTex);
	iceCream.setTextureRect(sf::IntRect(0, 0, 30, 27));
	iceCream.setPosition(sf::Vector2f(100, 100));

	lives.resize(zooki_ptr->getLivesLeft());
	sf::Sprite sprite;
	
	setLives();
}


Hud::~Hud()
{
}

void Hud::Update()
{
	
	if (zooki->getLivesLeft() != lives.size())
	{
		lives.clear();
		lives.resize(zooki->getLivesLeft());
		setLives();
	}
}

std::vector<sf::Sprite> Hud::getLives()
{
	return lives;
}

void Hud::setLives()
{
	for (int i = 0; i < lives.size(); i++)
	{
		lives[i].setTexture(zooki->zooki_texture);
		lives[i].setTextureRect(sf::IntRect(32, 0, 32, 32));
		lives[i].setPosition(sf::Vector2f(i * 34, 20));
	}
}
