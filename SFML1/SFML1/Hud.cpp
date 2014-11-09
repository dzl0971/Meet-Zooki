#include "Hud.h"


Hud::Hud()
{
}

Hud::Hud(sf::Clock* time, Zooki* zooki_ptr)
{
	zooki = zooki_ptr;
	clock = time;
	conesCollected = zooki_ptr->conesCollected;

	font.loadFromFile("Data/arial.ttf");
	
	livesText.setFont(font);
	livesText.setString("Lives:");
	livesText.setColor(sf::Color::Black);
	livesText.setCharacterSize(20);
	livesText.setPosition(sf::Vector2f(20, 20));

	

	iceCreamTex.loadFromFile("Data/cone.png");

	iceCream.setTexture(iceCreamTex);
	iceCream.setTextureRect(sf::IntRect(0, 0, 30, 27));
	iceCream.setPosition(sf::Vector2f(1100, 20));

	iceCreamCountText.setFont(font);
	iceCreamCountText.setString("x " + std::to_string(zooki_ptr->conesCollected));
	iceCreamCountText.setColor(sf::Color::Black);
	iceCreamCountText.setCharacterSize(20);
	iceCreamCountText.setPosition(sf::Vector2f(1128, 20));

	timeText.setFont(font);
	timeText.setString("Time Left: " + std::to_string(time->getElapsedTime().asSeconds()));
	timeText.setColor(sf::Color::Black);
	timeText.setCharacterSize(20);
	timeText.setPosition(sf::Vector2f(560, 20));

	lives.resize(zooki_ptr->getLivesLeft());
	sf::Sprite sprite;
	
	setLives();
}


Hud::~Hud()
{
}

sf::Sprite Hud::getIceCreamSprite()
{
	return iceCream;
}

std::vector<sf::Sprite> Hud::getLives()
{
	return lives;
}

sf::Text Hud::getLivesText()
{
	return livesText;
}
sf::Text Hud::getTimeText()
{
	return timeText;
}
sf::Text Hud::getIceCreamText()
{
	return iceCreamCountText;
}

void Hud::Update()
{

	if (zooki->getLivesLeft() != lives.size())
	{
		lives.clear();
		lives.resize(zooki->getLivesLeft());
		setLives();
	}

	if (zooki->conesCollected > conesCollected)
	{
		conesCollected = zooki->conesCollected;
		iceCreamCountText.setString("x " + std::to_string(zooki->conesCollected));
	}

	timeText.setString("Time Left: " + std::to_string(clock->getElapsedTime().asSeconds()));
}

void Hud::setLives()
{
	for (int i = 0; i < lives.size(); i++)
	{
		lives[i].setTexture(zooki->zooki_texture);
		lives[i].setTextureRect(sf::IntRect(32, 0, 32, 32));
		lives[i].setPosition(sf::Vector2f((i * 34) + 80, 10));
	}
}
