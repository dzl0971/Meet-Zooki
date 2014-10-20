#include "Igloo.h"

Igloo::Igloo()
{

	size_x = 30;
	size_y = 30;
	pos_x = 685;
	pos_y = 485;

	iglooTexture.loadFromFile("igloo.png");
	iglooSprite.setTexture(iglooTexture);
	iglooSprite.setPosition(sf::Vector2f(pos_x, pos_y));
	iglooSprite.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));
}



void Igloo::Update()
{
	iglooSprite.setPosition(sf::Vector2f(pos_x, pos_y));
}


Igloo::~Igloo()
{

}
